/* Implement a basic cache */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

void printCache(struct Cache* c){
  struct ListNode* head = c->head;
   
  while(head){
    printf("%s: %s\n", head->key, head->value);
    head = head->next;
  }
}

void addNode(struct Cache* c, struct ListNode* n){

  if (c->lastNode == NULL){
    c->head = n;
    c->lastNode = n;
  }
  else{
    c->lastNode->next = n;
    c->lastNode = n;
  }
}


struct ListNode* findNode(struct Cache* c, char* key){
  struct ListNode* head = c->head;
  while(head){
    if(strcmp(head->key, key) == 0){
      return head;
    }
    head = head->next;
  }
}




void deleteKey(struct Cache *c, char* key){
  struct ListNode* old = findNode(c, key);
  struct ListNode* toRemove;
  toRemove = old;
  toRemove = toRemove->next;
  printf("Old: %s\n", old->key);
  //printf("To Remove %s\n", toRemove->key);
  free(old);
}



void setKey(struct Cache* c, char* key, char* value){
  struct ListNode* tempNode = findNode(c, key);
  if(tempNode != NULL){
    tempNode->value = value;
    return;
  }
  struct ListNode *n = malloc(sizeof(struct ListNode));
  n->key = key;
  n->value = value;
  n->next = NULL;
  addNode(c, n);
}


char* getValue(struct Cache* c, char* key){
  struct ListNode* n = findNode(c, key);
  if(n){
    return n->value;
  }
}


int main(){
  struct Cache *c = malloc(sizeof(struct Cache));
  struct ListNode *n = malloc(sizeof(struct ListNode));
  char* key = "Foo";
  setKey(c, key, "1123");
  char* value = getValue(c, key); 
  printf("%s: %s\n", key, value);
  key = "Bar";
  setKey(c, key, "231");
  value = getValue(c, key);
  printf("%s: %s \n", key, value);
  key = "Non-existent";
  value = getValue(c, key);
  printf("%s: %s\n", key, value);
  key = "Foo";
  setKey(c, key, "1");
  value = getValue(c, key);
  printf("%s: %s\n", key, value);
  printCache(c);
  deleteKey(c, "Bar");
  printCache(c);
  return 0;
  
}
