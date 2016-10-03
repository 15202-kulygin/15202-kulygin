#if !defined(HASH_H)
#define HASH_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#if !defined(M)
#define M 50000
#endif
#if !defined(LOADFACTOR)
#define LOADFACTOR (float)(0.5)
#endif

typedef struct HT {
	char * name;
	float height;
	float weight;
	struct HT * next;
} ht;

char ** makekeys (char ** strings, int strct);
ht ** maketables (char ** strings, int strct);
ht ** makeht (long long int size);
int hash (char * key, long long int size);
void add (ht ** hashtable, long long int size, char * key, ht * table);
ht ** remake(ht ** hashtable, long long int * size, char ** keys, ht ** tables, int strct);
int search (char * key, ht ** hashtable, long long int size);
void printtable (ht * table);
void printht (ht ** hashtable, long long int size);
void delete (char * key, ht ** hashtable, long long int size);
void deleteht (ht ** hashtable, long long int size);

#endif