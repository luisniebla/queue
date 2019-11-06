
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
    // PrintSem(S);
    S->value--;
    if (S->value < 0) {
        // printf(">P(S) inner loop\n");
        // PrintSem(S);
        struct TCB_t * newItem = DelQueue(RunQ);
        if (newItem == NULL){
            if (DEBUG) printf("TRIED TO DELETE EMPTY RUNQ\n");
        }else{
            newItem->next = NULL;
            newItem->prev = NULL;
            AddQueue(S->queue, newItem);
        }
        
        // printf("RunQ\n");
        // PrintQueue(RunQ);
        // printf("Queue:\n");
        // PrintQueue(S->queue);
        // printf("S->value: %d\n", newItem->payload);
        while (S->value < 0) {
            // PrintSem(S);
            RotateQ(RunQ);
            yield_from(newItem);
            
            // sleep(1);
        }
    }
}

struct TCB_t * V(struct sem * S) {
    struct TCB_t * newRunner;
    S->value++;
    // printf(">>>V(S)\n");
    // printf(">>>>%d\n", S->value);
    if (S->value <= 0) {
        // Take PCB out of semaphore queue and put it into run queue
        // printf("Removing from queue\n");
        
        // PrintQueue(S->queue);
        struct TCB_t * newItem = DelQueue(S->queue);
        // printf("WE DELETED SUCCESFFULLY\n");
        // PrintQueue(S->queue);
        newItem->next = NULL;
        newItem->prev = NULL;
        // printf("RETRIEVING NEXT ITEM\n");
        struct TCB_t * currentItem = RunQ->next;
        // printf("WERE GOING TO ADD TO QUEU\n");
        AddQueue(RunQ, newItem); // take out element
        // printf("RunQ:\n");
        // PrintQueue(RunQ);
        // PrintQueue(RunQ);
        // printf("V is yielding\n");
        // printf("Payload: %d\n", RunQ->next->payload);
        // yield();
        yield_from(currentItem);
    }
    
}