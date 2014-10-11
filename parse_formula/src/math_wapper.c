/*
 * Author : yangzongze
 * Date : 2014/03/26
 *
 */

#include "math_wapper.h"
#include "macro.h"

#include <stdlib.h>
#include <math.h>

real sin_wapper(int n, real *para);
real cos_wapper(int n, real *para);
real tan_wapper(int n, real *para);
real exp_wapper(int n, real *para);

struct name_fun_pair fun_map[] =
{   "sin", sin_wapper,
    "cos", cos_wapper,
    "tan", tan_wapper,
    "exp", exp_wapper
};

math_function get_fun_pointer(char *fun_name)
{
    static int size = sizeof(fun_map)/sizeof(struct name_fun_pair);
    int i;

    for (i = 0; i < size; ++i) {
        if (!strcmp(fun_map[i].name, fun_name)) {
            return fun_map[i].fun;
        }
    }

    return NULL;
}

real sin_wapper(int n, real *para)
{
    CHECK_PARA(n, 1, para);

    return sin(para[0]);
}

real cos_wapper(int n, real *para)
{
    CHECK_PARA(n, 1, para);

    return cos(para[0]);
}

real tan_wapper(int n, real *para)
{
    CHECK_PARA(n, 1, para);

    return tan(para[0]);
}
real exp_wapper(int n, real *para)
{
    CHECK_PARA(n, 1, para);

    return exp(para[0]);
}
real add_wrapper(int num, real* paralist)
{
    CHECK_PARA(num, 2, paralist);

    return paralist[0] + paralist[1];
}
  

real min_wrapper(int num, real* paralist)
{
    CHECK_PARA(num, 2, paralist);

    return paralist[0] - paralist[1];
}

real mul_wrapper(int num, real* paralist)
{
    CHECK_PARA(num, 2, paralist);

    return paralist[0] * paralist[1];
}

real div_wrapper(int num, real* paralist)
{
    CHECK_PARA(num, 2, paralist);

    return paralist[0] / paralist[1];
}
