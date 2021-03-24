%code requires{
  // A lot of this parser is based off the ANSI C Yacc grammar
  // https://www.lysator.liu.se/c/ANSI-C-grammar-y.html
  #include "ast.hpp"
  #include "parser_list.hpp"

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
  long number;
  std::string *string;
  yytokentype token;
}

%token IDENTIFIER INT_LITERAL SIZEOF
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

%type <number> INT_LITERAL
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
	| declarator compound_statement { std::cerr << "Function with no type?, not sure what this is" << std::endl; }
	;

/* Name of something (variable, function, array) */
declarator
	: pointer direct_declarator { std::cerr << "deal with pointers later" << std::endl; }
	| direct_declarator { $$ = $1; }
	;

/* Bunch of different types of names, see declarator */
direct_declarator
	: IDENTIFIER { $$ = new Declarator(*$1); delete $1; };
	| '(' declarator ')' { $$ = $2; }
	| direct_declarator '[' constant_expression ']' { $$ = new ArrayDeclarator($1, $3); /* std::cerr << "Array declarator" << std::endl;*/ }
	| direct_declarator '[' ']' { $$ = new ArrayDeclarator($1); /*std::cerr << "Array declarator, size is no. of things in {} after =" << std::endl;*/ }
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
	| declaration_specifiers { std::cerr << "?" << std::endl; }
	;

declaration
	: declaration_specifiers ';' { $$ = new Declaration($1); std::cerr << "Idk what to do with this (int;)" << std::endl; }
	| declaration_specifiers init_declarator ';' { $$ = new Declaration($1, $2); }
	;

/* Type of something (+ typedef) */
declaration_specifiers
	: TYPEDEF { std::cerr << "deal with this shit later" << std::endl; }
	| TYPEDEF declaration_specifiers { std::cerr << "Not needed afaik since we only support TYPEDEF" << std::endl; }
	| type_specifier { $$ = $1; }
	| type_specifier declaration_specifiers { std::cerr << "I don't think we need this either" << std::endl; }
	;

type_specifier
	: VOID { std::cerr << "Unsuported" << std::endl; }
	| CHAR { std::cerr << "Unsuported" << std::endl; }
	| INT { $$ = new PrimitiveType(PrimitiveType::Specifier::_int); }
	| FLOAT { std::cerr << "Unsuported" << std::endl; }
	| DOUBLE { std::cerr << "Unsuported" << std::endl; }
	| UNSIGNED { std::cerr << "Unsuported" << std::endl; }
	| struct_specifier { std::cerr << "Unsuported" << std::endl; }
	| enum_specifier { std::cerr << "Unsuported" << std::endl; }
	;

init_declarator
	: declarator { $$ = $1; }
	| declarator '=' initializer { $$ = new InitDeclarator($1, $3); }
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')' { $$ = $2; }
	| '[' ']' { std::cerr << "Unsuported" << std::endl; }
	| '[' constant_expression ']' { std::cerr << "Unsuported" << std::endl; }
	| direct_abstract_declarator '[' ']' { std::cerr << "Unsuported" << std::endl; }
	| direct_abstract_declarator '[' constant_expression ']' { std::cerr << "Unsuported" << std::endl; }
	| '(' ')' { std::cerr << "Unsuported" << std::endl; }
	| '(' parameter_list ')' { std::cerr << "Unsuported" << std::endl; }
	| direct_abstract_declarator '(' ')' { std::cerr << "Unsuported" << std::endl; }
	| direct_abstract_declarator '(' parameter_list ')' { std::cerr << "Unsuported" << std::endl; }
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
	: IDENTIFIER ':' statement { std::cerr << "Add to AST" << std::endl ; }
	| CASE constant_expression ':' statement { ; }
	| DEFAULT ':' statement { ; }
	;

/* Standard stuff */
expression_statement
	: ';' { ; }
	| expression ';' { $$ = $1; }
	;

/* if else switch */
selection_statement
	: IF '(' expression ')' statement { $$ = new IfElse($3, $5); }
	| IF '(' expression ')' statement ELSE statement { $$ = new IfElse($3, $5, $7); }
	| SWITCH '(' expression ')' statement { ; }
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
	: CONTINUE ';' { std::cerr << "Extend AST" << std::endl; }
	| BREAK ';' { std::cerr << "Extend AST" << std::endl; }
	| RETURN ';' { $$ = new Return(); }
	| RETURN expression ';' { $$ = new Return($2); }
	;

