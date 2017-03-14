/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   node.h
 * Author: lexi
 *
 * Created on 14 mars 2017, 17:33
 */

#ifndef NODE_H
#define NODE_H

typedef enum { cstTYPE, idTYPE, opTYPE } TYPE;

typedef struct s_cst
{
    int value;
} CST;

typedef struct s_id
{
    char* value;
} ID;

typedef struct s_op
{
    int op; // operateur
    int nargs; // nombre operandes
    struct s_node **operands; // operandes
} OP;

typedef struct s_node
{
    TYPE type; // type du noeud
    union
    {
        CST cst; // si constante
        ID id; // si identifiant
        OP opr; // si operation
    };
}* NODE;

extern NODE cst(int value);
extern NODE id(char* value);
extern NODE op(int op_type, int nargs, ...);
extern void free_node(NODE nd);


#endif /* NODE_H */

