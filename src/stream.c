#include "stream.h"

Stream *stream_alloc() {
    Stream *stream = malloc(sizeof(Stream));
    stream->on_subscribe = NULL;
    stream->subscribe_arg = NULL;
    return stream;
}

void stream_free(Stream *stream) {
    free(stream->subscribe_arg);
    free(stream);
}

Subscriber *stream_subscribe(Stream *stream, void * (*handler)(void *)) {
    Subscriber *subscriber = subscriber_alloc(handler);
    if(subscriber == NULL)
        return NULL;
    if(stream->on_subscribe != NULL)
        stream->on_subscribe(stream, subscriber, stream->subscribe_arg);
    return subscriber;
}