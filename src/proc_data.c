#include "proc_data.h"

#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

#include "utility.h"

static const char* NAMES[] = {
    "JCM_c_queue", "JCM_c_queue_buffer",
    "JCM_d_queue", "JCM_d_queue_buffer"
};

#define QUEUE_NAME(i) NAMES[2*i]
#define QUEUE_BUFFER_NAME(i) NAMES[2*i + 1]
#define NAMES_COUNT (sizeof(NAMES) / sizeof(const char*))

static void qmem_open(struct proc_data* data) {
    for(int i = 0; i < QUEUE_COUNT; ++i) {
        printf("Tworzenie pamięci współdzielonej [%d]\n", i);
        int result;

        // open shared memory
        result = shm_open(QUEUE_BUFFER_NAME(i), O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
        if(result == -1) {
            failure("qmem_open%shm_open%queue_buffer_descriptor");
        } else {
            data->queue_buffer_descriptor[i] = result;
        }

        result = shm_open(QUEUE_NAME(i), O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
        if(result == -1) {
            failure("qmem_open%shm_open%queue_descriptor");
        } else {
            data->queue_descriptor[i] = result;
        }

        // truncate file to requires sizes
        result = ftruncate(data->queue_buffer_descriptor[i], QUEUE_MAX_SIZE * sizeof(int));
        if(result == -1) {
            failure("qmem_open%ftruncate%queue_buffer_descriptor");
        }

        result = ftruncate(data->queue_descriptor[i], sizeof(struct queue));
        if(result == -1) {
            failure("qmem_open%ftruncate%queue_descriptor");
        }
    }

    // map files into memory
    for(int i = 0; i < QUEUE_COUNT; ++i) {
        printf("Mapowanie pamięci [%d]\n", i);
        void* result;

        result = (int*) mmap(NULL, QUEUE_MAX_SIZE * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, data->queue_buffer_descriptor[i], 0);
        if(result == (void*)(-1)) {
            failure("qmem_open%mmap%queue_buffer");
        } else {
            data->queue_buffer[i] = result;
        }

        result = (struct queue*) mmap(NULL, sizeof(struct queue), PROT_READ | PROT_WRITE, MAP_SHARED, data->queue_descriptor[i], 0);
        if(result == (void*)(-1)) {
            failure("qmem_open%mmap%queue");
        } else {
            data->queue[i] = result;
        }

        // init queue with data
        data->queue[i]->memory = data->queue_buffer[i];
        data->queue[i]->size = 0;
    }
}

static void qmem_close(struct proc_data* data) {
    for(int i = QUEUE_COUNT; i-- > 0; ) {
        printf("Zamykanie pamięci współdzielonej [%d]\n", i);

        munmap(data->queue[i], sizeof(struct queue));
        munmap(data->queue_buffer, QUEUE_MAX_SIZE * sizeof(int));

        shm_unlink(QUEUE_NAME(i));
        shm_unlink(QUEUE_BUFFER_NAME(i));
    }
}

void proc_init(struct proc_data* data) {
    data->file = fopen("semaphores.log", "w");
    if(data->file == NULL) {
        failure("proc_data_fopen");
    }
    setbuf(data->file, NULL);

    qsem_open(&data->sem);
    qmem_open(data);
}


void proc_log(struct proc_data* data, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(data->file, fmt, args);
    va_end(args);
}

void proc_term(struct proc_data* data) {
    qmem_close(data);
    qsem_close(&data->sem);
    fclose(data->file);
}

void proc_wait(struct proc_data* data, int sem_type, int queue_id) {
    switch(sem_type) {
    case QSEM_MUTEX:
        sem_wait(data->sem.mutex[queue_id]);
        break;
        
    case QSEM_EMPTY_SEM:
        sem_wait(data->sem.empty_sem[queue_id]);
        break;

    case QSEM_FULL_SEM:
        sem_wait(data->sem.full_sem[queue_id]);
        break;
    }
}

void proc_post(struct proc_data* data, int sem_type, int queue_id) {
    switch(sem_type) {
    case QSEM_MUTEX:
        sem_post(data->sem.mutex[queue_id]);
        break;

    case QSEM_EMPTY_SEM:
        sem_post(data->sem.empty_sem[queue_id]);
        break;

    case QSEM_FULL_SEM:
        sem_post(data->sem.full_sem[queue_id]);
        break;
    }
}
