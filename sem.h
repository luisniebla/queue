
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
    
printf("\n====S=======\n");
    printf("|label: %s|\n", S->label);
    printf("|value: %d  |\n", S->value);
    printf("|queue: ");
    PrintQueue(S->queue);
    printf("==========\n");
    
    
}
void P(struct sem * S) {
    
    if (DEBUG) printf("======>P\n");
    S->value--;
    if(DEBUG) PrintSem(S);
    if (S->value < 0) {
        // printf(">P(S) inner loop\n");
        // PrintSem(S);
        struct TCB_t * newItem = DelQueue(RunQ);
        if (newItem == NULL){
            if (DEBUG) printf("TRIED TO DELETE EMPTY RUNQ\n");
        }else{
            if (DEBUG) printf("P deleted RunQ\n");
            if (DEBUG) PrintQueue(RunQ);
            newItem->next = NULL;
            newItem->prev = NULL;
            AddQueue(S->queue, newItem);

            if (DEBUG) PrintSem(S);
        }
        // printf("======%s\n", newItem->identifier);
        // printf("RunQ\n");
        // PrintQueue(RunQ);
        // printf("Queue:\n");
        // PrintQueue(S->queue);
        // sleep(1);
        // If we're at parity with consumers and producers, we should only see this a
        // printf("%s is waiting\n", newItem->identifier);
        // PrintSem(S);
        // sleep(1);
        yield_from(newItem);
        // sleep(1);
        while (S->value < 0) {
            // printf("%s passes\n", RunQ->next->identifier);
            // PrintSem(S);
            // RotateQ(RunQ);
            // yield_from(newItem);
            // RotateQ(RunQ);
            // setcontext(&(RunQ->next->context));
            // sleep(1);
            yield();
        }
    }
}

struct TCB_t * V(struct sem * S) {
    if (DEBUG) printf("====>V\n");
    if (DEBUG) PrintSem(S);
    struct TCB_t * newRunner;
    S->value++;
    if (S->value <= 0) {
        // Take PCB out of semaphore queue and put it into run queue
        // printf("Removing from queue\n");
        if (DEBUG) printf("Current Queue\n");
        if (DEBUG) PrintQueue(S->queue);
        struct TCB_t * newItem = DelQueue(S->queue);
        // printf("WE DELETED SUCCESFFULLY\n");
        // PrintQueue(S->queue);
        newItem->next = NULL;
        newItem->prev = NULL;
        // printf("RETRIEVING NEXT ITEM\n");
        struct TCB_t * currentItem = RunQ->next;
        // printf("WERE GOING TO ADD TO QUEU\n");
        AddToEnd(RunQ, newItem); // take out element
        if (DEBUG) printf("*********V just added to the queue\n");
        if (DEBUG) printf("RunQ:\n");
        if (DEBUG) PrintQueue(RunQ);
        // PrintQueue(RunQ);
        // printf("V is yielding\n");
        // printf("Payload: %d\n", RunQ->next->payload);
        // yield();
        // yield_from(currentItem);
        // We didn't want to yield_from here because of the case where you're releasing as the reader, you want to finish reading before throwing to writer
        // But since we added Writer to the front of the queue, we need to push it back so we yield correct
    }
    
}