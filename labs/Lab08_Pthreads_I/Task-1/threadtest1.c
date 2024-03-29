#include <stdio.h>
#include <pthread.h>

void* the_thread_funcA(void* arg) {
  long int i;
  double sum;
  for(i = 0; i < 2000000000; i++)
  sum += 1e-7;
  printf("Result of work in threadA(): sum = %f\n", sum);
  return NULL;
}

void* the_thread_funcB(void* arg) {
  long int i;
  double sum;
  for(i = 0; i < 100000000; i++)
  sum += 1e-7;
  printf("Result of work in threadB(): sum = %f\n", sum);
  return NULL;
}

int main() {
  printf("This is the main() function starting.\n");

  /* Start thread. */
  pthread_t threadA;
  pthread_t threadB;
  printf("the main() function now calling pthread_create().\n");
  pthread_create(&threadA, NULL, the_thread_funcA, NULL);
  pthread_create(&threadB, NULL, the_thread_funcB, NULL);

  printf("This is the main() function after pthread_create()\n");

  long int i;
  double sum;
  for(i = 0; i < 1000000000; i++)
  sum += 1e-7;
  printf("Result of work in main(): sum = %f\n", sum);

  /* Wait for thread to finish. */
  printf("the main() function now calling pthread_join().\n");
  pthread_join(threadA, NULL);
  pthread_join(threadB,NULL);

  return 0;
}
