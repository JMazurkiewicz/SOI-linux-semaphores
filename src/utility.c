#include "utility.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

const char* str_now() {
    static char buffer[9];

    time_t time_now;
    time(&time_now);
    strftime(buffer, 9, "%H:%M:%S", localtime(&time_now));
    return buffer;
}

void milli_sleep(int milliseconds) {
    usleep(1000 * milliseconds);
}

void failure(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}
