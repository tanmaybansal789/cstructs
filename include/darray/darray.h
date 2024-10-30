#ifndef DARRAY_H
#define DARRAY_H

#include "cstructs_defines.h"

#define CSTRUCTS_DARRAY_GROWTH_FACTOR 2
#define CSTRUCTS_DARRAY_SHRINK_FACTOR 2
#define CSTRUCTS_DARRAY_SHRINK_THRESHOLD 4

#define CSTRUCTS_DARRAY_SIZE(darray) ((darray)->size)
#define CSTRUCTS_DARRAY_CAPACITY(darray) ((darray)->capacity)
#define CSTRUCTS_DARRAY_EMPTY(darray) (CSTRUCTS_DARRAY_SIZE(darray) == 0)
#define CSTRUCTS_DARRAY_FULL(darray) (CSTRUCTS_DARRAY_SIZE(darray) == CSTRUCTS_DARRAY_CAPACITY(darray))
#define CSTRUCTS_DARRAY_SIZE_UNDER_THRESHOLD(darray) (CSTRUCTS_DARRAY_SIZE(darray) < CSTRUCTS_DARRAY_CAPACITY(darray) / CSTRUCTS_DARRAY_SHRINK_THRESHOLD)

// ---------------------------------------------------------------------
#define CSTRUCTS_DARRAY_CREATE(element_type, capacity) cstructs_darray_create(sizeof(element_type), capacity)
#define CSTRUCTS_DARRAY_NEW(element_type, capacity) cstructs_darray_new(sizeof(element_type), capacity)
#define CSTRUCTS_DARRAY_FREE(darray, free_darray) cstructs_darray_free(darray, free_darray)

#define CSTRUCTS_DARRAY_PUSH(darray, element) cstructs_darray_push(darray, &element)
#define CSTRUCTS_DARRAY_PUSH_PTR(darray, element) cstructs_darray_push(darray, element)
#define CSTRUCTS_DARRAY_POP(darray) cstructs_darray_pop(darray)
#define CSTRUCTS_DARRAY_INSERT(darray, index, element) cstructs_darray_insert(darray, index, &element)
#if defined(__GNUC__) || defined(__clang__)
#define CSTRUCTS_DARRAY_PUSH_ANY(darray, element) cstructs_darray_push(darray, &(typeof(element)){element})
#define CSTRUCTS_DARRAY_INSERT_ANY(darray, index, element) cstructs_darray_insert(darray, index, &(typeof(element)){element})
#endif // #if defined(__GNUC__) || defined(__clang__)
#define CSTRUCTS_DARRAY_REMOVE(darray, index) cstructs_darray_remove(darray, index)

#define CSTRUCTS_DARRAY_GET(darray, index) cstructs_darray_get(darray, index)

typedef struct {
    void* data;
    usize element_size;
    usize size;
    usize capacity;
} cstructs_darray_t;

cstructs_darray_t cstructs_darray_create(usize element_size, usize capacity);
cstructs_darray_t* cstructs_darray_new(usize element_size, usize capacity);
errno_t cstructs_darray_free(cstructs_darray_t* darray, bool free_darray);

errno_t cstructs_darray_push(cstructs_darray_t* darray, const void* element);
errno_t cstructs_darray_pop(cstructs_darray_t* darray);
errno_t cstructs_darray_insert(cstructs_darray_t* darray, usize index, const void* element);
errno_t cstructs_darray_remove(cstructs_darray_t* darray, usize index);

void* cstructs_darray_get(const cstructs_darray_t* darray, usize index);

#endif //DARRAY_H
