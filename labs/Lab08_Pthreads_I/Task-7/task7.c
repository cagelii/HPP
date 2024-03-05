#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* nestledThreadFunc(){
    printf("Now inside nestledThreadFunc\n");
}

void* threadFunc(){
    pthread_t threadA;
    pthread_t threadB;
    pthread_create(&threadA,NULL,nestledThreadFunc,NULL);
    pthread_create(&threadA,NULL,nestledThreadFunc,NULL);
    pthread_join(threadA,NULL);
    pthread_join(threadB,NULL);
}

int main(){
    pthread_t threadA;
    pthread_t threadB; 

    pthread_create(&threadA,NULL,threadFunc,NULL);
    pthread_create(&threadB,NULL,threadFunc,NULL);

    pthread_join(threadA,NULL);
    pthread_join(threadB,NULL);
}