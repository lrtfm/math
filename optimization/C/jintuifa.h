#include <stdio.h>

void jintuifa(double (*f)(double), double x, \
        double *a, double *b)
{
    double t = 2;
    double h = 0.1;
    if (f(x + h) > f(x)) h = -h;

    while (f(x + h) < f(x)) x = x + h;

    if (h > 0) {
        *a = x - h/2;
        *b = x + h;
    } else {
        *a = x + h;
        *b = x - h/2;
    }
}

/*
double fun(double x)
{
    return x * x + x;
}
int main(int argc, char ** argv)
{
    double a = -1;
    double b = 2;
    double e = 0.001;
    double x = -3;
    jintuifa(fun, -3, &a, &b);
    printf("Result : %f, %f\n", a, b);
    return 0;
} */
