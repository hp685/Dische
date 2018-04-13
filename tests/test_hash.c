#include "hash.h"
#include "unity.h"
#include <assert.h>

void test_get_key_simple(){
    map_init();
    set("A", "1");
    TEST_ASSERT_EQUAL_STRING("1", get("A"));
    set("FOO", "BAR");
    TEST_ASSERT_EQUAL_STRING(get("FOO"), "BAR");
    set("A", "2");
    TEST_ASSERT_EQUAL_STRING("2", get("A"));
}



void test_delete_key_simple(){


}


int main(){

    UNITY_BEGIN();
    RUN_TEST(test_get_key_simple);
    RUN_TEST(test_delete_key_simple);

    UNITY_END();
    return 0;
}
