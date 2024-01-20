#include <stdio.h>

int main(){
    int a;
    int b;

    printf("a?\n");
    scanf("%d",&a);
    printf("b?\n");
    scanf("%d",&b);

    for (int i=0; i<a; i++){
        for (int j=0; j<b; j++){
            if (j==0 || j==b-1 || i==0 || i==a-1){
                printf("*");
            }
            else {
                printf(".");
            }
        }
        printf("\n");
    }
}