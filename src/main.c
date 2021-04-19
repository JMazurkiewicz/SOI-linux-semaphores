#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "production.h"
#include "proc_data.h"
#include "utility.h"

void producer_routine(struct proc_data* data, producer_t producer, const char* name) {
    proc_log(data, "Producent \"%s\" rozpoczął pracę [pid = %d]\n", name, getpid());
    
    for(int i = 0; i < MAX_SENT_DATA; ++i) {
        const int receiver_queue = (i % QUEUE_COUNT);
        const int val = producer();

        proc_wait(data, QSEM_EMPTY_SEM, receiver_queue);
        proc_wait(data, QSEM_MUTEX, receiver_queue);
        
        queue_push(data->queue[receiver_queue], val);
        proc_log(data, "[%s] %s: wysłano wiadomość nr %04d o wartości \"%4d\" [kolejka: %s, rozmiar kolejki: %zu]\n",
                 str_now(), name, i+1, val, get_queue_name(receiver_queue), queue_size(data->queue[receiver_queue]));
        
        proc_post(data, QSEM_MUTEX, receiver_queue);
        proc_post(data, QSEM_FULL_SEM, receiver_queue);

        milli_sleep(PRODUCER_SLEEP_TIME);
    }

    proc_log(data, "Producent \"%s\" zakończył pracę [pid = %d]\n", name, getpid());
}

void consumer_routine(struct proc_data* data, int queue_id, const char* name) {
    proc_log(data, "Konsument \"%s\" rozpoczął pracę [pid = %d]\n", name, getpid());
    
    for(int i = 0; i < MAX_SENT_DATA; ++i) {
        proc_wait(data, QSEM_FULL_SEM, queue_id);
        proc_wait(data, QSEM_MUTEX, queue_id);
        
        const int val = queue_pop(data->queue[queue_id]);
        proc_log(data, "[%s] %s: otrzymano wiadomość nr %04d o treści \"%4d\" [kolejka: %s, rozmiar kolejki: %zu, nadawca: %s]\n",
                 str_now(), name, i+1, val, get_queue_name(queue_id), queue_size(data->queue[queue_id]), get_producer_name(val));
        
        proc_post(data, QSEM_MUTEX, queue_id);
        proc_post(data, QSEM_EMPTY_SEM, queue_id);

        milli_sleep(CONSUMER_SLEEP_TIME);
    }

    proc_log(data, "Konsument \"%s\" zakończył pracę [pid = %d]\n", name, getpid());
}

int main() {
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    puts("Inicjalizacja głównej struktury");
    struct proc_data data;
    proc_init(&data);

    for(int i = 0; i < PROC_COUNT; ++i) {
        printf("Uruchamianie procesów [%d]\n", i);
        const int pid = fork();
        
        if(pid == 0) {
            switch(i) {
            case PROC_A:
                srand((unsigned) time(NULL));
                producer_routine(&data, &producer_a, "process-a");
                break;

            case PROC_B:
                //producer_routine(&data, &producer_b, "process-b");
                break;

            case PROC_C:
                consumer_routine(&data, C_QUEUE, "process-c");
                break;

            case PROC_D:
                consumer_routine(&data, D_QUEUE, "process-d");
                break;
            }

            exit(0);
        } else if(pid == -1) {
            failure("main%fork");
            break;
        }

        milli_sleep(100);
    }
    
    while(wait(NULL) > 0);
    puts("Czyszczenie zasobów");
    proc_term(&data);
}
