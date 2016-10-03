#include "graph.h"



void addlink (link * links, graph ** vertexes, int * count, int * size) /* add vertexes to graph if needed and create a link */
{
	int hash_a = hash(links->a1, links->a2, *size);
	int hash_b = hash(links->b1, links->b2, *size);
	if (NULL == searchvert(vertexes, links->a1, links->a2, *size))
	{
		graph * start = vertexes[hash_a];
		if (NULL != vertexes[hash_a])
		{
			while (NULL != vertexes[hash_a]->next)
				vertexes[hash_a] = vertexes[hash_a]->next;
		}
		graph * temp = (graph *) calloc (1, sizeof(graph));
		temp->x = links->a1;
		temp->y = links->a2;
		temp->ct = 0;
		temp->mark = NOT_ADDED;
		if (NULL == vertexes[hash_a])
			vertexes[hash_a] = temp;
		else
		{
			vertexes[hash_a]->next = temp;
			vertexes[hash_a] = start;
		}
		(*count)++;
	}
	if (NULL == searchvert(vertexes, links->b1, links->b2, *size))
	{
		graph * start = vertexes[hash_b];
		if (NULL != vertexes[hash_b])
		{
			while (NULL != vertexes[hash_b]->next)
				vertexes[hash_b] = vertexes[hash_b]->next;
		}
		graph * temp = (graph *) calloc (1, sizeof(graph));
		temp->x = links->b1;
		temp->y = links->b2;
		temp->ct = 0;
		temp->mark = NOT_ADDED;
		if (NULL == vertexes[hash_b])
			vertexes[hash_b] = temp;
		else
		{
			vertexes[hash_b]->next = temp;
			vertexes[hash_b] = start;
		}
		(*count)++;
	}
	graph * sa = searchvert(vertexes, links->a1, links->a2, *size);
	graph * sb = searchvert(vertexes, links->b1, links->b2, *size);
	if (-1 == searchway(sa->ways, links->b1, links->b2, links->weight, sa->ct))
	{	
		sa->ways = (way **) realloc (sa->ways, (sa->ct + 1)*sizeof(graph *));
		sa->ways[sa->ct] = (way *) calloc (1, sizeof(way));
		sa->ways[sa->ct]->vertex = sb;
		sa->ways[sa->ct]->weight = links->weight;
		sa->ct++;
	}
}
graph ** remake(graph *** vertexes, link ** links, int count, int * size)
{
	int i = 0;
	graph ** smurf = *vertexes;
	deletegraph(smurf, *size);
	free(smurf);
	*vertexes = NULL;
	*size *= 2;
	graph ** new = (graph **) calloc (*size, sizeof(graph *));
	int newcount = 0;
	i = 1;
	while (newcount < count)
	{
		addlink(links[i], new, &newcount, size);
		i++;
	}
	printf("Graph remade.\n");
	return new;
}
int searchway (way ** ways, int sid1, int sid2, int sweight, int count) /* search a neighbor of a vertex and return its index */
{
    int i = 0;
    while (i < count)
    {
        if ((ways[i]->vertex->x == sid1) && (ways[i]->vertex->y == sid2) && (ways[i]->weight == sweight))
            return i;
        ++i;
    }
    return -1;
}
graph * searchvert (graph ** vertexes, int sid1, int sid2, int size) /* search a vertex in a graph and return its pointer to */
{
	if ((sid1 < 0) || (sid2 < 0))
		return NULL;
	int h = hash(sid1, sid2, size);
	if (NULL == vertexes[h])
		return NULL;
	graph * start = vertexes[h];
	while (NULL != vertexes[h])
	{
		if ((vertexes[h]->x == sid1) && (vertexes[h]->y == sid2))
		{
			graph * temp = vertexes[h];
			vertexes[h] = start;
			return temp;
		}
		vertexes[h] = vertexes[h]->next;
	}
	vertexes[h] = start;
	return NULL;
}
int hash (int x, int y, int size)
{
	int h = 0;
	int tempx = x;
	int tempy = y;
	while (0 != tempx)
	{
		h += (tempx % 10)*PARAMETER;
		tempx /= 10;
	}
	while (0 != tempy)
	{
		h += (tempy % 10)*(PARAMETER+1);
		tempy /= 10;
	}
	h = h % size;
	return h;
}
void printgraph (graph ** vertexes, int size)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < size; ++i)
	{
		graph * start = vertexes[i];
		while (NULL != vertexes[i])
		{
			printf ("vertex coordinates : %d %d. connected with: ", vertexes[i]->x, vertexes[i]->y);
    		for (j = 0; j < vertexes[i]->ct; ++j)
    			printf ("%d %d (w%.d)  ", vertexes[i]->ways[j]->vertex->x, vertexes[i]->ways[j]->vertex->y, vertexes[i]->ways[j]->weight);
    		printf("\n");
    		vertexes[i] = vertexes[i]->next;
		}
		vertexes[i] = start;
	}
}
void deletegraph(graph ** vertexes, int size)
{
	int i = 0;
	for (i = 0; i < size; ++i)
	{
		while (NULL != vertexes[i])
		{
			graph * temp = vertexes[i]->next;
			int k = 0;
			for (k = 0; k < vertexes[i]->ct; ++k)
				free(vertexes[i]->ways[k]);
			free(vertexes[i]->ways);
			free(vertexes[i]);
			vertexes[i] = temp;
		}
	}
}