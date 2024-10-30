#include <stdio.h>
#include <stdlib.h>

#include "darray/darray_test.h"
#include "stack/stack_test.h"
#include "queue/queue_test.h"
#include "deque/deque_test.h"

int main(void) {
    char* result;

    tests_run = 0;
    result = test_darray();
    if (result != NULL) {
        printf("%s\n", result);
        return EXIT_FAILURE;
    } else {
        printf("All darray tests (%d) passed!\n", tests_run);
    }

    tests_run = 0;
    result = test_stack();
    if (result != NULL) {
        printf("%s\n", result);
        return EXIT_FAILURE;
    } else {
        printf("All stack tests (%d) passed!\n", tests_run);
    }

    tests_run = 0;
    result = test_queue();
    if (result != NULL) {
        printf("%s\n", result);
        return EXIT_FAILURE;
    } else {
        printf("All queue tests (%d) passed!\n", tests_run);
    }

    tests_run = 0;
    result = test_deque();
    if (result != NULL) {
        printf("%s\n", result);
        return EXIT_FAILURE;
    } else {
        printf("All deque tests (%d) passed!\n", tests_run);
    }

    return EXIT_SUCCESS;
}
