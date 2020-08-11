#include "interval.h"

Stream *stream_from_interval(int seconds) {
    Stream *stream = stream_alloc();
    int *subscribe_arg = malloc(sizeof(int));
    *subscribe_arg = seconds;
    stream->on_subscribe = __interval_on_subscribe;
    stream->subscribe_arg = subscribe_arg;
    return stream;
}

void *__interval_on_subscribe(Stream *stream, Subscriber *subscriber, void *arg) {
    int *seconds = (int *) arg;
    pthread_t *thread_id = malloc(sizeof(pthread_t));
    struct {
        Stream *stream;
        Subscriber *subscriber;
        int seconds;
    } *thread_arg = malloc(sizeof(struct {
        Stream *stream;
        Subscriber *subscriber;
        int seconds;
    }));
    thread_arg->stream = stream;
    thread_arg->subscriber = subscriber;
    thread_arg->seconds = *seconds;
    pthread_create(thread_id, NULL, __interval_thread, thread_arg);
    subscriber->on_join = __interval_on_join;
    subscriber->join_arg = (void *) thread_id;
}

void *__interval_on_join(void *arg) {
    pthread_t *thread_id = (pthread_t *) arg;
    pthread_join(*thread_id, NULL);
}

void *__interval_thread(void *arg) {
    struct {
        Stream *stream;
        Subscriber *subscriber;
        int seconds;
    } *data = arg;
    Stream *stream = data->stream;
    Subscriber *subscriber = data->subscriber;
    int seconds = data->seconds;
    int time = 0;
    free(arg);
    while(1) {
        sleep(seconds);
        time += seconds;
        subscriber->handler(&time);
    }
}