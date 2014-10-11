/*
 * Author : yangzongze
 * Date : 2014/03/26
 *
 */

#ifndef PARSE_COMPUTE_H__
#define PARSE_COMPUTE_H__

#include "formula_struct.h"

F_NODE *parse(char *str);
real compute(F_NODE *formula, SYM_PAIR sym_value_map[], int sym_num);
int free_node(F_NODE* formula);

#endif
