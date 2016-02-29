/*
 *
 *
 */

#ifndef COLLECT_H__
#define COLLECT_H__

#include "parse_formula.h"

typedef struct str_type_info STR_TYPE_INFO;
struct str_type_info {
    int type;
    int index;
};

F_NODE *malloc_f_node();
int copy_str(char *dest, char* source, int len, int max_len);
int trim_brackets(char *str, int *start, int *len);

int get_str_type(char *str, int start, int len, STR_TYPE_INFO* type);
int get_fun_name(char *fun_name, char *str, int start, int len);
int get_para_sep_index(int *para_sep_index, char * str, int start, int len);

#endif
