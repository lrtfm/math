#include <stdlib.h>
#include <stdarg.h>

struct vector {
    int n; // 鍚戦噺缁村害
    double *data;
};

void initvector(struct vector *a)
{
    a->n = 0;
    a->data = NULL;
}

void initvector2(struct vector *a, int n, ...)
{
    a->n = n;
    a->data = malloc(n * sizeof(double));

    va_list ap;
    va_start(ap, n);
    int i = 0;
    double val;
    for (i = 0; i < n; ++i) {
        *(a->data + i) = va_arg(ap, double);
    }
    va_end(ap);
}

void finivector(struct vector *a)
{
    if (a->data)
    {
        free(a->data);
    }
    a->n = 0;
}

void add(struct vector *a, struct vector *b, struct vector *c)
{
    if (a->n != b->n)
    {
        // error.
        return ;
    }

    if (b != c) {
        finivector(c);
        c->n = a->n;
        c->data = malloc(c->n * sizeof(double));
    }
    int i = 0;
    for (i = 0; i < c->n; ++i) {
        *(c->data + i) = *(a->data + i) + *(b->data + i);
    }
}

void mul(double alpha, struct vector *a, struct vector *b)
{
    int i;
    if (a != b) {
        finivector(b);
        b->n = a->n;
        b->data = malloc(b->n * sizeof(double));
    }
    for (i = 0; i < a->n; ++i) {
        *(b->data + i) = *(a->data + i) * alpha;
    }
}

double len(struct vector * a)
{
    
    double l = 0;
    double t = 0;
    int i;
    for (i = 0; i < a->n; ++i) {
        t = *(a->data + i);
        l += t*t;
    }

    return l;
}

typedef double(*oned)(double);
typedef double (*fun)(struct vector*);
typedef void (*grad)(struct vector*, struct vector*);
