/*
 * mpicc pi.c
 * https://www.open-mpi.org/doc/v1.8/man3/MPI_Reduce.3.php
 */
#include <mpi.h>
#include <stdio.h>

#define N 100000

int main(int argc, char ** argv)
{
    double local, pi, w, temp;
    int i, taskid, numtask;

    w = 1.0 / N;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Comm_size(MPI_COMM_WORLD, &numtask);

    local = 0;
    for (i = taskid; i < N; i = i + numtask) {
        temp = (i + 0.5) * w;
        local += 4.0 / (1.0 + temp * temp);
    }
    printf("%d: local is %f.\n", taskid, local);

    MPI_Reduce(&local, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (taskid == 0) {
        printf("pi is %f.\n", pi * w);
    }

    MPI_Finalize();

    return 0;
}
