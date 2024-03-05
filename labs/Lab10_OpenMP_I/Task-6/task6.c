#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

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
    double start = omp_get_wtime();
    double primes[N];

    for (int i = 0; i < N; i++)
    {
        primes[i] = 0;
    }

    #pragma omp parallel num_threads(N)
    {
        int thread = omp_get_thread_num();
        for (int i = thread+2; i < M; i+=N)
        {
            primes[thread] += isPrime(i);
        }
    }
    
    double end = omp_get_wtime();
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum += primes[i];
    }
    
    printf("Number of primes is: %d\n Time = %lf s\n", sum, end-start);
}