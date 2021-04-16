#ifndef PRODUCTION_H
#define PRODUCTION_H

typedef int (*producer_t)(void);

int producer_a(void);
int producer_b(void);

const char* get_producer_name(int val);

#endif
