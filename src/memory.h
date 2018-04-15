#include <malloc.h>

/*check free lists if available*/
void* fmalloc(size_t size);

/* Return block back to the pool*/
/* If # blocks in pool above a threshold, release that back to the os*/

void* ffree(void *ptr);


typedef struct FreeList{

    struct List* head;
    int count;

}FreeList;


typedef struct structFreeMap{

    struct List** head;
    size_t size; /*size of the pointer table*/
    int e_count;

}FreeMap;

void alloc_maps();

void alloc_lists();
