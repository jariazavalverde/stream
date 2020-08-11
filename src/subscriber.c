#include "subscriber.h"

Subscriber *subscriber_alloc(void *(*handler)(void *)) {
    Subscriber *subscriber = malloc(sizeof(Subscriber));
    subscriber->handler = handler;
    subscriber->on_join = NULL;
    subscriber->join_arg = NULL;
    return subscriber;
}

void subscriber_free(Subscriber *subscriber) {
    free(subscriber->join_arg);
    free(subscriber);
}

void subscriber_join(Subscriber *subscriber) {
    if(subscriber->on_join != NULL)
        subscriber->on_join(subscriber->join_arg);
}