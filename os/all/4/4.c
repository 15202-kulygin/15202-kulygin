#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"
#include "util.h"

struct ListNode {
    char *str;
    struct ListNode *next;
};

struct List {
    struct ListNode *first;
    struct ListNode *last;
    unsigned int count;
};

int listInit(struct List **list) {
    *list = (struct List *)checkMalloc(sizeof(struct List));
    if(*list == NULL) {
        return MALLOC_ERROR;
    }

    (*list)->first = NULL;
    (*list)->last = NULL;
    (*list)->count = 0;

    return EXIT_SUCCESS;
}

void listDestroy(struct List **list) {
    if(!(*list)) {
        fprintf(stderr, "Error: Pointer can't be null\n");
        return;
    }

    for (struct ListNode *toDel = (*list)->first; toDel != NULL;) {
        struct ListNode *tmp = toDel->next;
        toDel->next = NULL;
        free(toDel->str);
        free(toDel);
        toDel = tmp;
    }
    free(*list);
    *list = NULL;
}

int addNode(struct List **list, const char *str) {
    if(!(*list)) {
        fprintf(stderr, "Error: Pointer can't be null\n");
        return NULL_POINTER_ERROR;
    }

    struct ListNode *newNode = (struct ListNode *)checkMalloc(sizeof(struct ListNode));
    if(!newNode) {
        return MALLOC_ERROR;
    }

    size_t length = strlen(str);
    newNode->str = (char *)checkMalloc(sizeof(char) * length + 1);
    if(!newNode->str) {
        free(newNode);
        return MALLOC_ERROR;
    }

    memcpy(newNode->str, str, length + 1);
    if((*list)->first == NULL) {
        (*list)->first = newNode;
    }
    if((*list)->last == NULL) {
        (*list)->last = newNode;
    }
    (*list)->last->next = newNode;
    (*list)->last = newNode;
    newNode->next = NULL;
    ++(*list)->count;

    return EXIT_SUCCESS;
}

int extendStr(char **str, size_t *length) {
    char *newStr = (char *)checkMalloc(sizeof(char) * (*length) * BUFFER_RATIO);
    if(!newStr) {
        fprintf(stderr, "Error: Can't save string\n");
        return MALLOC_ERROR;
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
        return SAVE_STR_ERROR;
    }
    (*str)[(*pos)++] = c;

    return EXIT_SUCCESS;
}



int main() {
    printf("Please, enter string:\n");

    size_t length = BUFFER_LENGTH;
    char *str = (char *)checkMalloc(sizeof(char) * length);
    if(!str) {
        return MALLOC_ERROR;
    }

    struct List *list = NULL;
    if(listInit(&list) != EXIT_SUCCESS) {
        free(str);
        return MALLOC_ERROR;
    }

    size_t pos = 0;
    char c = (char) getc(stdin);

    while(c != '.') {
        while(c != '\n') {
            if(addChar(&str, &length, &pos, c) != EXIT_SUCCESS) {
                free(str);
                listDestroy(&list);
                return SAVE_STR_ERROR;
            }
            c = (char)getc(stdin);
        }

        if(!pos) {
            c = (char)getc(stdin);
            continue;
        }

        if(addChar(&str, &length, &pos, 0) != EXIT_SUCCESS) {
            free(str);
            listDestroy(&list);
            return SAVE_STR_ERROR;

        }

        if(addNode(&list, str) != EXIT_SUCCESS) {
            free(str);
            listDestroy(&list);
            return SAVE_STR_ERROR;

        }

        c = (char)getc(stdin);
        pos = 0;
    }

    //Print all strings
    for(struct ListNode *node = list->first; node != NULL; node = node->next) {
        printf("%s\n", node->str);
    }

    free(str);
    listDestroy(&list);

    return EXIT_SUCCESS;
}
