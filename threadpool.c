
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "queue.h"
#include "threadpool.h"



void check_queue(ThreadPool* pool){
  for(;;){
    if (!is_empty(pool->work_q)){
      pthread_mutex_t* lock;
      lock = &pool->work_q->lock;
      pthread_mutex_lock(lock);
      Task* work = get(pool->work_q);
      pthread_mutex_unlock(lock);
      if(work){
        do_work(work);
      }
    }else{
      sleep(POLL_INTERVAL);
    }
  }
}

ThreadPool* create_new_pool(){

  ThreadPool* pool = (ThreadPool*) malloc(sizeof(ThreadPool));
  pool->work_q = create_new_queue();
  for (int i = 0; i < NUM_THREADS; i++){
    pthread_create(&pool->threads[i], NULL, (void*) (*check_queue), (void*) *(pool));
  }
  return pool;
}
