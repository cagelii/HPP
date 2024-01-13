/* factorial.c
   Program that tabulates the factorial function
*/
#include <stdio.h>

int factorial(int n) {
   if (n==0) {
	return 1; }
   else {
       return n*factorial(n-1);
   }
}

int main() {
   for (int i = 0; i<=10; i++)  {
       printf( "%2d %15d \n", i, factorial(i));
   }
   return 0;
}
