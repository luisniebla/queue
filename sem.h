
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
    while(S->value < 0) {
        printf("Adding to queue\n");
        struct TCB_t * newItem = DelQueue(RunQ->next);
        newItem->next = NULL;
        newItem->prev = NULL;
        AddQueue(S->queue, newItem);
        printf("RunQ\n");
        PrintQueue(RunQ);
        printf("Queue:\n");
        PrintQueue(S->queue);
        sleep(5);
        yield();
    }
}

struct TCB_t * V(struct sem * S) {
    struct TCB_t * newRunner;
    S->value++;
    if (S->value <= 0) {
        // Take PCB out of semaphore queue and put it into run queue
        printf("Adding to queue\n");
        AddQueue(RunQ->next, DelQueue(S->queue)); // take out element
        // PrintQueue(RunQ);
    }
    yield();
}