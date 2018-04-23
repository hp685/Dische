
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <semaphore.h>
#include "threadpool.h"



void check_queue(ThreadPool* pool){
  /*
  Check queue, process work items if acquired until signaled to shutdown.
  */
    for(;;){

        sem_wait(&pool->work_q->unblock_sem);

        /*Exit check*/
        if (pool->should_exit)
        {
          pthread_mutex_lock(&pool->lock);
          pool->num_exited++;
          pthread_mutex_unlock(&pool->lock);
          break;
        }
        Task* work = get(pool->work_q);


        work->state = PROCESSING;
        /* Lookup task's function referenced by fun_ptr pointer accepting
         one argument of void*.
        */
        void* (*fun_ptr)(void*) = work->function;

        /* Call function pointed by fun_ptr with its argument
        and assign the return value to result.
        Note: Implicit conversion of void* to used defined type and back
        from user defined type to char* for the result.
        */
        work->result = (*fun_ptr)(work->argument);
        work->state = COMPLETED;
        sem_post(&work->result_ready);


    }
}


ThreadPool* create_new_pool(){
    /*
    Create and return a pool instance with threads executing check_queue
    function indefinitely.
    */
    ThreadPool* pool = (ThreadPool*) malloc(sizeof(ThreadPool));
    pool->work_q = new_queue();
    pool->should_exit = false;
    pool->num_threads = NUM_THREADS;
    pool->num_exited = 0;

    if(pthread_mutex_init(&pool->work_q->lock, NULL) != 0){

        perror("Error initializing work q lock!");
        exit(EXIT_FAILURE);
    }

    sem_init(&pool->work_q->unblock_sem, 0, 0);

    if (pthread_cond_init(&pool->work_q->signal_work, NULL) != 0){

        perror("Error initializing signaling work condition!");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_THREADS; i++){

        pthread_create(&pool->threads[i], NULL, check_queue, (void*)pool);
        pool->num_running++;
    }

    return pool;
}


void shutdown_pool(ThreadPool* pool){
/*
    Graceful shutdown.
*/
  pool->should_exit = true;

  do{
    sem_post(&pool->work_q->unblock_sem);

  }while(pool->num_exited != pool->num_threads);


  for(int i = 0; i < NUM_THREADS; i++){

      pthread_join(&pool->threads[i], NULL);
  }
}


void terminate_pool(ThreadPool* pool){
/*
    Force clean-up of pool.
*/

}
