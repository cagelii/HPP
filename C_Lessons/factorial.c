/* factorial.c
   Program that tabulates the factorial function
*/
#include <stdio.h>

int factorial(int n) {
   int result = 1;
   while (n > 0) {
       result = result*n;
       n--;
   }
   return result;
}

int main() {
   for (int i = 0; i<=10; i++)  {
       printf( "%2d %15d \n", i, factorial(i));
   }
   return 0;
}
