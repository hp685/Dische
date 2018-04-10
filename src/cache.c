/* Implement a basic cache */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "cache.h"



void insertNode(Cache* c, ListNode* n){

    n->next = c->head;
    c->head = n;
}


ListNode* findPrev(Cache* c, char* key){
    
    ListNode* head = c->head;

    while (head){
    
        if (head->next == NULL){
            return NULL;
        }
        if (strcmp(head->next->key, key) == 0){
            return head;
        }
        
        head = head->next;
    }

}


ListNode* findNode(Cache* c, char* key){

    ListNode* head = c->head;

    while(head){

        if(strcmp(head->key, key) == 0){
            return head;
        }

        head = head->next;
    }

    return NULL;
}


void deleteKey(Cache *c, char* key){
  
    ListNode* prev = findPrev(c, key);
    ListNode* toRemove;
    toRemove = findNode(c, key);

    if (toRemove == NULL){  /* Key doesn't exist */
        return;
    }
  
    else if(prev == NULL){
        c->head = c->head->next;
    }
  
    else{
        prev->next = prev->next->next;
    }
  
    free(toRemove);

}


void setKey(Cache* c, char* key, char* value){
  
    ListNode* tempNode = findNode(c, key);
    
    if(tempNode != NULL){
        
        tempNode->value = value;
        return;
    }

  
    ListNode *n = malloc(sizeof(ListNode));
    n->key = key;
    n->value = value;
    n->next = NULL;  
    insertNode(c, n);

}


char* getValue(Cache* c, char* key){

    ListNode* n = findNode(c, key);
    if(n){
        return n->value;
    }
}


void printNode(ListNode* n){
    
      printf(" %s = %s", n->key, n->value);
}


void printCache(Cache* c){
 
    ListNode* head = c->head;
    printf("--------------------------------\n");
    
    while(head){
        
        printf("(%s, %s)-->", head->key, head->value);
        head = head->next;
    }
    assert(head == NULL);
    printf("%s\n", "NULL");
    printf("================================\n");

}


int countNodes(Cache* c){

    ListNode* head = c->head;
    int count = 0;
    while(head){
    
        head = head->next;
        count++;
    
    }
    return count;

}
