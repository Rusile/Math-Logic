%{
#include "ast.h"
#include "bison/gen/Expression.tab.h"
%}

%option outfile="lex.c" header-file="lex.h"

white [ \t]+
digit [0-9]
letter [A-Z`'’]
symbol {letter}({letter}|{digit})*

%%
{symbol} {
    yylval.name = yytext;
    return NAME;
}
"&"  return AND;
"|"  return OR;
"->" return IMP;
"!"  return NEG;
"("  return LEFT;
")"  return RIGHT;
"\n" return END;
%%