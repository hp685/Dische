#include "queue.h"
#include <assert.h>
#include <stdbool.h>


void put(Queue* q, Task* t){

    pthread_mutex_lock(&q->lock);


    if (is_empty(q) == true){

        q->head = t;
        q->tail = t;
        t->next = NULL;
        q->size++;

    }else{

        q->tail->next = t;
        t->next = NULL;
        q->tail = t;
        q->size++;
    }

    pthread_mutex_unlock(&q->lock);

}


Task* get(Queue* q){
    
    Task* top = q->head;
    
    pthread_mutex_lock(&q->lock);
    
    if(!is_empty(q)){

        top = q->head;
        
        if (q->size == 1){ /*In case we are the last item*/
            q->tail = q->tail->next;
        }

        q->head = q->head->next;
        q->size--;
        
        assert(q->size >= 0);
    }

    pthread_mutex_unlock(&q->lock);
  
    return top;
}


bool is_empty(Queue* q){

    if (q->size){

        return false;
    }

    return true;
}


void print_queue(Queue* q){

    Task* t = q->head;
    
    while (t){
        printf("%s->", t->item);
        t = t->next;
    }
    puts("\n");
}


Queue* new_queue(){
    
    Queue* q = (Queue*) malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;

}


Task* new_task(int fd){

    Task* task = (Task*) malloc(sizeof(Task));
    task->fd = fd;
    task->item = NULL;
    task->next = NULL;
    task->result = NULL;
    task->function = NULL;
    task->argument = NULL;
    task->state = "NEW";
  
    return task;
}

