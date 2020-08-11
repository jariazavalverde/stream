// gcc *.c *.h stream/*.c stream/*.h -lpthread -o react

#include "stream.h"
#include "subscriber.h"
#include "handler.h"
#include "stream/interval.h"

int main() {
    // create
    Stream *s_interval = make_interval(1);
    Subscriber *s1 = stream_subscribe(s_interval, h_println_int);
    // wait
    stream_join(s_interval);
    // free
    stream_free(s_interval);
    subscriber_free(s1);
}