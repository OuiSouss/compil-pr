%{
#include "bilquad.h"
#include <stdio.h>
#include <stdlib.h>
extern int yylex();
extern int yyerror(char* s);
%}
%union {
    struct cellquad storage;
    struct ENV* e;
}
%token Af Sk Se If Th El Wh Do Pl Mo Mu Lp Rp I V
%left Se
%nonassoc Th
%nonassoc El
%nonassoc Do
%start C

%type <storage> F E T
%type <e> C

%%

E:      E Pl T      { }
        | E Mo T    {  }
        | T         {$$ = $1; };

T:      T Mu F      {  }
        | F         {$$ = $1; };

F:      Lp E Rp     {  }
        | I         {  }
        | V         {  };

C:      V Af E              { printf("V Af E => '%s' '%s' '%s'\n", $<storage>1.ARG1, $<storage>2.ETIQ, $<storage>3.ARG2); }
        | Sk                { }
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
