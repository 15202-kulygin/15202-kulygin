#include "graph.h"



void addlink (link * links, graph ** vertexes, int * count, int * size) /* add vertexes to graph if needed and create a link */
{
	int hash_a = hash(links->a, *size);
	int hash_b = hash(links->b, *size);
	if (NULL == searchvert(vertexes, links->a, *size))
	{
		graph * start = vertexes[hash_a];
		if (NULL != vertexes[hash_a])
		{
			while (NULL != vertexes[hash_a]->next)
				vertexes[hash_a] = vertexes[hash_a]->next;
		}
		graph * temp = (graph *) calloc (1, sizeof(graph));
		temp->id = links->a;
		temp->ct = 0;
		temp->visited = 0;
		if (NULL == vertexes[hash_a])
			vertexes[hash_a] = temp;
		else
		{
			while (NULL != vertexes[hash_a]->next)
				vertexes[hash_a] = vertexes[hash_a]->next;
			vertexes[hash_a]->next = temp;
			vertexes[hash_a] = start;
		}
		(*count)++;
	}
	if (NULL == searchvert(vertexes, links->b, *size))
	{
		graph * start = vertexes[hash_b];
		if (NULL != vertexes[hash_b])
		{
			while (NULL != vertexes[hash_b]->next)
				vertexes[hash_b] = vertexes[hash_b]->next;
		}
		graph * temp = (graph *) calloc (1, sizeof(graph));
		temp->id = links->b;
		temp->ct = 0;
		temp->visited = 0;
		if (NULL == vertexes[hash_b])
			vertexes[hash_b] = temp;
		else
		{
			while (NULL != vertexes[hash_b]->next)
				vertexes[hash_b] = vertexes[hash_b]->next;
			vertexes[hash_b]->next = temp;
			vertexes[hash_b] = start;
		}
		(*count)++;
	}
	graph * sa = searchvert(vertexes, links->a, *size);
	graph * sb = searchvert(vertexes, links->b, *size);
	if (-1 == searchneighbor(sa->arr, links->b, sa->ct))
	{	
		sa->arr = (graph **) realloc (sa->arr, (sa->ct + 1)*sizeof(graph *));
		sa->arr[sa->ct] = sb;
		sa->ct++;
	}
	if (-1 == searchneighbor(sb->arr, links->a, sb->ct))
	{	
		sb->arr = (graph **) realloc (sb->arr, (sb->ct + 1)*sizeof(graph *));
		sb->arr[sb->ct] = sa;
		sb->ct++; 
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
int searchneighbor (graph ** vertexes, int sid, int count) /* search a neighbor of a vertex and return its index */
{
    int i = 0;
    while (i < count)
    {
        if (vertexes[i]->id == sid)
            return i;
        ++i;
    }
    return -1;
}
graph * searchvert (graph ** vertexes, int sid, int size) /* search a vertex in a graph and return its pointer to */
{
	int h = hash(sid, size);
	if (NULL == vertexes[h])
		return NULL;
	graph * start = vertexes[h];
	while (NULL != start)
	{
		if (start->id == sid)
		{
			return start;
		}
		start = start->next;
	}
	return NULL;
}
void width (graph * start) /* print all the vertexes in width bypass order */
{
	queue * first = (queue *) calloc (1, sizeof(queue));
	first->data = start;
	queue * last = first;
	first->data->visited = 1;
	int i = 0; 
	while (NULL != first)
	{
		while (i < first->data->ct)
		{
			if (0 == first->data->arr[i]->visited)
			{
				last->next = (queue *) calloc (1, sizeof(queue)); 
				last = last->next;
				last->data = first->data->arr[i];
				last->data->visited = 1;
			}
			++i;
		}
		i = 0;
		printf("%d ", first->data->id);
		queue * temp = first->next;
		free(first);
		first = temp;
		temp = NULL;
	}
	printf("\n");
}
int hash (int key, int size)
{
	int h = 0;
	int temp = key;
	while (0 != temp)
	{
		h += (temp % 10)*PARAMETER;
		temp /= 10;
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
			printf ("vertex id : %d. connected with: ", vertexes[i]->id);
    		for (j = 0; j < vertexes[i]->ct; ++j)
    			printf ("%d ", vertexes[i]->arr[j]->id);
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
			free(vertexes[i]->arr);
			free(vertexes[i]);
			vertexes[i] = temp;
		}
	}
}