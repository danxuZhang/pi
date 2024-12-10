#include <math.h>
#include <omp.h>
#include <stdio.h>

#ifndef STEPS
#define STEPS 100000000
#endif

double f(double x) { return sqrt(1.0 - x * x); }

int main() {
  double step = 1.0 / STEPS;
  double sum = 0.0;
  double start, end;

  start = omp_get_wtime();

#pragma omp parallel
  {
    double local_sum = 0.0;

#pragma omp for
    for (int i = 0; i < STEPS; i++) {
      double x = (i + 0.5) * step;
      local_sum += f(x);
    }

#pragma omp atomic
    sum += local_sum;
  }

  double pi = 4.0 * step * sum;

  end = omp_get_wtime();

  printf("Steps: %d\n", STEPS);
  printf("Threads: %d\n", omp_get_max_threads());
  printf("PI = %.10f (Error: %.10f)\n", pi, fabs(pi - M_PI));
  printf("Time: %f seconds\n", end - start);

  return 0;
}
