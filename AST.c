#include "node.h"
#include "iimp.tab.h"
#include "environ.h"

#include <stdlib.h>
#include <stdio.h>

static int eval_Mu(ENV* e, NODE nd);
static int eval_Mo(ENV* e, NODE nd);
static int eval_Pl(ENV* e, NODE nd);
static int eval_Af(ENV* e, NODE nd);
static int eval_If(ENV* e, NODE nd);
static int eval_Wh(ENV* e, NODE nd);
static int eval_Se(ENV* e, NODE nd);
static int eval_op(ENV* e, NODE nd);
static int eval_node(ENV* e, NODE nd);

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
    initenv(e, nd->opr.operands[0]->id.value);
    int rval = affect(*e, nd->opr.operands[0]->id.value, eval_node(e, nd->opr.operands[1]));
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
    }
}

static int eval_node(ENV* e, NODE nd)
{
    if (!nd)
        return 0;
    switch (nd->type)
    {
        case cstTYPE :
            return nd->cst.value;
        case idTYPE :
            return valch(*e, nd->id.value);
        case opTYPE :
            return eval_op(e, nd);
    }
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

static inline void ecrire_CST(CST cst)
{ fprintf(stdout, "%d", cst.value); }

static inline void ecrire_ID(ID id)
{ fprintf(stdout, "%s", id.value); }

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

int evalexpr(ENV* environ, NODE nd)
{
    int res = eval_node(environ, nd);
    ecrire_env(*environ);
    ecrire_AST(nd);
    return res;
}
