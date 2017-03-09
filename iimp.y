%{
#include "bilquad.h"
#include <stdio.h>
#include <stdlib.h>
extern int yylex();
extern int yyerror(char* s);
%}
%union {
    struct cellquad storage;
}
%token Af Sk Se If Th El Wh Do Pl Mo Mu Lp Rp I V

%%
C:      V Af E              { printf("V Af E => '%s' '%s' '%s'\n", $<storage>1.ARG1, $<storage>2.ETIQ, $<storage>3.ARG2); }
        | Sk                { }
        | Lp C Rp           { }
        | If E Th C El C    {  }
        | Wh E Do C         { }
        | C Se C            { };

E:      E Pl T      { }
        | E Mo T    {  }
        | T         { };

T:      T Mu F      {  }
        | F         { };

F:      Lp E Rp     {  }
        | I         {  }
        | V         {  };

%%
int main(int ac, char** av)
{
    yyparse();
    return 0;
}
