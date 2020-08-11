#include "subscriber.h"

Subscriber *subscriber_alloc(void * (*handler)(void *)) {
    Subscriber *subs = malloc(sizeof(Subscriber));
    subs->handler = handler;
    return subs;
}

void subscriber_free(Subscriber *subscriber) {
    free(subscriber);
}