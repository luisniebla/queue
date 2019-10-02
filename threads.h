#include "q.h"
#include <string.h>
struct TCB_t *RunQ;

void start_thread(void (*function) (void))
{
  // allocate a stack? 
  void * stackP = (void *) malloc(sizeof(void) * 8192);
  struct TCB_t * my_TCB = (struct TCB_t *) malloc(sizeof(struct TCB_t));
  init_TCB(my_TCB, function, stackP, 8192);
  AddQueue(RunQ, my_TCB);
}

