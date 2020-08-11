#include "../stream.h"
#include "../subscriber.h"

#ifndef STREAM_ARRAY_H
#define STREAM_ARRAY_H

Stream *stream_from_array_int(int *array, int length);
void *__array_int_on_subscribe(Stream *stream, Subscriber *subscriber, void *arg);

#endif