#include "array.h"

Stream *stream_from_array_int(int *array, int length) {
    Stream *stream = stream_alloc();
    struct {
        int *array;
        int length;
    } *subscribe_arg = malloc(sizeof(struct {
        int *array;
        int length;
    }));
    subscribe_arg->array = array;
    subscribe_arg->length = length;
    stream->on_subscribe = __array_int_on_subscribe;
    stream->subscribe_arg = subscribe_arg;
    return stream;
}

void *__array_int_on_subscribe(Stream *stream, Subscriber *subscriber, void *arg) {
    int i;
    struct { int *array; int length; } *data = arg;
    int *array = data->array;
    int length = data->length;
    for(i = 0; i < length && subscriber->subscribed; i++)
        stream->on_submit(stream, subscriber, stream->submit_arg, &(array[i]));
}