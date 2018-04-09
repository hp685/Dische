#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

#define PROCESSING "PROCESSING"
#define NEW "NEW"
#define COMPLETED "COMPLETED"



typedef struct Task{

    void* function;
    void* argument;
    struct Task* next;
    char* item;
    int fd ; /*File descriptor of the client*/
    void* result;
    char* state;

}Task;


typedef struct{

    Task* head;
    Task* tail;
    size_t size;
    pthread_mutex_t lock;
    pthread_cond_t signal_work;
}Queue;



void put(Queue*, Task*);

Task* get(Queue*);

bool is_empty(Queue*);

void print_queue(Queue*);

Queue* new_queue();

Task* new_task(int);

void print_task();
