#if !defined (LIST_H)
#define LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "input.h"

typedef struct list {
	char * name;
	float height;
	float weight;
	struct list * next;
} list;

list * splitstring (char * str, int strn, int strct);
list * makelist (char ** strings, int strct);
void sortlist (list * head);
void deletelist (list * head);
#endif