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

typedef enum m
{
	FULL, 
	NOTFULL
} m; 

typedef struct way
{
	struct g * vertex;
	int capacity;
	int flow;
	enum m mark;
} way;

typedef struct g
{
	int number;
	int ct;
	int widthvisited;
	struct g * widthparent;
	struct way ** ways;
	struct g * next;
} graph;

typedef struct q
{
	struct g * vertex;
	struct q * next;
} queue;

void addlink (link * links, graph ** vertexes, int * count, int * size);
int searchway (way ** vertexes, int sid, int count);
graph * searchvert (graph ** vertexes, int sid, int size);
int hash (int number, int size);
void printgraph (graph ** vertexes, int size);
graph ** remake(graph *** vertexes, link ** links, int count, int * size);
void deletegraph(graph ** vertexes, int size);
int find_max_flow(graph * S, graph * T, graph ** vertexes, int size);
graph ** find_min_way (graph * start, graph * finish, int * length, graph ** vertexes, int size);
#endif 