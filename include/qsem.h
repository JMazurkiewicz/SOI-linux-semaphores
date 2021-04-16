#ifndef QSEM_H
#define QSEM_H

#include <semaphore.h>

#include "def.h"

#define QSEM_MUTEX 0
#define QSEM_EMPTY_SEM 1
#define QSEM_FULL_SEM 2

struct qsem {
    sem_t* mutex[QUEUE_COUNT];
    sem_t* empty_sem[QUEUE_COUNT];
    sem_t* full_sem[QUEUE_COUNT];
};

void qsem_open(struct qsem* sem);
void qsem_close(struct qsem* sem);

#endif
