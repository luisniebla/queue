
#include "threads.h"

extern struct TCB_t * RunQ;
extern struct TCB_t * waitQ;
#include <string.h>
#define DEBUG 0
typedef struct sem {
  struct TCB_t *queue;
  int value;
  char *label;
} sem;

void InitSem(struct sem * S, int value, char str[]) {
    S->value = value;
    S->label = str;
}

void PrintSem(struct sem * S) {
    
printf("\n====S=======\n");
    printf("|label: %s|\n", S->label);
    printf("|value: %d  |\n", S->value);
    printf("==========\n");
    
    
}

extern int buffer;
void P(struct sem * S) {
    S->value--;
    if (S->value < 0) {
        struct TCB_t * newItem = DelQueue(RunQ);
        AddQueue(S->queue, newItem);
        printf("%s is waiting\n", newItem->identifier);
        yield_from(newItem);
        // Wait here until we have a valid semaphore value.
        while (S->value < 0) {
            RotateQ(RunQ);
            yield_from(newItem);
        }
    }
}

struct TCB_t * V(struct sem * S) {
    S->value++;
    if (S->value <= 0) {
        struct TCB_t * newItem = DelQueue(S->queue);
        newItem->next = NULL;
        newItem->prev = NULL;
        struct TCB_t * currentItem = RunQ->next;
        AddQueue(RunQ, newItem); // take out element
        yield_from(currentItem);
    }
    
}