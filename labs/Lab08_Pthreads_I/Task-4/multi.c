#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

void* numberOfPrimes(void* arg){
    int primes = 0;
    int *data = (int *) arg;
    int i;
    int M = data[1];
    for (i = data[0]; i<M; i++){
        int isPrime = 1;
        for (int j=2;j<i;j++){
            if (i%j == 0){
                isPrime = 0;
                break;
            }
        }
        if (isPrime){primes++;}
    }
    data[2] = primes;
}


int main(int argc,char* argv[]){
    int M = atoi(argv[1]);

    int data1[3];
    data1[0] = 2;
    data1[1] = M/2;
    data1[2] = 0;

    int data2[3];
    data2[0] = M/2;
    data2[1] = M;
    data2[2] = 0;

    double start = get_wall_seconds();
    pthread_t thread;
    pthread_create(&thread, NULL, numberOfPrimes, &data1);

    numberOfPrimes(data2);

    pthread_join(thread, NULL);
    double end = get_wall_seconds(); 
    printf("Primes: %d, M=%d\n",data2[2]+data1[2],M);
    printf("Time: %f s\n",end-start);
}