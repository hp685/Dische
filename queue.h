#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include "cache.h"

typedef struct Task{
    char* item;
    struct Task* next;
}Task;

typedef struct Queue{
  Task* head;
  Task* tail;
  size_t size;
  pthread_mutex_t lock;
}Queue;

void put(Queue*, Task*);
Task* get(Queue*);
bool is_empty(Queue*);
void print_queue(Queue*);
Queue* new_queue();
