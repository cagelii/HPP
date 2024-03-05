#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE* fp;
    fp = fopen("little_bin_file","rb");
    int i;
    double d;
    char c;
    float f;
    int x;
    fread(&i, sizeof(int),1,fp);
    fread(&d, sizeof(double),1,fp);
    fread(&c, sizeof(char),1,fp);
    fread(&f, sizeof(float),1,fp);

    fclose(fp);

    printf("%d\n", i);
    printf("%lf\n", d);
    printf("%c\n", c);
    printf("%f\n", f);
}