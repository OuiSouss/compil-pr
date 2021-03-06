%{
#include "node.h"
#include "environ.h"
#include "iimp.tab.h"
#include <string.h>
%}
%option noyywrap

INT         [0-9][0-9]*
VAR         [a-zA-Z][a-zA-Z0-9]*

%%
":="        { return Af; }
"skip"      { return Sk; }
";"         { return Se; }
"if"        { return If; }
"then"      { return Th; }
"else"      { return El; }
"while"     { return Wh; }
"do"        { return Do; }
"+"         { return Pl; }
"-"         { return Mo; }
"*"         { return Mu; }
"("         { return Lp; }
")"         { return Rp; }
[ \t\n]     { ; }
{INT}       {
    yylval.val = atoi(yytext);
    return I;
}
{VAR}       {
    yylval.id = strdup(yytext);
    return V;
}
""          { ; }
.           { return yytext[0]; }

%%
int yyerror(char* s)
{
    fprintf(stderr, "*** ERROR %s\n", s);
    return 0;
}
