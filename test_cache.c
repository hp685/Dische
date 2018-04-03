#include <stdio.h>
#include <stdlib.h>
#include "cache.h"
#include "unity.h"



void test_cache_insert(){
  Cache* c = malloc(sizeof(Cache));
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


void test_cache_delete(){
  Cache* c = malloc(sizeof(Cache));
  setKey(c, "A", "FOO");
  setKey(c, "B", "BAR");
  setKey(c, "C", "ME");
  deleteKey(c, "B");
  TEST_ASSERT_EQUAL(getValue(c, "B"), NULL);
  printCache(c);
  setKey(c, "B", "BAR");
  printCache(c);
  deleteKey(c, "B");
  printCache(c);
}


void test_cache_overwrite_value(){
  Cache* c = malloc(sizeof(Cache));
  setKey(c, "A", "DAFT");
  TEST_ASSERT_EQUAL(getValue(c, "A"), "DAFT");
  setKey(c, "B", "SKUNK");
  TEST_ASSERT_EQUAL(getValue(c, "B"), "SKUNK");
  setKey(c, "A", "PUNK");
  TEST_ASSERT_EQUAL(getValue(c, "A"), "PUNK");
  printCache(c);
}

void test_find_node(){
  Cache* c = malloc(sizeof(Cache));
  setKey(c, "A", "FIZZLE");
  TEST_ASSERT_EQUAL(getValue(c, "A"), "FIZZLE");
  setKey(c, "B", "DRIZZLE");
  TEST_ASSERT_EQUAL(getValue(c, "B"), "DRIZZLE");
  setKey(c, "C", "SIZZLE");
  TEST_ASSERT_EQUAL(getValue(c, "C"), "SIZZLE");
  TEST_ASSERT_TRUE(getValue(c, "Z") == NULL);

}


void test_find_prev(){
  Cache* c = malloc(sizeof(Cache));
  setKey(c, "A", "FIZZLE");
  TEST_ASSERT_EQUAL(getValue(c, "A"), "FIZZLE");
  setKey(c, "B", "DRIZZLE");
  TEST_ASSERT_EQUAL(getValue(c, "B"), "DRIZZLE");
  setKey(c, "C", "SIZZLE");
  ListNode* prev = findPrev(c, "B");
  TEST_ASSERT_EQUAL(prev->key, "C");
  TEST_ASSERT_EQUAL(prev->value, "SIZZLE");
  prev = findPrev(c, prev->key);
  TEST_ASSERT_EQUAL(prev, NULL);

}

void test_insert_10k_items(){
  Cache* c = malloc(sizeof(Cache));
  char *key , *value;
  for(int i = 0; i < 10000; i++){
    key = malloc(sizeof(char*));
    value = malloc(sizeof(char *));
    sprintf(key, "%d", i);
    sprintf(value, "%d", i);
    setKey(c, key, value);
    TEST_ASSERT_EQUAL(getValue(c,key), value);
  }
  TEST_ASSERT_EQUAL(countNodes(c), 10000);
}



int main(){
  UNITY_BEGIN();
  RUN_TEST(test_cache_insert);
  RUN_TEST(test_cache_delete);
  RUN_TEST(test_cache_overwrite_value);
  RUN_TEST(test_find_node);
  RUN_TEST(test_find_prev);
  RUN_TEST(test_insert_10k_items);
  UNITY_END();
  return 0;
}
