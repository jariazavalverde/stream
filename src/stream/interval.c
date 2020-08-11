#include "interval.h"

Stream *make_interval(int seconds) {
    Stream *stream = stream_alloc();
    pthread_t *thread_id = malloc(sizeof(pthread_t));
    struct { Stream *stream; int seconds; } *arg = malloc(sizeof(struct { Stream *stream; int seconds; }));
    arg->stream = stream;
    arg->seconds = seconds;
    stream->join = __interval_join;
    stream->join_arg = (void *) thread_id;
    pthread_create(thread_id, NULL, __interval_execution, arg);
    return stream;
}

void *__interval_execution(void *arg) {
    struct { Stream *stream; int seconds; } *data = arg;
    Stream *stream = data->stream;
    int seconds = data->seconds;
    int time = 0;
    free(arg);
    while(1) {
        sleep(seconds);
        time += seconds;
        stream_send(stream, &time);
    }
}

void *__interval_join(void *arg) {
    pthread_t *thread_id = (pthread_t *) arg;
    pthread_join(*thread_id, NULL);
}