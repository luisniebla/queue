
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
        printf(">>>P(S)\n");
        printf(">>>>%d\n", S->value);
        struct TCB_t * newItem = DelQueue(RunQ);
        newItem->next = NULL;
        newItem->prev = NULL;
        AddQueue(S->queue, newItem);
        printf("RunQ\n");
        PrintQueue(RunQ);
        printf("Queue:\n");
        PrintQueue(S->queue);
        setcontext(&(RunQ->next->context));
    }
}

struct TCB_t * V(struct sem * S) {
    struct TCB_t * newRunner;
    S->value++;
    printf(">>>V(S)\n");
    printf(">>>>%d\n", S->value);
    if (S->value <= 0) {
        // Take PCB out of semaphore queue and put it into run queue
        printf("Adding to queue\n");
        struct TCB_t * newItem = DelQueue(S->queue);
        newItem->next = NULL;
        newItem->prev = NULL;
        AddQueue(RunQ, newItem); // take out element
        // PrintQueue(RunQ);
    }
    yield();
}