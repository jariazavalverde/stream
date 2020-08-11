#include <stdlib.h>
#include "subscriber.h"

#ifndef STREAM_H
#define STREAM_H

typedef struct Stream {
    void *(*on_submit)(struct Stream *, Subscriber *, void *, void *);
    void *(*on_subscribe)(struct Stream *, Subscriber *, void *);
    void *submit_arg;
    void *subscribe_arg;
} Stream;

Stream *stream_alloc();
void stream_free(Stream *stream);
Subscriber *stream_subscribe(Stream *stream, void * (*handler)(void *));
void stream_join(Stream *stream);
Stream *stream_filter(Stream *stream, int (*predicate)(void *));
Stream *stream_map(Stream *stream, void *(*fn)(void *));
Stream *stream_take(Stream *stream, int count);
void *__stream_on_submit_id(Stream *stream, Subscriber *subscriber, void *arg, void *elem);
void *__stream_on_submit_filter(Stream *stream, Subscriber *subscriber, void *arg, void *elem);
void *__stream_on_submit_map(Stream *stream, Subscriber *subscriber, void *arg, void *elem);
void *__stream_on_submit_take(Stream *stream, Subscriber *subscriber, void *arg, void *elem);

#endif