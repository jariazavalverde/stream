#include <stdlib.h>

#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

typedef struct Subscriber {
    void *(*handler)(void *);
    void *(*on_join)(void *);
    void *join_arg;
} Subscriber;

Subscriber *subscriber_alloc(void *(*handler)(void *));
void subscriber_free(Subscriber *subscriber);
void subscriber_join(Subscriber *subscriber);

#endif