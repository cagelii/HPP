#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("Total size is: %ld + %ld + %ld + %ld = %ld\n",sizeof(int),sizeof(double),sizeof(char),sizeof(float),sizeof(int)+sizeof(double)+sizeof(char)+sizeof(float));
    FILE* fp;
    fp = fopen("little_bin_file","rb");
    int i;
    double d;
    char c;
    float f;
    fread(&i, sizeof(int),1,fp);
    fread(&d, sizeof(double),1,fp);
    fread(&c, sizeof(char),1,fp);
    fread(&f, sizeof(float),1,fp);

    fclose(fp);

    printf("Integer: %d\n", i);
    printf("Double: %lf\n", d);
    printf("Char: %c\n", c);
    printf("Float: %f\n", f);
}