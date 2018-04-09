
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "threadpool.h"


void check_queue(ThreadPool* pool){
  /*
  Check queue, process work items if acquired until signaled to shutdown.
  */
    for(;;){

        // if (pthread_cond_wait(&pool->work_q->signal_work, &pool->work_q->lock) != 0){
        //
        //     perror("Condition 'signal_work' wait failure!");
        //     exit(EXIT_FAILURE);
        // }

        Task* work = get(pool->work_q);

        if (work == NULL){
            sleep(POLL_INTERVAL);
            continue;
        }

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


    }
}


ThreadPool* create_new_pool(){
    /*
    Create and return a pool instance with threads executing check_queue
    function indefinitely.
    */
    ThreadPool* pool = (ThreadPool*) malloc(sizeof(ThreadPool));
    pool->work_q = new_queue();

    if(pthread_mutex_init(&pool->work_q->lock, NULL) != 0){

        perror("Error initializing work q lock!");
        exit(EXIT_FAILURE);
    }


    if (pthread_cond_init(&pool->work_q->signal_work, NULL) != 0){

        perror("Error initializing signaling work condition!");
        exit(EXIT_FAILURE);
    }



    for (int i = 0; i < NUM_THREADS; i++){

        pthread_create(&pool->threads[i], NULL, check_queue, (void*)pool);
    }

    return pool;
}


void shutdown_pool(ThreadPool* pool){
/*
    Graceful shutdown.
*/

}


void terminate_pool(ThreadPool* pool){
/*
    Force clean-up of pool.
*/

}
