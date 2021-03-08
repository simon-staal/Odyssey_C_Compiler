%code requires{
  #include "ast.hpp"

  #include <cassert>

  extern const NodePtr g_root; // A way of getting the AST out
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
  SeqPtr exprSeq;
  long number;
  std::string *string;
}

%token IDENTIFIER CONSTANT SIZEOF
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
%type <expr> specifier_qualifier_list struct_declarator declarator
%type <expr> enum_specifier enumerator direct_declarator pointer

%type <expr> parameter_declaration type_name abstract_declarator direct_abstract_declarator
%type <expr> initializer statement labeled_statement compound_statement
%type <expr> expression_statement selection_statement iteration_statement
%type <expr> jump_statement translation_unit external_declaration function_definition

%type <exprSeq> argument_expression_list init_declarator_list struct_declaration_list
%type <exprSeq> specifier_qualifier_list struct_declarator_list
%type <exprSeq> enumerator_list parameter_list
%type <exprSeq> identifier_list initializer_list declaration_list statement_list

%type <number> CONSTANT
%type <string> IDENTIFIER

TODO: Unsure (probably expr):
unary_operator assignment_operator

%start translation_unit

%%

// Top level entity
translation_unit
	: external_declaration { $$ = $1; }
	| translation_unit external_declaration { std::cerr << "TODO, multiple funcitons" << std::endl; }
	;

// Global declaration
external_declaration
	: function_definition { $$ = $1; }
	| declaration { $$ = $1; }
	;

// Function definition (duh)
function_definition
	: declaration_specifiers declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement {}
	| declarator declaration_list compound_statement
	| declarator compound_statement
	;

declaration
	: declaration_specifiers ';' { $$ = new Declaration($1); }
	| declaration_specifiers init_declarator_list ';'
	;

declaration_specifiers
	: TYPEDEF { std::cerr << "Make ast for this" << std::endl; }
	| TYPEDEF declaration_specifiers { std::cerr << "New type ?" << std::endl; }
	| type_specifier { $$ = $1; }
	| type_specifier declaration_specifiers
	;

primary_expression
  : IDENTIFIER { $$ = new Identifier(*$1); }
	| CONSTANT { $$ = new Constant($1); }
	| '(' expression ')' { $$ = $2; }
	;

postfix_expression
	: primary_expression { $$ = $1; }
	| postfix_expression '[' expression ']' { std::cerr << "element access (array)" << std::endl; }
	| postfix_expression '(' ')' { std::cerr << "Function call" << std::endl; }
	| postfix_expression '(' argument_expression_list ')' { std::cerr << "Function call" << std::endl; }
	| postfix_expression '.' IDENTIFIER { std::cerr << "member variable access" << std::endl; }
	| postfix_expression PTR_OP IDENTIFIER { std::cerr << "->" << std::endl; }
	| postfix_expression INC_OP { std::cerr << "Unsuported" << std::endl; }
	| postfix_expression DEC_OP { std::cerr << "Unsuported" << std::endl; }
	;

argument_expression_list
	: assignment_expression { std::cerr << "Unsuported" << std::endl; }
	| argument_expression_list ',' assignment_expression { std::cerr << "Unsuported" << std::endl; }
	;

unary_expression
	: postfix_expression { $$ = $1; }
	| INC_OP unary_expression { std::cerr << "Unsuported" << std::endl; }
	| DEC_OP unary_expression { std::cerr << "Unsuported" << std::endl; }
	| unary_operator unary_expression { std::cerr << "Unsuported" << std::endl; }
	| SIZEOF unary_expression { std::cerr << "Unsuported" << std::endl; }
	| SIZEOF '(' type_name ')' { std::cerr << "Unsuported" << std::endl; }
	;

unary_operator
	: '&' { std::cerr << "Unsuported" << std::endl; }
	| '*' { std::cerr << "Unsuported" << std::endl; }
	| '+' { std::cerr << "Unsuported" << std::endl; }
	| '-' { std::cerr << "Unsuported" << std::endl; }
	| '~' { std::cerr << "Unsuported" << std::endl; }
	| '!' { std::cerr << "Unsuported" << std::endl; }
	;

multiplicative_expression
	: unary_expression { $$ = $1; }
	| multiplicative_expression '*' unary_expression { std::cerr << "Unsuported" << std::endl; }
	| multiplicative_expression '/' unary_expression { std::cerr << "Unsuported" << std::endl; }
	| multiplicative_expression '%' unary_expression { std::cerr << "Unsuported" << std::endl; }
	;

additive_expression
	: multiplicative_expression { $$ = $1; }
	| additive_expression '+' multiplicative_expression { std::cerr << "Unsuported" << std::endl; }
	| additive_expression '-' multiplicative_expression { std::cerr << "Unsuported" << std::endl; }
	;

