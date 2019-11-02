
#include "threads.h"

typedef struct sem {
  struct TCB_t *queue;
  int value;
} sem;

void InitSem(struct sem * S, int value) {
    S->value = value;
}

void P(struct sem * S) {
    S->value--;
    while(S->value < 0) {;}
}

struct TCB_t * V(struct sem * S) {
    struct TCB_t * newRunner;
    S->value++;
    if (S->value <= 0) {
        // Take PCB out of semaphore queue and put it into run queue
        newRunner = DelQueue(S->queue); // take out element
    }
    yield();
}