#include "unity.h"
#include "cache.h"




void test_init_cache(){
    init_cache();
    TEST_ASSERT_EQUAL(__c->buckets[0].head->next, NULL);
    TEST_ASSERT_EQUAL(__c->buckets[0].head->key, NULL);
    TEST_ASSERT_EQUAL(__c->buckets[0].head->value, NULL);

}

void test_set_simple(){
    init_cache();
    set("FOO", "BAR");
    TEST_ASSERT_EQUAL_STRING(get("FOO"), "BAR");
}

void test_many_set(){
    init_cache();
    char* s = malloc(sizeof(char) * 5);
    for (int i = 0; i < 10000; i++){
        sprintf(s, "%d", i);
        set(s, s);
    }
    for (int i = 0; i < 10000; i++){
        sprintf(s, "%d", i);
        TEST_ASSERT_EQUAL(get(s), s);
    }
}



int main(){
    UNITY_BEGIN();
    RUN_TEST(test_init_cache);
    RUN_TEST(test_set_simple);
    RUN_TEST(test_many_set);
    UNITY_END();
    return 0;
}
