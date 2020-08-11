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

void *succ(void *arg) {
    int *elem = arg;
    int *result = malloc(sizeof(int));
    *result = *elem + 1;
    return result;
}

int main() {
    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    // create streams
    Stream *s_array_int = stream_from_array_int(arr, 10);
    Stream *s_interval = stream_from_interval(1);
    Stream *s_take = stream_take(s_interval, 5);
    Stream *s_map = stream_map(s_take, succ);
    Stream *s_filter = stream_filter(s_map, even);
    // subscribe
    Subscriber *s1 = stream_subscribe(s_array_int, h_println_int);
    Subscriber *s2 = stream_subscribe(s_filter, h_println_int);
    // wait
    subscriber_join(s1);
    subscriber_join(s2);
    // free memory
    stream_free(s_array_int);
    stream_free(s_interval);
    stream_free(s_map);
    stream_free(s_filter);
    stream_free(s_take);
    subscriber_free(s1);
    subscriber_free(s2);
}