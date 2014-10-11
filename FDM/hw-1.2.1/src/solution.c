/*
 *
 * solution.c 
 * for hw 1.2.1
 *
 */

#include "parse_formula.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

#define PI 3.141593

// a.config
// D:M = 10
// D:delta_t = 0.02
// D:nu = 1/6
// A:T = 0.06, 0.1, 0.9, 50.0
// F:f(x) = sin(2*3.1415926*x)
// F:a(t) = 0
// F:b(t) = 0

struct config {
    int M;
    double delta_t;
    double max_t;
    double nu;
    double* T;
    int T_len;
    
    F_NODE *u_real;
    SYM_PAIR u_sym[2];
    F_NODE *f_x;
    SYM_PAIR f_sym[1];
    F_NODE *a_t;
    SYM_PAIR a_sym[1];
    F_NODE *b_t;
    SYM_PAIR b_sym[1];
};

double T[] = {0.06, 0.1, 0.9, 50.0};

int parse_config_file(char* file_name, struct config *data)
{
    // todo read from file
    data->M = 10;
    data->delta_t = 0.02;
    // data->max_t = 0.9;
    data->max_t = 50.0;
    data->nu = 1.0/6;
    data->T = T;
    data->T_len = 4;
    data->u_real = 
        parse("exp(0-4*3.1415926*3.1415926/6*t)*sin(2*3.1415926*x)");
    strcpy(data->u_sym[0].sym_name, "x");
    strcpy(data->u_sym[1].sym_name, "t");
    data->f_x = parse("sin(2*3.1415926*x)");
    strcpy(data->f_sym[0].sym_name, "x");
    data->a_t = parse("0");
    strcpy(data->a_sym[0].sym_name, "t");
    data->b_t = parse("0");
    strcpy(data->b_sym[0].sym_name, "t");
}

int output(int M, double delta_x, double t, double *data, double *real)
{
    int i = 0;
    if (real == NULL) {
        printf("t = %lf:\n", t);
        for (i = 0; i <= M; ++i) {
            printf("\tu(%lf, %lf) = %lf\n", i*delta_x, t, data[i]);
        }
        return 0;
    }

    printf("t = %lf:\n", t);
    double e; 
    for (i = 0; i <= M; ++i) {
        if (real[i] <= 0.000001 && real[i] >= -0.000001) {
            printf("\tu(%lf, %lf) = %lf, real = %lf, e = NAN\n", \
                i*delta_x, t, data[i], real[i]);
        }
        else {
            e = (data[i] - real[i])/real[i]*100; 
            printf("\tu(%lf, %lf) = %lf, real = %lf, e = %lf\%\n", \
                    i*delta_x, t, data[i], real[i], e);
        }
    }


    return 0;
}

int main(int argc, char*argv[])
{
    int M = 10;
    int N = 0.9/0.02;
    double delta_t = 0.02;
    double delta_x = 1.0/M;
    double nu = 1/6;

    // 临时变量
    double t ;
    double *pre_u, *cur_u, *real_u, *tmp;
    int i, j;
    
    char * file_name = NULL;
    struct config data;
    parse_config_file(file_name, &data);

    M = data.M;
    delta_t = data.delta_t;
    delta_x = 1.0/M;
    nu = data.nu;
    N = data.max_t/data.delta_t + 1;

    pre_u = (double *)malloc(sizeof(double)*(M+1));
    cur_u = (double *)malloc(sizeof(double)*(M+1));
    real_u = (double *)malloc(sizeof(double)*(M+1));

    // initial condition
    for (i = 0; i <= M; ++i) {
        data.f_sym[0].sym_value = i * delta_x;
        cur_u[i] = compute(data.f_x, data.f_sym, 1);
    }
    output(M, delta_x, 0, cur_u, NULL);

    // main loop for time;
    for (i = 1; i <= N; ++i) {
        tmp = cur_u;
        cur_u = pre_u;
        pre_u = tmp;

        // boundary condition
        t = i*delta_t;
        data.a_sym[0].sym_value = t;
        data.b_sym[0].sym_value = t;
        cur_u[0] = compute(data.a_t, data.a_sym, 1);
        cur_u[M] = compute(data.b_t, data.a_sym, 1);

        for (j = 1; j < M; ++j) {
            cur_u[j] = pre_u[j] + nu*delta_t*(pre_u[j+1] - 2*pre_u[j] \
                + pre_u[j-1])/(delta_x*delta_x);
        }



        data.u_sym[1].sym_value = t;
        for (j = 0; j <= M; j++) {
            data.u_sym[0].sym_value = j*delta_x;
            real_u[j] = compute(data.u_real, data.u_sym, 2);
        }
        // output data.
        for (j = 0; j < data.T_len; ++j)
        {
            //printf("T[%d] = %lf, t = %lf\n", j, T[j], t);
            if (data.T[j] <= t + 0.000001 && data.T[j] >= t - 0.000001) {
                output(M, delta_x, t, cur_u, real_u);
            }
        }
    }
        
    return 0;
}

