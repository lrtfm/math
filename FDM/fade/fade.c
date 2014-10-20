#include <stdio.h>
#include <string.h>
#include <math.h>

// 边界条件 初始条件全部为零
double gweight(int k, double alpha);
double advection(double v, double x);
double dispersion(double d, double x);
double force(double x, double t);
double phi(double x);
int multip_sddmo(double s, int d, double *D, double *M, double *O);
int minus_dmmmo(int d, double *M1, double *M2, double *M3, double *O);
void print_matrix(int m, int n, double *A, char *str); 
double rboundary(double x);
double lboundary(double x);

#define N 60

int main(int argc, char **argv)
{
    // int N; // 空间网格数
    
    double V[N]; // 对角阵，一阶项系数
    double D[N]; // 对角阵，分数阶项系数
    double F[N]; // 列向量，右端项

    //  1  0  0  0
    // -1  1  0  0
    //  0 -1  1  0
    //  0  0  0 -1
    double L[N*N]; 

    // g1 g0  0  0
    // g2 g1 g0  0
    // g3 g2 g1 g0
    // g4 g3 g2 g1
    double T[N*N];

    memset(V, 0, N*sizeof(double));
    memset(D, 0, N*sizeof(double));
    memset(F, 0, N*sizeof(double));
    memset(L, 0, N*N*sizeof(double));
    memset(T, 0, N*N*sizeof(double));

    // L
    int i = 0;
    int j = 0;
    L[N*N - 1] = 1;
    for (i = 0; i < N - 1; i++) {
        L[i + i * N] = 1; // i 行 i 列
        L[i + i * N + 1] = -1; // i+1 行 j 列
    }


    double alpha;  // 空间导数阶数
    double tau, h; // tau 时间步长，h 空间步长
    double r, s; // r = tau / h; s = tau / (h^alpha);
    double a, b;
    double x, t;
    double v0, d0;
    double TIME; 

    // TODO
    a = -60.127; b = -0.127;
    v0 = 4.0; d0 = 2.4;
    tau = 1;
    alpha = 1.6;
    TIME = 200;

    h = (b - a) / N;
    r = tau/h; s = tau / (pow(h, alpha));

    for (i = 0; i < N ; i++) {  // i 行标
        for (j = 0; j < N ; j++) {  // j 列标
            if (i - j + 1 >= 0) {
                T[i + j * N ] = gweight(i - j + 1, alpha);
            }
        }
    }

//    print_matrix(N - 1, N - 1, L, "Matrix L");
//    print_matrix(N - 1, N - 1, T, "Matrix T");

    for (i = 0; i < N ; ++i) {
        x = a + (i + 1) * h;
        V[i] = advection(v0, x);
        D[i] = dispersion(d0, x);
    }

    double C[N];
    memset(C, 0, N*sizeof(double));

    for (i = 0; i < N; i++) {
        C[i] = phi((i+1)*h);
    }

    double WORK1[N*N];
    double WORK2[N*N];
    memset(WORK1, 0, N*N*sizeof(double));
    memset(WORK2, 0, N*N*sizeof(double));
    double A[N*N];
    memset(A, 0, N*N*sizeof(double));

    multip_sddmo(r, N, V, L, WORK1);
    //print_matrix(N - 1, N - 1, T, "Matrix T");
    multip_sddmo(s, N, D, T, WORK2);
    // printf(" r = %lf, s = %f\n", r, s);
    //print_matrix(N - 1, 1, D, "Matrix D");
    //print_matrix(N - 1, N - 1, WORK1, "Matrix work1");
    //print_matrix(N - 1, N - 1, WORK2, "Matrix work2");

    double I[N*N];
    memset(I, 0, N*N*sizeof(double));
    for (i = 0; i < N; ++i) {
        I[i + i * N] = 1.0;
    }

    minus_dmmmo(N, I, WORK1, WORK2, A);

    // adjust A by boundary condition.
    
    print_matrix(N, N, A, "Matrix A");
    for (i = 0; i < N; ++i) {
        A[ N - 1 + i * N] = 0;
    }
    A[N*N - 1] = 1;
    A[N*N - N - 1] = - 1;
    print_matrix(N, N, A, "Matrix A");

    int DIM = N;
    int NRHS = 1;
    int INFO = 0;
    double R[N];
    memset(R, 0, N*sizeof(double));
    double B[N];
    memset(B, 0, N*sizeof(double));

    // 时间步循环迭代
    t = 0;
    while (t < TIME) {
        t += tau;

        // 右端项 f
        for (i = 0; i < N; i++) {
            F[i] = tau * force(a + (i+1)*h, t);
        }
        
        print_matrix(1, N, F, "vector F");
        // 边界条件
        double c0, cN; // c0, cN 
        c0 = lboundary(t); // t = (n + 1)*tau
        cN = rboundary(t); // nouse

        for ( i = 0; i < N; i++) {
            R[i] = s * c0 * D[i] * gweight(i + 2, alpha);
        }
        R[0] = R[0] - r * V[0] * c0;

        for (i = 0; i < N; i++) {
            B[i] = R[i] + F[i] + C[i];
        }

        // 调整最后一个值 B[N-1]  需要根据边界条件更改
        B[N-1] = 0;

        print_matrix(1, N, B, "vector B");
        // A*X = B 求解
        dgesv_(&DIM, &NRHS, A, &DIM, R, B, &DIM, &INFO);

        print_matrix(1, N, B, "vector solution B");
//        printf("%lf ", B[N-1]);
        // C <- B 
        memcpy(C, B, N*sizeof(double));
    }

    return 0;
}


double gweight(int k, double alpha)
{
    double a = 1.0, b = 1.0;
    int i = 0; 
    for (i = 0; i < k; ++i) {
        a = a *(-alpha + i);
        b = b * (i + 1);
    }

    return a / b;
}

double advection(double v, double x)
{
    return v/x;
}

double dispersion(double d, double x)
{
    return d/x;
}

double force(double x, double t)
{
    if (x > -30.2 && x < -30.1 && t < 4) {
        return 5.93;
    }
    return 0;
}
double phi(double x)
{
    return 0;
}
int multip_sddmo(double s, int d, double *D, double *M, double *O)
{
    int i, j;
    for (i = 0; i < d; ++i) { // 行
        for (j = 0; j < d; ++j) {
            O[i + j * d] = s * D[i] * M[i + j * d];
        }
    }
    return 0;
}

int minus_dmmmo(int d, double *I, double *M2, double *M3, double *O)
{

    int i, j;
    for (i = 0; i < d; ++i) { // 行
        for (j = 0; j < d; ++j) {
            O[i + j * d] = I[i + j * d] + M2[i + j * d] - M3[i + j * d];
        }
    }
    return 0;
}

void print_matrix(int m, int n, double *A, char *str)
{
    printf("%s:\n", str);
    int i = 0;
    int j = 0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%lf ", A[i + j * m]);
        }
        printf("\n");
    }
    printf("\n");
}
double lboundary(double x)
{
    return 0;
}
double rboundary(double x)
{
    return 0;
}
