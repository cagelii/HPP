/* cat.c
   Copy standard input to standard output. 
*/
#include <stdio.h>
int main() {
   char c;
   c = getchar();
   int chars = 0;
   int i = 0;
   while (c != EOF) {
       putchar(c);
       c = getchar();
	printf("Number of Characters: %d\n", i);
	i++;
   }
   printf("Number of characters: %d\n", i);
   return 0;
}
