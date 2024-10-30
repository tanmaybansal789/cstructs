#include "stack/stack.h"

static errno_t cstructs_stack_grow(cstructs_stack_t* stack) {
    const usize new_capacity = stack->capacity * 2;

    void* new_data = realloc(stack->data, new_capacity * stack->element_size);
    if (new_data == NULL) {
        return ENOMEM;
    }

    stack->data = new_data;
    stack->capacity = new_capacity;

    return EXIT_SUCCESS;
}

static errno_t cstructs_stack_shrink(cstructs_stack_t* stack) {
    const usize new_capacity = stack->capacity / 2;

    void* new_data = realloc(stack->data, new_capacity * stack->element_size);
    if (new_data == NULL) {
        return ENOMEM;
    }

    stack->data = new_data;
    stack->capacity = new_capacity;

    return EXIT_SUCCESS;
}

// ---------------------------------------------------------------------

cstructs_stack_t cstructs_stack_create(usize element_size, usize capacity) {
    return (cstructs_stack_t) {
        .data = malloc(element_size * capacity),
        .element_size = element_size,
        .tail = 0,
        .capacity = capacity
    };
}

cstructs_stack_t* cstructs_stack_new(usize element_size, usize capacity) {
    cstructs_stack_t* stack = malloc(sizeof(cstructs_stack_t));
    if (stack == NULL) {
        return NULL;
    }

    *stack = cstructs_stack_create(element_size, capacity);
    return stack;
}

errno_t cstructs_stack_free(cstructs_stack_t* stack, bool free_stack) {
    free(stack->data);
    if (free_stack) {
        free(stack);
    }

    return EXIT_SUCCESS;
}

// ---------------------------------------------------------------------

errno_t cstructs_stack_push(cstructs_stack_t* stack, const void* element) {
    if (CSTRUCTS_STACK_FULL(stack)) {
        const errno_t result = cstructs_stack_grow(stack);
        if (result != EXIT_SUCCESS) {
            return result;
        }
    }

    memcpy(stack->data + stack->tail * stack->element_size, element, stack->element_size);
    stack->tail++;

    return EXIT_SUCCESS;
}

void* cstructs_stack_pop(cstructs_stack_t* stack) {
    if (CSTRUCTS_STACK_EMPTY(stack)) {
        return NULL;
    }

    if (CSTRUCTS_STACK_SIZE_UNDER_THRESHOLD(stack)) {
        cstructs_stack_shrink(stack);
    }

    stack->tail--;
    return stack->data + stack->tail * stack->element_size;
}

void* cstructs_stack_peek(const cstructs_stack_t* stack) {
    if (CSTRUCTS_STACK_EMPTY(stack)) {
        return NULL;
    }

    return stack->data + (stack->tail - 1) * stack->element_size;
}

// ---------------------------------------------------------------------

void* cstructs_stack_get(const cstructs_stack_t* stack, usize index) {
    if (index >= stack->tail) {
        return NULL;
    }

    return stack->data + index * stack->element_size;
}