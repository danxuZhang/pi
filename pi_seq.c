#include <stdio.h>
#include <math.h>
#include <time.h>

#ifndef STEPS
#define STEPS 100000000
#endif

double f(double x) {
    return sqrt(1.0 - x * x);
}

int main() {
    int i;
    double step = 1.0 / STEPS;
    double sum = 0.0;
    double x;
    clock_t start, end;

    start = clock();

    for (i = 0; i < STEPS; i++) {
        x = (i + 0.5) * step;
        sum += f(x);
    }

    double pi = 4.0 * step * sum;
    end = clock();
    double cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Steps: %d\n", STEPS);
    printf("PI = %.10f (Error: %.10f)\n", pi, fabs(pi - M_PI));
    printf("Time: %f seconds\n", cpu_time);

    return 0;
}

