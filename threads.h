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
  swapcontext(&parent, &(RunQ->next->context));
}

int yield() {
  TCB_t * parent_child = RunQ->next;
  RotateQ(RunQ);
  swapcontext(&(parent_child->context), &(RunQ->next->context));
}

// For when you messed up the RunQ header and just need to go to the next context
int yield_from(TCB_t * parent) {
  swapcontext(&(parent->context), &(RunQ->next->context));
  
}
