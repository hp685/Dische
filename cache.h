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

void printCache(struct Cache*);
void insertNode(struct Cache* , struct ListNode* );
struct ListNode* findNode(struct Cache* , char* );
void setKey(struct Cache* , char* , char* );
char* getValue(struct Cache*, char* );
void deleteKey(struct Cache*, char* );
void printNode(struct ListNode*);
