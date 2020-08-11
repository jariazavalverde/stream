#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "../stream.h"

#ifndef STREAM_INTERVAL_H
#define STREAM_INTERVAL_H

Stream *make_interval(int seconds);
void *__interval_execution(void *arg);
void *__interval_join(void *arg);

#endif