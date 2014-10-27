#include <stdio.h>

double interpolation(double (*f)(double), double a, double b, double c, double e)
{
    double fa, fb, fc;
    double num, den;
    
    while (b - c > e || c - b > e) {
        fa = f(a);
        fb = f(b);
        fc = f(c);
        num = (b*b - c*c)*fa + (c*c - a*a)*fb + (a*a - b*b)*fc;
        den = (b - c)*fa + (c - a)*fb + (a - b)*fc;

        a = b;
        b = c;
        c = num / (2 * den);
    }

    return c;
}

// test fun

double fun(double x)
{
    return x * x + x;
}

int main(int argc, char ** argv)
{
    double a = -1;
    double b = 2;
    double c = 3;
    double e = 0.001;

    printf("Result : %f\n", interpolation(fun, a, b, c, e));
    
    return 0;
}

       

