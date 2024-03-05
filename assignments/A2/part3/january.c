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
     Data *data;
     struct Node *next;
   } Node, *link; 

void printData(Data data){
    printf("%d\t%f\t%f\n",data.day,data.min,data.max);
}

Node *cons(Data *data, Node *next){
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) {
    printf("Out of memory in cons\n");
    exit(1);}
    n->data = data;
    n->next = next;

    return n;
}

void printList(Node *f){
    printf("Day\tmin\t\tmax\n");
    while (f){
        printData(*f->data);

        f = (*f).next;
    }
}

Node *addSorted(link *n, Data *data) {
  if (*n == NULL || data->day < (*n)->data->day) {
    *n = cons(data, *n);
  
  }
  else if ((*n)->data->day == data->day)
  {
    (*n)->data = data;
  }
  else {
    (*n)->next=addSorted(&((*n)->next), data);
  }
  return *n;
}	

void removeNode(link *n, int day){
    if(*n==NULL){
      
    }
    else if (day == (*n)->data->day) {
        link toBeReleased = *n;
        *n = (*n)->next;
        free(toBeReleased->data);
        free(toBeReleased);
  } else {
    removeNode(&((*n)->next), day); 
  }
}

int main(){
    link list = NULL;
    while (1)
    {
      printf("Enter command:");
      char text[20];
      scanf("%19s",text);
      switch (text[0])
      {
        case 'A':
          int day;
          float min;
          float max;
          scanf("%d",&day);
          scanf("%f",&min);
          scanf("%f",&max);
          Data *temp = (Data *)malloc(sizeof(Data));
          temp->day = day;
          temp->min = min;
          temp->max = max;
          list = addSorted(&list, temp);
          break;
        case 'D':
          int d;
          scanf("%d",&d);
          removeNode(&list,d);
          break;
          
        case 'P':
          printList(list);
          break;

        case 'Q':
          return 0;
          break;

        default:
          printf("Invalid command\n");
          break;
      }
    }
}