primary_expression
  : IDENTIFIER { $$ = new Identifier(*$1); }
	| INT_LITERAL { $$ = new Integer($1); }
	| '(' expression ')' { $$ = $2; }
	;

postfix_expression
	: primary_expression { $$ = $1; }
	| postfix_expression '[' expression ']' { $$ = new ArrayIndex($1, $3); }
	| postfix_expression '(' ')' { $$ = new FunctionCall($1); }
	| postfix_expression '(' argument_expression_list ')' { $$ = new FunctionCall($1, *$3); delete $3; }
	| postfix_expression '.' IDENTIFIER { std::cerr << "member variable access" << std::endl; }
	| postfix_expression PTR_OP IDENTIFIER { std::cerr << "->" << std::endl; }
	| postfix_expression INC_OP { std::cerr << "++" << std::endl; }
	| postfix_expression DEC_OP { std::cerr << "--" << std::endl; }
	;

argument_expression_list
  : assignment_expression { $$ = initList($1); }
  | argument_expression_list ',' assignment_expression { $$ = concatList($1, $3); }

unary_expression
	: postfix_expression { $$ = $1; }
	| INC_OP unary_expression { std::cerr << "pre increment" << std::endl; }
	| DEC_OP unary_expression { std::cerr << "pre decrement" << std::endl; }
	| '&' unary_expression { $$ = new UnaryAdr($2); }
	| '*' unary_expression { $$ = new UnaryPtr($2); }
	| '+' unary_expression { $$ = new UnaryAdd($2); }
	| '-' unary_expression { $$ = new UnarySub($2); }
	| '~' unary_expression { $$ = new UnaryBWNOT($2); }
	| '!' unary_expression { $$ = new UnaryNOT($2); }
	| SIZEOF unary_expression { std::cerr << "sizeof (duh)" << std::endl; }
	| SIZEOF '(' type_name ')' { std::cerr << "sizeof a primitive" << std::endl; }
	;

/*  I've effectively removed this and just moved it above leaving it here just in case tho.

	this is also from above
	| unary_operator unary_expression { std::cerr << "chaining stuff, add later ig?" << std::endl; }


unary_operator
	: '&' { std::cerr << "Unsuported" << std::endl; }
	| '*' { std::cerr << "Unsuported" << std::endl; }
	| '+' { std::cerr << "Unsuported" << std::endl; }
	| '-' { std::cerr << "Unsuported" << std::endl; }
	| '~' { std::cerr << "Unsuported" << std::endl; }
	| '!' { std::cerr << "Unsuported" << std::endl; }
	;
*/

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
	| logical_or_expression '?' expression ':' conditional_expression { std::cerr << "Unsuported" << std::endl; }
	;

assignment_expression
	: conditional_expression { $$ = $1; }
	| unary_expression '=' assignment_expression { $$ = new BinaryNormalAss($1, $3); }
	| unary_expression MUL_ASSIGN assignment_expression { $$ = new BinaryMulAss($1, $3); }
	| unary_expression DIV_ASSIGN assignment_expression { $$ = new BinaryDivAss($1, $3); }
	| unary_expression MOD_ASSIGN assignment_expression { $$ = new BinaryModAss($1, $3); }
	| unary_expression ADD_ASSIGN assignment_expression { $$ = new BinaryAddAss($1, $3); }
	| unary_expression SUB_ASSIGN assignment_expression { $$ = new BinarySubAss($1, $3); }
	| unary_expression LEFT_ASSIGN assignment_expression { $$ = new BinaryLeftAss($1, $3); }
	| unary_expression RIGHT_ASSIGN assignment_expression { $$ = new BinaryRightAss($1, $3); }
	| unary_expression AND_ASSIGN assignment_expression { $$ = new BinaryANDAss($1, $3); }
	| unary_expression XOR_ASSIGN assignment_expression { $$ = new BinaryXORAss($1, $3); }
	| unary_expression OR_ASSIGN assignment_expression { $$ = new BinaryORAss($1, $3); }
	;

