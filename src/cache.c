#include <malloc.h>
#include "cache.h"







void init_bucket(Bucket* e){

    e = malloc(sizeof(Bucket));
    e->head = malloc(sizeof(Data)); /* Initially. May point to a (sub) Cache later.*/
    e->head->key = NULL;
    e->head->value = NULL;
    e->head->next = NULL;
    e->size = 1;
}


void init_cache(){
    int i;
    __c = (Cache*) malloc(sizeof(Cache));
    __c->size = MAX_BUCKETS;
    __c->buckets =  malloc(__c->size * sizeof(Bucket*));
    for (i = 0; i < __c->size; ++i){
        __c->buckets[i] =  malloc(sizeof(Bucket));
        //__c->buckets[i]->head->key = NULL;
        //init_bucket(__c->buckets[i]);
    }
    puts("Done");
    puts("BAR");
}
