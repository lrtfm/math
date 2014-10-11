/*
 *
 * parse_formula.h
 *
 * This will be the interface of this model.
 *
 * CTRL-R %  当前文件名称
 */

#ifndef PARSE_FORMULA_H__
#define PARSE_FORMULA_H__

#define MAX_CHILD_NODE 4
#define MAX_SYMBOL_LEN 16

typedef int NODE_TYPE;
typedef double real;

typedef struct formula_node  F_NODE;
typedef struct symbol_pair SYM_PAIR;
typedef real (*math_function)(int num, real* para_list);

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

F_NODE *parse(char *str);
real compute(F_NODE *formula, SYM_PAIR sym_value_map[], int sym_num);
int free_node(F_NODE* formula);

#endif
