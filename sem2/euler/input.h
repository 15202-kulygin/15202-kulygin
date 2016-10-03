#if !defined (INPUT_H)
#define INPUT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct l 
{
	int a;
	int b;
} link;

int inputcheck(int argc, char ** argv);
int filecheck(int argc, char ** argv, FILE* input_file);
link ** makelinks(FILE * input_file);



#endif 