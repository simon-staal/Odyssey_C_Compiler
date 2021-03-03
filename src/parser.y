%code requires{
  #include "ast.hpp"

  #include <cassert>

  extern const ProgramPtr g_root; // A way of getting the AST out
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
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%type <expr> primary_expression postfix_expression unary_expression cast_expression
%type <expr> multiplicative_expression additive_expression shift_expression
%type <expr> relational_expression equality_expression and_expression
%type <expr> exclusive_or_expression inclusive_or_expression logical_and_expression
%type <expr> logical_or_expression conditional_expression assignment_expression
%type <expr> expression constant_expression

%type <expr> declaration init_declarator
%type <expr> declaration_specifiers storage_class_specifier type_specifier type_qualifier
%type <expr> struct_or_union_specifier struct_or_union struct_declaration
%type <expr> specifier_qualifier_list struct_declarator declarator
%type <expr> enum_specifier enumerator direct_declarator pointer

%type <expr> parameter_declaration type_name abstract_declarator direct_abstract_declarator
%type <expr> initializer statement labeled_statement compound_statement
%type <expr> expression_statement selection_statement iteration_statement
%type <expr> jump_statement translation_unit external_declaration function_definition

%type <exprSeq> argument_expression_list init_declarator_list struct_declaration_list
%type <exprSeq> specifier_qualifier_list struct_declarator_list
%type <exprSeq> enumerator_list type_qualifier_list parameter_type_list parameter_list
%type <exprSeq> identifier_list initializer_list declaration_list statement_list

%type <number> CONSTANT
%type <string> IDENTIFIER

TODO: Unsure (probably expr):
unary_operator assignment_operator

%start translation_unit

%%

primary_expression
    : IDENTIFIER { $$ = new Identifier(*$1); }
	| CONSTANT { $$ = new Constant($1); }
	| '(' expression ')' { $$ = $2; }
	;

postfix_expression
	: primary_expression { $$ = $1; }
	| postfix_expression '[' expression ']' { std::cerr << "Unsuported" << std::endl; }
	| postfix_expression '(' ')' { std::cerr << "Unsuported" << std::endl; }
	| postfix_expression '(' argument_expression_list ')' { std::cerr << "Unsuported" << std::endl; }
	| postfix_expression '.' IDENTIFIER { std::cerr << "Unsuported" << std::endl; }
	| postfix_expression PTR_OP IDENTIFIER { std::cerr << "Unsuported" << std::endl; }
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
	| unary_operator cast_expression { std::cerr << "Unsuported" << std::endl; }
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

cast_expression
	: unary_expression { $$ = $1; }
	| '(' type_name ')' cast_expression { std::cerr << "Unsuported" << std::endl; }
	;

multiplicative_expression
	: cast_expression { $$ = $1; }
	| multiplicative_expression '*' cast_expression { std::cerr << "Unsuported" << std::endl; }
	| multiplicative_expression '/' cast_expression { std::cerr << "Unsuported" << std::endl; }
	| multiplicative_expression '%' cast_expression { std::cerr << "Unsuported" << std::endl; }
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
	| expression ',' assignment_expression { std::cerr << "Unsuported" << std::endl; }
	;

constant_expression
	: conditional_expression { $$ = $1; }
	;

declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';'
	;

declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier
	| type_specifier declaration_specifiers
	| type_qualifier
	| type_qualifier declaration_specifiers
	;

init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: declarator
	| declarator '=' initializer
	;

storage_class_specifier
	: TYPEDEF
	| EXTERN
	| STATIC
	| AUTO
	| REGISTER
	;

type_specifier
	: VOID
	| CHAR
	| SHORT
	| INT
	| LONG
	| FLOAT
	| DOUBLE
	| SIGNED
	| UNSIGNED
	| struct_or_union_specifier
	| enum_specifier
	| TYPE_NAME
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}'
	| struct_or_union '{' struct_declaration_list '}'
	| struct_or_union IDENTIFIER
	;

struct_or_union
	: STRUCT
	| UNION
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
	| type_qualifier specifier_qualifier_list
	| type_qualifier
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

type_qualifier
	: CONST
	| VOLATILE
	;

declarator
	: pointer direct_declarator
	| direct_declarator
	;

direct_declarator
	: IDENTIFIER
	| '(' declarator ')'
	| direct_declarator '[' constant_expression ']'
	| direct_declarator '[' ']'
	| direct_declarator '(' parameter_type_list ')'
	| direct_declarator '(' identifier_list ')'
	| direct_declarator '(' ')'
	;

pointer
	: '*'
	| '*' type_qualifier_list
	| '*' pointer
	| '*' type_qualifier_list pointer
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;


parameter_type_list
	: parameter_list
	| parameter_list ',' ELLIPSIS
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
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
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
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: IDENTIFIER ':' statement
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

compound_statement
	: '{' '}'
	| '{' statement_list '}'
	| '{' declaration_list '}'
	| '{' declaration_list statement_list '}'
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

statement_list
	: statement
	| statement_list statement
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
	: GOTO IDENTIFIER ';'
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';' { $$ = new Return($2); }
	;

translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement
	| declarator declaration_list compound_statement
	| declarator compound_statement
	;

%%

ProgramPtr g_root;

ProgramPtr parseAST()
{
  g_root = 0;
  yyparse();
  return g_root;
}
