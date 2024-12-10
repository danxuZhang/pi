#include <stdio.h>
#include <math.h>
#include <mpi.h>

#ifndef STEPS
#define STEPS 100000000
#endif

double f(double x) {
    return sqrt(1.0 - x * x);
}

int main(int argc, char *argv[]) {
    int rank, size, i;
    double step, sum = 0.0, pi = 0.0;
    double start, end;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    step = 1.0 / STEPS;
    
    start = MPI_Wtime();
    
    int local_steps = STEPS / size;
    int start_step = rank * local_steps;
    int end_step = (rank == size - 1) ? STEPS : start_step + local_steps;
    
    double local_sum = 0.0;
    for (i = start_step; i < end_step; i++) {
        double x = (i + 0.5) * step;
        local_sum += f(x);
    }
    
    MPI_Reduce(&local_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        pi = 4.0 * step * sum;
        end = MPI_Wtime();
        
        printf("Steps: %d\n", STEPS);
        printf("Processes: %d\n", size);
        printf("PI = %.10f (Error: %.10f)\n", pi, fabs(pi - M_PI));
        printf("Time: %f seconds\n", end - start);
    }
    
    MPI_Finalize();
    return 0;
}
