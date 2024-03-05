#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* the_thread_func(void* arg) {
  int data[5] = {1,2,3,4,5};
  int *ptr;
  ptr = (int*)malloc(5*sizeof(int));
  for (int i = 0; i < 5; i++)
  {
    ptr[i] = data[i];
  }
  return ptr;
  
  // pthread_exit((void*)data);
 
}

int main() {
  printf("This is the main() function starting.\n");

  /* Start thread. */
  pthread_t thread;
  printf("the main() function now calling pthread_create().\n");
  if(pthread_create(&thread, NULL, the_thread_func, NULL) != 0) {
    printf("ERROR: pthread_create failed.\n");
    return -1;
  }

  printf("This is the main() function after pthread_create()\n");

  void* return_value;

  /* Wait for thread to finish. */
  printf("the main() function now calling pthread_join().\n");
  if(pthread_join(thread, &return_value) != 0) {
    printf("ERROR: pthread_join failed.\n");
    return -1;
  }

  int* ptr = (int*) return_value;
  for (int i = 0; i < 5; i++)
  {
    printf("%d\n",ptr[i]);
  }
  free(ptr);
  return 0;
}
