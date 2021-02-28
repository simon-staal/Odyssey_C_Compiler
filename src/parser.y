%code requires{
  #include "ast.hpp"

  #include <cassert>

  extern const ProgramPtr g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  const ProgramPtr program;
  int32_t number;
  std::string *string;
}

%token INT
%token CONSTANT IDENTIFIER

%token RETURN

%type <program> FUNCTION
%type <number> T_INTLITERAL
%type <string> T_IDENTIFIER

%start ROOT

%%

ROOT : PROGRAM { g_root = $1; }

PROGRAM : FUNCTION { $$ = $1; }

FUNCTION : T_INT T_IDENTIFIER '(' ')' '{' STATEMENT '}' { $$ = }

%%

const ProgramPtr g_root;

const ProgramPtr parseAST()
{
  g_root = 0;
  yyparse();
  return g_root;
}
