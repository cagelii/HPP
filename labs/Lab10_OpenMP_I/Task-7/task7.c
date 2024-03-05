#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
#include <omp.h>
#endif


int isPrime(int n){
    if (n <= 1) return 0;
    for (int j=2;j<n;j++){
        if (n%j == 0){
            return 0;
        }
    }
    return 1;
}

int main(int argc, char* argv[]){
    if (argc != 3){
        printf("Angry boi\n");
        return 1;
    }
    
    int M = atoi(argv[1]);
    int N = atoi(argv[2]);
    int primes = 0;
    //double start = omp_get_wtime();
    #pragma omp parallel num_threads(N) reduction(+:primes) // create local variables for each thread
    {
        #ifdef _OPENMP
            int myID = omp_get_thread_num();
            int threadNum = omp_get_num_threads();
        #else
            int myID = 0;
            int threadNum = 1;
        #endif

        for (int i = myID+2; i < M; i+=threadNum)
        {
            primes += isPrime(i);
        }
    }
    //double end = omp_get_wtime();
    //printf("Number of primes is: %d\n Time = %lf s\n", primes, end-start);
    printf("Number of primes is: %d\n", primes);
}