#include <stdlib.h>
#include "subscriber.h"

#ifndef STREAM_H
#define STREAM_H

typedef struct Stream {
    void *(*on_subscribe)(struct Stream *, Subscriber *, void *);
    void *subscribe_arg;
} Stream;

Stream *stream_alloc();
void stream_free(Stream *stream);
Subscriber *stream_subscribe(Stream *stream, void * (*handler)(void *));
void stream_join(Stream *stream);

#endif