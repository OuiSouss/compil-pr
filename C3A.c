#include "environ.h"
#include "node.h"
#include "iimp.tab.h"
#include <stdlib.h>
#include <stdio.h>

#define St 300

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
        case (St) :
            return ("St");
        default :
            return NULL;
    }
}

static int eval_op(ENV* e, NODE nd);

static int currentState()
{
    static int state = 0;
    return state++;
}

static void ecrire_C3A(int current, char* opstr, char* arg1, char* arg2, char* res)
{
    fprintf(stdout, "ET%-8d:%-6s:%-10s:%-10s:%-10s\n", current, opstr, arg1?arg1:"", arg2?arg2:"", res?res:"");
}

static int eval_node(ENV* e, NODE nd)
{
    if (!nd)
        return 0;
    char buffer[4][20];
    switch (nd->type)
    {
        case cstTYPE :
        {
            int current = currentState();
            snprintf(buffer[0], 20, "%d", nd->cst.value);
            snprintf(buffer[1], 20, "CT%d", current);
            ecrire_C3A(currentState(), "Afc", buffer[0], NULL, buffer[1]);
            char* value = malloc(sizeof(*value) * 11);
            snprintf(value, 10, "%-10d", nd->cst.value);
            initenv(e, buffer[1]);
            snprintf(value, 10, "CT%d", current);
            nd->id.value = value;
            return nd->cst.value;
        }
        case idTYPE :
        {
            int current = currentState();
            snprintf(buffer[0], 20, "CT%s", current);
            ecrire_C3A(current, "Af", buffer[0], nd->id.value, NULL);
            return 0;
        }
        case opTYPE :
            return eval_op(e, nd);
    }
}

static int eval_Mu(ENV* e, NODE nd)
{
    int lval = eval_node(e, nd->opr.operands[0]);
    int rval = eval_node(e, nd->opr.operands[1]);
    return lval * rval;
}

static int eval_Mo(ENV* e, NODE nd)
{
    int lval = eval_node(e, nd->opr.operands[0]);
    int rval = eval_node(e, nd->opr.operands[1]);
    return lval - rval;
}

static int eval_Pl(ENV* e, NODE nd)
{
    int lval = eval_node(e, nd->opr.operands[0]);
    int rval = eval_node(e, nd->opr.operands[1]);
    return lval + rval;
}

static int eval_Af(ENV* e, NODE nd)
{
    int current = currentState();
    initenv(e, nd->opr.operands[0]->id.value);
    int rval = affect(*e, nd->opr.operands[0]->id.value, eval_node(e, nd->opr.operands[1]));
    ecrire_C3A(current, opstr(Af), nd->opr.operands[0]->id.value, nd->opr.operands[1]->id.value, NULL);
    return rval;
}

static int eval_If(ENV* e, NODE nd)
{
    if (eval_node(e, nd->opr.operands[0]))
    {
        eval_node(e, nd->opr.operands[1]);
    } else
    {
        eval_node(e, nd->opr.operands[2]);
    }
    return 0;
}

static int eval_Wh(ENV* e, NODE nd)
{
    while (eval_node(e, nd->opr.operands[0]))
    {
        eval_node(e, nd->opr.operands[1]);
    }
    return 0;
}

static int eval_Se(ENV* e, NODE nd)
{
    eval_node(e, nd->opr.operands[0]);
    return eval_node(e, nd->opr.operands[1]);
}

static int eval_Sk(ENV* e, NODE nd)
{
    int current = currentState();
    ecrire_C3A(current, opstr(Sk), NULL, NULL, NULL);
    return 0;
}

static int eval_op(ENV* e, NODE nd)
{
    switch (nd->opr.op)
    {
        case Se :
            return eval_Se(e, nd);
        case Wh :
            return eval_Wh(e, nd);
        case If :
            return eval_If(e, nd);
        case Af :
            return eval_Af(e, nd);
        case Pl :
            return eval_Pl(e, nd);
        case Mo :
            return eval_Mo(e, nd);
        case Mu :
            return eval_Mu(e, nd);
        case Sk :
            return eval_Sk(e, nd);
    }
}

static int eval_St()
{
    int current = currentState();
    ecrire_C3A(current, opstr(St), NULL, NULL, NULL);
}
int eval_C3A(ENV* e, NODE nd)
{
    int res = eval_node(e, nd);
    eval_St();
    return res;
}
