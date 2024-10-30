#ifndef QUEUE_H
#define QUEUE_H

#include "cstructs_defines.h"

#define CSTRUCTS_QUEUE_GROWTH_FACTOR 2
#define CSTRUCTS_QUEUE_SHRINK_FACTOR 2
#define CSTRUCTS_QUEUE_SHRINK_THRESHOLD 4

#define CSTRUCTS_QUEUE_SIZE(queue) ((queue)->size)
#define CSTRUCTS_QUEUE_CAPACITY(queue) ((queue)->capacity)
#define CSTRUCTS_QUEUE_EMPTY(queue) (CSTRUCTS_QUEUE_SIZE(queue) == 0)
#define CSTRUCTS_QUEUE_FULL(queue) (CSTRUCTS_QUEUE_SIZE(queue) == CSTRUCTS_QUEUE_CAPACITY(queue))
#define CSTRUCTS_QUEUE_SIZE_UNDER_THRESHOLD(queue) (CSTRUCTS_QUEUE_SIZE(queue) < CSTRUCTS_QUEUE_CAPACITY(queue) / CSTRUCTS_QUEUE_SHRINK_THRESHOLD)

// ---------------------------------------------------------------------
#define CSTRUCTS_QUEUE_CREATE(element_type, capacity) cstructs_queue_create(sizeof(element_type), capacity)
#define CSTRUCTS_QUEUE_NEW(element_type, capacity) cstructs_queue_new(sizeof(element_type), capacity)
#define CSTRUCTS_QUEUE_FREE(queue, free_queue) cstructs_queue_free(queue, free_queue)
#define CSTRUCTS_QUEUE_PUSH(queue, element) cstructs_queue_push(queue, &element)
#if defined(__GNUC__) || defined(__clang__)
#define CSTRUCTS_QUEUE_PUSH_ANY(queue, element) cstructs_queue_push(queue, &(typeof(element)){element})
#endif // #if defined(__GNUC__) || defined(__clang__)
#define CSTRUCTS_QUEUE_PUSH_PTR(queue, element) cstructs_queue_push(queue, element)
#define CSTRUCTS_QUEUE_POP(queue) cstructs_queue_pop(queue)
#define CSTRUCTS_QUEUE_PEEK(queue) cstructs_queue_peek(queue)
#define CSTRUCTS_QUEUE_GET(queue, index) cstructs_queue_get(queue, index)

typedef struct {
    void* data;
    usize element_size;
    usize tail;
    usize head;
    usize size;
    usize capacity;
} cstructs_queue_t;

cstructs_queue_t cstructs_queue_create(usize element_size, usize capacity);
cstructs_queue_t* cstructs_queue_new(usize element_size, usize capacity);
errno_t cstructs_queue_free(cstructs_queue_t* queue, bool free_queue);

errno_t cstructs_queue_push(cstructs_queue_t* queue, const void* element);
void* cstructs_queue_pop(cstructs_queue_t* queue);
void* cstructs_queue_peek(const cstructs_queue_t* queue);

void* cstructs_queue_get(const cstructs_queue_t* queue, usize index);

#endif //QUEUE_H
