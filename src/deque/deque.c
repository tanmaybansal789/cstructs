#include "deque/deque.h"

static errno_t cstructs_deque_grow(cstructs_deque_t* deque) {
    const usize new_capacity = deque->capacity * 2;

    void* new_data = malloc(new_capacity * deque->element_size);
    if (new_data == NULL) {
        return ENOMEM;
    }

    if (deque->size == 0) {
        // update attributes, nothing to copy
        free(deque->data);
        deque->data = new_data;
        deque->capacity = new_capacity;
        deque->tail = 0;
        deque->head = 0;
        return EXIT_SUCCESS;
    }

    // copy data to new location
    if (deque->tail >= deque->head) {
        // remember that the head is the next position, not the current one -
        // there should not be a case where head == tail and size != 0, as data will be lost
        memcpy(new_data, deque->data + deque->head * deque->element_size, deque->size * deque->element_size);
    } else {
        const usize tail_size = deque->capacity - deque->head;
        memcpy(new_data, deque->data + deque->head * deque->element_size, tail_size * deque->element_size);
        memcpy(new_data + tail_size * deque->element_size, deque->data, deque->tail * deque->element_size);
    }

    // update attributes
    free(deque->data);
    deque->data = new_data;
    deque->capacity = new_capacity;
    deque->head = 0;
    deque->tail = deque->size;

    return EXIT_SUCCESS;
}

static errno_t cstructs_deque_shrink(cstructs_deque_t* deque) {
    const usize new_capacity = deque->capacity / 2;
    if (new_capacity < deque->size) { // data will be lost
        return EXIT_FAILURE;
    }

    void* new_data = malloc(new_capacity * deque->element_size);
    if (new_data == NULL) {
        return ENOMEM;
    }

    if (deque->head <= deque->tail) {
        memcpy(new_data, deque->data + deque->head * deque->element_size, deque->size * deque->element_size);
    } else {
        const usize tail_size = deque->capacity - deque->head;
        memcpy(new_data, deque->data + deque->head * deque->element_size, tail_size * deque->element_size);
        memcpy(new_data + tail_size * deque->element_size, deque->data, deque->tail * deque->element_size);
    }

    free(deque->data);
    deque->data = new_data;
    deque->capacity = new_capacity;
    deque->head = 0;
    deque->tail = deque->size;

    return EXIT_SUCCESS;
}

// ---------------------------------------------------------------------

cstructs_deque_t cstructs_deque_create(usize element_size, usize capacity) {
    return (cstructs_deque_t) {
        .data = malloc(element_size * capacity),
        .element_size = element_size,
        .tail = 0,
        .head = 0,
        .size = 0,
        .capacity = capacity
    };
}

cstructs_deque_t* cstructs_deque_new(usize element_size, usize capacity) {
    cstructs_deque_t* deque = malloc(sizeof(cstructs_deque_t));
    if (deque == NULL) {
        return NULL;
    }

    *deque = cstructs_deque_create(element_size, capacity);
    return deque;
}

errno_t cstructs_deque_free(cstructs_deque_t* deque, bool free_deque) {
    free(deque->data);
    if (free_deque) { // this can be used if the deque was allocated on the heap
        free(deque);
    }

    return EXIT_SUCCESS;
}

// ---------------------------------------------------------------------

errno_t cstructs_deque_push_front(cstructs_deque_t* deque, const void* element) {
    if (deque->size == deque->capacity - 1) {
        if (cstructs_deque_grow(deque) != EXIT_SUCCESS) {
            return ENOMEM;
        }
    }

    if (deque->head == 0) {
        deque->head = deque->capacity - 1;
    } else {
        deque->head--;
    }

    memcpy(deque->data + deque->head * deque->element_size, element, deque->element_size);
    deque->size++;

    return EXIT_SUCCESS;
}

errno_t cstructs_deque_push_back(cstructs_deque_t* deque, const void* element) {
    if (deque->size == deque->capacity - 1) {
        if (cstructs_deque_grow(deque) != EXIT_SUCCESS) {
            return ENOMEM;
        }
    }

    memcpy(deque->data + deque->tail * deque->element_size, element, deque->element_size);
    deque->tail = (deque->tail + 1) % deque->capacity;
    deque->size++;

    return EXIT_SUCCESS;
}

void* cstructs_deque_pop_front(cstructs_deque_t* deque) {
    if (CSTRUCTS_DEQUE_EMPTY(deque)) {
        return NULL;
    }

    void* element = malloc(deque->element_size);
    if (element == NULL) {
        return NULL;
    }

    memcpy(element, deque->data + deque->head * deque->element_size, deque->element_size);

    deque->head = (deque->head + 1) % deque->capacity;
    deque->size--;

    if (CSTRUCTS_DEQUE_SIZE_UNDER_THRESHOLD(deque)) {
        cstructs_deque_shrink(deque);
    }

    return element;
}

void* cstructs_deque_pop_back(cstructs_deque_t* deque) {
    if (deque->size == 0) {
        return NULL;
    }

    if (deque->tail == 0) {
        deque->tail = deque->capacity - 1;
    } else {
        deque->tail--;
    }

    void* element = malloc(deque->element_size);
    if (element == NULL) {
        return NULL;
    }

    memcpy(element, deque->data + deque->tail * deque->element_size, deque->element_size);

    deque->size--;

    if (CSTRUCTS_DEQUE_SIZE_UNDER_THRESHOLD(deque)) {
        cstructs_deque_shrink(deque);
    }

    return element;
}

// ---------------------------------------------------------------------

void* cstructs_deque_peek_front(const cstructs_deque_t* deque) {
    if (deque->size == 0) {
        return NULL;
    }

    return deque->data + deque->head * deque->element_size;
}

void* cstructs_deque_peek_back(const cstructs_deque_t* deque) {
    if (deque->size == 0) {
        return NULL;
    }

    return deque->data + deque->tail * deque->element_size;
}

// ---------------------------------------------------------------------

void* cstructs_deque_get(const cstructs_deque_t* deque, usize index) {
    if (index >= deque->size) {
        return NULL;
    }

    return deque->data + ((deque->head + index) % deque->capacity) * deque->element_size;
}