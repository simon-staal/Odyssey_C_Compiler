%code requires{
  // A lot of this parser is based off the ANSI C Yacc grammar
  // https://www.lysator.liu.se/c/ANSI-C-grammar-y.html
  #include "ast.hpp"
  #include "parser_list.hpp" // Contains list management functions

  extern Node *g_root; // A way of getting the AST out
  extern FILE *yyin;

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  NodePtr expr;
  ListPtr exprList;
  int number;
  double numberFloat;
  std::string *string;
  yytokentype token;
}

%token IDENTIFIER INT_LITERAL FLOAT_LITERAL CHAR_LITERAL SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN

%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR INT SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR CONTINUE BREAK RETURN

%type <expr> primary_expression postfix_expression unary_expression
%type <expr> multiplicative_expression additive_expression shift_expression
%type <expr> relational_expression equality_expression and_expression
%type <expr> exclusive_or_expression inclusive_or_expression logical_and_expression
%type <expr> logical_or_expression conditional_expression assignment_expression
%type <expr> expression constant_expression

%type <expr> declaration init_declarator
%type <expr> declaration_specifiers type_specifier
%type <expr> struct_specifier struct_declaration
%type <expr> struct_declarator declarator
%type <expr> enum_specifier enumerator direct_declarator pointer

%type <expr> parameter_declaration type_name abstract_declarator direct_abstract_declarator
%type <expr> initializer statement labeled_statement compound_statement
%type <expr> expression_statement selection_statement iteration_statement
%type <expr> jump_statement external_declaration function_definition

%type <exprList> translation_unit struct_declaration_list argument_expression_list
%type <exprList> specifier_qualifier_list struct_declarator_list
%type <exprList> enumerator_list parameter_list
%type <exprList> identifier_list initializer_list declaration_list statement_list

%type <number> INT_LITERAL CHAR_LITERAL
%type <numberFloat> FLOAT_LITERAL
%type <string> IDENTIFIER


%start ROOT

%%
/* Extracts AST */
ROOT : translation_unit { g_root = new Root(new GlobalScope(*$1)); delete $1; }

/* Top level entity */
translation_unit
	: external_declaration { $$ = initList($1); }
	| translation_unit external_declaration { $$ = concatList($1, $2); }
	;

/* Global declaration */
external_declaration
	: function_definition { $$ = $1; }
	| declaration { $$ = $1; }
	;

/* Function definition (duh) */
function_definition
	: declaration_specifiers declarator compound_statement { $$ = new FunctionDefinition(new Declaration($1, $2), $3); }
	| declarator compound_statement { std::cerr << "Function with no type?, maybe calling void function globally?" << std::endl; }
	;

/* Name of something (variable, function, array) */
declarator
	: pointer direct_declarator { $$ = new PointerDeclarator($2); }
	| direct_declarator { $$ = $1; }
	;

/* Bunch of different types of names, see declarator */
direct_declarator
	: IDENTIFIER { $$ = new Declarator(*$1); delete $1; };
	| '(' declarator ')' { $$ = $2; }
	| direct_declarator '[' constant_expression ']' { $$ = new ArrayDeclarator($1, $3); }
  	| direct_declarator '[' ']' { $$ = new ArrayDeclarator($1); }
	| direct_declarator '(' parameter_list ')' { $$ = new FunctionDeclarator($1, *$3); delete $3; }
	| direct_declarator '(' identifier_list ')' { $$ = new FunctionDeclarator($1, *$3); delete $3; }
	| direct_declarator '(' ')' { $$ = new FunctionDeclarator($1); }
	;

/* Function input parameters */
parameter_list
	: parameter_declaration { $$ = initList($1); }
	| parameter_list ',' parameter_declaration { $$ = concatList($1, $3); }
	;

parameter_declaration
	: declaration_specifiers declarator { $$ = new Declaration($1, $2); }
	| declaration_specifiers abstract_declarator { $$ = new Declaration($1, $2); }
	| declaration_specifiers { std::cerr << "No clue what this is meant to be" << std::endl; }
	;

declaration
	: declaration_specifiers ';' { $$ = $1; }
	| declaration_specifiers init_declarator ';' { $$ = new Declaration($1, $2); }
	;

/* Type of something (+ typedef) */
declaration_specifiers
  : TYPEDEF { $$ = new TypeDef(new PrimitiveType(Specifier::_void)); /*idk when we'd use this*/ }
	| TYPEDEF declaration_specifiers { $$ = new TypeDef($2); }
	| type_specifier { $$ = $1; }
	| type_specifier declaration_specifiers { std::cerr << "I don't think we need this either (function ptrs?)" << std::endl; }
	;

