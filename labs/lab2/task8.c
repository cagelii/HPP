#include <stdio.h>

int main(){
    int i = 58;
    double d = 40.2;
    char c = 'x';

    printf("Value: %d, adress: %x, memory usage: %ld bytes \n",i,&i,sizeof(i));
    printf("Value: %f, adress: %x, memory usage: %ld bytes \n",d,&d,sizeof(d));
    printf("Value: %d, adress: %x, memory usage: %ld bytes \n",c,&c,sizeof(c));
}