/*
	| unary_expression assignment_operator assignment_expression { std::cerr << "Unsuported" << std::endl; }

assignment_operator
	: '=' { std::cerr << "Unsuported" << std::endl; }
	| MUL_ASSIGN { std::cerr << "Unsuported" << std::endl; }
	| DIV_ASSIGN { std::cerr << "Unsuported" << std::endl; }
	| MOD_ASSIGN { std::cerr << "Unsuported" << std::endl; }
	| ADD_ASSIGN { std::cerr << "Unsuported" << std::endl; }
	| SUB_ASSIGN { std::cerr << "Unsuported" << std::endl; }
	| LEFT_ASSIGN { std::cerr << "Unsuported" << std::endl; }
	| RIGHT_ASSIGN { std::cerr << "Unsuported" << std::endl; }
	| AND_ASSIGN { std::cerr << "Unsuported" << std::endl; }
	| XOR_ASSIGN { std::cerr << "Unsuported" << std::endl; }
	| OR_ASSIGN { std::cerr << "Unsuported" << std::endl; }
	;
*/

expression
	: assignment_expression { $$ = $1; }
	| expression ',' assignment_expression { std::cerr << "Not assessed by spec (?)" << std::endl; }
	;

constant_expression
	: conditional_expression { $$ = $1; }
	;

struct_specifier
	: STRUCT IDENTIFIER '{' struct_declaration_list '}' { std::cerr << "Unsuported" << std::endl; }
	| STRUCT '{' struct_declaration_list '}' { std::cerr << "Unsuported" << std::endl; }
	| STRUCT IDENTIFIER { std::cerr << "Unsuported" << std::endl; }
	;

struct_declaration_list
	: struct_declaration { $$ = initList($1); }
	| struct_declaration_list struct_declaration { $$ = concatList($1, $2); }
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';' { std::cerr << "Unsuported" << std::endl; }
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list { std::cerr << "Unsuported" << std::endl; }
	| type_specifier { std::cerr << "Unsuported" << std::endl; }
	;

struct_declarator_list
	: struct_declarator { $$ = initList($1); }
	| struct_declarator_list ',' struct_declarator { $$ = concatList($1, $3); }
	;

struct_declarator
	: declarator { $$ = $1; }
	| ':' constant_expression { std::cerr << "Unsuported" << std::endl; }
	| declarator ':' constant_expression { std::cerr << "Unsuported" << std::endl; }
	;

enum_specifier
	: ENUM '{' enumerator_list '}' { std::cerr << "Unsuported" << std::endl; }
	| ENUM IDENTIFIER '{' enumerator_list '}' { std::cerr << "Unsuported" << std::endl; }
	| ENUM IDENTIFIER { std::cerr << "Unsuported" << std::endl; }
	;

enumerator_list
	: enumerator { $$ = initList($1); }
	| enumerator_list ',' enumerator { $$ = concatList($1, $3); }
	;

enumerator
	: IDENTIFIER { std::cerr << "Unsuported" << std::endl; }
	| IDENTIFIER '=' constant_expression { std::cerr << "Unsuported" << std::endl; }
	;

pointer
	: '*' { std::cerr << "Unsuported" << std::endl; }
	| '*' pointer { std::cerr << "Unsuported" << std::endl; }
	;

identifier_list
	: IDENTIFIER { $$ = initList(new Identifier(*$1)); delete $1; }
	| identifier_list ',' IDENTIFIER { $$ = concatList($1, new Identifier(*$3)); delete $3; }
	;

type_name
	: specifier_qualifier_list { std::cerr << "Unsuported" << std::endl; }
	| specifier_qualifier_list abstract_declarator { std::cerr << "Unsuported" << std::endl; }
	;

initializer
	: assignment_expression { $$ = $1; }
	| '{' initializer_list '}' { std::cerr << "Array initialiser" << std::endl; }
	| '{' initializer_list ',' '}' { std::cerr << "whats the difference?? other than comma obv" << std::endl; }
	;

initializer_list
	: initializer { $$ = initList($1); }
	| initializer_list ',' initializer { $$ = concatList($1, $3); }
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
