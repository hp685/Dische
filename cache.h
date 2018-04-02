#include <stdlib.h>


typedef struct ListNode{
  struct ListNode* next;
  char* key;
  char* value;
}ListNode;


typedef struct Cache{
  struct ListNode* head;
  struct ListNode* lastNode;
  int size;
}Cache;

void printCache(Cache*);
void insertNode(Cache* , ListNode* );
ListNode* findNode(Cache* , char* );
void setKey(Cache* , char* , char* );
char* getValue(Cache*, char* );
void deleteKey(Cache*, char* );
void printNode(ListNode*);
ListNode* findPrev(Cache* c, char* key);
int countNodes(Cache* c);
