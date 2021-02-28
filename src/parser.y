%code requires{
  #include "ast.hpp"

  #include <cassert>

  extern const TreePtr *g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  const TreePtr tree;
  int32_t number;
  std::string *string;
}

%token T_LBRACKET T_RBRACKET T_LBRACE T_RBRACE
%token T_SEMICOLON
%token T_INT T_RETURN
%token T_INTLITERAL T_IDENTIFIER

%type <tree> FUNCTION
%type <number> T_INTLITERAL
%type <string> T_IDENTIFIER

%start ROOT

%%

ROOT : PROGRAM { g_root = $1; }

PROGRAM : FUNCTION { $$ = $1; }

FUNCTION : TYPE T_IDENTIFIER T_LBRACKET T_RBRACKET CONTENTS
