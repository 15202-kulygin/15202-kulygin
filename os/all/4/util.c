#include "util.h"

#include <stdio.h>

void * checkMalloc(size_t size) {
    void *ptr = malloc(size);

    if(ptr == NULL) {
        perror("Malloc error");
    }

    return ptr;
}
