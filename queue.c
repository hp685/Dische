#include "queue.h"


void put(Queue* q, Task* t){

  pthread_mutex_lock(q->lock);
  q->size++;

  if (q.is_empty()){
    q->head = t;
    t->next = NULL;
    q->tail = t;
  }else{
    q->tail->next = t;
    t->next = NULL;
    q->tail = t;
  }
  pthread_mutex_unlock(q->lock);
}


Task* get(Queue* q){
  Task* top = q->head;
  pthread_mutex_lock(q->lock);
  if(!q.is_empty()){
    top = q->head;
    if (q->tail == q->head){ /*In case we are the last item*/
      q->tail = q->tail->next;
    }
    q->head = q->head->next;
    q->size--;
    assert (q->size >= 0);
  }
  pthread_mutex_unlock(q->lock);
  return top;
}


bool is_empty(Queue* q){
  if (q->size){
    return true;
  }
  return false;
}
