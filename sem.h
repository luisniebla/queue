
#include "threads.h"

extern struct TCB_t * RunQ;
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
    printf("\n====S: %s=======\n", S->label);
    printf("|value: %d  |\n", S->value);
    printf("|queue: ");
    PrintQueue(S->queue);
    printf("==========\n");
}

void P(struct sem * S) {
    S->value--;
    if (S->value < 0) {
        struct TCB_t * newItem = DelQueue(RunQ);
        if (newItem == NULL){
            if (DEBUG) printf("TRIED TO DELETE EMPTY RUNQ\n");
        }else{
            newItem->next = NULL;
            newItem->prev = NULL;
            AddQueue(S->queue, newItem);
        }
        yield_from(newItem);
        while (S->value < 0) {
            if(DEBUG) printf("Stuck in a P loop possibly\n");
            if(DEBUG) PrintSem(S);
            if(DEBUG) exit(1);
            yield();
            
        }
    }
}

struct TCB_t * V(struct sem * S) {
    struct TCB_t * newRunner;
    S->value++;
    if (S->value <= 0) {
        // Take PCB out of semaphore queue and put it into run queue
        struct TCB_t * newItem = DelQueue(S->queue);
        newItem->next = NULL;
        newItem->prev = NULL;
        struct TCB_t * currentItem = RunQ->next;
        AddToEnd(RunQ, newItem); // take out element
    }
    
}