#if !defined (INPUT_H)
#define INPUT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#if !defined(MAXSTRLEN) 
#define MAXSTRLEN 1000
#endif
#if !defined(MAXNAME)
#define MAXNAME 500
#endif
#if !defined(MAXHEIGHT)
#define MAXHEIGHT 200
#endif

int inputcheck(int argc, char ** argv);
int filecheck(int argc, char ** argv, FILE* input_file);
int islaststring(char * string);
int checkstring(char * string);
char ** strings(FILE * input_file);
int stringscount(char ** strings);
#endif