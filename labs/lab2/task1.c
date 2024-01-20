#include <stdio.h>

int main(){
    // for (int i=100; i>=0; i-=4){
    //     printf("%d\n",i);
    // }
    //return 1;
    test();
}

int test(){
    int i = 100;
    do {
        printf("%d\n",i);
        i-=4;
    } while(i>=0);
}