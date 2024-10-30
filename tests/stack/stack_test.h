#ifndef STACK_TEST_H
#define STACK_TEST_H

#include "stack/stack.h"
#include "minunit.h"

char* test_stack_create(void) {
    cstructs_stack_t stack = CSTRUCTS_STACK_CREATE(int, 10);
    mu_assert("Stack creation test failed: stack.data is NULL", stack.data != NULL);
    mu_assert("Stack creation test failed: stack.element_size is not equal to sizeof(int)", stack.element_size == sizeof(int));
    mu_assert("Stack creation test failed: stack.tail is not equal to 0", stack.tail == 0);
    mu_assert("Stack creation test failed: stack.capacity is not equal to 10", stack.capacity == 10);
    CSTRUCTS_STACK_FREE(&stack, false);
    return NULL;
}

char* test_stack_new(void) {
    cstructs_stack_t* stack = CSTRUCTS_STACK_NEW(int, 10);
    mu_assert("Stack new test failed: stack is NULL", stack != NULL);
    mu_assert("Stack new test failed: stack->data is NULL", stack->data != NULL);
    mu_assert("Stack new test failed: stack->element_size is not equal to sizeof(int)", stack->element_size == sizeof(int));
    mu_assert("Stack new test failed: stack->tail is not equal to 0", stack->tail == 0);
    mu_assert("Stack new test failed: stack->capacity is not equal to 10", stack->capacity == 10);
    CSTRUCTS_STACK_FREE(stack, true);
    return NULL;
}

char* test_stack_push_pop(void) {
    cstructs_stack_t* stack = CSTRUCTS_STACK_NEW(int, 5);
    for (int i = 0; i < 5; i++) {
        CSTRUCTS_STACK_PUSH(stack, i);
    }

    for (int i = 4; i >= 0; i--) {
        mu_assert("Stack push/pop test failed: CSTRUCTS_STACK_POP(stack) is not equal to i", *(int*)CSTRUCTS_STACK_POP(stack) == i);
    }

    CSTRUCTS_STACK_FREE(stack, true);
    return NULL;
}

char* test_stack_peek(void) {
    cstructs_stack_t* stack = CSTRUCTS_STACK_NEW(int, 5);
    for (int i = 0; i < 5; i++) {
        CSTRUCTS_STACK_PUSH(stack, i);
    }

    mu_assert("Stack peek test failed: CSTRUCTS_STACK_PEEK(stack) is not equal to 4", *(int*)CSTRUCTS_STACK_PEEK(stack) == 4);

    CSTRUCTS_STACK_FREE(stack, true);
    return NULL;
}

char* test_stack_get(void) {
    cstructs_stack_t* stack = CSTRUCTS_STACK_NEW(int, 5);
    for (int i = 0; i < 5; i++) {
        CSTRUCTS_STACK_PUSH(stack, i);
    }

    for (int i = 0; i < 5; i++) {
        mu_assert("Stack get test failed: CSTRUCTS_STACK_GET(stack, i) is not equal to i", *(int*)CSTRUCTS_STACK_GET(stack, i) == i);
    }

    CSTRUCTS_STACK_FREE(stack, true);
    return NULL;
}

char* test_stack(void) {
    mu_run_test(test_stack_create);
    mu_run_test(test_stack_new);
    mu_run_test(test_stack_push_pop);
    mu_run_test(test_stack_peek);
    mu_run_test(test_stack_get);
    return NULL;
}

#endif //STACK_TEST_H