type_specifier
	: VOID { $$ = new PrimitiveType(Specifier::_void); }
	| CHAR { $$ = new PrimitiveType(Specifier::_char); }
	| INT { $$ = new PrimitiveType(Specifier::_int); }
	| FLOAT { $$ = new PrimitiveType(Specifier::_float); }
	| DOUBLE { $$ = new PrimitiveType(Specifier::_double); }
	| UNSIGNED { $$ = new PrimitiveType(Specifier::_unsigned); }
	| struct_specifier { std::cerr << "Unsupported" << std::endl; }
	| enum_specifier { $$ = $1; }
	;

init_declarator
	: declarator { $$ = $1; }
	| declarator '=' initializer { $$ = new InitDeclarator($1, $3); }
	;

initializer
	: assignment_expression { $$ = $1; }
	| '{' initializer_list '}' { $$ = new ArrayInit(*$2); }
	| '{' initializer_list ',' '}' { $$ = new ArrayInit(*$2); }
	;

initializer_list
	: initializer { $$ = initList($1); }
	| initializer_list ',' initializer { $$ = concatList($1, $3); }
	;

abstract_declarator
	: pointer {/* $$ = new Pointer($1); */}
	| direct_abstract_declarator
	| pointer direct_abstract_declarator {/* $$ = new Pointer($1); */}
	;

direct_abstract_declarator
	: '(' abstract_declarator ')' { $$ = $2; }
	| '[' ']' { std::cerr << "Unsupported" << std::endl; }
	| '[' constant_expression ']' { std::cerr << "Unsupported" << std::endl; }
	| direct_abstract_declarator '[' ']' { std::cerr << "Unsupported" << std::endl; }
	| direct_abstract_declarator '[' constant_expression ']' { std::cerr << "Unsupported" << std::endl; }
	| '(' ')' { std::cerr << "Unsupported" << std::endl; }
	| '(' parameter_list ')' { std::cerr << "Unsupported" << std::endl; }
	| direct_abstract_declarator '(' ')' { std::cerr << "Unsupported" << std::endl; }
	| direct_abstract_declarator '(' parameter_list ')' { std::cerr << "Unsupported" << std::endl; }
	;

declaration_list
	: declaration { $$ = initList($1); }
	| declaration_list declaration { $$ = concatList($1, $2); }
	;

/* Shit a function contains, (scope) */
compound_statement
	: '{' '}' { $$ = new Scope(); }
	| '{' statement_list '}' { $$ = new Scope(*$2); delete $2; }
	| '{' declaration_list '}' { $$ = new Scope(*$2); delete $2; }
	| '{' declaration_list statement_list '}' { $$ = new Scope(*$2, *$3); delete $2; delete $3; }
	;

statement_list
  : statement { $$ = initList($1); }
	| statement_list statement { $$ = concatList($1, $2); }
	;

statement
	: labeled_statement { $$ = $1; }
	| compound_statement { $$ = $1; }
	| expression_statement { $$ = $1; }
	| selection_statement	{ $$ = $1; }
	| iteration_statement { $$ = $1; }
	| jump_statement { $$ = $1; }
	;

/* Case statements */
labeled_statement
	: IDENTIFIER ':' statement { $$ = new Case(new Identifier(*$1), $3); delete $1; }
	| CASE constant_expression ':' statement { $$ = new Case($2, $4); }
	| DEFAULT ':' statement { $$ = new Default($3); }
	;

/* Standard stuff */
expression_statement
	: ';' { std::cerr << "Do nothing ig?" << std::endl; }
	| expression ';' { $$ = $1; }
	;

/* if else switch */
selection_statement
	: IF '(' expression ')' statement { $$ = new IfElse($3, $5); }
	| IF '(' expression ')' statement ELSE statement { $$ = new IfElse($3, $5, $7); }
	| SWITCH '(' expression ')' statement { $$ = new Switch($3, $5); }
	;
/* we can solve the shift/reduce conflict by writing '%right "then" "else"' to give right asssociasivity to else
 (shift) tho it already does this and may cause further ambiguities */

/* loops */
iteration_statement
	: WHILE '(' expression ')' statement { $$ = new While($3, $5); }
	| DO statement WHILE '(' expression ')' ';' { ; }
	| FOR '(' expression_statement expression_statement ')' statement { $$ = new For($3, $4, new EmptyNode(), $6); }
	| FOR '(' expression_statement expression_statement expression ')' statement { $$ = new For($3, $4, $5, $7); }
	;

/* Continue / break / return */
jump_statement
	: CONTINUE ';' { $$ = new Continue(); }
	| BREAK ';' { $$ = new Break(); }
	| RETURN ';' { $$ = new Return(new Integer()); }
	| RETURN expression ';' { $$ = new Return($2); }
	;

