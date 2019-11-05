#include "q.h"
#include <string.h>

extern struct TCB_t * RunQ;
extern struct ucontext_t parent;
void start_thread(void (*function) (void), int payload)
{
  char * stackP = (char *) malloc(sizeof(char) * 8192);
  struct TCB_t * my_TCB = (struct TCB_t *) malloc(sizeof(struct TCB_t));
  init_TCB(my_TCB, function, stackP, 8192);
  my_TCB->payload = payload;
  AddQueue(RunQ, my_TCB);
}

void run() {
  swapcontext(&parent, &(RunQ->next->context));
}

int yield() {
  ucontext_t * parent_child = &(RunQ->next->context);
  RotateQ(RunQ);
  printf("We're going to swap from %d to %d\n", parent_child, &(RunQ->next->context));
  // 
  // printf("Swap Context Returned: %d\n", swapcontext(parent_child, &(RunQ->next->context)));
  if (parent_child == &(RunQ->next->context)) {
    return;
  }else{
    swapcontext(parent_child, &(RunQ->next->context));
  }
  
}

// matthew 
// labs something
// Fill a position of a React developer and calling in people for interviews
// React.js developer
// Downtown area
// Basic interview, get a sense of technical qualifications
// A few questions, React component lifecycle in async enviornment
  // Their application is 100% react material 
  // Model View Controller in terms of react lifecycle with constructor.
  // Redux stuff
// Wednesday Morning
  // 9 AM - 
// Thursday Morning at 9 AM
// Redux forms are include