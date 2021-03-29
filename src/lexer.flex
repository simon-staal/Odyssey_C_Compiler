%option noyywrap

%{
// A lot of this lexer is based off the ANSI C grammar:
// https://www.lysator.liu.se/c/ANSI-C-grammar-l.html#MUL-ASSIGN
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

"break"			{ return(BREAK); }
"case"			{ return(CASE); }
"char"			{ return(CHAR); }
"continue"		{ return(CONTINUE); }
"default"		{ return(DEFAULT); }
"do"			{ return(DO); }
"double"		{ return(DOUBLE); }
"else"			{ return(ELSE); }
"enum"			{ return(ENUM); }
"float"			{ return(FLOAT); }
"for"			{ return(FOR); }
"if"			{ return(IF); }
"int"			{ return(INT); }
"return"		{ return(RETURN); }
"sizeof"		{ return(SIZEOF); }
"struct"		{ return(STRUCT); }
"switch"		{ return(SWITCH); }
"typedef"		{ return(TYPEDEF); }
"unsigned"		{ return(UNSIGNED); }
"void"			{ return(VOID); }
"volatile"		{ return(VOLATILE); }
"while"			{ return(WHILE); }

{L}({L}|{D})*  { yylval.string=new std::string(yytext); return IDENTIFIER; }

{D}+{IS}?  { yylval.number=(int)strtol(yytext, NULL, 0); return INT_LITERAL; }
0[xX]{H}+{IS}? { yylval.number=(int)strtol(yytext, NULL, 0); return INT_LITERAL; }
0{D}+{IS}? { yylval.number=(int)strtol(yytext, NULL, 0); return INT_LITERAL; }

{D}+{E}{FS}? { yylval.numberFloat=strtod(yytext, NULL); return FLOAT_LITERAL; }
{D}*"."{D}+({E})?{FS}? { yylval.numberFloat=strtod(yytext, NULL); return FLOAT_LITERAL; }
{D}+"."{D}*({E})?{FS}? { yylval.numberFloat=strtod(yytext, NULL); return FLOAT_LITERAL; }

'(\\.|[^'\\])' { // Handles char literals (treated as ints) -- This is bad if i had more time i'd make a new class
                  std::string tmp(yytext);
                  if(tmp.size() == 3) { yylval.number=(int)tmp[1]; }
                  else{
                    switch(tmp[2])
                    {
                      case '0': yylval.number=0x00;
                      break;
                      case '\'': yylval.number=0x27;
                      break;
                      case '"': yylval.number=0x22;
                      break;
                      case '?': yylval.number=0x3f;
                      break;
                      case '\\': yylval.number=0x5c;
                      break;
                      case 'a': yylval.number=0x07;
                      break;
                      case 'b': yylval.number=0x08;
                      break;
                      case 'f': yylval.number=0x0c;
                      break;
                      case 'n': yylval.number=0x0a;
                      break;
                      case 'r': yylval.number=0x0d;
                      break;
                      case 't': yylval.number=0x09;
                      break;
                      case 'v': yylval.number=0x0b;
                      break;
                      default: std::cerr << "ERROR: I'm not sure how to manage escaped char" << std::endl;
                    }
                  }
                  return CHAR_LITERAL; }

">>="			{ return(RIGHT_ASSIGN); }
"<<="			{ return(LEFT_ASSIGN); }
"+="			{ return(ADD_ASSIGN); }
"-="			{ return(SUB_ASSIGN); }
"*="			{ return(MUL_ASSIGN); }
"/="			{ return(DIV_ASSIGN); }
"%="			{ return(MOD_ASSIGN); }
"&="			{ return(AND_ASSIGN); }
"^="			{ return(XOR_ASSIGN); }
"|="			{ return(OR_ASSIGN); }
">>"			{ return(RIGHT_OP); }
"<<"			{ return(LEFT_OP); }
"++"			{ return(INC_OP); }
"--"			{ return(DEC_OP); }
"->"			{ return(PTR_OP); }
"&&"			{ return(AND_OP); }
"||"			{ return(OR_OP); }
"<="			{ return(LE_OP); }
">="			{ return(GE_OP); }
"=="			{ return(EQ_OP); }
"!="			{ return(NE_OP); }
";"			{ return(';'); }
("{"|"<%")		{ return('{'); }
("}"|"%>")		{ return('}'); }
","			{ return(','); }
":"			{ return(':'); }
"="			{ return('='); }
"("			{ return('('); }
")"			{ return(')'); }
("["|"<:")		{ return('['); }
("]"|":>")		{ return(']'); }
"."			{ return('.'); }
"&"			{ return('&'); }
"!"			{ return('!'); }
"~"			{ return('~'); }
"-"			{ return('-'); }
"+"			{ return('+'); }
"*"			{ return('*'); }
"/"			{ return('/'); }
"%"			{ return('%'); }
"<"			{ return('<'); }
">"			{ return('>'); }
"^"			{ return('^'); }
"|"			{ return('|'); }
"?"			{ return('?'); }

[ \t\r\n] { ; }

%%

void yyerror (char const *s)
{
  fprintf(stderr, "Lexing error: %s\n", s);
  exit(1);
}
