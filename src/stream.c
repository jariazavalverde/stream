#include "stream.h"

Stream *stream_alloc() {
    Stream *stream = malloc(sizeof(Stream));
    stream->on_submit = __stream_on_submit_id;
    stream->on_subscribe = NULL;
    stream->submit_arg = NULL;
    stream->subscribe_arg = NULL;
    return stream;
}

void stream_free(Stream *stream) {
    if(stream->submit_arg != NULL)
        free(stream->submit_arg);
    if(stream->subscribe_arg != NULL)
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

Stream *stream_filter(Stream *stream, int (*predicate)(void *)) {
    Stream *out = stream_alloc();
    struct {
        Stream *stream;
        int (*predicate)(void *);
    } *submit_arg = malloc(sizeof(struct {
        Stream *stream;
        int (*predicate)(void *);
    }));
    submit_arg->stream = stream;
    submit_arg->predicate = predicate;
    out->on_submit = __stream_on_submit_filter;
    out->on_subscribe = stream->on_subscribe;
    out->submit_arg = submit_arg;
    out->subscribe_arg = stream->subscribe_arg;
    return out;
}

Stream *stream_map(Stream *stream, void *(*fn)(void *)) {
    Stream *out = stream_alloc();
    struct {
        Stream *stream;
        void *(*fn)(void *);
    } *submit_arg = malloc(sizeof(struct {
        Stream *stream;
        void *(*fn)(void *);
    }));
    submit_arg->stream = stream;
    submit_arg->fn = fn;
    out->on_submit = __stream_on_submit_map;
    out->on_subscribe = stream->on_subscribe;
    out->submit_arg = submit_arg;
    out->subscribe_arg = stream->subscribe_arg;
    return out;
}

void *__stream_on_submit_id(Stream *stream, Subscriber *subscriber, void *arg, void *elem) {
    return subscriber->handler(elem);
}

void *__stream_on_submit_filter(Stream *stream, Subscriber *subscriber, void *arg, void *elem) {
    struct { Stream *stream; int (*predicate)(void *); } *data = arg;
    Stream *outer = data->stream;
    int (*predicate)(void *) = data->predicate;
    if(predicate(elem))
        return outer->on_submit(outer, subscriber, outer->submit_arg, elem);
}

void *__stream_on_submit_map(Stream *stream, Subscriber *subscriber, void *arg, void *elem) {
    struct { Stream *stream; void *(*fn)(void *); } *data = arg;
    Stream *outer = data->stream;
    void *(*fn)(void *) = data->fn;
    void *map = fn(elem);
    void *result = outer->on_submit(outer, subscriber, outer->submit_arg, map);
    free(map);
    return result;
}