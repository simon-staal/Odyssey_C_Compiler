%option noyywrap

%{
// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include "parser.tab.hpp"
%}

%%
[(]     { return T_LBRACKET; }
[)]     { return T_RBRACKET; }
[{]     { return T_LBRACE; }
[}]     { return T_RBRACE; }
[;]     { return T_SEMICOLON; }

int     { return T_INT; }
return  { return T_RETURN; }

[0-9]+  { yylval.number=stol(yytext); return T_INTLITERAL; }
([A-Za-z]|_)+([A-Za-z]|_|[0-9])*  { yylval.string=new std::string(yytext); return T_IDENTIFIER}
