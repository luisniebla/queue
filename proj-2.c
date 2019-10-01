#include <stdlib.h> // For malloc
#include <stdio.h> // printf
#include <assert.h> // assert, obviously
#include "q.h"

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
