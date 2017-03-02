#include "util.h"

#include <stdio.h>
#include <string.h>
#include "header.h"

void * checkMalloc(size_t size) {
    void *ptr = malloc(size);

    if(ptr == NULL) {
        perror("Malloc error");
    }

    return ptr;
}

int extendStr(char **str, size_t *length) {
    char *newStr = (char *)checkMalloc(sizeof(char) * (*length) * BUFFER_RATIO);
    if(!newStr) {
        fprintf(stderr, "Error: Can't save string\n");
        return EXIT_FAILURE;
    }

    memcpy(newStr, *str, (*length));
    *length *= BUFFER_RATIO;
    free(*str);
    *str = newStr;

    return EXIT_SUCCESS;
}

int addChar(char **str, size_t *length, size_t *pos, char c) {
    if(*pos < *length) {
        (*str)[(*pos)++] = c;
        return EXIT_SUCCESS;
    }

    if(*pos >= *length && extendStr(str, length) != 0) {
        return EXIT_FAILURE;
    }
    (*str)[(*pos)++] = c;

    return EXIT_SUCCESS;
}

