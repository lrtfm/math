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
    
    double V[N-1]; // 对角阵，一阶项系数
    double D[N-1]; // 对角阵，分数阶项系数
    double F[N-1]; // 列向量，右端项

    //  1  0  0  0
    // -1  1  0  0
    //  0 -1  1  0
    //  0  0  0 -1
    double L[(N-1)*(N-1)]; 

    // g1 g0  0  0
    // g2 g1 g0  0
    // g3 g2 g1 g0
    // g4 g3 g2 g1
    double T[(N-1)*(N-1)];

    memset(V, 0, (N-1)*sizeof(double));
    memset(D, 0, (N-1)*sizeof(double));
    memset(F, 0, (N-1)*sizeof(double));
    memset(L, 0, (N-1)*(N-1)*sizeof(double));
    memset(T, 0, (N-1)*(N-1)*sizeof(double));

    // L
    int i = 0;
    int j = 0;
    L[(N-1)*(N-1) - 1] = 1;
    for (i = 0; i < N - 2; i++) {
        L[i + i * (N - 1)] = 1; // i 行 i 列
        L[i + i * (N - 1) + 1] = -1; // i+1 行 j 列
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
    TIME = 100;

    h = (b - a) / N;
    r = tau/h; s = tau / (pow(h, alpha));

    for (i = 0; i < N - 1; i++) {  // i 行标
        for (j = 0; j < N - 1; j++) {  // j 列标
            if (i - j + 1 >= 0) {
                T[i + j * (N - 1)] = gweight(i - j + 1, alpha);
            }
        }
    }

//    print_matrix(N - 1, N - 1, L, "Matrix L");
//    print_matrix(N - 1, N - 1, T, "Matrix T");

    for (i = 0; i < N - 1; ++i) {
        x = a + (i + 1) * h;
        V[i] = advection(v0, x);
        D[i] = dispersion(d0, x);
    }

    double C[N-1];
    memset(C, 0, (N-1)*sizeof(double));
    double CN[N-1];
    memset(CN, 0, (N-1)*sizeof(double));

    for (i = 0; i < N - 1; i++) {
        C[i] = phi((i+1)*h);
    }

    double WORK1[(N-1)*(N-1)];
    double WORK2[(N-1)*(N-1)];
    memset(WORK1, 0, (N-1)*(N-1)*sizeof(double));
    memset(WORK2, 0, (N-1)*(N-1)*sizeof(double));
    double A[(N-1)*(N-1)];
    memset(A, 0, (N-1)*(N-1)*sizeof(double));

    multip_sddmo(r, N - 1, V, L, WORK1);
    //print_matrix(N - 1, N - 1, T, "Matrix T");
    multip_sddmo(s, N - 1, D, T, WORK2);
    printf(" r = %lf, s = %f\n", r, s);
    //print_matrix(N - 1, 1, D, "Matrix D");
    //print_matrix(N - 1, N - 1, WORK1, "Matrix work1");
    //print_matrix(N - 1, N - 1, WORK2, "Matrix work2");

    double I[(N-1)*(N-1)];
    memset(I, 0, (N-1)*(N-1)*sizeof(double));
    for (i = 0; i < N - 1; ++i) {
        I[i + i * (N-1)] = 1.0;
    }

    minus_dmmmo(N - 1, I, WORK1, WORK2, A);

    int DIM = N - 1;
    int NRHS = 1;
    int INFO = 0;
    double R[N-1];
    memset(R, 0, (N-1)*sizeof(double));
    double B[N-1];
    memset(B, 0, (N-1)*sizeof(double));
    print_matrix(N - 1, N - 1, A, "Matrix A");

    // 时间步循环迭代
    t = 0;
    while (t < TIME) {
        t += tau;

        // 右端项 f
        for (i = 0; i < N - 1; i++) {
            F[i] = force(a + (i+1)*h, t);
        }
        
        print_matrix(1, N - 1, F, "vector F");
        // 边界条件
        double c0, cN; // c0, cN 
        c0 = lboundary(t); // t = (n + 1)*tau
        cN = rboundary(t);

        for ( i = 0; i < N - 1; i++) {
            R[i] = s * c0 * D[i] * gweight(i + 2, alpha);
        }
        R[0] = R[0] - r * V[0] * c0;
        R[N-1] = R[N-1] + s * D[N-1] * cN * gweight(0, alpha);

        for (i = 0; i < N - 1; i++) {
            B[i] = R[i] + F[i] + C[i];
        }

        print_matrix(1, N - 1, B, "vector B");
        // A*CN = B 求解
        dgesv_(&DIM, &NRHS, A, &DIM, R, B, &DIM, &INFO);
        // lapack

        // output CN
        print_matrix(1, N - 1, B, "vector solution B");
        // C <- B 
        memcpy(C, B, (N-1)*sizeof(double));
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
    // TODO
    if (x > -30.2 && x < -30.1 && t < 4) {
        return 5.93;
    }
    return 0;
}
double phi(double x)
{
    // TODO
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
//            if (i == j) {
                O[i + j * d] = I[i + j * d] - (M2[i + j * d] + M3[i + j * d]);
//            }
//            else {
//                O[i + j * d] = - (M2[i + j * d] + M3[i + j * d]);
//            }

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
