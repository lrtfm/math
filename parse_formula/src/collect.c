/*
 * Author : yangzongze
 * Date : 2014/03/26
 *
 */


#include "collect.h"
#include <ctype.h>
#include <malloc.h>
#include <stdlib.h>
#include <assert.h>
#include "const_define.h"

F_NODE *malloc_f_node()
{
    int i;
    F_NODE *f_node = NULL;
    
    f_node = (F_NODE*)malloc(sizeof(F_NODE));

    if (f_node == NULL) {
        printf("Error in malloc_f_node.\n");
        return NULL;
    }

    for (i = 0; i < MAX_CHILD_NODE; ++i) {
        f_node->child[i] = NULL;
    }

    return f_node;
}

int copy_str(char *dest, char* source, int len, int max_len)
{
    
    int ret = (len > max_len) ? max_len : len;

    int i;
    for (i = 0; i < ret; ++i) {
        dest[i] = source[i];
    }

    dest[i] = '\0';
    
    return ret;
}

// trim space, bracket pair 
// 新的实现思路：读取完字符串， 分析字符串的信息， 括号匹配，空格等， 作为全局变量存储。
int trim_brackets(char *str, int *start, int* len)
{
    int old_start = *start;
    int old_len = *len;

    int i, j;
    int b_pos[40][2];
    int b_num;
    int begin_space = 0;
    int end_space = 0;
    j = 0;

    for (i = 0; i < old_len; i++) {
        if (str[old_start+i] == ' ') {
            begin_space++;
            continue;
        } else if (str[old_start+i] == '(') {
            b_pos[j++][0] = i;
        } else {
            break;
        }
    }

    b_num = j;
    j = 0;
    int flag = 0;

    for (i = old_len - 1; i >= 0; i--) {
        if (str[old_start+i] == ' ' && flag == 0) {
            end_space++;
        } else if (str[old_start+i] == ')') {
            flag = 1;
            j++;
        } else {
            break;
        }
    }

    if (b_num > j) {
        b_num = j;
    }

    int backet = 0;
    j = b_num - 1;
    flag = 0;
    for ( i = b_pos[j][0] + 1; i < old_len && j >= 0; ++i) {
        if (backet == 0 && str[old_start+i] == ')') {
            if (flag == 0) {
                b_num--;
            }
            b_pos[j][1] = i;
            flag = 0;
            j--;
        }
        else if (str[old_start+i] == ')') {
            flag = 1;
            backet--;
        }
        else if (str[old_start+i] == '(') {
            flag = 1;
            backet++;
        }
        else {
            if (str[old_start+i] != ' ') {
                flag = 1;
            }
        }
    }

    if (b_num == 0) {
        *start = old_start + begin_space;
        *len = old_len - begin_space - end_space;
        return 0;
    }


    int new_begin = old_start + b_pos[b_num - 1][0] + 1;
    int new_len = b_pos[b_num - 1][1] - b_pos[b_num - 1][0] - 1;
    begin_space = 0;
    end_space = 0;
    for (i = 0; i < new_len; ++i) {
        if (str[new_begin + i] == ' ') {
            begin_space++;
        } 
        else {
            break;
        }
    }

    for (i = new_len - 1; i >= 0; i--) {
        if (str[new_begin + i] == ' ') {
            end_space++;
        } 
        else {
            break;
        }
    }

    *start = new_begin + begin_space;
    *len = new_len - begin_space - end_space;

    return 0;
}


int get_para_sep_index(int *para_sep_index, char * str, int start, int len)
{

    int i = 0;
    for (i = 0; i < len; ++i) {
        if (str[start + i] != L_BRACKET) {
            continue;
        } else {
            break;
        }
    }
    int backet = 1;
    para_sep_index[0] = i;
    int j = 1;
    i++;
    for (; i < len; ++i) {
        if (str[start + i] == L_BRACKET) {
            backet += 1;
        } 
        else if (backet == 1 && str[start+i] == SEPRATOR) {
            para_sep_index[j++] = i;
        }
        else if (backet == 1 && str[start+i] == R_BRACKET) {
            para_sep_index[j++] = i;
        }
        else if (str[start+i] == R_BRACKET) {
            backet -= 1;
        }
    }

    return j - 1;
}

int get_fun_name(char *fun_name, char *str, int start, int len)
{
    int i;
    for (i = 0; i < len; ++i) {
        if (str[start + i] != L_BRACKET && str[start + i] != ' ') {
            continue;
        } else {
            break;
        }
    }

    // need process error
    copy_str(fun_name, str + start, i, 16);

    return 0;
}


int get_str_type(char *str, int start, int len, STR_TYPE_INFO* type)
{
    // +, -, *, /,  num, sym, fun;

    int i = 0;
    int bracket = 0;
    char c = 0;

    int add_pos = -1;
    int div_pos = -1;
    int mul_pos = -1;
    int min_pos = -1;
    int alpha = 0;
    int digit = 0;

    for (i = 0; i < len; i++) {
        c = str[start + i];

        if (c == L_BRACKET) {
            bracket++;
            continue;
        }
        else if (c == R_BRACKET) {
            bracket--;
            continue;
        }
        else if (bracket == 0) {
            if (c == OP_ADD && add_pos == -1) { 
                add_pos = i; 
            }
            if (c == OP_MIN) {
                min_pos = i;
            }
            if (c == OP_MUL && mul_pos == -1) {
                mul_pos = i;
            }
            if (c == OP_DIV) {
                div_pos = i;
            }
        }
        // else {
        if (isalpha(c)) {
            alpha++;
        }
        else if (isdigit(c) || c == '.' ) {
            digit++;
        }
        // }
    }

    //if (add_pos == 0 || mul_pos == 0 || min_pos == 0 || div_pos == 0)
    if (mul_pos == 0 || div_pos == 0)
    {
        // error TODO
        return -1;
    }

    if (add_pos != -1) {
        type->type = STR_TYPE_ADD;
        type->index = add_pos;
        return 0;
    }
    if (min_pos != -1) {
        type->type = STR_TYPE_MIN;
        type->index = min_pos;
        return 0;
    } 
    if (mul_pos != -1) {
        type->type = STR_TYPE_MUL;
        type->index = mul_pos;
        return 0;
    }
    if (div_pos != -1) {
        type->type = STR_TYPE_DIV;
        type->index = div_pos;
        return 0;
    }
    if (alpha == len) {
        type->type = STR_TYPE_SYM;
        type->index = 0;
        return 0;
    }
    if (digit == len) {
        type->type = STR_TYPE_DIG;
        type->index = 0;
        return 0;
    }
    type->type = STR_TYPE_FUN;
    type->index = 0;
    return 0;
}

