#ifndef QPROC_H
#define QPROC_H

#include <stdio.h>

#include "def.h"
#include "qsem.h"
#include "queue.h"

struct proc_data {
    FILE* file;

    int queue_descriptor[QUEUE_COUNT];
    int queue_buffer_descriptor[QUEUE_COUNT];

    int* queue_buffer[QUEUE_COUNT];
    struct queue* queue[QUEUE_COUNT];

    struct qsem sem;
};

void proc_init(struct proc_data* data);
void proc_log(struct proc_data* data, const char* fmt, ...);
void proc_term(struct proc_data* data);

void proc_wait(struct proc_data* data, int sem_type, int queue_id);
void proc_post(struct proc_data* data, int sem_type, int queue_id);

#endif
