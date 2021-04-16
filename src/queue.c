#include "queue.h"

#include <errno.h>

void qpush(struct queue* q, int val) {
    if(q->size < QUEUE_MAX_SIZE) {
        int* const new_location = q->memory + q->size;

        *new_location = val;
        ++q->size;
    }
}

int qpop(struct queue* q) {
    if(q->size > 0) {
        const int val = *q->memory;

        for(size_t i = 1; i < q->size; ++i) {
            q->memory[i - 1] = q->memory[i];
        }

        --q->size;
        return val;
    }

    errno = ENODATA;
    return -1;
}

size_t qsize(const struct queue* q) {
    return q->size;
}

const char* get_queue_name(int queue_id) {
    switch(queue_id) {
    case C_QUEUE:
        return "c-queue";
    case D_QUEUE:
        return "d-queue";
    default:
        return "unknown queue";
    }
}
