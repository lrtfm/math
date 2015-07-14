/*
 * hw_0_0_1.c
 *
 * 2014-12-21 19:31:17
 *
 * YangZongze yangzongze@gmail.com
 */

/*
 * v_t + av_x = \mu v_{xx}
 */

#include <math.h>
#include <stdio.h>
#include <malloc.h>


double initinal(double x)
{
    return sin(2*3.1415926*x);
}

int main(int argc, char **argv)
{
    int M = 10;
    int N = 9;
    double a = 0;
    double b = 1;
    double delta_t = 0.025;
    double mu = 0.2;

    printf("\nPlease INPUT mu:"); scanf("%lf", &mu);
    printf("\nPlease INPUT a:"); scanf("%lf", &a);
    printf("\nPlease INPUT b:"); scanf("%lf", &b);
    printf("\nPlease INPUT M:"); scanf("%d", &M);
    printf("\nPlease INPUT delta_t:"); scanf("%lf", &delta_t);
    printf("\nPlease INPUT N:"); scanf("%d", &N);
    printf("\n");

    printf("mu = %lf, a = %lf, b = %lf, M = %d, delta_t = %lf, N = %d\n",
            mu, a, b, M, delta_t, N);

    double delta_x = (b - a)/M;

    double *temp = NULL;
    double *Uold = (double*)malloc((M+1)*sizeof(double));
    double *Unew = (double*)malloc((M+1)*sizeof(double));

    for (int i = 0; i <= M; i++) {
        Uold[i] = initinal(i*delta_x);
    }

    double r = delta_t / delta_x;
    double R = delta_t / (delta_x * delta_x);
    for (int j = 1; j <= N; j++) {
        // t = j * delta_t;
        Unew[0] = 0; Unew[M] = 0;
        for (int i = 1; i < M; ++i) {
            Unew[i] = Uold[i] - r * Uold[i] * (Uold[i+1] - Uold[i]) / 2 + 
                mu * R * (Uold[i+1] - 2*Uold[i] + Uold[i-1]);
        }

        for (int i = 0; i <= M; ++i) {
            printf("%lf ", Unew[i]);
        }
        printf("\n");
        
        temp = Uold;
        Uold = Unew;
        Unew = temp;
    }

    return 0;
}


