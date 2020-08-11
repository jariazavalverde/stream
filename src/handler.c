#include "handler.h"

void *h_println_int(void *data) {
    printf("%d\n", (* (int *) data));
    return data;
}