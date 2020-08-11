// gcc *.c *.h stream/*.c stream/*.h -lpthread -o react

#include "stream.h"
#include "subscriber.h"
#include "handler.h"
#include "stream/interval.h"
#include "stream/array.h"

int even(void *arg) {
    int *elem = arg;
    return *elem % 2 == 0;
}

int main() {
    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    // create streams
    Stream *s_interval = stream_from_interval(1);
    Stream *s_array_int = stream_from_array_int(arr, 10);
    Stream *s_filter = stream_filter(s_array_int, even);
    // subscribe
    Subscriber *s1 = stream_subscribe(s_interval, h_println_int);
    Subscriber *s2 = stream_subscribe(s_array_int, h_println_int);
    Subscriber *s3 = stream_subscribe(s_filter, h_println_int);
    // wait
    subscriber_join(s1);
    subscriber_join(s2);
    subscriber_join(s3);
    // free memory
    stream_free(s_interval);
    stream_free(s_array_int);
    stream_free(s_filter);
    subscriber_free(s1);
    subscriber_free(s2);
    subscriber_free(s3);
}