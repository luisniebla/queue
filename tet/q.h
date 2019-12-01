#include <stdlib.h> // For malloc
#include <stdio.h> // printf
#include <assert.h> // assert, obviously
#include "tcb.h"

#define DEBUG 0

/**
 * Note: This queue does not start at head. Head is the pointer element which handles the queue location
 */
void PrintQueue(struct TCB_t *);

struct TCB_t * NewItem() {
  return (struct TCB_t *) malloc(sizeof(struct TCB_t));
}

int QueueLength(TCB_t *head) {
  int length = 0;
  if (head != NULL && head->next != NULL) {
    length++;
    struct TCB_t* temp = head->next;
    temp = temp->next;
    while(temp != head->next) {
      length++;
      temp = temp->next;
    }
  }else{
    return 0;
  }
  return length;
}
int IsInQueue(TCB_t *head, TCB_t * testItem) {
  if (head != NULL && head->next != NULL) {
    if (head == testItem) {
      return 1;
    }
    struct TCB_t* temp = head->next;
    temp = temp->next;
    while(temp != head->next) {
      if (temp == testItem) {
        return 1;
      }
      temp = temp->next;
    }
    
  }
  return 0;
}

// Add the item queue to the top of the head queue
// A double linked list doesn't use next at the end
void AddQueue(struct TCB_t *head, struct TCB_t * newItem){
  if (head == NULL || newItem == NULL) {
    printf("TRIED TO ADD NULL HEAD");
    return;
  }
  if (head->next == NULL){
    newItem->next = newItem;
    newItem->prev = newItem;
    newItem->payload = newItem->payload;
    head->next = newItem;
  }else{
    struct TCB_t* prevFirst = head->next;
    struct TCB_t* last = head->next->prev;
    
    prevFirst->prev = newItem;
    newItem->next = prevFirst;
    newItem->prev = last;
    newItem->payload = newItem->payload;
    head->next = newItem;
    last->next = newItem;
  }
  if(DEBUG) {
    printf("Adding %d resulted in queue: ", newItem->payload);
    PrintQueue(head);
  }
}
void AddToEnd(struct TCB_t *head, struct TCB_t * newItem){
  AddQueue(head, newItem);
  head->next = head->next->next;
}
struct TCB_t* DelQueue(struct TCB_t *head){
  if (head == NULL) {
    printf("---Tried to delete queue---");
    return NULL;
  }
  if (head->next == NULL) {
    printf("----Tried to delete empty queue---\n");
    return NULL;
  }
  struct TCB_t* last = head->next->prev;
  struct TCB_t* deleteMe = head->next;
  if (deleteMe == deleteMe->next) {
    head->next = NULL;
    if (DEBUG) printf("Deleting resulted in queue: end\n");
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
  return deleteMe;
}
    
void PrintQueue(TCB_t *head) {
  if (head != NULL && head->next != NULL) {
    struct TCB_t* temp = head->next;
    printf("%s -> ", temp->identifier);
    temp = temp->next;
    while(temp != head->next) {
      printf("%s -> ", temp->identifier);
      temp = temp->next;
    }
  
  }
  printf("end of queue");
  printf("\n");
}

void RotateQ(struct TCB_t *head) {
  head->next = head->next->next;
  if (DEBUG) {
    printf("Rotating queue: ");
    PrintQueue(head);
    printf("\n");
  }
  
}
