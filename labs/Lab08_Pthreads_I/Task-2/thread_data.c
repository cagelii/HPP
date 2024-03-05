#include <stdio.h>
#include <pthread.h>

void* the_thread_func(void* arg) {
  /* Do something here? */
  double sum = 0;
  double *data = (double *) arg;
  for (int i = 0; i<3; i++){
    sum += data[i];
    printf("%f\n",data[i]);
  }
  printf("Sum: %f\n",sum);
  return NULL;
}

int main() {
  printf("This is the main() function starting.\n");

  double data_for_thread[3];
  data_for_thread[0] = 5.7;
  data_for_thread[1] = 9.2;
  data_for_thread[2] = 1.6;

  double data_for_threadB[3];
  data_for_threadB[0] = 3.2;
  data_for_threadB[1] = 5.4;
  data_for_threadB[2] = 4.3;

  /* Start thread. */
  pthread_t thread;
  pthread_t threadB;
  printf("the main() function now calling pthread_create().\n");
  pthread_create(&thread, NULL, the_thread_func, data_for_thread);
  pthread_create(&threadB, NULL, the_thread_func, data_for_threadB);

  printf("This is the main() function after pthread_create()\n");

  /* Do something here? */

  /* Wait for thread to finish. */
  printf("the main() function now calling pthread_join().\n");
  pthread_join(thread, NULL);

  return 0;
}
