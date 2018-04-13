
#include <pthread.h>
#define MAX_BUCKETS 65536


typedef struct Map{

    char* key;
    char* value;
    struct Map* next;
    pthread_mutex_t index_lock;

}Map;

unsigned long hash(char*);

void delete(void* key);
char* get(void* key);
void set(void* key, void* value);
void rehash();
void map_init();

Map* __m[MAX_BUCKETS];
