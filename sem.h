
#include "threads.h"

extern struct TCB_t * RunQ;

typedef struct sem {
  struct TCB_t *queue;
  int value;
} sem;

void InitSem(struct sem * S, int value) {
    S->value = value;
}

void P(struct sem * S) {
    S->value--;
    while(S->value < 0) {yield();}
}

struct TCB_t * V(struct sem * S) {
    printf("Entering V\n");
    struct TCB_t * newRunner;
    S->value++;
    if (S->value <= 0) {
        // Take PCB out of semaphore queue and put it into run queue
        printf("Adding to queue\n");
        AddQueue(RunQ, DelQueue(S->queue)); // take out element
        PrintQueue(RunQ);
    }
    printf("Finished with V\n");
    // yield();
    yield();
    printf("-------Return from Yield-------");
}