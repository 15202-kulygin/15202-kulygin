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

typedef enum list
{
	OPENED, CLOSED, NOT_ADDED
} list;

typedef struct way
{
	struct g * vertex;
	int weight;
} way;

typedef struct g
{
	int x;
	int y;
	int ct;
	struct way ** ways;
	struct g * next;
	enum list mark;
} graph;

void addlink (link * links, graph ** vertexes, int * count, int * size);
int searchway (way ** vertexes, int sid1, int sid2, int sweight, int count);
graph * searchvert (graph ** vertexes, int sid1, int sid2, int size);
int hash (int x, int y, int size);
void printgraph (graph ** vertexes, int size);
graph ** remake(graph *** vertexes, link ** links, int count, int * size);
void deletegraph(graph ** vertexes, int size);

#endif 