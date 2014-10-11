/*
 * Author: yangzongze
 * Date: 2014/03/26
 *
 *
 */

#ifndef MATH_WAPPER_H__
#define MATH_WAPPER_H__

#include "const_define.h"

typedef double real;
typedef real (*math_function)(int num, real* para_list);

struct name_fun_pair {
    char name[MAX_SYMBOL_LEN];
    math_function fun;
};

math_function get_fun_pointer(char *fun_name);

real add_wrapper(int num, real* paralist);
real min_wrapper(int num, real* paralist);
real mul_wrapper(int num, real* paralist);
real div_wrapper(int num, real* paralist);

#endif
