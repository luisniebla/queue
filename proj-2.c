#include <stdlib.h> // For malloc
#include <stdio.h> // printf
#include <assert.h> // assert, obviously
#include "q.h"

struct TCB_t * Push(int i) {
  struct TCB_t * newItem = NewItem();
  newItem->payload = i;
  return newItem;
}

void test_add_queue() {
  struct TCB_t *head;

  head = NewItem();
  
  AddQueue(head, Push(1));
  assert(head->next->payload == 1);
  DelQueue(head);
  DelQueue(head);
  DelQueue(head);
  AddQueue(head, Push(99));
  AddQueue(head, Push(1));
  AddQueue(head, Push(2));
  AddQueue(head, Push(3));
  RotateQ(head);
  RotateQ(head);
  
}

int main(){
  test_add_queue();
  
  return 0;
}
