#include "q.h"
#include <string.h>

extern struct TCB_t * RunQ;
extern struct ucontext_t parent;
void start_thread(void (*function) (void), int payload, char * output_string)
{
  char * stackP = (char *) malloc(sizeof(char) * 8192);
  struct TCB_t * my_TCB = (struct TCB_t *) malloc(sizeof(struct TCB_t));
  init_TCB(my_TCB, function, stackP, 8192);
  my_TCB->payload = payload;
  my_TCB->identifier = output_string;
  AddToEnd(RunQ, my_TCB);
}

void run() {
  printf("Running----\n");
  swapcontext(&parent, &(RunQ->next->context));
}

int yield() {
  TCB_t * parent_child = RunQ->next;
  RotateQ(RunQ);
  // printf("Hi\n");
  // printf("We're going to swap from %d:%d to %d:%d\n", parent_child->payload, &(parent_child->context), RunQ->next->payload, &(RunQ->next->context));
  swapcontext(&(parent_child->context), &(RunQ->next->context));
  
  // PrintQueue(RunQ);
  // printf("Swap Context Returned: %d\n", swapcontext(parent_child, &(RunQ->next->context)));
  // if (parent_child == &(RunQ->next->context)) {
  //   return;
  // }else{
  // }
  
}

int yield_from(TCB_t * parent) {
  // printf("=========Context Switch => Payload %d: %d > Payload %d: %d\n", parent->payload, &(parent->context), RunQ->next->payload, &(RunQ->next->context));
  swapcontext(&(parent->context), &(RunQ->next->context));
  
}
