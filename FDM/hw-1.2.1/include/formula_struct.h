/*
 * Author : yangzongze
 * Date : 2014/03/26
 *
 */

#ifndef FORMULA_STRUCT_H__
#define FORMULA_STRUCT_H__

#include "const_define.h"
#include "math_wapper.h"
#include <stdlib.h>

typedef int NODE_TYPE;
typedef struct formula_node  F_NODE;

struct formula_node {
    NODE_TYPE node_type; // num, fun or symbol. 

    real num;
    math_function fun;
    char sym[MAX_SYMBOL_LEN];

    F_NODE* child[MAX_CHILD_NODE];
};

struct symbol_pair {
    char sym_name[MAX_SYMBOL_LEN];
    double sym_value;
};

typedef struct symbol_pair SYM_PAIR;

struct str_type_info {
    int type;
    int index;
};

typedef struct str_type_info STR_TYPE_INFO;

#endif
