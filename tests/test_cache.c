#include "unity.h"
#include "cache.h"




void test_init_cache(){
    init_cache();
    TEST_ASSERT_EQUAL(__c->buckets[0]->head, NULL);
    TEST_ASSERT_EQUAL(__c->buckets[0]->head, NULL);
    TEST_ASSERT_EQUAL(__c->buckets[0]->head, NULL);

}


void test_set_simple(){
    init_cache();
    set("FOO", "BAR");
    TEST_ASSERT_EQUAL_STRING("BAR", get_value("FOO"));
}


void test_many_set(){

    init_cache();
    char* s = malloc(sizeof(char) * 10);
    int NUM_KEYS = 10000;
    for (int i = 0; i < NUM_KEYS; i++){
        sprintf(s, "%d", i);
        set(s, s);
    }

    for (int i = 0; i < NUM_KEYS; i++){
        sprintf(s, "%d", i);
        TEST_ASSERT_EQUAL_STRING(s, get_value(s));
    }

    for(int i = 0; i < NUM_KEYS; ++i){
        sprintf(s, "%d", i);
        delete(s);
        TEST_ASSERT_EQUAL(NULL, get_value(s));
    }

}


void test_delete_key_simple(){

  init_cache();
  set("FOO", "BAR");
  TEST_ASSERT_EQUAL_STRING(get_value("FOO"), "BAR");
  delete("FOO");
  puts("---------------");
  TEST_ASSERT_EQUAL(get_value("FOO"), NULL);

}


int main(){
    UNITY_BEGIN();
    RUN_TEST(test_init_cache);
    RUN_TEST(test_set_simple);
    RUN_TEST(test_many_set);
    RUN_TEST(test_delete_key_simple);
    UNITY_END();
    return 0;
}
