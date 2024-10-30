#ifndef STACK_H
#define STACK_H

#include "cstructs_defines.h"

#define CSTRUCTS_STACK_GROWTH_FACTOR 2
#define CSTRUCTS_STACK_SHRINK_FACTOR 2
#define CSTRUCTS_STACK_SHRINK_THRESHOLD 4

#define CSTRUCTS_STACK_SIZE(stack) ((stack)->tail)
#define CSTRUCTS_STACK_CAPACITY(stack) ((stack)->capacity)
#define CSTRUCTS_STACK_EMPTY(stack) (CSTRUCTS_STACK_SIZE(stack) == 0)
#define CSTRUCTS_STACK_FULL(stack) (CSTRUCTS_STACK_SIZE(stack) == CSTRUCTS_STACK_CAPACITY(stack))
#define CSTRUCTS_STACK_SIZE_UNDER_THRESHOLD(stack) (CSTRUCTS_STACK_SIZE(stack) < CSTRUCTS_STACK_CAPACITY(stack) / CSTRUCTS_STACK_SHRINK_THRESHOLD)

// ---------------------------------------------------------------------
#define CSTRUCTS_STACK_CREATE(element_type, capacity) cstructs_stack_create(sizeof(element_type), capacity)
#define CSTRUCTS_STACK_NEW(element_type, capacity) cstructs_stack_new(sizeof(element_type), capacity)
#define CSTRUCTS_STACK_FREE(stack, free_stack) cstructs_stack_free(stack, free_stack)

#define CSTRUCTS_STACK_PUSH(stack, element) cstructs_stack_push(stack, &element)
#if defined(__GNUC__) || defined(__clang__)
#define CSTRUCTS_STACK_PUSH_ANY(stack, element) cstructs_stack_push(stack, &(typeof(element)){element})
#endif // #if defined(__GNUC__) || defined(__clang__)
#define CSTRUCTS_STACK_PUSH_PTR(stack, element) cstructs_stack_push(stack, element)
#define CSTRUCTS_STACK_POP(stack) cstructs_stack_pop(stack)
#define CSTRUCTS_STACK_PEEK(stack) cstructs_stack_peek(stack)
#define CSTRUCTS_STACK_GET(stack, index) cstructs_stack_get(stack, index)


typedef struct {
    void* data;
    usize element_size;
    usize tail;
    usize capacity;
} cstructs_stack_t;

cstructs_stack_t cstructs_stack_create(usize element_size, usize capacity);
cstructs_stack_t* cstructs_stack_new(usize element_size, usize capacity);
errno_t cstructs_stack_free(cstructs_stack_t* stack, bool free_stack);

errno_t cstructs_stack_push(cstructs_stack_t* stack, const void* element);
void* cstructs_stack_pop(cstructs_stack_t* stack);
void* cstructs_stack_peek(const cstructs_stack_t* stack);

void* cstructs_stack_get(const cstructs_stack_t* stack, usize index);

#endif //STACK_H
