#ifndef UTILITY_H
#define UTILITY_H

// get 'hh:mm:ss' string representing current moment
const char* str_now();

// sleep for 'n' milliseconds
void milli_sleep(int milliseconds);

// print error message and terminate
void failure(const char* msg);

#endif
