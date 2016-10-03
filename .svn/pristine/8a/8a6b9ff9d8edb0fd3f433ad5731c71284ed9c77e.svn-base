#if !defined (TREE_H)
#define TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "input.h"

typedef struct tree {
	char * name;
	float height;
	float weight;
	struct tree * left;
	struct tree * right;
} tree;

tree * maketree (list ** head, int strct);
int searchtree (tree * root, char * name);
void deletetree (tree * root);
#endif
