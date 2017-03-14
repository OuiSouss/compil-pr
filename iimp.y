%{
#include "bilquad.h"
#include <stdio.h>
#include <stdlib.h>
extern int yylex();
extern int yyerror(char* s);
%}
%union {
    char* id;
    int val;
    QUAD quad;
}

%token Af Sk Se If Th El Wh Do Pl Mo Mu Lp Rp I V
%left Se
%nonassoc Th
%nonassoc El
%nonassoc Do
%start C

%type <id> V
%type <val> I E T F
%type <quad> C

%%

E:      E Pl T      { $$ = $1 + $3; }
        | E Mo T    { $$ = $1 - $3; }
        | T         {$$ = $1; };

T:      T Mu F      { $$ = $1 * $3; }
        | F         {$$ = $1; };

F:      Lp E Rp     { $$ = $2; }
        | I         { $$ = $1; }
        | V         {  };

C:      V Af E              {  }
        | Sk                {  }
        | Lp C Rp           {$$ = $2; }
        | If E Th C El C    {  }
        | Wh E Do C         { }
        | C Se C            { };

%%
int main(int ac, char** av)
{
    yyparse();
    return 0;
}
