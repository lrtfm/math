#include <stdio.h>
#define G 0.618

double gold(double (*f)(double), \
        double a, double b, double e)
{
    double lambda = a + (1 - G)*(b - a);
    double mu = a + G * (b - a);
    while (a - b > e || b - a > e) {
        if (f(lambda) > f(mu)) {
            a = lambda;
            lambda = mu;
            // b do not change.
            mu = a + G * (b - a);
        } else {
            // a do not change.
            b = mu;
            mu = lambda;
            lambda = a + (1 - G) * (b - a);
        }
    }
    return lambda;
}
/* // test fun
double fun(double x)
{
    return x * x + x;
}
int main(int argc, char ** argv)
{
    double a = -1;
    double b = 2;
    double e = 0.001;
    printf("Result : %f\n", gold(fun, a, b, e));
    return 0;
} */
