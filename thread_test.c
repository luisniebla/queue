// CSE 330 - Fall 19
// Luis Guillermo Niebla Rios - 1206613079

#include "threads.h"

struct TCB_t * RunQ;

void increment_by_1() {
  struct TCB_t * local_var = NewItem();
  local_var->payload = 0;
  while(1 == 1) {
    local_var->payload += 1;
    RunQ->payload += 1;
    printf("This is function %d th execution of function 1 with global variable value %d", local_var->payload, RunQ->payload);
    yield();
  }
  printf("Done with incremenet by 1");
}

int main() {
  RunQ = NewItem();
  RunQ->payload = 0;
  start_thread(increment_by_1);
  run();
  return 0;
}
