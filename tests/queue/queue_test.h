#ifndef QUEUE_TEST_H
#define QUEUE_TEST_H

#include "queue/queue.h"
#include "minunit.h"

char* test_queue_create(void) {
    cstructs_queue_t queue = CSTRUCTS_QUEUE_CREATE(int, 5);
    mu_assert("Queue creation test failed: queue.head is not equal to 0", queue.head == 0);
    mu_assert("Queue creation test failed: queue.tail is not equal to 0", queue.tail == 0);
    mu_assert("Queue creation test failed: queue.size is not equal to 0", queue.size == 0);
    mu_assert("Queue creation test failed: queue.capacity is not equal to 5", queue.capacity == 5);
    mu_assert("Queue creation test failed: queue.data is NULL", queue.data != NULL);
    mu_assert("Queue creation test failed: queue.element_size is not equal to sizeof(int)", queue.element_size == sizeof(int));
    CSTRUCTS_QUEUE_FREE(&queue, false);
    return NULL;
}

char* test_queue_new(void) {
    cstructs_queue_t* queue = CSTRUCTS_QUEUE_NEW(int, 5);
    mu_assert("Queue new test failed: queue is NULL", queue != NULL);
    mu_assert("Queue new test failed: queue->head is not equal to 0", queue->head == 0);
    mu_assert("Queue new test failed: queue->tail is not equal to 0", queue->tail == 0);
    mu_assert("Queue new test failed: queue->size is not equal to 0", queue->size == 0);
    mu_assert("Queue new test failed: queue->capacity is not equal to 5", queue->capacity == 5);
    mu_assert("Queue new test failed: queue->data is NULL", queue->data != NULL);
    mu_assert("Queue new test failed: queue->element_size is not equal to sizeof(int)", queue->element_size == sizeof(int));
    CSTRUCTS_QUEUE_FREE(queue, true);
    return NULL;
}

char* test_queue_free(void) {
    cstructs_queue_t queue = CSTRUCTS_QUEUE_CREATE(int, 5);
    mu_assert("Queue free test failed: cstructs_queue_free returned an error", CSTRUCTS_QUEUE_FREE(&queue, false) == EXIT_SUCCESS);
    return NULL;
}

char* test_queue_push_pop(void) {
    cstructs_queue_t* queue = CSTRUCTS_QUEUE_NEW(int, 5);
    for (int i = 0; i < 5; i++) {
        CSTRUCTS_QUEUE_PUSH(queue, i);
    }

    for (int i = 0; i < 5; i++) {
        mu_assert("Queue push/pop test failed: CSTRUCTS_QUEUE_POP(queue) is not equal to i", *(int*)CSTRUCTS_QUEUE_POP(queue) == i);
    }

    CSTRUCTS_QUEUE_FREE(queue, true);
    return NULL;
}

char* test_queue_peek(void) {
    cstructs_queue_t* queue = CSTRUCTS_QUEUE_NEW(int, 5);
    for (int i = 0; i < 5; i++) {
        CSTRUCTS_QUEUE_PUSH(queue, i);
    }

    mu_assert("Queue peek test failed: CSTRUCTS_QUEUE_PEEK(queue) is not equal to 0", *(int*)CSTRUCTS_QUEUE_PEEK(queue) == 0);

    CSTRUCTS_QUEUE_FREE(queue, true);
    return NULL;
}

char* test_queue(void) {
    mu_run_test(test_queue_create);
    mu_run_test(test_queue_new);
    mu_run_test(test_queue_free);
    mu_run_test(test_queue_push_pop);
    mu_run_test(test_queue_peek);
    return NULL;
}

#endif //QUEUE_TEST_H
