
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "threadpool.h"


void check_queue(ThreadPool* pool){
  for(;;){

    if (!is_empty(pool->work_q)){
      pthread_mutex_t* lock;
      lock = &pool->work_q->lock;
      Task* work = get(pool->work_q);
      if(work){
        work->state = PROCESSING;
        void* (*fun_ptr)(void*) = work->function;
        work->result = (*fun_ptr)(work->argument);
        work->state = COMPLETED;
      }
    }else{
      sleep(POLL_INTERVAL);
    }
  }
}

ThreadPool* create_new_pool(){

  ThreadPool* pool = (ThreadPool*) malloc(sizeof(ThreadPool));
  pool->work_q = new_queue();
  for (int i = 0; i < NUM_THREADS; i++){
    pthread_create(&pool->threads[i], NULL, check_queue, (void*)pool);
  }
  return pool;
}
