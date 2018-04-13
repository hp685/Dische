#include <string.h>
#include <stdlib.h>

#include "hash.h"


#define MULTIPLIER 97


void rehash(){
    /*TODO Implement rehashing of the map*/
}


unsigned long hash(char* s){

    unsigned long h;
    unsigned char* us;
    s += '\0';
    us = (unsigned char* ) s;
    puts(s);
    h = 0;
    while( *us != '\0' ){
        puts(*us);
        h = h * MULTIPLIER + *us;
        us++;
    }

    return h;
}

unsigned long get_index(void* key){

    unsigned long index;
    unsigned long hash_code = hash((char*)key);

    index = hash_code % MAX_BUCKETS;
    printf("%lu", index);
    return index;
}



void delete(void* key){

    unsigned long index;
    index = get_index(key);
    Map* node = __m[index];

    for(; node->next != NULL && strcmp(node->next->key, key) !=0; node=node->next){
    }

    Map* to_delete = node->next;
    node->next = node->next->next;
    free(to_delete);

}

void* get(void* key){

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
    printf("%lu", index);
    Map* _dn = __m[index];

    num_nodes = 0;
    while ( _dn->next != NULL ){
        _dn = _dn->next;
        num_nodes++;
    }

    Map* node = malloc(sizeof(Map));

    node->key = malloc( sizeof(char) * (strlen(key) + 1) );
    strcpy(node->key, key);

    node->value = malloc( sizeof(char) *  (strlen(value) + 1) );
    strcpy(node->value, value);

    node->next = NULL;
    _dn->next = node;

    if (num_nodes / MAX_BUCKETS == 1){
        /* Needs rehash*/
        rehash();
    }

    }
