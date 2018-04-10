#include <pthread.h>
#include "queue.h"

#define NUM_THREADS 1
#define POLL_INTERVAL 1

typedef struct {

 	pthread_mutex_t lock;
    pthread_t threads[NUM_THREADS];
    Queue* work_q;

}ThreadPool;


void check_queue(ThreadPool*);

ThreadPool* create_new_pool();
