#include "hash.h"
#include "unity.h"
#include <assert.h>

void setUp(){
    map_init();
}

void tearDown(){
    destroy_map();
}

void test_get_key_simple(){
    set("A", "1");
    TEST_ASSERT_EQUAL_STRING("1", get("A"));
    set("FOO", "BAR");
    TEST_ASSERT_EQUAL_STRING(get("FOO"), "BAR");
    set("A", "2");
    TEST_ASSERT_EQUAL_STRING("2", get("A"));
}



void test_delete_key_simple(){

    set("A", "1");
    TEST_ASSERT_EQUAL_STRING(get("A"), "1");
    delete("A");
    TEST_ASSERT_EQUAL(get("A"), NULL);
}


void test_insert_multiple_to_same_slot_and_delete(){

    set("A", "1");
    set("B", "2");
    set("C", "42");
    set("D", "4");
    TEST_ASSERT_EQUAL_STRING(get("D"), "4");
    delete("D");
    TEST_ASSERT_EQUAL(get("D"), NULL);
    TEST_ASSERT_EQUAL_STRING(get("A"), "1");
    TEST_ASSERT_EQUAL_STRING(get("B"), "2");
    delete("B");
    TEST_ASSERT_EQUAL(get("B"), NULL);
    TEST_ASSERT_EQUAL_STRING(get("C"), "42");

}


int main(){

    UNITY_BEGIN();
    RUN_TEST(test_get_key_simple);
    RUN_TEST(test_delete_key_simple);
    RUN_TEST(test_insert_multiple_to_same_slot_and_delete);
    UNITY_END();
    return 0;
}
