#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

#include "def.h"

struct queue {
    int* memory;
    size_t size;
};

void queue_init(struct queue* q, int* mem);
void queue_push(struct queue* q, int val);
int queue_pop(struct queue* q);
size_t queue_size(const struct queue* q);

const char* get_queue_name(int queue_id);

#endif
