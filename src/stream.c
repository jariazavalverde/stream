#include "stream.h"

Stream *stream_alloc() {
    Stream *stream = malloc(sizeof(Stream));
    stream->nb_subscribers = 0;
    stream->subscribers = NULL;
    stream->join = NULL;
    stream->join_arg = NULL;
    return stream;
}

void stream_free(Stream *stream) {
    free(stream->subscribers);
    free(stream->join_arg);
    free(stream);
}

Subscriber *stream_subscribe(Stream *stream, void * (*handler)(void *)) {
    Subscriber *subscriber;
    stream->subscribers = realloc(stream->subscribers, sizeof(Subscriber*) * (stream->nb_subscribers+1));
    if(stream->subscribers != NULL) {
        subscriber = subscriber_alloc(handler);
        stream->subscribers[stream->nb_subscribers] = subscriber;
        stream->nb_subscribers++;
        return subscriber;
    }
    return NULL;
}

void stream_send(Stream *stream, void *data) {
    int i;
    for(i = 0; i < stream->nb_subscribers; i++) {
        stream->subscribers[i]->handler(data);
    }
}

void stream_join(Stream *stream) {
    stream->join(stream->join_arg);
}