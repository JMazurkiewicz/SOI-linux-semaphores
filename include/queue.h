#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

#include "def.h"

struct queue {
    int* memory;
    size_t size;
};

void qpush(struct queue* q, int val);
int qpop(struct queue* q);
size_t qsize(const struct queue* q);

const char* get_queue_name(int queue_id);

#endif
