#include <stdlib.h>
#include "subscriber.h"

#ifndef STREAM_H
#define STREAM_H

typedef struct Stream {
    int nb_subscribers;
    Subscriber **subscribers;
    void * (*join)(void *);
    void *join_arg;
} Stream;

Stream *stream_alloc();
void stream_free(Stream *stream);
void stream_send(Stream *stream, void *data);
void stream_join(Stream *stream);
Subscriber *stream_subscribe(Stream *stream, void * (*handler)(void *));

#endif