#include "cache.h"
#include "unity.h"



void test_cache_insert(){
  struct Cache *c = malloc(sizeof(struct Cache));
  struct ListNode *n = malloc(sizeof(struct ListNode));
  char* key;
  char* vtable[10], *ktable[10];

  ktable[0] = "A";
  ktable[1] = "B";
  ktable[2] = "C";
  vtable[0] = "1";
  vtable[1] = "STRINGY";
  vtable[2] = "FOOBAR";
  
  key = "Foo";

  for (int i = 0; i < 3; i++){
    setKey(c, ktable[i], vtable[i]);
    char *value = getValue(c, ktable[i]); 

    TEST_ASSERT_EQUAL_STRING(value, vtable[i]);  
  }
  printCache(c);
}

int main(){
  UNITY_BEGIN();
  RUN_TEST(test_cache_insert);
  UNITY_END();
  return 0;
}
