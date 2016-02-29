/*
 * Author : yangzongze
 * Date : 2014/03/26
 *
 */

#include "parse_formula.h"

#include "const_define.h"
#include "collect.h"
#include "math_wapper.h"
#include "macro.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

F_NODE *recursion_create_node(char *str, int start, int len);
real get_sym_value(char *str, SYM_PAIR sym_value_map[], int sym_num);
F_NODE * create_zero_node();
F_NODE * normal_math_node(math_function fun, char* str, int start, int len, int index);

F_NODE *parse(char *str)
{
    int len = strlen(str);
    F_NODE * ret;
    ret = recursion_create_node(str, 0, len);
    if (ret == NULL) {
        printf("Error in create inner format of the formula:%s,\n" \
               "Please checke your input or report a bug!\n", str);
    }

    return ret;
}

real compute(F_NODE *formula, SYM_PAIR sym_value_map[], int sym_num)
{
    if (formula->node_type == NODE_TYPE_NUM) {
        return formula->num;
    }

    if (formula->node_type == NODE_TYPE_SYM) {
        return get_sym_value(formula->sym, sym_value_map, sym_num);
    }

    int i;
    real para[MAX_CHILD_NODE];
    if (formula->node_type == NODE_TYPE_FUN) {
        for (i = 0; i < MAX_CHILD_NODE; ++i) {
            if (formula->child[i] == NULL) {
                break;
            }
            para[i] = compute(formula->child[i], sym_value_map, sym_num);
        }

        return formula->fun(i, para);
    }

    // error
    return 0.0;
}

int free_node(F_NODE* formula)
{
    if (formula == NULL) return 0;

    int i = 0;
    for (i = 0; i < MAX_CHILD_NODE; ++i) {
        free_node(formula->child[i]);
    }
    return 0;
}

F_NODE *recursion_create_node(char *str, int start, int len)
{
    F_NODE *f_node = NULL;
    
    int index;
    real value;
    int trim_num;

    // adjust start len.
    trim_brackets(str, &start, &len);

    STR_TYPE_INFO type;
    if (get_str_type(str, start, len, &type) != 0) {
        // error TODO
        return NULL;
    }

    if (type.type == STR_TYPE_DIG) {
        value = atof(str + start);
        f_node = malloc_f_node();
        f_node->node_type = NODE_TYPE_NUM;
        f_node->num = value;
        return f_node;
    }

    if (type.type == STR_TYPE_SYM) {
        f_node = malloc_f_node();
        f_node->node_type = NODE_TYPE_SYM;
        copy_str(f_node->sym, str + start, len, MAX_SYMBOL_LEN);
        return f_node;
    }

    char fun_name[16];
    int para_num;
    int para_sep_index[4];
    int i;
    if (type.type == STR_TYPE_FUN) {

        get_fun_name(fun_name, str, start, len); 
        para_num = get_para_sep_index(para_sep_index, str, start, len); 
        f_node = malloc_f_node();
        f_node->node_type = NODE_TYPE_FUN;
        f_node->fun = get_fun_pointer(fun_name); 
        for ( i = 0; i < para_num; i++)
        {
            f_node->child[i] = recursion_create_node(str, start + para_sep_index[i] + 1,
                    para_sep_index[i + 1] - para_sep_index[i] - 1);
        }

        return f_node;
    }

    index = type.index;

	if (type.type == STR_TYPE_ADD) {
		return normal_math_node(add_wrapper, str, start, len, index);
	}

	if (type.type == STR_TYPE_MIN) {
		return normal_math_node(min_wrapper, str, start, len, index);
	}

	if (type.type == STR_TYPE_MUL) {
		return normal_math_node(mul_wrapper, str, start, len, index);
	}
	if (type.type == STR_TYPE_DIV){
		return normal_math_node(div_wrapper, str, start, len, index);
	}

	// error
    return f_node;
}

F_NODE * normal_math_node(math_function fun, char* str, int start, int len, int index)
{
	F_NODE* f_node;
	if (0 == index && fun == add_wrapper) {
		return recursion_create_node(str, start + 1, len - 1);
	}
    f_node = malloc_f_node();
    f_node->node_type = NODE_TYPE_FUN;
    f_node->fun = fun;
    if (0 == index && fun == min_wrapper) {
    	f_node->child[0] = create_zero_node();
    }
    else {
    	f_node->child[0] = recursion_create_node(str, start, index);
    }
    f_node->child[1] = recursion_create_node(str, start + index + 1, \
            len - index - 1);
    return f_node;
}

real get_sym_value(char *str, SYM_PAIR sym_value_map[], int sym_num)
{
    int i;
    for (i = 0; i < sym_num; ++i) {
        if (!strcmp(str, sym_value_map[i].sym_name))
        {
            return sym_value_map[i].sym_value;
        }
    }
    // error TODO
    return 0.0;
}

F_NODE * create_zero_node()
{
	F_NODE * f_node;
    f_node = malloc_f_node();\
    f_node->node_type = NODE_TYPE_NUM;\
    f_node->num = 0.0;\
    return f_node;
}

