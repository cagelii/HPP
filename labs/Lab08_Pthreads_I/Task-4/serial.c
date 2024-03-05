#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int primes = 1;
    int M = atoi(argv[1]);
    for (int i = 3; i<M; i++){
        int isPrime = 0;
        for (int j=2;j<i;j++){
            if (i%j == 0){
                isPrime = -1;
                break;
            }
        }
        if (isPrime == 0){
            primes++;
        }
    }
    printf("Primes: %d, when M = %d\n",primes,M);
}