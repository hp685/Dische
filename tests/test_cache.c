#include "unity.h"
#include "cache.h"



void test_init_cache(){
    init_cache();
    puts("CC");
    printf("%ld", __c->size);
    puts("DD");
    printf("%ld", __c->buckets[0]->size);
    //TEST_ASSERT_EQUAL(__c->buckets[0]->head->next, NULL);
    //TEST_ASSERT_EQUAL(__c->buckets[0]->head->key, NULL);
    //TEST_ASSERT_EQUAL(__c->buckets[0]->head->value, NULL);

}

int main(){
    UNITY_BEGIN();
    RUN_TEST(test_init_cache);
    UNITY_END();
    return 0;
}
