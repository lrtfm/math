/*
 * mulsplit.c
 *
 * 2015-02-08 04:53:59 PM
 *
 * YangZongze yufeiyang@mail.nwpu.edu.cn
 */

#include "jacobi.h"

#include <mpi.h>
#include <stdio.h>

#define DIETAG  99999

double boundary(double x, double y)
{
    return x * y * y;
}

double source(double x, double y)
{
    return 2 * x * y;
}

int main(int argc, char ** argv)
{
    int pid, pnum;
 
    MPI_Status status; 
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &pnum);

    int bn, n;
    double hx, hy;
    double Mx = 51;
    double My = 51;
    hx = 1.0/51, hy = 1.0/51;
    bn = My - 1; n = Mx - 1;

    // 0 p 不运算  1 ~ (pnum - 1) yun suan 
    int m = n / (pnum - 1) + 1;
    double *b = NULL;
    double *y = NULL;
    double *t = NULL;
   
    double maxE = 0;
    double *e = malloc(bn*n*sizeof(double));
    double *x = (double*)malloc(bn*n*sizeof(double));
    double *oldx = (double*)malloc(bn*n*sizeof(double));
    memset(oldx, 0, sizeof(double)*bn*n);
    memset(x, 0, sizeof(double)*bn*n);
    memset(e, 0, sizeof(double)*bn*n);

    int averageSize = m*bn;
    int lastSize = n*bn - (m-1)*bn*(pnum-2);
    int size;
    // sleep();

    
    if (pid == 0) {
        b = (double*)malloc(bn*n*sizeof(double));
        y = (double*)malloc(bn*m*sizeof(double));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < bn; ++j) {
                double temp = 0;
                if (i == 0) {
                    temp += Mx*Mx*boundary(i*hx, (j+1)*hy);
                } else if (i == n - 1) {
                    temp += Mx*Mx*boundary((i+2)*hx, (j+1)*hy);
                }

                if (j == 0) {
                    temp += Mx*Mx*boundary((i+1)*hx, j*hy);
                } else if (j == bn - 1) {
                    temp += Mx*Mx*boundary((i+1)*hx, (j+2)*hy);
                }

                b[i*bn + j] = source((i+1)*hx,(j+1)*hy) - temp;
                // printf("b[%d] = %lf\n", i*bn + j, b[i*bn + j]);
            }
        }
        for (int i = 1; i < pnum; ++i) {
            int rs = (i != pnum -1)? averageSize : lastSize;
            // printf("send dest:%03d start:%03d size:%03d\n", i, (i-1)*(m-1)*bn, rs);
            MPI_Send(b+(i-1)*(m-1)*bn, rs, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
        }
    } else {
        size = (pid != pnum -1)? averageSize : lastSize;
        b = (double *)malloc(size*sizeof(double));
        y = (double *)malloc(size*sizeof(double));
        t = (double *)malloc(size*sizeof(double));
        MPI_Recv(b, size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
        // printf("recv id:%03d size:%03d\n", pid, size);
    }
    struct Tridiagonal C, A, B;
    C.center = -2*Mx*Mx-2*My*My; C.above = My*My; C.below = My*My;
    A.center = Mx*Mx; A.above = 0; A.below = 0;
    B.center = Mx*Mx; B.above = 0; B.below = 0;
    int tag;
    for (tag = 1; tag < DIETAG; ++tag) {
        if (pid != 0) {  // slave
            memcpy(t, b, size*sizeof(double));
            if (tag != 1) {
                MPI_Recv(x, n*bn, MPI_DOUBLE, 0 , MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                if (status.MPI_TAG == DIETAG) {
                    printf("pid = %03d get DIETAG\n", pid);
                    break;
                } else if (status.MPI_TAG == tag - 1) {
                    for (int i = 0; i < bn; ++i) {
                        if (pid != 1) {
                            t[i] += -B.center * x[(pid - 1)*(m-1)*bn - bn + i];
                        } 
                        if (pid != pnum - 1) {
                            t[(m-1)*bn + i] += -A.center * x[pid*(m-1)*bn + bn + i];
                        }
                    }
                } else {
                    printf("pid = %03d get ERROR TAG\n", pid);
                }
            }

            jacobi(pid, C, A, B, bn, size/bn, t, y);
            MPI_Send(y, size, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
        } else { // host
            double *sw = oldx;
            oldx = x; x = sw;
            memset(x, 0, sizeof(double)*bn*n);
            for (int i = 1; i < pnum; ++i) {
                int rs = (i != pnum -1)? averageSize : lastSize;
                MPI_Recv(y, rs, MPI_DOUBLE, i, tag, MPI_COMM_WORLD, &status);
                for (int j = 0; j < rs; ++j) {
                    if (i != 1 && j < bn) {
                        x[(i-1)*(m-1)*bn + j] += y[j]/2;
                    } else if (i != pnum - 1 && j >= bn * (m-1)) {
                        x[(i-1)*(m-1)*bn + j] += y[j]/2;
                    } else {
                        x[(i-1)*(m-1)*bn + j] += y[j];
                    }
                }
            }
            for (int i = 1; i < n*bn; ++i) {
                e[i] = fabs(x[i] - oldx[i]);
            }
            maxE = max(n*bn, e);
            if (maxE > 0.0000001) {
                for (int i = 1; i < pnum; ++i) {
                    MPI_Send(x, n*bn, MPI_DOUBLE, i , tag, MPI_COMM_WORLD);
                }
            } else {
                for (int i = 1; i < pnum; ++i) {
                    MPI_Send(0, 0, MPI_INT, i, DIETAG, MPI_COMM_WORLD);
                    printf("HOST SEND DIE TO ALL\n");
                }
                break;
            }
        }
    }
    if (pid == 0) {
        printf("interat times %3d\n", tag);
        double real;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < bn; ++j) {
                real =boundary((i+1)*hx, (j+1)*hy);
                printf("x[%d] = %lf ", i*bn + j, x[i*bn + j]);
                printf("rx[%d] = %lf ", i*bn + j, real);
                printf("err = %lf\n", real - x[i*bn+j]);
            }
        }
        printf("Solution:\n");
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < bn; ++j) {
                printf("%lf ", i*bn + j, x[i*bn + j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    /*
    free(x);
    free(y);
    free(b);
    free(e);
    free(oldx);
    free(t);
    */
    MPI_Finalize();
    return 0;
}

