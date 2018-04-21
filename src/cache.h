#include <stdio.h>

#define MAX_BUCKETS 65536

typedef struct Cache Cache;
typedef struct Data Data;
typedef struct Bucket Bucket;


struct Cache{
    size_t size;
    Bucket** buckets; 
    int type;

};


struct Data{
    void* key;
    void* value;
    Data* next;
    int type;
};


struct Bucket{

    Data* head;
    size_t size;
    int type;

};

Cache* __c;

void init_cache();

void set(void* key, void* value);
