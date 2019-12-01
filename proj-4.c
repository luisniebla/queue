// Luis Guillermo Niebla Rios

#include "sem.h"

struct TCB_t * RunQ;
struct TCB_t * touchedHistory;
#define DEBUG 0 
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
    int readers;
} rwlock_t;

rwlock_t mutex;

// The concept for these rwlock_* functions comes from OS: 3 Easy Pieces.
// We modify the internals to work with our semlocks instead of C pthreads
void rwlock_init(rwlock_t * lock) {
    lock->readers = 0;
    lock->lock = (struct sem *) malloc(sizeof(struct sem));
    lock->writelock = (struct sem *) malloc(sizeof(struct sem));
    InitSem((lock->lock), 1, "lock");
    InitSem((lock->writelock), 1, "writelock"); 
}

void rwlock_acquire_readlock(rwlock_t *lock) {
    P(lock->lock);
    lock->readers++;
    if (lock->readers == 1) {
        printf("Locking writelock\n");
        P(lock->writelock);
    }
    V(lock->lock);
}

void rwlock_release_readlock(rwlock_t *lock) {
    P(lock->lock);
    lock->readers--;
    if (lock->readers == 0){
        // printf("releasing writelock\n");
        V(lock->writelock);
    }
       
    V(lock->lock);
}

void rwlock_acquire_writelock(rwlock_t *lock) {
    P(lock->writelock);
}

void rwlock_release_writelock(rwlock_t *lock) {
    V(lock->writelock);
}

int out;

int item;
int last_touched = 0;
int counter = 0;


void writer() {
    writerID++;
    int i;
    rwlock_acquire_writelock(&mutex);
    counter++;
    printf("This is the %dth writer writing value i = %d\n", writerID, counter);
    yield();
    rwlock_release_writelock(&mutex);
    // yield();
    printf("This is the %dth writer verifying value i = %d\n", writerID, counter);
    // return NULL;
    // yield();
}

void reader() {
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

    // return NULL;
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
    RunQ = NewItem();
    RunQ->payload = 0;
    // mutex = return (struct TCB_t *) malloc(sizeof(struct TCB_t));
    rwlock_init(&mutex); 
    generate_threads(reader, 1, "Reader", 5);
    generate_threads(writer, 1, "Writer", 1);
    // getcontext(&parent);
    // run();
    // 
    // printf("Printing Queue\n");
    // PrintQueue(RunQ);
    run();
    // generate_threads(reader, 6, "Reader", 4);
    // generate_threads(writer, 2, "Writer", 2);
    // generate_threads(reader, 11, "Reader", 5);
    // generate_threads(writer, 4, "Writer", 1);
    // generate_threads(reader, 17, "Reader", 3);

    // run();
}