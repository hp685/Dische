#include <stdlib.h>


struct ListNode{
  struct ListNode* next;
  char* key;
  char* value;
};


struct Cache{
  struct ListNode* head;
  struct ListNode* lastNode;
  int size;
};

void printCache(struct Cache* c);
void insertNode(struct Cache* c, struct ListNode* n);
struct ListNode* findNode(struct Cache* c, char* key);
void setKey(struct Cache* c, char* key, char* value);
char* getValue(struct Cache* c, char* key);
