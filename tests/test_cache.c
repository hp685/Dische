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
    TEST_ASSERT_EQUAL_STRING(get("FOO"), "BAR");
}

void test_many_set(){
    init_cache();
    char* s = malloc(sizeof(char) * 7);
    for (int i = 0; i < 10; i++){
        sprintf(s, "%d", i);
        set(s, s);
    }
    for (int i = 0; i < 10; i++){
        sprintf(s, "%d", i);
        TEST_ASSERT_EQUAL_STRING(get(s), s);
    }
}


void test_delete_key_simple(){

  init_cache();
  set("FOO", "BAR");
  TEST_ASSERT_EQUAL_STRING(get("FOO"), "BAR");
  delete("FOO");
  TEST_ASSERT_EQUAL(get("FOO"), NULL);

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
