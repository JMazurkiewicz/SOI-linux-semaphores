#ifndef PROC_H
#define PROC_H

#define PROC_COUNT 4
#define PROC_A 0
#define PROC_B 1
#define PROC_C 2
#define PROC_D 3

#define QUEUE_MAX_SIZE 4
#define QUEUE_COUNT 2
#define C_QUEUE 0
#define D_QUEUE 1

#define MAX_SENT_DATA 20
#if MAX_SENT_DATA % 2 != 0
# error "MAX_SENT_DATA" must have even value
#endif

#define PRODUCTION_A_TIME 500
#define PRODUCTION_B_TIME 300

#define PRODUCER_SLEEP_TIME 100
#define CONSUMER_SLEEP_TIME 800

#endif
