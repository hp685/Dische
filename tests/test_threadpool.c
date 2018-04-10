#include "threadpool.h"
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "tests.h"

#define DUMMY_FD 0
#define BLOCK_UNTIL_DONE(work) {sem_wait(&work->result_ready);}
#undef NUM_THREADS
#define NUM_THREADS 10

int square(int n){
    return n*n;
}


char *reverse(char *str){

    int i = strlen(str) - 1, j = 0;
    char ch;
    while (i > j){

        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        i--;
        j++;
    }

    return str;
}


void test_work_square_int(){
    ThreadPool* pool = create_new_pool();
    Task* work = new_task(DUMMY_FD);

    work->function = &square;
    work->argument = (int*) 2;
    put(pool->work_q, work);

    BLOCK_UNTIL_DONE(work);

    TEST_ASSERT_EQUAL(work->result, 4);

}


void test_work_reverse_string(){

    ThreadPool *pool = create_new_pool();
    Task* work = new_task(DUMMY_FD);
    work->function = &reverse;
    char* arg = "VIENNA";
    work->argument = malloc(sizeof(arg)+1);
    strcpy(work->argument, arg);
    put(pool->work_q, work);
    BLOCK_UNTIL_DONE(work);

    TEST_ASSERT_EQUAL_STRING(work->argument, "ANNEIV");
}


void test_work_square_int_multiple(){

    ThreadPool* pool = create_new_pool();
    Task* work[100];

    for (int i = 0; i < 100; i++){

        work[i] = new_task(DUMMY_FD);
        work[i]->function = &square;
        work[i]->argument = i;
        put(pool->work_q, work[i]);
    }

    for(int i = 0; i < 100; i++){

        BLOCK_UNTIL_DONE(work[i]);
        TEST_ASSERT_EQUAL(work[i]->result, i*i);
    }
}


void_test_terminate_pool(){



}



int main(){
    puts("-------------------------------Thread Pool tests-----------------------------\n");
    UNITY_BEGIN();

    RUN_TEST(test_work_square_int);
    RUN_TEST(test_work_reverse_string);
    RUN_TEST(test_work_square_int_multiple);

    UNITY_END();

    return 0;
}
