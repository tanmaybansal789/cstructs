#include "darray/darray.h"

#include <stdio.h>

static errno_t cstructs_darray_grow(cstructs_darray_t* darray) {
    const usize new_capacity = darray->capacity * 2;

    void* new_data = realloc(darray->data, new_capacity * darray->element_size);
    if (new_data == NULL) {
        return ENOMEM;
    }

    darray->data = new_data;
    darray->capacity = new_capacity;

    return EXIT_SUCCESS;
}

static errno_t cstructs_darray_shrink(cstructs_darray_t* darray) {
    const usize new_capacity = darray->capacity / 2;

    void* new_data = realloc(darray->data, new_capacity * darray->element_size);
    if (new_data == NULL) {
        return ENOMEM;
    }

    darray->data = new_data;
    darray->capacity = new_capacity;

    return EXIT_SUCCESS;
}

// ---------------------------------------------------------------------

cstructs_darray_t cstructs_darray_create(usize element_size, usize capacity) {
    return (cstructs_darray_t) {
        .data = malloc(element_size * capacity),
        .element_size = element_size,
        .size = 0,
        .capacity = capacity
    };
}

cstructs_darray_t* cstructs_darray_new(usize element_size, usize capacity) {
    cstructs_darray_t* darray = malloc(sizeof(cstructs_darray_t));
    if (darray == NULL) {
        return NULL;
    }

    *darray = cstructs_darray_create(element_size, capacity);
    return darray;
}

errno_t cstructs_darray_free(cstructs_darray_t* darray, bool free_darray) {
    free(darray->data);
    if (free_darray) {
        free(darray);
    }

    return EXIT_SUCCESS;
}

// ---------------------------------------------------------------------

errno_t cstructs_darray_push(cstructs_darray_t* darray, const void* element) {
    if (CSTRUCTS_DARRAY_FULL(darray)) {
        errno_t result = cstructs_darray_grow(darray);
        if (result != EXIT_SUCCESS) {
            return result;
        }
    }

    memcpy(darray->data + darray->size * darray->element_size, element, darray->element_size);
    darray->size++;

    return EXIT_SUCCESS;
}

errno_t cstructs_darray_pop(cstructs_darray_t* darray) {
    if (CSTRUCTS_DARRAY_EMPTY(darray)) {
        return EXIT_FAILURE;
    }

    darray->size--;

    if (CSTRUCTS_DARRAY_SIZE_UNDER_THRESHOLD(darray)) {
        errno_t result = cstructs_darray_shrink(darray);
        if (result != EXIT_SUCCESS) {
            return result;
        }
    }

    return EXIT_SUCCESS;
}

errno_t cstructs_darray_insert(cstructs_darray_t* darray, usize index, const void* element) {
    if (CSTRUCTS_DARRAY_FULL(darray)) {
        errno_t result = cstructs_darray_grow(darray);
        if (result != EXIT_SUCCESS) {
            return result;
        }
    }

    usize bytes_to_move = (darray->size - index) * darray->element_size;
    if (bytes_to_move > 0) {
        memmove(darray->data + (index + 1) * darray->element_size, darray->data + index * darray->element_size, bytes_to_move);
    }
    memcpy(darray->data + index * darray->element_size, element, darray->element_size);
    darray->size++;

    return EXIT_SUCCESS;
}

errno_t cstructs_darray_remove(cstructs_darray_t* darray, usize index) {
    if (CSTRUCTS_DARRAY_EMPTY(darray)) {
        return EXIT_FAILURE;
    }

    if (index >= darray->size) {
        return EXIT_FAILURE;
    }

    usize bytes_to_move = (darray->size - index - 1) * darray->element_size;
    if (bytes_to_move > 0) {
        memmove(darray->data + index * darray->element_size, darray->data + (index + 1) * darray->element_size, bytes_to_move);
    }
    darray->size--;

    if (CSTRUCTS_DARRAY_SIZE_UNDER_THRESHOLD(darray)) {
        errno_t result = cstructs_darray_shrink(darray);
        if (result != EXIT_SUCCESS) {
            return result;
        }
    }

    return EXIT_SUCCESS;
}
// ---------------------------------------------------------------------

void* cstructs_darray_get(const cstructs_darray_t* darray, usize index) {
    if (index >= darray->size) {
        return NULL;
    }

    return darray->data + index * darray->element_size;
}