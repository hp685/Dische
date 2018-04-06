#include "queue.h"
#include "unity.h"
#include <stdio.h>
#include <stdlib.h>


void test_queue_put(){
  Queue *q = malloc(sizeof(Queue));
  Task *t = malloc(sizeof(Task));
  t->item = "SET A 1";
  put(q, t);

  TEST_ASSERT_EQUAL(q->size, 1);
  TEST_ASSERT_EQUAL(q->head,  q->tail);
  TEST_ASSERT_EQUAL(q->head->item, t->item);
  TEST_ASSERT_EQUAL(q->tail->item, t->item);
  print_queue(q);
}

void test_queue_get(){

  Queue *q = malloc(sizeof(Queue));
  Task *t = malloc(sizeof(Task));
  t->item =  "SET A 1";
  put(q, t);
  print_queue(q);
  TEST_ASSERT_EQUAL(q->size, 1);
  Task* got_item = get(q);
  TEST_ASSERT_EQUAL(got_item->item, t->item);
  TEST_ASSERT_EQUAL(q->size, 0);
  TEST_ASSERT_EQUAL(q->head, NULL);
  TEST_ASSERT_EQUAL(q->tail, NULL);
  print_queue(q);
}

void test_queue_empty_check(){
  Queue* q = new_queue();
  Task *t;
  TEST_ASSERT_EQUAL(q->size, 0);
}


void test_queue_put_concurrent(){
  Queue *q = new_queue();
  /*TODO*/

}

void test_queue_put_large_payload(){
  Queue *q = new_queue();
  Task *t = malloc(sizeof(Task));
  t->item = "funkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunk\
  funkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunk\
  funkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunk\
  funkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunk\
  funkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunk\
  funkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunk\
  funkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunk\
  funkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunk\
  funkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunk\
  funkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunk\
  funkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunk\
  funkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunk\
  funkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunk\
  funkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunkfunk";
  put(q, t);
  TEST_ASSERT_EQUAL(q->size, 1);
  TEST_ASSERT_EQUAL(get(q), t);

}

void tests_queue_put_many_items(){
  int N_ITEMS = 1000000;
  Queue* q = new_queue();
  Task *t;
  TEST_ASSERT_EQUAL(q->size, 0);
  char *query = "SET A 12321";
  for(int i = 0; i < N_ITEMS; i++){
    t = malloc(sizeof(Task));
    t->item = query;
    put(q, t);
    TEST_ASSERT_EQUAL(q->size, i+1);
  }

  for(int i = 0; i < N_ITEMS; i++){
    t = get(q);
    TEST_ASSERT_EQUAL(t->item, query);
    TEST_ASSERT_EQUAL(q->size, N_ITEMS-i-1);
  }

}


int main(){
  UNITY_BEGIN();
  RUN_TEST(test_queue_put);
  RUN_TEST(test_queue_get);
  RUN_TEST(test_queue_empty_check);
  RUN_TEST(test_queue_put_concurrent);
  RUN_TEST(test_queue_put_large_payload);
  RUN_TEST(tests_queue_put_many_items);
  UNITY_END();
  return 0;
}