primary_expression
  	: IDENTIFIER { $$ = new Identifier(*$1); delete $1; }
	| INT_LITERAL { $$ = new Integer($1); }
  	| FLOAT_LITERAL { $$ = new Float($1); }
	| CHAR_LITERAL { $$ = new Integer($1); /*Should use char once it's implemented*/ }
	| '(' expression ')' { $$ = $2; }
	;

postfix_expression
	: primary_expression { $$ = $1; }
	| postfix_expression '[' expression ']' { $$ = new ArrayIndex($1, $3); }
	| postfix_expression '(' ')' { $$ = new FunctionCall($1); }
	| postfix_expression '(' argument_expression_list ')' { $$ = new FunctionCall($1, *$3); delete $3; }
	| postfix_expression '.' IDENTIFIER { std::cerr << "member variable access" << std::endl; }
	| postfix_expression PTR_OP IDENTIFIER { std::cerr << "->" << std::endl; }
  | postfix_expression INC_OP { $$ = new UnaryPostInc($1); /* need post inc + pre inc classes tho*/ }
| postfix_expression DEC_OP { $$ = new UnaryPostDec($1); /*Shouldn't have changed the file name can implement this pretty easy*/ }
	;

argument_expression_list
  : assignment_expression { $$ = initList($1); }
  | argument_expression_list ',' assignment_expression { $$ = concatList($1, $3); }

unary_expression
	: postfix_expression { $$ = $1; }
	| INC_OP unary_expression { $$ = new UnaryInc($2); }
	| DEC_OP unary_expression { $$ = new UnaryDec($2); }
	| '&' unary_expression { $$ = new UnaryAdr($2); }
	| '*' unary_expression { $$ = new UnaryPtr($2); }
  	| '+' unary_expression { $$ = $2; /*I'm sorry kai it had to be done */ }
	| '-' unary_expression { $$ = new UnarySub($2); }
	| '~' unary_expression { $$ = new UnaryBWNOT($2); }
	| '!' unary_expression { $$ = new UnaryNOT($2); }
	| SIZEOF unary_expression { $$ = new SizeOf($2); }
	| SIZEOF '(' type_name ')' { $$ = new SizeOf($3); }
	;

multiplicative_expression
	: unary_expression { $$ = $1; }
	| multiplicative_expression '*' unary_expression {  $$ = new BinaryMul($1, $3);  }
	| multiplicative_expression '/' unary_expression {  $$ = new BinaryDiv($1, $3);  }
	| multiplicative_expression '%' unary_expression {  $$ = new BinaryMod($1, $3);  }
	;

additive_expression
	: multiplicative_expression { $$ = $1; }
	| additive_expression '+' multiplicative_expression { $$ = new BinaryAdd($1, $3); }
	| additive_expression '-' multiplicative_expression { $$ = new BinarySub($1, $3); }
	;

shift_expression
	: additive_expression {$$ = $1; }
	| shift_expression LEFT_OP additive_expression { $$ = new BinaryLShift($1, $3); }
	| shift_expression RIGHT_OP additive_expression { $$ = new BinaryRShift($1, $3); }
	;

relational_expression
	: shift_expression { $$ = $1; }
	| relational_expression '<' shift_expression { $$ = new BinaryLT($1, $3); }
	| relational_expression '>' shift_expression { $$ = new BinaryGT($1, $3); }
	| relational_expression LE_OP shift_expression { $$ = new BinaryLTEQ($1, $3); }
	| relational_expression GE_OP shift_expression { $$ = new BinaryGTEQ($1, $3); }
	;

equality_expression
	: relational_expression { $$ = $1; }
	| equality_expression EQ_OP relational_expression { $$ = new BinaryEQ($1, $3); }
	| equality_expression NE_OP relational_expression { $$ = new BinaryNEQ($1, $3); }
	;

and_expression
	: equality_expression { $$ = $1; }
	| and_expression '&' equality_expression { $$ = new BinaryAND($1, $3); }
	;

exclusive_or_expression
	: and_expression { $$ = $1; }
	| exclusive_or_expression '^' and_expression { $$ = new BinaryXOR($1, $3); }
	;

