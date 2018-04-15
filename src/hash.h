
#include <pthread.h>
#include <stdbool.h>

#define MAX_BUCKETS 65536

// //
// typedef struct ListNode{
//     void* key;
//     void* value;
//     struct ListNode* next;
//     size_t n_cnt;
// }ListNode;
//
//
// typedef struct Map{
//     bool is_map_ptr;
//     void* bucket;  /* may be a Map or a ListNode*/
//     int MULTIPLIER;
//     size_t size;
//     int e_cnt; /* # of elements stored*/
// }Map;



typedef struct Map{
    void* key;
    void* value;
    struct Map* next;
    int multiplier;  /*TODO: optimize so multiplier can be looked up based on depth dynamically*/
    bool is_map;     /* Make this a bit in either key or value - compress?*/
    size_t size;  /* # elements allocated*/
    pthread_mutex_t index_lock;

}Map;




unsigned long hash(char*);

void delete(void* key);

char* get(void* key);

void set(void* key, void* value);

void rehash();

void map_init();

void destroy_map();

Map** __m;
