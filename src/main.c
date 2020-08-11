// gcc *.c *.h stream/*.c stream/*.h -lpthread -o react

#include "stream.h"
#include "subscriber.h"
#include "handler.h"
#include "stream/interval.h"

int main() {
    // create streams
    Stream *s_interval = stream_from_interval(1);
    // subscribe
    Subscriber *s1 = stream_subscribe(s_interval, h_println_int);
    // wait
    subscriber_join(s1);
    // free memory
    stream_free(s_interval);
    subscriber_free(s1);
}