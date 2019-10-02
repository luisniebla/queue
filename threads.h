#include "q.h"
#include <string.h>

extern struct TCB_t * RunQ;

void start_thread(void (*function) (void))
{
  // allocate a stack? 
  
  char * stackP = (char *) malloc(sizeof(char) * 8192);
  struct TCB_t * my_TCB = (struct TCB_t *) malloc(sizeof(struct TCB_t));
  my_TCB->payload = 0;
  init_TCB(my_TCB, function, stackP, 8192);
  printf("We did it");
  printf("\n%d\n", my_TCB->payload);
  printf("\n%d\n", RunQ->payload);
  AddQueue(RunQ, my_TCB);
}

void run() {
  ucontext_t parent;
  getcontext(&parent);
  swapcontext(&parent, &(RunQ->next->context));
}

void yield() {
  RotateQ(RunQ);
  ucontext_t parent;
  getcontext(&parent);
  swapcontext(&parent, &(RunQ->next->context));
}
