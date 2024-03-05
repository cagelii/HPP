#include <stdio.h>
#include <omp.h>

void thread_func() {
  int thread = omp_get_thread_num();
  int threads = omp_get_num_threads();
  printf("Thread num: %d\n Number of threads: %d\n",thread,threads);
}

int main(int argc, char** argv) {

#pragma omp parallel num_threads(4)
  {
    thread_func();
  }

  return 0;
}