inclusive_or_expression
	: exclusive_or_expression { $$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression { $$ = new BinaryOR($1, $3); }
	;

logical_and_expression
	: inclusive_or_expression { $$ = $1; }
	| logical_and_expression AND_OP inclusive_or_expression { $$ = new BinaryLogAND($1, $3); }
	;

logical_or_expression
	: logical_and_expression { $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression { $$ = new BinaryLogOR($1, $3); }
	;

conditional_expression
	: logical_or_expression { $$ = $1; }
	| logical_or_expression '?' expression ':' conditional_expression { std::cerr << "Unsupported" << std::endl; }
	;

constant_expression
	: conditional_expression { $$ = $1; }
	;

assignment_expression
	: conditional_expression { $$ = $1; }
	| unary_expression '=' assignment_expression { $$ = new BinaryAssign($1, $3); }
	| unary_expression MUL_ASSIGN assignment_expression { $$ = new BinaryAssign($1, new BinaryMul($1, $3)); }
	| unary_expression DIV_ASSIGN assignment_expression { $$ = new BinaryAssign($1, new BinaryDiv($1, $3)); }
	| unary_expression MOD_ASSIGN assignment_expression { $$ = new BinaryAssign($1, new BinaryMod($1, $3)); }
	| unary_expression ADD_ASSIGN assignment_expression { $$ = new BinaryAssign($1, new BinaryAdd($1, $3)); }
	| unary_expression SUB_ASSIGN assignment_expression { $$ = new BinaryAssign($1, new BinarySub($1, $3)); }
	| unary_expression LEFT_ASSIGN assignment_expression { $$ = new BinaryAssign($1, new BinaryLShift($1, $3)); }
	| unary_expression RIGHT_ASSIGN assignment_expression { $$ = new BinaryAssign($1, new BinaryRShift($1, $3)); }
	| unary_expression AND_ASSIGN assignment_expression { $$ = new BinaryAssign($1, new BinaryAND($1, $3)); }
	| unary_expression XOR_ASSIGN assignment_expression { $$ = new BinaryAssign($1, new BinaryXOR($1, $3)); }
	| unary_expression OR_ASSIGN assignment_expression { $$ = new BinaryAssign($1, new BinaryOR($1, $3)); }
	;

expression
	: assignment_expression { $$ = $1; }
	| expression ',' assignment_expression { std::cerr << "Not assessed by spec (?)" << std::endl; }
	;

enum_specifier
	: ENUM '{' enumerator_list '}' { $$ = new EnumSpecifier("<NULL>", *$3); delete $3; }
	| ENUM IDENTIFIER '{' enumerator_list '}' { $$ = new EnumSpecifier(*$2, *$4); delete $2; delete $4; }
	| ENUM IDENTIFIER { $$ = new EnumSpecifier(*$2); delete $2; }
	;

enumerator_list
	: enumerator { $$ = initList($1); }
	| enumerator_list ',' enumerator { $$ = concatList($1, $3); }
	;

enumerator
	: IDENTIFIER { $$ = new Enumerator(*$1, NULL); delete $1; }
	| IDENTIFIER '=' constant_expression { $$ = new Enumerator(*$1, $3); delete $1; }
	;

/* Since we don't need to check types, we don't need to know how deep the pointer goes (hopefully) */
pointer
	: '*'
	| '*' pointer {}
	;

identifier_list
	: IDENTIFIER { $$ = initList(new Identifier(*$1)); delete $1; }
	| identifier_list ',' IDENTIFIER { $$ = concatList($1, new Identifier(*$3)); delete $3; }
	;

type_name
	: specifier_qualifier_list { std::cerr << "Unsupported" << std::endl; }
	| specifier_qualifier_list abstract_declarator { std::cerr << "Unsupported" << std::endl; }
	;

struct_specifier
	: STRUCT IDENTIFIER '{' struct_declaration_list '}' { std::cerr << "Unsupported" << std::endl; }
	| STRUCT '{' struct_declaration_list '}' { std::cerr << "Unsupported" << std::endl; }
	| STRUCT IDENTIFIER { std::cerr << "Unsupported" << std::endl; }
	;

struct_declaration_list
	: struct_declaration { $$ = initList($1); }
	| struct_declaration_list struct_declaration { $$ = concatList($1, $2); }
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';' { std::cerr << "Unsupported" << std::endl; }
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list { std::cerr << "Unsupported" << std::endl; }
	| type_specifier { std::cerr << "Unsupported" << std::endl; }
	;

struct_declarator_list
	: struct_declarator { $$ = initList($1); }
	| struct_declarator_list ',' struct_declarator { $$ = concatList($1, $3); }
	;

struct_declarator
	: declarator { $$ = $1; }
	| ':' constant_expression { std::cerr << "Unsupported" << std::endl; }
	| declarator ':' constant_expression { std::cerr << "Unsupported" << std::endl; }
	;

%%

Node *g_root;

Node *parseAST(std::string filename)
{
  yyin = fopen(filename.c_str(), "r");
  if(yyin == NULL){
    std::cerr << "Couldn't open input file: " << filename << std::endl;
    exit(1);
  }
  g_root = NULL;
  yyparse();
  return g_root;
}
