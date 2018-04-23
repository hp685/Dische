#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>
#include "queue.h"

#define NUM_THREADS 1
#define POLL_INTERVAL 1

typedef struct {

    size_t num_threads;
    size_t num_exited;
    size_t num_running;
 	  pthread_mutex_t lock;
    pthread_t threads[NUM_THREADS];
    Queue* work_q;
    bool should_exit;
}ThreadPool;


void check_queue(ThreadPool*);

ThreadPool* create_new_pool();

void shutdown_pool();

void terminate_pool();
