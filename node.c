#include <stdarg.h>
#include <stdlib.h>
#include "node.h"

NODE    cst(int value)
{
    NODE node_ptr = malloc(sizeof(*node_ptr));
    node_ptr->type = cstTYPE;
    node_ptr->cst.value = value;
    return node_ptr;
}

NODE    id(char* value)
{
    NODE node_ptr = malloc(sizeof(*node_ptr));
    node_ptr->type = idTYPE;
    node_ptr->id.value = value;
    return node_ptr;
}

NODE    op(int op_type, int nargs, ...)
{
    va_list ap;
    NODE ptr = malloc(sizeof(*ptr));
    ptr->type = opTYPE;
    OP* oper = &(ptr->opr);
    oper->op = op_type;
    oper->nargs = nargs;
    oper->operands = malloc(sizeof(*(oper->operands)) * (nargs + 1));
    va_start(ap, nargs);
    for (int i = 0; i < nargs; ++i)
    {
        oper->operands[i] = va_arg(ap, NODE);
    } va_end(ap);
    oper->operands[nargs] = NULL;
    return ptr;
}

void free_node(NODE nd)
{
  if (nd->type == opTYPE)
    {
      for (int i = 0; i< nd->opr.nargs; ++i)
	{
	  free_node(nd->opr.operands[i]);
	}
    }
  free(nd);
}
