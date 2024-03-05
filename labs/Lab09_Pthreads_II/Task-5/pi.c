/**********************************************************************
 * This program calculates pi using C
 *
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

const int N = 10; //number of threads
const int intervals = 500000000;
const int subintervals = intervals/N;
const double dx = 1.0/intervals;

typedef struct dataStruct{
  int start,end;
  double subsum;
} dataStruct;

void* threadFunc(void* arg){
  dataStruct* data = (dataStruct*)arg;
  int i;
  double x;
  for (i = data->start; i <= data->end; i++) { 
    x = dx*(i - 0.5);
    data->subsum += dx*4.0/(1.0 + x*x);
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  double sum = 0.0;

  pthread_t threads[N];
  dataStruct data[N];
  for (int i = 0; i < N; i++)
  {
    data[i].start = i*subintervals; data[i].end = (i+1)*subintervals; data[i].subsum = 0.0;
    pthread_create(&threads[i],NULL,threadFunc,&data[i]);
  }
  for (int i = 0; i < N; i++)
  {
    pthread_join(threads[i],NULL);
  }
  for (int i = 0; i < N; i++)
  {
    sum += data[i].subsum;
  }
  printf("PI is approx. %.16f\n",  sum);

  return 0;
}
