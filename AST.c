#include "node.h"
#include "iimp.tab.h"
#include "environ.h"

#include <stdlib.h>
#include <stdio.h>

static char *opstr(int op)
{
    switch (op)
    {
        case (Se) :
            return ("Se");
        case (Wh) :
            return ("Wh");
        case (If) :
            return ("IfThEl");
        case (Sk) :
            return ("skip");
        case (Af) :
            return ("Af");
        case (Pl) :
            return ("+");
        case (Mo) :
            return ("-");
        case (Mu) :
            return ("*");
        default :
            return NULL;
    }
}

static inline void ecrire_ID(ID id)
{ fprintf(stdout, "%s", id.value); }

static inline void ecrire_CST(CST cst)
{ fprintf(stdout, "%d", cst.value); }

static int ecrire_OP(OP opr)
{
    fprintf(stdout, " %s", opstr(opr.op));
    for (int i = 0; i < opr.nargs; ++i)
    {
        if (opr.operands[i])
        {
            switch (opr.operands[i]->type)
            {
                case (cstTYPE) :
                {
                    fprintf(stdout, " ");
                    ecrire_CST(opr.operands[i]->cst);
                    break;
                }
                case (idTYPE) :
                {
                    fprintf(stdout, " ");
                    ecrire_ID(opr.operands[i]->id);
                    break;
                }
                case (opTYPE) :
                {
                    ecrire_OP(opr.operands[i]->opr);
                    break;
                }
            }
        }
    }
}

int ecrire_AST(NODE nd)
{
    if (!nd)
        return 0;
    fprintf(stdout, "Mp");
    ecrire_OP(nd->opr);
    fprintf(stdout, "\n");
    return 0;
}


