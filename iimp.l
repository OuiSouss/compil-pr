%{
#include "environ.h"
#include "bilquad.h"
#include "iimp.tab.h"
#include <string.h>
int arg = 0;
%}

%option noyywrap

INT         [1-9][0-9]*
VAR         [A-Z][A-Z0-9]*

%%
":="        { yylval.storage.ETIQ = strdup(yytext); return Af; }
"Skip"      { return Sk; }
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
{INT}       {
    if (arg == 0)
    {
        arg = 1;
        yylval.storage.ARG1 = strdup(yytext);
    } else
    {
        arg = 0;
        yylval.storage.ARG2 = strdup(yytext);
    }
    return I;
}
{VAR}       {
    if (arg == 0)
    {
        arg = 1;
        yylval.storage.ARG1 = strdup(yytext);
    } else
    {
        arg = 0;
        yylval.storage.ARG2 = strdup(yytext);
    }
    return V;
}


%%
int yyerror(char* s)
{
    fprintf(stderr, "*** ERROR %s\n", s);
    return 0;
}
