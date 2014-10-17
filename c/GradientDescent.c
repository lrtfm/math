#include "vector.h"
#include "gold.h"
#include <stdio.h>
double funciton(struct vector& x)
{
    a = *x->data;
    b = *(x->data + 1);
    return a*a + 2*a + b*b;
}

void gradien(struct vector&x, struct vector &d)
{
    mul(1.0, x, d);
    *(d->data) = *(x->data) * 2 + 2.0;
    *(d->data + 1) = *(x->data + 1) * 2;
}

fun myfun = function;
grad mygrad = gradien;
struct vector gx;
struct vector gd;

double oneD(double alpha) 
{
    struct vector a;
    initvector(a);
    mul(alpha, gd, a);
    add(gx, a, a);
    return myfun(a);
}

void gradient_descent(struct vector &x, double e)
{
    // init global var
    initvector(&gd);
    initvector(&gx);

    double alpha;
    struct vector d;
    initvector(&d);
    mygrad(x, &d);
    mul(-1.0, &d);
    double a, b;

    while(len(d) > e) {
        mul(1.0, x, gx);
        mul(1.0, d, gd);
        jintuifa(oneD, 10, &a, &b);
        alpha = gold(oneD, a, b, e);
        mul(alpha, d, d);
        add(d, x, x);
        mygrad(x, &d);
        mul(-1.0, d, d);
    }
}

int main(int argc, char **argv)
{
    struct vector x;
    initvector2(x, 2, 2.0, 3.0);
    gradient_descent(&x, 0.001);
    printf("x: %f, %f\n", *(x->data), *(x->data + 1));

    return 0;
}

