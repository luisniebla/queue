// Luis Guillermo Niebla Rios

#include "sem.h"

struct TCB_t * RunQ;
struct TCB_t * touchedHistory;
#define DEBUG 0
#define DEBUG_SEM 0
#define DEBUG_RUNQ 0
ucontext_t uctx_main;
ucontext_t parent;
struct sem * resource;
int buffer;
int buff[5];
int fill = 0;
int use = 0;
int i = 0;
int readcount = 0;
int readerID = 0;
int writerID = 0;

typedef struct _rwlock_t {
    struct sem * writelock;
    struct sem * lock;
    struct sem * readlock;
    int readers;
} rwlock_t;

int magicSwitch = 0; // I couldn't figure out how to differentiate between the first writer wait and the other writer waits
                    // which require different output behavior (Adding to front of queue instead of to the end)
                    // It's purely for aesthetic and grading reasons, I don't think it actually effects how the algorithm works
rwlock_t mutex;

/** 
The basic names and concept for these rwlock_* functions comes from Operating Systems: 3 Easy Pieces (http://pages.cs.wisc.edu/~remzi/OSTEP/)
We modify the internals to work with our semlocks instead of C pthreads
**/
void rwlock_init(rwlock_t * lock) {
    lock->readers = 0;
    lock->lock = (struct sem *) malloc(sizeof(struct sem));
    lock->lock->queue = NewItem();
    lock->readlock = (struct sem *) malloc(sizeof(struct sem));
    lock->readlock->queue = NewItem();
    lock->writelock = (struct sem *) malloc(sizeof(struct sem));
    lock->writelock->queue = NewItem();
    InitSem((lock->lock), 1, "lock");
    InitSem((lock->writelock), 1, "writelock"); 
    InitSem((lock->readlock), 1, "readlock");
}

void rwlock_acquire_readlock(rwlock_t *lock) {
    P(lock->readlock);
    P(lock->lock);
    lock->readers++;
    if (lock->readers == 1) {
        P(lock->writelock);
    }
    V(lock->lock);
    V(lock->readlock);
}

void rwlock_release_readlock(rwlock_t *lock) {
    P(lock->lock);
    lock->readers--;
    if (lock->readers == 0){
        // Since all the readers are done reading, let's get all the pending writers into the queue.
        // We could just call V(writelock), but we need to change the ordering behavior for correct output
        // But I didn't want to modify the sem
        while(lock->writelock->queue->next != NULL) {
            lock->writelock->value++;
            struct TCB_t * newItem = DelQueue(lock->writelock->queue);
            newItem->next = NULL;
            newItem->prev = NULL;
            struct TCB_t * currentItem = RunQ->next;
            AddToFront(RunQ, newItem);
        }
        
    }
    V(lock->lock);
}

void rwlock_acquire_writelock(rwlock_t *lock) {
    // This readlock tells any additional readers that want to read that a writer is in the writelock queue.
    P(lock->readlock);
    P(lock->writelock);
}

void rwlock_release_writelock(rwlock_t *lock) {
    V(lock->readlock);
    V(lock->writelock);
}

int out;

int item;
int last_touched = 0;
int counter = 0;


void writer() {
    int localWriterID = ++writerID; // Save the writerID for when we come back to this function from another "thread"
    rwlock_acquire_writelock(&mutex);
    counter++;
    printf("This is the %dth writer writing value i = %d\n", localWriterID, counter);
    rwlock_release_writelock(&mutex);
    printf("This is the %dth writer verifying value i = %d\n", localWriterID, counter);

    DelQueue(RunQ); // Delete this writer from the queue
    // The block below basically does V() but inserts them to the queue in a different order    
    rwlock_t *lock = &mutex;
    while(lock->readlock->queue->next != NULL){
        AddQueue(RunQ, DelQueue(lock->readlock->queue));
        lock->readlock->value++;
    }
    swapcontext(&parent, &(RunQ->next->context));
}       

void reader() {
    int localReaderID = ++readerID;

    rwlock_acquire_readlock(&mutex);
    printf("This is the %dth reader reading value i = %d for the first time\n", localReaderID, counter );

    yield();

    rwlock_release_readlock(&mutex);
    printf("This is the %dth reader reading value i = %d for the second time\n", localReaderID, counter );

    DelQueue(RunQ); // Remove this reader from the queue
    swapcontext(&parent, &(RunQ->next->context));
}

// Helper functions for inserting a function into the queue multiple times. The payload is basically just an identifier
void generate_threads(void (*function) (void), int payload, char * str, int threads) 
{
    for (int i = 0; i < threads; i++) {
        start_thread(function, payload + i, str);
    }
}

int main() {
    RunQ = NewItem();
    RunQ->payload = 0;
    rwlock_init(&mutex); 

    generate_threads(reader, 1, "Reader", 5);
    generate_threads(writer, 1, "Writer", 1);
    generate_threads(reader, 6, "Reader", 4);
    generate_threads(writer, 2, "Writer", 2);
    generate_threads(reader, 11, "Reader", 5);
    generate_threads(writer, 4, "Writer", 1);
    generate_threads(reader, 17, "Reader", 3);

    run();
}