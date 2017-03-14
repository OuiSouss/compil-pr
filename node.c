#include <stdarg.h>
#include <stdlib.h>
#include "node.h"

NODE*    constant(int value)
{
    NODE* node_ptr = malloc(sizeof(*node_ptr));
    node_ptr->type = cst;
    node_ptr->cst.value = value;
    return node_ptr;
}

NODE*    id(char* value)
{
    NODE* node_ptr = malloc(sizeof(*node_ptr));
    node_ptr->type = ident;
    node_ptr->id.value = value;
    return node_ptr;
}

NODE*    operand(int op_type, int nargs, ...)
{
    va_list ap;
    NODE* ptr = malloc(sizeof(*ptr));
    ptr->type = opr;
    OP* oper = &(ptr->opr);
    oper->op = opr;
    oper->nargs = nargs;
    oper->operands = malloc(sizeof(*(oper->operands)) * (nargs + 1));
    va_start(ap, nargs);
    for (int i = 0; i < nargs; ++i)
    {
        oper->operands[i] = va_arg(ap, NODE*);
    } va_end(ap);
    oper->operands[nargs] = NULL;
    return ptr;
}