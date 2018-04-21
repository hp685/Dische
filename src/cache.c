#include <malloc.h>
#include <string.h>
#include "cache.h"
#define MULTIPLIER 61


unsigned long hash(char* s){

    unsigned long h;
    unsigned char* us;
    s += '\0';
    us = (unsigned char* ) s;
    h = 0;
    for(int i = 0; i < strlen(us); i++){
        h = h * MULTIPLIER + us[i];
    }

    return h;
}


unsigned long get_index(void* key){

    unsigned long index;
    unsigned long hash_code = hash((char*)key);

    index = hash_code % MAX_BUCKETS;
    return index;

}


void set(void* key, void* value){

    unsigned int index = get_index(key);
    Data* head = __c->buckets[index]->head;

    if (__c->buckets[index]->head == NULL){
        __c->buckets[index]->head = malloc(sizeof(Data));
        set_node(__c->buckets[index]->head, key, value);
        return;
    }

    else{
        Data* node = head;
        while(node->next != NULL){
            if (strcmp(node->key, key) == 0){
              node->value = value;
              return;
            }

            node = node->next;
            if (node != NULL){
              puts(node->key);
          }
        }
        node = node->next;
        node = (Data*) malloc(sizeof(Data));
        set_node(node, key, value);
        node->next = NULL;

    }
}


void* get(void* key){

    unsigned int index = get_index(key);
    Data* head = __c->buckets[index]->head;
    /*TODO why is head not null here?*/
    if (head && head->key == NULL){
      return NULL;
    }

    else if (strcmp(head->key, key) == 0){
        return head->value;
    }
    else{

        Data* node = head;
        while(node->next){
            node = node->next;
            if (strcmp(node->key, key) == 0){
                return node->value;
            }
        }
    }
    return NULL;
}



void delete(void* key){

  unsigned int index = get_index(key);
  Data* head = __c->buckets[index]->head;
  Data* to_free;
  to_free = NULL;

  if (strcmp(head->key, key) == 0){
      to_free = head;
      head = NULL;
      free(to_free->key);
      free(to_free->value);
      free(to_free);
      return;
  }
  while(head->next != NULL){

      if (strcmp(head->next->key, key) == 0 ){

          if (head->next->next != NULL){
              to_free = head->next;
              head->next = head->next->next;

          }
          else{
            to_free = head->next;
            head->next = NULL;

          }
        }

      head = head->next;
    }

    if (to_free != NULL) {
      free(to_free);
    }
}

void set_node(Data* head, void* key, void* value){

    head->key = malloc(sizeof(void*));
    head->value = malloc(sizeof(void*));
    strcpy(head->key, key);
    strcpy(head->value, value);
}



void init_cache(){

    unsigned int i;
    __c = (Cache*) malloc(sizeof(Cache));
    __c->size = MAX_BUCKETS;
    __c->buckets =  malloc((__c->size) * sizeof(Bucket*));

    for (i = 0; i < __c->size; ++i){
        __c->buckets[i] = malloc(sizeof(Bucket));
        __c->buckets[i]->head = NULL;

    }

}

//
// void print_buckets(){
//     for ( int i = 0; i < __c->size; ++i ){
//         puts("Bucket:");
//         printf("%d", __c->buckets[i])
//     }
// }
