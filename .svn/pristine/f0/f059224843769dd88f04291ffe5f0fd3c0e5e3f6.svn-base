#include "graph.h"
void addlink (link * links, graph ** vertexes, int * count, int * size) /* add vertexes to graph if needed and create a link */
{
	if (NULL == search(vertexes, links->a, *size))
	{
		int h = hash(links->a, *size);
		if (NULL == vertexes[h])
		{
			vertexes[h] = (graph *) calloc (1, sizeof(graph));
			vertexes[h]->id = links->a;
			vertexes[h]->ct = 0;
			vertexes[h]->visited = 0;
		}
		else
		{
			graph * start = vertexes[h];
			while (NULL != start->next)
				start = start->next;
			graph * grnew = (graph *) calloc (1, sizeof(graph));
			grnew->id = links->a;
			grnew->ct = 0;
			grnew->visited = 0;
			start->next = grnew;
		}
		(*count)++;
		if (((float)(*count))/((float)(*size)) >= LOADFACTOR)
		{	
			vertexes = remake(vertexes, size);
		}
	}
	printf("%d linkb\n", links->b);
	if (NULL == search(vertexes, links->b, *size))
		printf("SEARCH NULL\n");
	else
		printf("SEARCH NOT NULL\n");
	if (NULL == search(vertexes, links->b, *size))
	{
		printf("OK\n");
		int h = hash(links->b, *size);
		if (NULL == vertexes[h])
		{
			vertexes[h] = (graph *) calloc (1, sizeof(graph));
			vertexes[h]->id = links->b;
			vertexes[h]->ct = 0;
			vertexes[h]->visited = 0;
		}
		else
		{
			graph * start = vertexes[h];
			while (NULL != start->next)
				start = start->next;
			graph * grnew = (graph *) calloc (1, sizeof(graph));
			grnew->id = links->b;
			grnew->ct = 0;
			grnew->visited = 0;
			start->next = grnew;
		}
		(*count)++;
		if (((float)(*count))/((float)(*size)) >= LOADFACTOR)
		{	
			vertexes = remake(vertexes, size);
		}
	}

	graph * sa = search(vertexes, links->a, *size);
	graph * sb = search(vertexes, links->b, *size);
	if (-1 == searchvert(sa->arr, links->b, sa->ct))
	{	
		sa->arr = (graph **) realloc (sa->arr, (sa->ct + 1)*sizeof(graph *));
		sa->arr[sa->ct] = sb;
		sa->ct++;
		
	}
	if (-1 == searchvert(sb->arr, links->a, sb->ct))
	{	
		sb->arr = (graph **) realloc (sb->arr, (sb->ct + 1)*sizeof(graph *));
		sb->arr[sb->ct] = sa;
		sb->ct++; 
	}
}
int searchvert (graph ** vertexes, int sid, int count) /* search a vertex in a graph neighbors array and return its index */
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
}




/********************************/
int hash (int key, int size) /* hash-function */
{
	int h = 0;
	int p = 1;
	while (0 != key)
	{
		h += (key%10)*p;
		p *= P;
		key /= 10;
	}
	return (int)((h)%size);
}

graph * search (graph ** vertexes, int key, int size) /* search a vertex with a needed id in the hashtable */
{
	int h = hash(key, size);
	printf("%d hash of key %d with size %d\n", h, key, size);
	graph * start = vertexes[h];
	while (NULL != vertexes[h])
	{
		if (vertexes[h]->id == key)
		{
			graph * temp = vertexes[h];
			vertexes[h] = start;
			return temp;
		}
		vertexes[h] = vertexes[h]->next;
	}
	printf("GOOD\n");
	vertexes[h] = start;
	return NULL;	
}

graph ** remake(graph ** vertexes, int * size)
{
	graph ** temp = (graph **) calloc (1, sizeof(graph *));
	int i = 0;
	int j = 0;

	for (i = 0; i < *size; ++i)
	{
		if (NULL != vertexes[i])
		{
			graph * start = vertexes[i];
			while (NULL != start)
			{
				temp = (graph **) realloc (temp, (j+1)*sizeof(graph *));
				temp[j] = (graph *) calloc (1, sizeof(graph));
				temp[j]->id = start->id;
				temp[j]->ct = start->ct;
				temp[j]->visited = start->visited;
				int k = 0;
				for (k = 0; k < temp[j]->ct; ++k)
				{
					temp[j]->arr[k] = start->arr[k];
				}
				++j;
				start = start->next;
			}
		}
	}
	for (i = 0; i < *size; ++i)
	{
		if (NULL != vertexes[i])
		{
			graph * tmpgraph = vertexes[i]->next;
			while (NULL != tmpgraph)
			{
				free (vertexes[i]);
				vertexes[i] = tmpgraph;
				tmpgraph = vertexes[i]->next;
			}
		}
	}
	free(vertexes);
	(*size) *= 2;
	vertexes = (graph **) calloc (*size, sizeof(graph *));
	//printf("OK\n");
	//printf("%d j\n", j);
	for (i = 0; i < j; ++i)
	{
		int h = hash(temp[i]->id, *size);
		if (NULL == vertexes[h])
		{
			vertexes[h] = (graph *) calloc (1, sizeof(graph));
			vertexes[h]->id = temp[i]->id;
			vertexes[h]->ct = temp[i]->ct;
			vertexes[h]->visited = temp[i]->visited;
			int k = 0;
			for (k = 0; k < temp[i]->ct; ++k)
				vertexes[h]->arr[k] = temp[i]->arr[k];
		}
		else
		{
			graph * start = vertexes[h];
			while (NULL != start->next)
				start = start->next;
			graph * grnew = (graph *) calloc (1, sizeof(graph));
			grnew->id = temp[i]->id;
			grnew->ct = temp[i]->ct;
			grnew->visited = temp[i]->visited;
			int k = 0;
			for (k = 0; k < temp[i]->ct; ++k)
				grnew->arr[k] = temp[i]->arr[k];
			start->next = grnew;
		}
		free(temp[i]);
	}
	free(temp);
	return vertexes;
}