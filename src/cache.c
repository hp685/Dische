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
    Bucket bucket = __c->buckets[index];
    if (bucket.head->key == NULL){
        bucket.head->key = key;
        bucket.head->value = value;
    }
    else{
        Data* node = bucket.head;
        while(node->next != NULL){
            node = node->next;
        }

        node->next = (Data*) malloc(sizeof(Data));
        node->next->key = key;
        node->next->value = value;
        node->next->next = NULL;
    }
}


void* get(void* key){
    unsigned int index = get_index(key);
    Bucket bucket = __c->buckets[index];
    if (strcmp(bucket.head->key, key) == 0){
        return bucket.head->value;
    }
    else{
        Data* node = bucket.head;
        while(node->next){
            node = node->next;
            if (strcmp(node->key, key) == 0){
                return node->value;
            }
        }
    }
    return NULL;
}


void init_cache(){

    unsigned int i;
    __c = (Cache*) malloc(sizeof(Cache));
    __c->size = MAX_BUCKETS;
    __c->buckets = (Bucket*) malloc((__c->size) * sizeof(Bucket));

    for (i = 0; i < __c->size; ++i){
        __c->buckets[i].head = (Data*) malloc(sizeof(Data));
        __c->buckets[i].head->key = NULL;
        __c->buckets[i].head->value = NULL;
        __c->buckets[i].head->next = NULL;
    }

}
