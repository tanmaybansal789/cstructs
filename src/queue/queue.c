#include "queue/queue.h"

#include <stdio.h>

static errno_t cstructs_queue_grow(cstructs_queue_t* queue) {
    const usize new_capacity = queue->capacity * CSTRUCTS_QUEUE_GROWTH_FACTOR;

    void* new_data = malloc(new_capacity * queue->element_size);
    if (new_data == NULL) {
        return ENOMEM;
    }

    if (queue->tail >= queue->head) {
        // copy the data from the head to the tail - if they are equal, nothing will be copied
        memcpy(new_data, queue->data + queue->head * queue->element_size, queue->size * queue->element_size);
    } else {
        const usize tail_size = queue->capacity - queue->head;
        // if our current queue is : _ _ _ _ _ _ _] _ [_ _
        //                                             ^ ^ are copied to the beginning of the new queue
        //                           ^ ^ ^ ^ ^ ^ ^ are copied to the next part of the new queue
        //
        //                          [_ _ _ _ _ _ _ _ _] _ ... (the ... is the rest of the new queue, since its capacity is larger)
        memcpy(new_data, queue->data + queue->head * queue->element_size, tail_size * queue->element_size);
        memcpy(new_data + tail_size * queue->element_size, queue->data, queue->tail * queue->element_size);
    }

    free(queue->data);
    queue->data = new_data;
    queue->capacity = new_capacity;
    queue->head = 0;
    queue->tail = queue->size;

    return EXIT_SUCCESS;
}

static errno_t cstructs_queue_shrink(cstructs_queue_t* queue) {
    const usize new_capacity = queue->capacity / CSTRUCTS_QUEUE_SHRINK_FACTOR;
    if (new_capacity < queue->size) { // data will be lost
        return EXIT_FAILURE;
    }

    void* new_data = malloc(new_capacity * queue->element_size);
    if (new_data == NULL) {
        return ENOMEM;
    }

    if (queue->tail >= queue->head) {
        memcpy(new_data, queue->data + queue->head * queue->element_size, queue->size * queue->element_size);
    } else {
        const usize tail_size = queue->capacity - queue->head;
        memcpy(new_data, queue->data + queue->head * queue->element_size, tail_size * queue->element_size);
        memcpy(new_data + tail_size * queue->element_size, queue->data, queue->tail * queue->element_size);
    }

    free(queue->data);
    queue->data = new_data;
    queue->capacity = new_capacity;
    queue->head = 0;
    queue->tail = queue->size;

    return EXIT_SUCCESS;
}

// ---------------------------------------------------------------------

cstructs_queue_t cstructs_queue_create(usize element_size, usize capacity) {
    return (cstructs_queue_t) {
        .data = malloc(element_size * capacity),
        .element_size = element_size,
        .tail = 0,
        .head = 0,
        .size = 0,
        .capacity = capacity
    };
}

cstructs_queue_t* cstructs_queue_new(usize element_size, usize capacity) {
    cstructs_queue_t* queue = malloc(sizeof(cstructs_queue_t));
    if (queue == NULL) {
        return NULL;
    }

    *queue = cstructs_queue_create(element_size, capacity);
    return queue;
}

errno_t cstructs_queue_free(cstructs_queue_t* queue, bool free_queue) {
    free(queue->data);
    if (free_queue) { // this can be used if the queue was allocated on the heap
        free(queue);
    }

    return EXIT_SUCCESS;
}

// ---------------------------------------------------------------------

errno_t cstructs_queue_push(cstructs_queue_t* queue, const void* element) {
    if (queue->size == queue->capacity - 1) {
        const errno_t result = cstructs_queue_grow(queue);
        if (result != EXIT_SUCCESS) {
            return result;
        }
    }

    memcpy(queue->data + queue->tail * queue->element_size, element, queue->element_size);
    queue->tail = (queue->tail + 1) % queue->capacity;
    queue->size++;

    return EXIT_SUCCESS;
}

void* cstructs_queue_pop(cstructs_queue_t* queue) {
    if (CSTRUCTS_QUEUE_EMPTY(queue)) {
        return NULL;
    }

    void* element = malloc(queue->element_size);
    if (element == NULL) {
        return NULL;
    }

    memcpy(element, queue->data + queue->head * queue->element_size, queue->element_size);
    queue->head = (queue->head + 1) % queue->capacity;
    queue->size--;

    if (CSTRUCTS_QUEUE_SIZE_UNDER_THRESHOLD(queue)) {
        cstructs_queue_shrink(queue);
    }

    return element;
}

void* cstructs_queue_peek(const cstructs_queue_t* queue) {
    if (CSTRUCTS_QUEUE_EMPTY(queue)) {
        return NULL;
    }

    return queue->data + queue->head * queue->element_size;
}

// ---------------------------------------------------------------------

void* cstructs_queue_get(const cstructs_queue_t* queue, usize index) {
    if (index >= queue->size) {
        return NULL;
    }

    return queue->data + ((queue->head + index) % queue->capacity) * queue->element_size;
}