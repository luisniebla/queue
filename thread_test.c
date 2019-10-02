// CSE 330 - Fall 19
// Luis Guillermo Niebla Rios - 1206613079

#include "threads.h"

struct TCB_t * RunQ;

void increment_by_1() {
  int local_count;
  while(1 == 1) {
    local_count += 1;
    RunQ->payload += 1;
    printf("This is function %d th execution of function 1 with global variable value %d\n", local_count, RunQ->payload);
    yield();
  }
  printf("Done with incremenet by 1");
}

void increment_by_2() {
  int local_count;
  while(1 == 1) {
    local_count += 1;
    RunQ->payload += 2;
    printf("This is function %d th execution of function 2 with global variable value %d\n", local_count, RunQ->payload);
    yield();
  }
  printf("Done with incremenet by 2");
}

void increment_by_3() {
  int local_count;
  while(1 == 1) {
    local_count += 1;
    RunQ->payload += 3;
    printf("This is function %d th execution of function 3 with global variable value %d\n", local_count, RunQ->payload);
    yield();
  }
}

int main() {
  RunQ = NewItem();
  RunQ->payload = 0;
  start_thread(increment_by_1);
  start_thread(increment_by_2);
  start_thread(increment_by_3);
  run();
  return 0;
}
