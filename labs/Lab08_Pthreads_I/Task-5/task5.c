#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct threadStruct
{
    pthread_t thread;
    int index;
} threadStruct;

void* threadFunc(void* arg){
    threadStruct* t = (threadStruct*)arg;
    int index = t->index;
    printf("%d\n",index);
}

int main(int argc, char* argv[]){
    int N = atoi(argv[1]);
    threadStruct threads[N];
    for (int i = 0; i<N; i++){
        threads[i].index = i;
        pthread_create(&threads[i].thread,NULL,threadFunc,&threads[i]);
    }

    for (int i = 0; i < N; i++){
        pthread_join(threads[i].thread, NULL);
    }
}