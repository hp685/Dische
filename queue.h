#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>

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
    sem_t result_ready;

}Task;


typedef struct{

    Task* head;
    Task* tail;
    size_t size;
    pthread_mutex_t lock;
    pthread_cond_t signal_work;
    sem_t there_is_work_sem;
}Queue;



void put(Queue*, Task*);

Task* get(Queue*);

bool is_empty(Queue*);

void print_queue(Queue*);

Queue* new_queue();

Task* new_task(int);

void print_task();
