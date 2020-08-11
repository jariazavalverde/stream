#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "../stream.h"

#ifndef STREAM_INTERVAL_H
#define STREAM_INTERVAL_H

Stream *stream_from_interval(int seconds);
void *__interval_on_subscribe(Stream *stream, Subscriber *subscriber, void *arg);
void *__interval_on_join(void *arg);
void *__interval_thread(void *arg);

#endif