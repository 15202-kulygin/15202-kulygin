#if !defined (FIBO_H)
#define FIBO_H

#include <stdio.h>
#include <math.h>
#include "graph.h"

typedef enum hasdeletedkids
{
	IS_TRUE, IS_FALSE 
} hasdeletedkids;

typedef struct node {
	struct node * parent;     // указатель на отца
	struct node * child;      // указатель на одного из сыновей
	struct node * left;       // указатель на левого брата
	struct node * right;      // указатель на правого брата
 	int childct;       // количество дочерних узлов
 	enum hasdeletedkids mark;        // метка - был ли удален один из дочерних элементов
 	graph * data;
 	int Fvalue;
 	int Gvalue;
 	int Hvalue;
} node;

typedef struct hp
{
	struct node * min;        // узел с минимальным Fvalue
	int rootsct; // количество узлов
} HEAP;

int heuristic (graph * first, graph * second);
void addheap (node * toadd, HEAP * H);
node * extractheap (HEAP * H);
node * createnodeheap (graph * current, graph * end, int cur_weight);
void changevalueheap(HEAP * heap, node * current, int newvalue) ;
void cut_to_root(HEAP * heap, node * current, node * par); // utility for changevalueheap
void cascade_cut(HEAP * heap, node * current); // utility for changevalueheap
int distance (graph * startvertex, graph * endvertex);
node * findheap(node * start, graph * vertex, int rootsct); // find a node, that contains the search vertex
void deleteheap (HEAP * heap);
void deletechildtree (node * start);


#endif