shift_expression
	: additive_expression {$$ = $1; }
	| shift_expression LEFT_OP additive_expression { std::cerr << "Unsuported" << std::endl; }
	| shift_expression RIGHT_OP additive_expression { std::cerr << "Unsuported" << std::endl; }
	;

relational_expression
	: shift_expression { $$ = $1; }
	| relational_expression '<' shift_expression { std::cerr << "Unsuported" << std::endl; }
	| relational_expression '>' shift_expression { std::cerr << "Unsuported" << std::endl; }
	| relational_expression LE_OP shift_expression { std::cerr << "Unsuported" << std::endl; }
	| relational_expression GE_OP shift_expression { std::cerr << "Unsuported" << std::endl; }
	;

equality_expression
	: relational_expression { $$ = $1; }
	| equality_expression EQ_OP relational_expression { std::cerr << "Unsuported" << std::endl; }
	| equality_expression NE_OP relational_expression { std::cerr << "Unsuported" << std::endl; }
	;

and_expression
	: equality_expression { $$ = $1; }
	| and_expression '&' equality_expression { std::cerr << "Unsuported" << std::endl; }
	;

exclusive_or_expression
	: and_expression { $$ = $1; }
	| exclusive_or_expression '^' and_expression { std::cerr << "Unsuported" << std::endl; }
	;

inclusive_or_expression
	: exclusive_or_expression { $$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression { std::cerr << "Unsuported" << std::endl; }
	;

logical_and_expression
	: inclusive_or_expression { $$ = $1; }
	| logical_and_expression AND_OP inclusive_or_expression { std::cerr << "Unsuported" << std::endl; }
	;

logical_or_expression
	: logical_and_expression { $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression { std::cerr << "Unsuported" << std::endl; }
	;

conditional_expression
	: logical_or_expression { $$ = $1; }
	| logical_or_expression '?' expression ':' conditional_expression { std::cerr << "Unsuported" << std::endl; }
	;

assignment_expression
	: conditional_expression { $$ = $1; }
	| unary_expression assignment_operator assignment_expression { std::cerr << "Unsuported" << std::endl; }
	;

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

expression
	: assignment_expression { $$ = $1; }
	| expression ',' assignment_expression { std::cerr << "Not assessed by spec (?)" << std::endl; }
	;

constant_expression
	: conditional_expression { $$ = $1; }
	;

init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: declarator
	| declarator '=' initializer
	;

type_specifier
	: VOID
	| CHAR
	| INT { $$ = new PrimitiveType(PrimitiveType::Specifier::_int); }
	| FLOAT
	| DOUBLE
	| UNSIGNED
	| struct_specifier
	| enum_specifier
	;

struct_specifier
	: STRUCT IDENTIFIER '{' struct_declaration_list '}'
	| STRUCT '{' struct_declaration_list '}'
	| STRUCT IDENTIFIER
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: declarator
	| ':' constant_expression
	| declarator ':' constant_expression
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator
	: IDENTIFIER
	| IDENTIFIER '=' constant_expression
	;

declarator
	: pointer direct_declarator
	| direct_declarator { $$ = $1; }
	;

direct_declarator
	: IDENTIFIER { $$ = new Identifier(*$1); }
	| '(' declarator ')' { $$ = $1; }
	| direct_declarator '[' constant_expression ']' { /* array */} 
	| direct_declarator '[' ']' { /* array */}
	| direct_declarator '(' parameter_list ')' { /*  new functionDecl() */}
	| direct_declarator '(' identifier_list ')' { $$ = new FunctionDecl($1,$3); }
	| direct_declarator '(' ')' { $$ = new FunctionDecl($1); }
	;

pointer
	: '*'
	| '*' pointer
	;

parameter_list
	: parameter_declaration
	| parameter_list ',' parameter_declaration
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_list ')'
	;

initializer
	: assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;

statement
	: labeled_statement { $$ = $1; }
	| compound_statement { $$ = $1; }
	| expression_statement { $$ = $1; }
	| selection_statement	{ $$ = $1; }
	| iteration_statement { $$ = $1; }
	| jump_statement { $$ = $1; }
	;

labeled_statement
	: IDENTIFIER ':' statement
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

compound_statement
	: '{' '}'
	| '{' statement_list '}' { $$ = $2; }
	| '{' declaration_list '}' { /* local variables */ }
	| '{' declaration_list statement_list '}' { }
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

statement_list
	: statement { $$ = $1; }
	| statement_list statement { /* append to list */ }
	;

expression_statement
	: ';'
	| expression ';'
	;

selection_statement
	: IF '(' expression ')' statement
	| IF '(' expression ')' statement ELSE statement
	| SWITCH '(' expression ')' statement
	;

iteration_statement
	: WHILE '(' expression ')' statement
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	;

jump_statement
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';' { $$ = new Return(); }
	| RETURN expression ';' { $$ = new Return($2); }
	;



%%

NodePtr g_root;

NodePtr parseAST()
{
  g_root = 0;
  yyparse();
  return g_root;
}
