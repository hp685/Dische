#include <stdio.h>
#include <pthread.h>
#include "cache.h"

struct Task{
    char* item;
    Task* next;
};

typedef struct Queue{
  Task* head;
  Task* tail;
  size_t size;
  pthread_mutex_t lock;
}Queue;

void put(Queue*, Task*);
Task* get(Queue*, Task*);
void is_empty(Queue*);
