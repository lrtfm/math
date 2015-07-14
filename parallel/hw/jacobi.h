/*
 * jacobi.h
 *
 * 2014-12-12 20:06:39
 *
 * YangZongze yangzongze@gmail.com
 */

// gcc -std=c99 -g jacobi.c -o jacobi

#ifndef JACOBI_H__
#define JACOBI_H__

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
struct Tridiagonal {
    double center;
    double above;
    double below;
};
        
double max(int n, double *y)
{
    if (n <= 0) { return 0;}
    double ret = y[0];
    for (int i = 0; i < n; ++i) {
        if (y[i] > ret) {
            ret = y[i];
        }
    }
    return ret;
}


int jacobi(int id, struct Tridiagonal C, struct Tridiagonal A, struct Tridiagonal B, int nb, int n, double *b, double *y)
{
    double size = n * nb;
    double maxE = 0;
    double *e = malloc(size * sizeof(double));
    double *ty1 = malloc(size * sizeof(double));
    double *ty2 = malloc(size * sizeof(double));
    double *ty;
    for (int i = 0; i < size; ++i) {
        ty1[i] = 0;
        ty2[i] = b[i] / C.center;
        e[i] = fabs(ty1[i] - ty2[i]);
    }
    maxE = max(size, e);

    // for (int j = 0; j < size; ++j) {
    //     printf("%02d \tb[%d] = %lf\n",id, j, b[j]);
    // }
    int k;
    for(k = 0; maxE > 0.0000001 && k < 9999; k++) {
        ty = ty1;
        ty1 = ty2;
        ty2 = ty;
        // memcpy(ty1, ty2, size*sizeof(double));
        
        for (int i = 0; i < size; ++i) {
            double s = 0;
            // s += C.center * ty1[i];
            if (i%nb != (nb - 1)) s += C.above * ty1[i+1];
            if (i%nb != 0) s += C.below * ty1[i-1];
            if (i/nb != (n - 1)) {
                s += A.center * ty1[i+nb];
                if (i%nb != (nb - 1))    s += A.above * ty1[i+nb+1];
                if (i%nb != 0)  s += A.below * ty1[i+nb-1];
            }
            if (i/nb != 0) {
                s += B.center * ty1[i-nb];
                if (i%nb != (nb - 1))  s += B.above * ty1[i-nb+1];
                if (i%nb != 0)   s += B.below * ty1[i-nb-1];
            }
            ty2[i] = (b[i] - s) / C.center;
            e[i] = fabs(ty1[i] - ty2[i]);
        }

        // for (int j = 0; j < size; ++j) {
        //     printf("%03d    ty2[%d] = %lf\n", k, j, ty2[j]);
        // }
        maxE = max(size, e);
        // printf("%03d  maxE = %lf\n", k, maxE);
    } 
    
    printf("%02d OVER k = %03d maxE = %lf\n", id, k, maxE);
    memcpy(y,ty2, size * sizeof(double));
    free(e);
    free(ty1);
    free(ty2);
    return 0;
}


//  int main()
//  {
//      struct Tridiagonal C;
//      struct Tridiagonal A;
//      struct Tridiagonal B;
//      C.center = -4; C.above = 1; C.below = 1;
//      A.center = 1; A.above = 0; A.below = 0;
//      B.center = 1; B.above = 0; B.below = 0;
//      int nb = 50; 
//      int n = 4;
//      int size = n * nb;
//  
//      double *b = malloc(size * sizeof(double));
//      double *y = malloc(size * sizeof(double));
//      memset(b, 0, size * sizeof(double));
//      memset(y, 0, size * sizeof(double));
//      b[0] = 1;
//      b[size - 1] = 1;
//      jacobi(C, A, B, nb, n, b, y); 
//      for (int i = 0; i < size; ++i) {
//          printf("y[%d] = %lf\n", i, y[i]);
//      }
//      return 0;
//  }

#endif
