/*
 * jacobi.c
 *
 * 2015-02-08 10:37:59 PM
 *
 * Name Name@nwpu.edu.cn
 */


// gcc -std=c99 -g jacobi.c -o jacobi

#include "jacobi.h"

int main()
{
    struct Tridiagonal C;
    struct Tridiagonal A;
    struct Tridiagonal B;
    C.center = -2*51 - 2 * 51; C.above = 51; C.below = 51;
    A.center = 51; A.above = 0; A.below = 0;
    B.center = 51; B.above = 0; B.below = 0;
    int nb = 50; 
    int n = 6;
    int size = n * nb;

    double *b = malloc(size * sizeof(double));
    double *y = malloc(size * sizeof(double));
    memset(b, 0, size * sizeof(double));
    memset(y, 0, size * sizeof(double));
    b[0] = 1;
    b[size - 1] = 1;
    jacobi(C, A, B, nb, n, b, y); 
    for (int i = 0; i < size; ++i) {
        printf("y[%d] = %lf\n", i, y[i]);
    }
    return 0;
}
