#include <assert.h>
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


Data* get_head_from_key(void* key){

    unsigned long index = get_index(key);
    return __c->buckets[index]->head;
}


void set(char* key, char* value){

    unsigned long index = get_index(key);

    if (__c->buckets[index]->head == NULL){

        __c->buckets[index]->head = malloc(sizeof(Data));
        set_node(__c->buckets[index]->head, key, value);
        __c->buckets[index]->head->next = NULL;
        __c->buckets[index]->size++;

    }
    else{

        Data* head = __c->buckets[index]->head;

        /* Special check for match at head */
        if (strcmp(head->key, key) == 0){
            set_node(head, key, value);
            return;
        }

        while(head->next != NULL){
            /* Search as we traverse */

            if (strcmp(head->key, key) == 0){
                /* Overwrite */
                set_node(head, key, value);
                return;
            }
            head = head->next;
        }

        head->next = malloc(sizeof(Data));
        set_node(head->next, key, value);
        head->next->next = NULL;
        __c->buckets[index]->size++;
    }

}


char* get_value(char* key){

    Data* head = get_head_from_key(key);

    while(head != NULL){

        if (strcmp(head->key, key) == 0){
            return head->value;
        }

        head = head->next;
    }
    return NULL;
}


void delete(void* key){

    unsigned long index = get_index(key);

    Data* to_free = NULL;

    if(__c->buckets[index]->head && strcmp(__c->buckets[index]->head->key, key) == 0){
        to_free = __c->buckets[index]->head;
        __c->buckets[index]->head = __c->buckets[index]->head->next;
        __c->buckets[index]->size--;

    }
    else{
        Data* head = __c->buckets[index]->head;
        while(head->next != NULL){

            if (head->next && strcmp(head->next->key, key) == 0){
                to_free = head->next;
                head->next = head->next->next;
                __c->buckets[index]->size--;
                break;
            }
            head = head->next;
        }
    }
    if (to_free){
        cleanup(to_free);
    }
}



void set_node(Data* head, void* key, void* value){

    assert( head != NULL);
    head->key = (char*) malloc( (strlen(key) + 1) * sizeof(char));
    head->value = (char*) malloc( (strlen(value) + 1) * sizeof(char));
    strcpy(head->key, key);
    strcpy(head->value, value);

}


void cleanup(Data* node){

    free(node->key);
    free(node->value);
    free(node);
}


void init_cache(){

    unsigned int i;
    __c = (Cache*) malloc(sizeof(Cache));
    __c->size = MAX_BUCKETS;
    __c->buckets =  malloc((__c->size) * sizeof(Bucket*));

    for (i = 0; i < __c->size; ++i){
        __c->buckets[i] = malloc(sizeof(Bucket));
        __c->buckets[i]->head = NULL;
        __c->buckets[i]->size = 0;
    }

}


void print_buckets(){

    for (int i = 0; i < __c->size; ++i){
        Data* head = __c->buckets[i]->head;
        if (head != NULL){
            puts("\n");
            puts("Bucket:");
        }
        while(head != NULL){

            printf("(%s, %s)->", head->key, head->value);
            head = head->next;
        }
        }
}
