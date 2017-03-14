%{
#include "node.h"
#include "bilquad.h"
#include "environ.h"
#include "rho.h"

#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyerror(char* s);

%}
%union {
    char* id;
    int val;
    struct s_node nd;
}

%token <id> V
%token <id> I
%token Af Sk Se If Th El Wh Do Pl Mo Mu Lp Rp
%left Se
%nonassoc Th
%nonassoc El
%nonassoc Do
%type <nd> E T F
%type <nd> C

%%

S:      C           {  }

E:      E Pl T      {  }
        | E Mo T    {  }
        | T         { $$ = $1; };

T:      T Mu F      {  }
        | F         { $$ = $1; };

F:      Lp E Rp     { $$ = $2; }
        | I         { }
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
