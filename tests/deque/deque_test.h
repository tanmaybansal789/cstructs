#ifndef DEQUE_TEST_H
#define DEQUE_TEST_H

#include "deque/deque.h"
#include "minunit.h"

char* test_deque_create(void) {
    cstructs_deque_t deque = CSTRUCTS_DEQUE_CREATE(int, 10);
    mu_assert("Deque creation test failed: deque.data is NULL", deque.data != NULL);
    mu_assert("Deque creation test failed: deque.element_size is not equal to sizeof(int)", deque.element_size == sizeof(int));
    mu_assert("Deque creation test failed: deque.size is not equal to 0", deque.size == 0);
    mu_assert("Deque creation test failed: deque.capacity is not equal to 10", deque.capacity == 10);
    mu_assert("Deque creation test failed: deque.head is not equal to 0", deque.head == 0);
    mu_assert("Deque creation test failed: deque.tail is not equal to 0", deque.tail == 0);
    CSTRUCTS_DEQUE_FREE(&deque, false);
    return NULL;
}

char* test_deque_new(void) {
    cstructs_deque_t* deque = CSTRUCTS_DEQUE_NEW(int, 10);
    mu_assert("Deque new test failed: deque is NULL", deque != NULL);
    mu_assert("Deque new test failed: deque->data is NULL", deque->data != NULL);
    mu_assert("Deque new test failed: deque->element_size is not equal to sizeof(int)", deque->element_size == sizeof(int));
    mu_assert("Deque new test failed: deque->size is not equal to 0", deque->size == 0);
    mu_assert("Deque new test failed: deque->capacity is not equal to 10", deque->capacity == 10);
    mu_assert("Deque new test failed: deque->head is not equal to 0", deque->head == 0);
    mu_assert("Deque new test failed: deque->tail is not equal to 0", deque->tail == 0);
    CSTRUCTS_DEQUE_FREE(deque, true);
    return NULL;
}

char* test_deque_push_front_back(void) {
    cstructs_deque_t* deque = CSTRUCTS_DEQUE_NEW(int, 5);
    for (int i = 0; i < 5; i++) {
        CSTRUCTS_DEQUE_PUSH_FRONT(deque, i);
    }

    for (int i = 5; i < 10; i++) {
        CSTRUCTS_DEQUE_PUSH_BACK(deque, i);
    }

    int expected[] = {4, 3, 2, 1, 0, 5, 6, 7, 8, 9};
    for (int i = 0; i < 10; i++) {
        mu_assert("Deque push front/back test failed: deque->data[i] is not equal to expected[i]", *(int*)CSTRUCTS_DEQUE_GET(deque, i) == expected[i]);
    }

    CSTRUCTS_DEQUE_FREE(deque, true);

    return NULL;
}

char* test_deque_pop_front_back(void) {
    cstructs_deque_t* deque = CSTRUCTS_DEQUE_NEW(int, 5);
    for (int i = 0; i < 10; i++) {
        CSTRUCTS_DEQUE_PUSH_BACK(deque, i);
    }

    for (int i = 0; i < 5; i++) {
        CSTRUCTS_DEQUE_PUSH_FRONT(deque, i);
    }

    for (int i = 0; i < 5; i++) {
        int* element = CSTRUCTS_DEQUE_POP_FRONT(deque);
        mu_assert("Deque pop front test failed: deque->data[i] is not equal to 4 - i", *element == 4 - i);
        free(element);
    }

    for (int i = 0; i < 5; i++) {
        int* element = CSTRUCTS_DEQUE_POP_BACK(deque);
        mu_assert("Deque pop back test failed: deque->data[i] is not equal to 9 - i", *element == 9 - i);
        free(element);
    }

    CSTRUCTS_DEQUE_FREE(deque, true);
    return NULL;
}

char* test_deque() {
    mu_run_test(test_deque_create);
    mu_run_test(test_deque_new);
    mu_run_test(test_deque_push_front_back);
    mu_run_test(test_deque_pop_front_back);
    return NULL;
}

#endif //DEQUE_TEST_H
