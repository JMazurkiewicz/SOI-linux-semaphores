#include "qsem.h"

#include <fcntl.h>
#include <stdio.h>

#include "queue.h"
#include "utility.h"

static const char* NAMES[] = {
    "JCM_c_queue_mutex", "JCM_c_queue_empty_sem", "JCM_c_queue_full_sem",
    "JCM_d_queue_mutex", "JCM_d_queue_empty_sem", "JCM_d_queue_full_sem"
};

#define QSEM_MUTEX_NAME(i) NAMES[3*i]
#define QSEM_EMPTY_SEM_NAME(i) NAMES[3*i + 1]
#define QSEM_FULL_SEM_NAME(i) NAMES[3*i + 2]

void qsem_open(struct qsem* sem) {
    for(int i = 0; i < QUEUE_COUNT; ++i) {
        printf("Tworzenie semaforów [%d]\n", i);
        sem_t* result;

        result = sem_open(QSEM_MUTEX_NAME(i), O_CREAT | O_EXCL, 0666, 1);
        if(result == SEM_FAILED) {
            failure("qsem_open%sem_open%mutex");
        } else {
            sem->mutex[i] = result;
        }

        result = sem_open(QSEM_EMPTY_SEM_NAME(i), O_CREAT | O_EXCL, 0666, QUEUE_MAX_SIZE);
        if(result == SEM_FAILED) {
            failure("qsem_open%sem_open%empty_sem");
        } else {
            sem->empty_sem[i] = result;
        }

        result = sem_open(QSEM_FULL_SEM_NAME(i), O_CREAT | O_EXCL, 0666, 0);
        if(result == SEM_FAILED) {
            failure("qsem_open%sem_open%full_sem");
        } else {
            sem->full_sem[i] = result;
        }
    }
}

void qsem_close(struct qsem* sem) {
    for(int i = QUEUE_COUNT; i-- > 0; ) {
        printf("Zamykanie semaforów [%d]\n", i);
        
        sem_unlink(QSEM_FULL_SEM_NAME(i));
        sem_close(sem->full_sem[i]);

        sem_unlink(QSEM_EMPTY_SEM_NAME(i));
        sem_close(sem->empty_sem[i]);

        sem_unlink(QSEM_MUTEX_NAME(i));
        sem_close(sem->mutex[i]);
    }
}
