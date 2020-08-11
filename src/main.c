// gcc *.c *.h stream/*.c stream/*.h -lpthread -o react

#include "stream.h"
#include "subscriber.h"
#include "handler.h"
#include "stream/interval.h"
#include "stream/array.h"

int main() {
    int even[] = {2,4,6,8,10};
    // create streams
    Stream *s_interval = stream_from_interval(1);
    Stream *s_array_int = stream_from_array_int(even, 5);
    // subscribe
    Subscriber *s1 = stream_subscribe(s_interval, h_println_int);
    Subscriber *s2 = stream_subscribe(s_array_int, h_println_int);
    // wait
    subscriber_join(s1);
    subscriber_join(s2);
    // free memory
    stream_free(s_interval);
    stream_free(s_array_int);
    subscriber_free(s1);
    subscriber_free(s2);
}