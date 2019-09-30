#include <stdlib.h> // For malloc
#include <stdio.h> // printf

// A q-element is a structure with a prev, next, and payload of 1 integer. 
struct q_element {
  struct q_element* next;
  struct q_element* prev;
  int payload;
};

// A queue conists of a head pointer and a set of q-elements. This means that a queue is just a pointer to a q_element.
struct queue {
  struct q_element *head;
  
};

struct q_element * NewItem() {
  return (struct q_element *) malloc(sizeof(struct q_element));
}

// Add the item queue to the top of the head queue
// A double linked list doesn't use next at the end
void AddQueue(struct q_element *head, int item){
  struct q_element* newItem = NewItem();
  newItem->payload = item;
  if (head->next == NULL){
    newItem->next = NULL;
    newItem->prev = NULL;
    head->next = newItem;
  }else{
    struct q_element* temp = head->next;
    temp->prev = newItem;
    newItem->next = temp;
    newItem->prev = NULL;
    head->next = newItem;
  }
}

void PrintQueue(struct q_element *head) {
  struct q_element* temp = head->next;
  while(temp != NULL) {
    printf("%d -> ", temp->payload);
    temp = temp->next;
  }
}
int main(){
  struct q_element *head1;
  struct q_element *head2;
4
  head1 = NewItem();
  head2 = NewItem();
  
  head1->payload = 99;
  AddQueue(head2, 1);
  AddQueue(head2, 2);
  AddQueue(head2, 3);
  PrintQueue(head2);
  return 0;
}
