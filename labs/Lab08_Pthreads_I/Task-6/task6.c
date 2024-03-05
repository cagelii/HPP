#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

typedef struct dataStruct
{
    int start;
    int stop;
    int sum;
} dataStruct;


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
    data[2] += primes;
}

int main(int argc, char* argv[]){
    int M = atoi(argv[1]);
    int N = atoi(argv[2]);
    int sum = 0;
    pthread_t threads[N];
    const int chunk = M/N; //antar att snälla värden stoppas in
    dataStruct data[N];

    double start = get_wall_seconds();
    data[0].start = 2; data[0].stop = chunk; data[0].sum=0;
    pthread_create(&threads[0],NULL,numberOfPrimes,&data[0]);

    for (int i = 1; i < N; i++)
    {
        data[i].start = i*chunk;
        data[i].stop = (i+1)*chunk;
        data[i].sum = 0;
        pthread_create(&threads[i],NULL,numberOfPrimes,&data[i]);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(threads[i], NULL);
        sum += data[i].sum;
    }
    double stop = get_wall_seconds();
    printf("Sum of primes: %d, when M=%d. Time of computation: %f\n",sum,M,stop-start);
}