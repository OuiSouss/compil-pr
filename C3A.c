#include "environ.h"
#include "node.h"
#include "iimp.tab.h"
#include <stdlib.h>
#include <stdio.h>

static int get_ETIQ()
{
    static int current = 0;
    return (current++);
}

static char* ETIQAlloc()
{
    char* newETIQ = malloc(sizeof(*newETIQ) * 11);
    *newETIQ = '\0';
    return newETIQ;
}

static char* ecrire_OP_etiq()
{
    char* etiq = ETIQAlloc();
    sprintf(etiq, "ET%d", get_ETIQ());
    return etiq;
}

static inline int ecrire_ID(ID id)
{
    return fprintf(stdout, "\t:\t%s", id.value);
}

static inline int ecrire_CST()
{
    char* etiq = ETIQAlloc();
    sprintf(etiq, "CT%d", get_ETIQ());
    int nb_write = fprintf(stdout, "\t:\t%s", etiq);
    free(etiq);
    return nb_write;
}

static char *opstr(int op)
{
    switch (op)
    {
        case (Se) :
            return ("Se");
        case (Wh) :
            return ("Wh");
        case (If) :
            return ("If");
        case (Sk) :
            return ("Sk");
        case (Af) :
            return ("Af");
        case (Pl) :
            return ("Pl");
        case (Mo) :
            return ("Mo");
        case (Mu) :
            return ("Mu");
        default :
            return NULL;
    }
}

static int ecrire_OP(OP opr)
{
    char* etiq = ecrire_OP_etiq();
    for (int i = 0; i < opr.nargs; ++i)
    {
        if (opr.operands[i])
        {
            switch (opr.operands[i]->type)
            {
                case (cstTYPE) :
                    ecrire_CST();
                    break;
                case (idTYPE) :
                    ecrire_ID(opr.operands[i]->id);
                    break;
                case (opTYPE) :
                    ecrire_OP(opr.operands[i]->opr);
                    break;
            }
        }
    }
    fprintf(stdout, "%s\t:\t%s", etiq, opstr(opr.op));
    free(etiq);
    fprintf(stdout, "\n");
}

int ecrire_C3A(ENV* e, NODE nd)
{
    if (!nd)
        return 0;
    ecrire_OP(nd->opr);
    return 0;
}
