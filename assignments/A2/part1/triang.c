#include <stdio.h>
#include <stdlib.h>

int element(float n, float k){
    float ans = 1;
    for (int i=1; i<=k; i++){
        ans *= (n+1-i)/i;
    }
    return ans;
}

int main(int argc, char *argv[]){
    char *a = argv[1];
    int rows = atoi(a);
    for (int n = 0; n<rows; n++){
        for (int k = 0; k<=n; k++){
            printf("%d ", element(n,k));
        }
        printf("\n");
    }
}