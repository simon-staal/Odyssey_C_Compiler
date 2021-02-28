%option noyywrap

%{
// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include "parser.tab.hpp"
%}

%%

int     { return INT; }
return  { return RETURN; }

[0-9]+  { yylval.number=stol(yytext); return CONSTANT; }
[A-Za-z_]+([A-Za-z_0-9])*  { yylval.string=new std::string(yytext); return IDENTIFIER}

%%

void yyerror (char const *s)
{
  fprintf(stderr, "Lexing error: %s\n", s);
  exit(1);
}
