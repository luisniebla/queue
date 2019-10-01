#include <stdlib.h> // For malloc
#include <stdio.h> // printf
#include <assert.h> // assert, obviously

#define DEBUG 1

// A q-element is a structure with a prev, next, and payload of 1 integer. 
struct q_element {
  struct q_element* next;
  struct q_element* prev;
  int payload;
};

void PrintQueue(struct q_element *);
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
    newItem->next = newItem;
    newItem->prev = newItem;
    head->next = newItem;
  }else{
    struct q_element* prevFirst = head->next;
    struct q_element* last = head->next->prev;
    
    prevFirst->prev = newItem;
    newItem->next = prevFirst;
    newItem->prev = last;
    head->next = newItem;
    last->next = newItem;
  }
  if(DEBUG) {
    printf("Adding %d resulted in queue: ", item);
    PrintQueue(head);
  }
}

struct q_element* DelQueue(struct q_element *head){
  if (head->next == NULL) {
    printf("----Tried to delete empty queue---\n");
    return NULL;
  }
  struct q_element* last = head->next->prev;
  struct q_element* deleteMe = head->next;
  if (deleteMe == deleteMe->next) {
    head->next = NULL;
    printf("Deleting resulted in queue: end\n");
    return deleteMe;
  }
  head->next = deleteMe->next;
  head->next->prev = last;
  head->next->next = deleteMe->next->next;
  last->next = head->next;
  if(DEBUG) {
    printf("Deleting resulted in queue: ");
    PrintQueue(head);
  }
}
    
void PrintQueue(struct q_element *head) {
  struct q_element* temp = head->next;
  printf("%d -> ", temp->payload);
  temp = temp->next;
  while(temp != head->next) {
    printf("%d -> ", temp->payload);
    temp = temp->next;
  }
  printf("end");
  printf("\n");
}

void RotateQ(struct q_element *head) {
  printf("Rotating queue: ");
  head->next = head->next->next;
  PrintQueue(head);
}
void test_add_queue() {
  struct q_element *head;

  head = NewItem();
  AddQueue(head, 1);
  assert(head->next->payload == 1);
  AddQueue(head, 2);
  assert(head->next->payload == 2);
  AddQueue(head, 3);

  assert(head->next->payload == 3);
  DelQueue(head);
  DelQueue(head);
  DelQueue(head);
  AddQueue(head, 99);
  AddQueue(head, 1);
  AddQueue(head, 2);
  AddQueue(head, 3);
  RotateQ(head);
  RotateQ(head);
  
}

int main(){
  test_add_queue();
  
  return 0;
}
