// Luis Guillermo Niebla Rios

#include "sem.h"

struct TCB_t * RunQ;
struct TCB_t * touchedHistory;
#define DEBUG 0 
ucontext_t uctx_main;
ucontext_t parent;
struct sem * resource;
struct sem * mutex;
int buffer;
struct TCB_t * tcb_buff;
int buff[5];
int fill = 0;
int use = 0;
int i = 0;
int readcount = 0;
int readerID = 0;
int writerID = 0;

void put(int value) {
    // if (buff[fill] != 0){
    //     printf("=====ERROR PRODUCED AT NON A NULL VALUE=====\n");
    //     sleep(3);
    // }
    struct TCB_t * thisRecord = NewItem();
    thisRecord->identifier = RunQ->next->identifier;
    AddToEnd(touchedHistory, thisRecord);
    // printf("Touched history\n");
    // PrintQueue(touchedHistory);
    // buff[fill] = value;
    
    // fill = (fill + 1) % 6;
}

TCB_t * get() {
    TCB_t *head = DelQueue(touchedHistory);
    return head;
};

int out;

int item;
int last_touched = 0;



void writer() {
    writerID++;
    P(resource);
    printf("This is the %d th writer writing value i = %d\n", writerID, i );
    V(resource);
    printf("This is the %d th w­riter verifying value i = %dn", writerID, i );
    yield();
}

void reader() {
    readerID++;
    P(mutex);
    readcount++;          //Indicate that you are a reader trying to enter the Critical Section
    if (readcount == 1)   //Checks if you are the first reader trying to enter CS
        P(resource);
    V(mutex);
    // Read the variable value and print the current value
    printf("This is the %d th reader reading value i = %d for the first time\n", readerID, i );
    P(mutex);
    readcount--;
    if (readcount == 0)
        V(resource);
    V(mutex);
    printf("This is the %d th reader reading value i = %d for the second time\n", readerID, i );
    yield();
}

void generate_threads(void (*function) (void), int payload, char * str, int threads) 
{
    for (int i = 0; i < threads; i++) {
        start_thread(function, payload + i, str);
    }
}
int main() {
    tcb_buff = NewItem();
    out = 0;
    touchedHistory = NewItem();
    touchedHistory->payload = 0;
    mutex = (struct sem *) malloc(sizeof(struct sem));
    resource = (struct sem *) malloc(sizeof(struct sem));
    InitSem(resource, 1, "resource");
    resource->queue = NewItem();
    InitSem(mutex, 1, "mutex");
    mutex->queue = NewItem();
    RunQ = NewItem();
    RunQ->payload = 0;

    generate_threads(reader, 1, "Reader", 5);
    generate_threads(writer, 1, "Writer", 1);
    generate_threads(reader, 6, "Reader", 4);
    generate_threads(writer, 2, "Writer", 2);
    generate_threads(reader, 11, "Reader", 5);
    generate_threads(writer, 4, "Writer", 1);
    generate_threads(reader, 17, "Reader", 3);

    run();
}