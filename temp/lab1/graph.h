#if !defined (GRAPH_H)
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include "input.h"

#if !defined(P)
#define P 7
#endif

#if !defined(SIZE)
#define SIZE 2
#endif

#if !defined(LOADFACTOR)
#define LOADFACTOR (float)(0.5)
#endif

typedef struct g
{
	int id;
	int ct;
	int visited;
	struct g ** arr;
	struct g * next;
} graph;
typedef struct q
{
	struct g * data;
	struct q * next;
} queue;

void addlink (link * links, graph ** vertexes, int * count, int * size);
int searchvert (graph ** vertexes, int id, int count);
void width (graph * start);
int hash (int key, int size);
graph * search (graph ** vertexes, int key, int size);
graph ** remake(graph ** vertexes, int * size);


#endif 