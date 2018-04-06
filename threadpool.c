
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "queue.h"

#define NUM_THREADS 1
#define POLL_INTERVAL 1

typedef struct {

  pthread_mutex_t lock;
  pthread_t threads[NUM_THREADS];
  Queue* work_q;

}ThreadPool;


void check_queue(Threadpool* pool){
  for(;;){
    if (!is_empty(pool->work_q)){
      pthread_mutex_t* lock = pool->work_q->lock;
      pthread_mutex_lock(lock));
      FuncTask* work = get(pool->work_q);
      pthread_mutex_unlock(lock);
      if(work){
        work->function(work->argument);
      }
    }else{
      sleep(POLL_INTERVAL);
    }
  }
}

ThreadPool* create_new_pool(){

  ThreadPool* pool = malloc(sizeof(ThreadPool));
  pool->work_q = create_new_queue();
  for (int i = 0; i < NUM_THREADS; i++){
    pthread_create(&threads[i], NULL, (void*) do_work, (void*) pool);

  }
}
