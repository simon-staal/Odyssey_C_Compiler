%option noyywrap

%{
// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include "parser.tab.hpp"
%}

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?(D)+
FS			(f|F|l|L)
IS			(u|U|l|L)*

%%

int     { return INT; }
return  { return RETURN; }

[0-9]+  { yylval.number=stol(yytext); return CONSTANT; }
[A-Za-z_]+([A-Za-z_0-9])*  { yylval.string=new std::string(yytext); return IDENTIFIER}

[ \t\r\n] { ; }

%%

void yyerror (char const *s)
{
  fprintf(stderr, "Lexing error: %s\n", s);
  exit(1);
}
