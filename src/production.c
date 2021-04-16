#include "production.h"

#include <stdlib.h>
#include <unistd.h>

#include "def.h"
#include "utility.h"

int producer_a(void) {
    milli_sleep(PRODUCTION_A_TIME);
    return 3 * (rand() % 1000);
}

int producer_b(void) {
    static int val = 0;

    ++val;
    if(val % 3 == 0) {
        ++val;
    }

    milli_sleep(PRODUCTION_B_TIME);
    return val;
}

const char* get_producer_name(int val) {
    return (val % 3 == 0) ? "process-a" : "process-b";
}
