#ifndef DEQUE_H
#define DEQUE_H

#include "cstructs_defines.h"

#define CSTRUCTS_DEQUE_GROWTH_FACTOR 2
#define CSTRUCTS_DEQUE_SHRINK_FACTOR 2
#define CSTRUCTS_DEQUE_SHRINK_THRESHOLD 4

#define CSTRUCTS_DEQUE_SIZE(deque) ((deque)->size)
#define CSTRUCTS_DEQUE_CAPACITY(deque) ((deque)->capacity)
#define CSTRUCTS_DEQUE_EMPTY(deque) (CSTRUCTS_DEQUE_SIZE(deque) == 0)
#define CSTRUCTS_DEQUE_FULL(deque) (CSTRUCTS_DEQUE_SIZE(deque) == CSTRUCTS_DEQUE_CAPACITY(deque))
#define CSTRUCTS_DEQUE_SIZE_UNDER_THRESHOLD(deque) (CSTRUCTS_DEQUE_SIZE(deque) < CSTRUCTS_DEQUE_CAPACITY(deque) / CSTRUCTS_DEQUE_SHRINK_THRESHOLD)

// ---------------------------------------------------------------------
#define CSTRUCTS_DEQUE_CREATE(element_type, capacity) cstructs_deque_create(sizeof(element_type), capacity)
#define CSTRUCTS_DEQUE_NEW(element_type, capacity) cstructs_deque_new(sizeof(element_type), capacity)
#define CSTRUCTS_DEQUE_FREE(deque, free_deque) cstructs_deque_free(deque, free_deque)

#define CSTRUCTS_DEQUE_PUSH_FRONT(deque, element) cstructs_deque_push_front(deque, &element)
#define CSTRUCTS_DEQUE_PUSH_BACK(deque, element) cstructs_deque_push_back(deque, &element)

#if defined(__GNUC__) || defined(__clang__)
#define CSTRUCTS_DEQUE_PUSH_FRONT_ANY(deque, element) cstructs_deque_push_front(deque, &(typeof(element)){element})
#define CSTRUCTS_DEQUE_PUSH_BACK_ANY(deque, element) cstructs_deque_push_back(deque, &(typeof(element)){element})
#endif // #if defined(__GNUC__) || defined(__clang__)

#define CSTRUCTS_DEQUE_PUSH_FRONT_PTR(deque, element) cstructs_deque_push_front(deque, element)
#define CSTRUCTS_DEQUE_PUSH_BACK_PTR(deque, element) cstructs_deque_push_back(deque, element)

#define CSTRUCTS_DEQUE_POP_FRONT(deque) cstructs_deque_pop_front(deque)
#define CSTRUCTS_DEQUE_POP_BACK(deque) cstructs_deque_pop_back(deque)
#define CSTRUCTS_DEQUE_PEEK_FRONT(deque) cstructs_deque_peek_front(deque)
#define CSTRUCTS_DEQUE_PEEK_BACK(deque) cstructs_deque_peek_back(deque)
#define CSTRUCTS_DEQUE_GET(deque, index) cstructs_deque_get(deque, index)

typedef struct {
    void* data;
    usize element_size;
    usize tail;
    usize head;
    usize size;
    usize capacity;
} cstructs_deque_t;

cstructs_deque_t cstructs_deque_create(usize element_size, usize capacity);
cstructs_deque_t* cstructs_deque_new(usize element_size, usize capacity);
errno_t cstructs_deque_free(cstructs_deque_t* deque, bool free_deque);

errno_t cstructs_deque_push_front(cstructs_deque_t* deque, const void* element);
errno_t cstructs_deque_push_back(cstructs_deque_t* deque, const void* element);
void* cstructs_deque_pop_front(cstructs_deque_t* deque);
void* cstructs_deque_pop_back(cstructs_deque_t* deque);

void* cstructs_deque_peek_front(const cstructs_deque_t* deque);
void* cstructs_deque_peek_back(const cstructs_deque_t* deque);

void* cstructs_deque_get(const cstructs_deque_t* deque, usize index);

#endif //DEQUE_H