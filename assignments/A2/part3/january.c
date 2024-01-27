#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef 
    struct Data{
    int day;
    float min, max;
} Data;

typedef
   struct Node {
     Data data;
     struct Node *next;
   } Node, *link; 

void printData(Data data){
    printf("%d\t%f\t%f\n",data.day,data.min,data.max);
}

link cons(Data data, link next){
    Node *n = (Node *)malloc(sizeof(Node));
    n->data = data;
    n->next = next;

    return n;
}

void print(Node *f){
    printf("Day\tmin\tmax\n");
    while (f){
        printData((*f).data);

        f = (*f).next;
    }
}

void addSorted(link *n, Data x) {
  if (*n == NULL || x.day < (*n)->data.day) {
    *n = cons(x, *n);
  } else {
    addSorted(&((*n)->next), x); 
  }
}	

// void remove(link *n, int day){
//     assert(*n);
//     if (*n == NULL || day < (*n)->data.day) {
//         link toBeReleased = *n;
//         *n = (*n)->next;
//         // Data result = (*toBeReleased)->data;
//         free(toBeReleased);
//   } else {
//     remove(&((*n)->next), day); 
//   }
// }

int main(){
    int i = 1;
    while (i)
    {
      printf("Enter command:");
      char text[20];
      scanf("%19f",text);
      switch (text[0])
      {
        case 'A':
          int day;
          float min;
          float max;

          printf("A\n");
          scanf("%d",&day);
          scanf("%f",&min);
          scanf("%f",&max);
          break;
        case 'D':
          printf("D\n");
          break;
          
        case 'P':
          printf("P\n");
          break;

        case 'Q':
          printf("Q\n");
          i = 0;
          break;

        default:
          printf("Invalid command\n");
          break;
      }
    }
}