
#include "threads.h"

extern struct TCB_t * RunQ;
#include <string.h>
#define DEBUG 1
typedef struct sem {
  struct TCB_t *queue;
  int value;
  char *label;
} sem;

void InitSem(struct sem * S, int value, char str[]) {
    // printf("initializing to %d\n", value);
    S->value = value;
    // printf("here is yuor proof %d\n", S->value);
    S->label = str;
}

void PrintSem(struct sem * S) {
    if (DEBUG) {
printf("\n====S=======\n");
    printf("|label: %s|\n", S->label);
    printf("|value: %d  |\n", S->value);
    printf("==========\n");
    }
    
}
void P(struct sem * S) {
    S->value--;
    // printf("P(S) incrementing S\n");
    // PrintSem(S);
    if (S->value < 0) {
        struct TCB_t * currentItem = DelQueue(RunQ);
        currentItem->next = NULL;
        currentItem->prev = NULL;
        AddQueue(S->queue, currentItem);
        // yield_from(currentItem);
        while (S->value < 0) {
            printf("%s is waiting\n", currentItem->identifier);
            // PrintSem(S);
            // printf("P(S) RunQueue\n");
            // PrintQueue(RunQ);
            // sleep(1);
            RotateQ(RunQ);
            yield_from(currentItem);
            // RotateQ(RunQ);
            // sleep(1);
            // wait();
        }
    }
}

struct TCB_t * V(struct sem * S) {
    S->value++;
    // printf("V(S) is incrementing S\n");
    // PrintSem(S);
    if (S->value <= 0) {
        // Take PCB out of semaphore queue and put it into run queue
        // printf("V prints queue\n");
        // PrintQueue(S->queue);
        struct TCB_t * newItem = DelQueue(S->queue);
        newItem->next = NULL;
        newItem->prev = NULL;
        struct TCB_t * currentItem = RunQ->next;
        AddQueue(RunQ, newItem); 
        // printf("V printing modified RunQ\n");
        // PrintQueue(RunQ);
        // RotateQ(RunQ);
        yield_from(currentItem);
    }
    
}