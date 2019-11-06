#include "sem.h"

struct TCB_t * RunQ;
struct TCB_t * touchedHistory;

ucontext_t uctx_main;
ucontext_t parent;
struct sem * empty;
struct sem * full;
struct sem * mutex;
int buffer;
struct TCB_t * tcb_buff;
int buff[5];
int fill = 0;
int use = 0;

void put(int value) {
    buff[fill] = value;
    if (buff[fill] != 0){
        // printf("=====Fuckedup=====\n");
    }
    fill = (fill + 1) % 6;
}

int get() {
    int tmp = buff[use];
    buff[use] = 0;
    use = (use + 1) % 6;
    return tmp;
}

int out;
int in;
int item;
int last_touched = 0;



void producer_1() {
    while(1) {
        // printf("==This is Producer 1\n");
        P(empty);
        P(mutex);
        put(in++);
        V(mutex);
        V(full);
        // struct TCB_t * thisRecord = NewItem();
        // thisRecord->payload = 1;
        // AddQueue(touchedHistory, thisRecord);
        // PrintQueue(touchedHistory);
        printf("This is producer producing item number %d\n", in - 1);
        printf("out: %d %d %d %d %d %d\n", buff[0], buff[1], buff[2], buff[3], buff[4], buff[5]);
        yield();
    }
}
void producer_2() {
    while(1) {
        P(empty);
        P(mutex);
        put(in++);
        V(mutex);
        V(full);
        struct TCB_t * thisRecord = NewItem();
        thisRecord->payload = 2;
        AddQueue(touchedHistory, thisRecord);
        // PrintQueue(touchedHistory);
        printf("This is producer 2 producing item number %d\n", in - 1);
        // printf("out: %d %d %d %d %d %d\n", buff[0], buff[1], buff[2], buff[3], buff[4], buff[5]);
        sleep(1);
        yield();
    }
}

void consumer_1() {
    while(1) {
        // printf(">Entering consumer %d\n", RunQ->next->payload);
        P(full);
        P(mutex);
        int tmp = get();
        V(mutex);
        V(empty);
        // buffer--;
        // struct TCB_t * lastTouch = DelQueue(touchedHistory);
        printf(">This is consumer %d consuming %d\n", RunQ->next->payload, tmp);
        // printf("out: %d %d %d %d %d %d\n", buff[0], buff[1], buff[2], buff[3], buff[4], buff[5]);
        sleep(1);
        yield();
    }
}

int main() {
    tcb_buff = NewItem();
    out = 0;
    in = 1;
    touchedHistory = NewItem();
    touchedHistory->payload = 0;
    empty = (struct sem *) malloc(sizeof(struct sem));
    mutex = (struct sem *) malloc(sizeof(struct sem));
    full = (struct sem *) malloc(sizeof(struct sem));
    InitSem(empty, 6, "empty");
    empty->queue = NewItem();
    InitSem(mutex, 1, "mutex");
    mutex->queue = NewItem();
    InitSem(full, 0, "full");
    printf("did it work %d\n", mutex->value);
    PrintSem(full);
    full->queue = NewItem();
    RunQ = NewItem();
    RunQ->payload = 0;
    start_thread(consumer_1, 1);
    start_thread(producer_1, 2);
    start_thread(consumer_1, 3);
    // start_thread(consumer_1, 2);
    // start_thread(producer_1, 2);
    // start_thread(producer_1, 2);
    // start_thread(producer_1, 2);
    // start_thread(producer_1, 2);
    // start_thread(producer_1, 2);
    // start_thread(producer_1, 2);
    // start_thread(producer_1, 2);
    // start_thread(consumer_1, 2);
    // start_thread(consumer_1, 2);
    // start_thread(consumer_1, 2);
    // start_thread(consumer_1, 2);
    // start_thread(consumer_1, 2);
    // start_thread(consumer_1, 2);
    // start_thread(consumer_1, 2);
    // start_thread(producer_1, 2);
    // start_thread(producer_1, 2);
    // start_thread(producer_1, 2);

    // PrintQueue(RunQ);
    // sleep(5);
    run();

}