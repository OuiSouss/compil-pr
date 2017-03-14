%{
#include "node.h"
#include "bilquad.h"
#include "environ.h"
#include "rho.h"

#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyerror(char* s);
 extern int evalexpr(ENV *environ, NODE nd);
%}
%union {
    char* id;
    int val;
    NODE nd;
}

%token <id> V
%token <val> I
%token Af Sk Se If Th El Wh Do Pl Mo Mu Lp Rp
%left Se
%nonassoc Th
%nonassoc El
%nonassoc Do
%type <nd> E T F
%type <nd> C

%%

S:      C           { ENV e = Envalloc(); evalexpr(&e,$1); }

E:      E Pl T      { $$ = operand(Pl, 2, $1, $3); }
        | E Mo T    { $$ = operand(Mo, 2, $1, $3); }
        | T         { $$ = $1; };

T:      T Mu F      { $$ = operand(Mu, 2, $1, $3); }
        | F         { $$ = $1; };

F:      Lp E Rp     { $$ = $2; }
        | I         { $$ = constant($1); }
        | V         { $$ = id($1); };

C:      V Af E              { $$ = operand(Af, 2, $1, $3);  }
        | Sk                { $$ = operand(Sk, 0); }
        | Lp C Rp           { $$ = $2; }
        | If E Th C El C    { $$ = operand(If, 3, $2, $4, $6); }
        | Wh E Do C         { $$ = operand(Wh, 2, $2, $4); }
        | C Se C            { $$ = operand(Se, 2, $1, $3);};

%%
int main(int ac, char** av)
{
    yyparse();
    return 0;
}
