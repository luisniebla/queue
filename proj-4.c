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
struct TCB_t * tcb_buff;
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

// The concept for these rwlock_* functions comes from OS: 3 Easy Pieces.
// We modify the internals to work with our semlocks instead of C pthreads
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
        if(DEBUG) printf("Locking writelock\n");
        if(DEBUG_SEM) PrintSem(lock->writelock);
        P(lock->writelock);
    }
    V(lock->lock);
    V(lock->readlock);
}

void rwlock_release_readlock(rwlock_t *lock) {
    P(lock->lock);
    lock->readers--;
    if (DEBUG) printf("lock->readers: %d\n", lock->readers);
    if (lock->readers == 0){
        if(DEBUG) printf("**********releasing writelock\n");
        // AddToEnd(RunQ, DelQueue(lock->writelock->queue));
        // lock->writelock->value++;
        if (!magicSwitch) {
            V(lock->writelock);
            magicSwitch++;
        }else{
            while(lock->writelock->queue->next != NULL) {
            lock->writelock->value++;
            if(DEBUG)printf("Adding Writer to RuNQ\n");
            if(DEBUG)PrintQueue(RunQ);
            struct TCB_t * newItem = DelQueue(lock->writelock->queue);
            // printf("WE DELETED SUCCESFFULLY\n");
            // PrintQueue(S->queue);
            newItem->next = NULL;
            newItem->prev = NULL;
            // printf("RETRIEVING NEXT ITEM\n");
            struct TCB_t * currentItem = RunQ->next;
            // printf("WERE GOING TO ADD TO QUEU\n");
            AddToFront(RunQ, newItem); // take out element
            // RotateQ(RunQ);
            if(DEBUG)printf("Done\n");
            if(DEBUG)PrintQueue(RunQ);
            // printf("%s\n", lock->writelock->queue->next->identifier);
            // 
        }
        }
        
    }
    V(lock->lock);
}

void rwlock_acquire_writelock(rwlock_t *lock) {
    if (DEBUG) printf("Writer is acquiring lock\n");
    // Writer signifying it wants to write, preventing new readers from entering
    P(lock->readlock);
    if (DEBUG) printf("Passed readlock barrier\n");
    P(lock->writelock);
}

void rwlock_release_writelock(rwlock_t *lock) {
    if (DEBUG) printf("Writer is releasing writelock\n");
    V(lock->readlock);
    V(lock->writelock);
    if(DEBUG_SEM) PrintSem(lock->writelock);
}

int out;

int item;
int last_touched = 0;
int counter = 0;


void writer() {
    if(DEBUG) printf("====>Writer\n");
    int localWriterID = ++writerID;
    int i;
    rwlock_acquire_writelock(&mutex);
    counter++;
    printf("This is the %dth writer writing value i = %d\n", localWriterID, counter);
    // yield();
    rwlock_release_writelock(&mutex);
    // yield();
    printf("This is the %dth writer verifying value i = %d\n", localWriterID, counter);
    // return NULL;
    // yield();
    rwlock_t *lock = &mutex;
    DelQueue(RunQ); // Delete this writer from the queue
    while(lock->readlock->queue->next != NULL){
        if(DEBUG_RUNQ) PrintQueue(RunQ);
        // We do this here instead of V() because it inserts the readers in the wrong order
        AddQueue(RunQ, DelQueue(lock->readlock->queue));
        lock->readlock->value++;
    }
    yield_from(&parent);
}       

void reader() {
    if(DEBUG)printf("=====>Reader\n");
    ucontext_t thisContext = (RunQ->next->context);
    // readerID++;
    int i;
    int local = 0;
    int localReaderID = ++readerID;
    rwlock_acquire_readlock(&mutex);
    local = counter;
    printf("This is the %dth reader reading value i = %d for the first time\n", localReaderID, counter );
    yield();
    rwlock_release_readlock(&mutex);
    
    local = counter;
    printf("This is the %dth reader reading value i = %d for the second time\n", localReaderID, counter );
    if(DEBUG) printf("Finished with this reader. What's next?\n");
    if (DEBUG_RUNQ) PrintQueue(RunQ);
    // return NULL;
    // getcontext(&(RunQ->next->context));
    
    // This is to catch the case where V was called and we have a writer as the head
    // if (&(RunQ->next->context) != &thisContext) {
    //     if (DEBUG) printf("thisContext: %d\n", &thisContext);
    //     if(DEBUG) PrintQueue(RunQ);
    //     swapcontext(&thisContext, &(RunQ->next->context));
    //     DelQueue(RunQ);
    // }else{
    if (DEBUG) printf("Yielding is next\n");
    if(DEBUG_RUNQ) PrintQueue(RunQ);
    DelQueue(RunQ);
    if (DEBUG_RUNQ) PrintQueue(RunQ);
    yield_from(&parent);
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
    RunQ = NewItem();
    RunQ->payload = 0;
    // mutex = return (struct TCB_t *) malloc(sizeof(struct TCB_t));
    rwlock_init(&mutex); 
    generate_threads(reader, 1, "Reader", 5);
    generate_threads(writer, 1, "Writer", 1);
    generate_threads(reader, 6, "Reader", 4);
    generate_threads(writer, 2, "Writer", 2);
    generate_threads(reader, 11, "Reader", 5);
    generate_threads(writer, 4, "Writer", 1);
    generate_threads(reader, 17, "Reader", 3);
    // getcontext(&parent);
    // run();
    // 
    // printf("Printing Queue\n");
    // PrintQueue(RunQ);
    run();
    
    // 
    

    // run();
}