#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include "hash.h"
#include "utils.h"
//#include "memory.h"

#define MULTIPLIER 97


void rehash(){
    /*TODO  */

}


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



void delete(void* key){

    unsigned long index;
    Map* to_delete;
    Map* node;
    index = get_index(key);
    node = __m[index];

    if (node == NULL){ /* Key doesn't exist*/
      return;
    }
    else if(node->next == NULL){

      reinit_node(node);
      return;
    }
    else{

      while(node->next != NULL){

        if (strcmp(node->next->key, key)){
          to_delete = node->next;
          node->next  = node->next->next;
        }
        else{
          node = node->next;
        }
      }
    }
    if (to_delete  != NULL){

      print_chain(__m[index], index);
      free(to_delete->value);
      free(to_delete->key);
      free(to_delete);

    }
}

char* get(void* key){

    unsigned long index;
    index = get_index(key);
    Map* node = __m[index];

    if ( node->key == NULL ){
        return NULL;
    }
    if ( strcmp(node->key, key) == 0 ){
        return node->value;
    }
    else{

        while ( node->key ){
            node = node->next;
            if ( strcmp(node->key, key) == 0 ){
                return node->value;
            }
        }
    }
    return NULL;

}


void set(void* key, void* value){

    unsigned long index;
    int num_nodes;

    index = get_index(key);
    Map* _dn = __m[index];
    num_nodes = 0;


    while ( _dn->next != NULL ){
        _dn = _dn->next;
        num_nodes++;
    }

    Map* node = malloc(sizeof(Map*));

    node->key = malloc( sizeof(char) * (strlen(key) + 1) );
    strcpy(node->key, key);

    node->value = malloc( sizeof(char) *  (strlen(value) + 1) );
    strcpy(node->value, value);

    node->next = malloc(sizeof(Map*));
    node->next = NULL;

    if(num_nodes == 0){
        __m[index] = node;

    }else{

        _dn->next = node;
    }
    if (num_nodes / MAX_BUCKETS >= 1){
        /* Needs rehash*/
        rehash();
    }

    print_chain(__m[index], index);
    puts("Set\n");
    }





void reinit_node(Map* node){
    node->key = NULL;
    node->value = NULL;
    node->next = NULL;
    node->is_map = false;
}


void map_init(){

    __m = malloc(MAX_BUCKETS * sizeof(Map*));
    Map *m = &__m;
    m->size = MAX_BUCKETS;
    for (int i = 0; i < MAX_BUCKETS; ++i){
        __m[i] = malloc(sizeof(Map));
    }
}


Map** get_map(){
    return __m;
}

void destroy_map(){
    Map* m_ptr = &__m;
    Map* free_ptr;
    for(int i = 0; i < m_ptr->size; i++){
            if ( !__m[i]->is_map ){
                /* unlink and return to free pool*/
                free_ptr = __m[i]->next;
                __m[i]->next = NULL;
            }
    }

    ffree(free_ptr);  /* Do this asynchronously?*/

}


void print_chain(Map* head, unsigned long index){

    printf("Bucket: %d", index);

    while(head){

        printf("(%s, %s)->",head->key, head->value);
        head = head->next;
    }

    putchar('\n');
}
