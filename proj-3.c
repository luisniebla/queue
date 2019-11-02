#include "sem.h"

struct TCB_t * RunQ;

struct sem * S;

void producer() {
    printf("Hello World");
    yield();
}

void consumer() {
    printf("Hello World2");
    yield();
}

int main() {
    S = (struct sem *) malloc(sizeof(struct sem));
    RunQ = NewItem();
    RunQ->payload = 0;
    start_thread(producer);
    start_thread(consumer);
    run();

}