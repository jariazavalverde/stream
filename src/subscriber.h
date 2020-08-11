#include <stdlib.h>

#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

typedef struct Subscriber {
    void * (*handler)(void *);
} Subscriber;

Subscriber *subscriber_alloc(void * (*handler)(void *));
void subscriber_free(Subscriber *subscriber);

#endif