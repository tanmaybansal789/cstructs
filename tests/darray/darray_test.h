#ifndef DARRAY_TEST_H
#define DARRAY_TEST_H

#include "darray/darray.h"
#include "minunit.h"

#include <stdio.h>

char* test_darray_create(void) {
    // Test 1: Create a new dynamic array with a capacity of 10 elements.
    cstructs_darray_t darray = CSTRUCTS_DARRAY_CREATE(int, 10);
    mu_assert("Darray creation test failed: darray.data is NULL", darray.data != NULL);
    mu_assert("Darray creation test failed: darray.element_size is not equal to sizeof(int)", darray.element_size == sizeof(int));
    mu_assert("Darray creation test failed: darray.size is not equal to 0", darray.size == 0);
    mu_assert("Darray creation test failed: darray.capacity is not equal to 10", darray.capacity == 10);
    CSTRUCTS_DARRAY_FREE(&darray, false);
    return NULL;
}

char* test_darray_new(void) {
    cstructs_darray_t* darray = CSTRUCTS_DARRAY_NEW(int, 10);
    mu_assert("Darray new test failed: darray is NULL", darray != NULL);
    mu_assert("Darray new test failed: darray->data is NULL", darray->data != NULL);
    mu_assert("Darray new test failed: darray->element_size is not equal to sizeof(int)", darray->element_size == sizeof(int));
    mu_assert("Darray new test failed: darray->size is not equal to 0", darray->size == 0);
    mu_assert("Darray new test failed: darray->capacity is not equal to 10", darray->capacity == 10);
    CSTRUCTS_DARRAY_FREE(darray, true);
    return NULL;
}

char* test_darray_push(void) {
    cstructs_darray_t* darray = CSTRUCTS_DARRAY_NEW(int, 5);
    for (int i = 0; i < 10; i++) {
        CSTRUCTS_DARRAY_PUSH(darray, i);
    }
    mu_assert("Darray push test failed: darray->size is not equal to 10", darray->size == 10);

    for (int i = 0; i < 10; i++) {
        mu_assert("Darray push test failed: darray->data[i] is not equal to i", *(int*)CSTRUCTS_DARRAY_GET(darray, i) == i);
    }

    CSTRUCTS_DARRAY_FREE(darray, true);
    return NULL;
}

char* test_darray_pop(void) {
    cstructs_darray_t* darray = CSTRUCTS_DARRAY_NEW(int, 10);
    for (int i = 0; i < 10; i++) {
        CSTRUCTS_DARRAY_PUSH(darray, i);
    }
    mu_assert("Darray pop test failed: darray->size is not equal to 10", darray->size == 10);

    while (!CSTRUCTS_DARRAY_EMPTY(darray)) {
        CSTRUCTS_DARRAY_POP(darray);
    }

    mu_assert("Darray pop test failed: darray->size is not equal to 0", darray->size == 0);

    CSTRUCTS_DARRAY_FREE(darray, true);
    return NULL;
}

char* test_darray_insert(void) {
    cstructs_darray_t* darray = CSTRUCTS_DARRAY_NEW(int, 10);
    for (int i = 0; i < 10; i++) {
        CSTRUCTS_DARRAY_PUSH(darray, i);
    }
    mu_assert("Darray insert test failed: darray->size is not equal to 10", darray->size == 10);

    for (int i = 0; i < 10; i++) {
        CSTRUCTS_DARRAY_INSERT_ANY(darray, i, i * i);
    }

    mu_assert("Darray insert test failed: darray->size is not equal to 20", darray->size == 20);

    int expected[] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int i = 0; i < 20; i++) {
        mu_assert("Darray insert test failed: darray->data[i] is not equal to expected[i]", *(int*)CSTRUCTS_DARRAY_GET(darray, i) == expected[i]);
        // printf("%d ", *(int*)CSTRUCTS_DARRAY_GET(darray, i));
    }

    printf("\n");

    CSTRUCTS_DARRAY_FREE(darray, true);
    return NULL;
}

char* test_darray_remove(void) {
    cstructs_darray_t* darray = CSTRUCTS_DARRAY_NEW(int, 10);
    for (int i = 0; i < 10; i++) {
        CSTRUCTS_DARRAY_PUSH(darray, i);
    }
    mu_assert("Darray remove test failed: darray->size is not equal to 10", darray->size == 10);

    for (int i = 0; i < 10; i++) {
        /*for (int j = 0; j < darray->size; j++) {
            printf("%d ", *(int*)CSTRUCTS_DARRAY_GET(darray, j));
        }
        printf("\n");*/
        CSTRUCTS_DARRAY_REMOVE(darray, 0);
    }

    mu_assert("Darray remove test failed: darray->size is not equal to 0", darray->size == 0);

    CSTRUCTS_DARRAY_FREE(darray, true);
    return NULL;
}

char* test_darray(void) {
    mu_run_test(test_darray_create);
    mu_run_test(test_darray_new);
    mu_run_test(test_darray_push);
    mu_run_test(test_darray_pop);
    mu_run_test(test_darray_insert);
    mu_run_test(test_darray_remove);
    return NULL;
}

#endif //DARRAY_TEST_H
