#if !defined (GRAPH_H)
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include "input.h"

#if !defined(LOADFACTOR)
#define LOADFACTOR (float)(0.5)
#endif

#if !defined(PARAMETER)
#define PARAMETER 7
#endif

typedef struct g
{
	int id;
	int ct;
	int visited;
	struct g ** arr;
	struct g * next;
} graph;

typedef struct STACK
{
    struct g * data;
    struct STACK * next;
} STACK;

void addlink (link * links, graph ** vertexes, int * count, int * size);
int searchneighbor (graph ** vertexes, int sid, int count);
graph * searchvert (graph ** vertexes, int sid, int size);
void width (graph * start);
int hash (int key, int size);
void printgraph (graph ** vertexes, int size);
graph ** remake(graph *** vertexes, link ** links, int count, int * size);
void euler (graph ** vertexes, int size, int vertexquality);
void deletegraph(graph ** vertexes, int size);

#endif 