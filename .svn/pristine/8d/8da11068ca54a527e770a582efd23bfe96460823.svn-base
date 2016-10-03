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
		temp->number = links->a;
		temp->ct = 0;
		temp->next = NULL;
		temp->widthparent = NULL;
		temp->widthvisited = 0;
		if (NULL == vertexes[hash_a])
			vertexes[hash_a] = temp;
		else
		{
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
		temp->number = links->b;
		temp->ct = 0;
		temp->next = NULL;
		temp->widthparent = NULL;
		temp->widthvisited = 0;
		if (NULL == vertexes[hash_b])
			vertexes[hash_b] = temp;
		else
		{
			vertexes[hash_b]->next = temp;
			vertexes[hash_b] = start;
		}
		(*count)++;
	}
	graph * sa = searchvert(vertexes, links->a, *size);
	graph * sb = searchvert(vertexes, links->b, *size);
	if (-1 == searchway(sa->ways, links->b, sa->ct))
	{	
		sa->ways = (way **) realloc (sa->ways, (sa->ct + 1)*sizeof(graph *));
		sa->ways[sa->ct] = (way *) calloc (1, sizeof(way));
		sa->ways[sa->ct]->vertex = sb;
		sa->ways[sa->ct]->capacity = links->capacity;
		sa->ways[sa->ct]->flow = 0;
		sa->ways[sa->ct]->mark = NOTFULL;
		sa->ct++;
	}
	if (-1 == searchway(sb->ways, links->a, sb->ct))
	{	
		sb->ways = (way **) realloc (sb->ways, (sb->ct + 1)*sizeof(graph *));
		sb->ways[sb->ct] = (way *) calloc (1, sizeof(way));
		sb->ways[sb->ct]->vertex = sa;
		sb->ways[sb->ct]->capacity = 0;
		sb->ways[sb->ct]->flow = 0;
		sb->ways[sb->ct]->mark = FULL;
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
int searchway (way ** ways, int sid, int count) /* search a neighbor of a vertex and return its index */
{
    int i = 0;    
	while (i < count)
    {
        if (ways[i]->vertex->number == sid)
            return i;
        ++i;
    }
    return -1;
}
graph * searchvert (graph ** vertexes, int sid, int size) /* search a vertex in a graph and return its pointer to */
{
	if (sid < 0)
		return NULL;
	int h = hash(sid, size);
	if (NULL == vertexes[h])
		return NULL;
	graph * start = vertexes[h];
	while (NULL != vertexes[h])
	{
		if (vertexes[h]->number == sid) 
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
int hash (int number, int size)
{
	int h = 0;
	int tempnumber = number;
	while (0 != tempnumber)
	{
		h += (tempnumber % 10)*(PARAMETER+1);
		tempnumber /= 10;
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
			printf ("vertex id : %d. connected with: ", vertexes[i]->number);
    		for (j = 0; j < vertexes[i]->ct; ++j)
    			if (0 != vertexes[i]->ways[j]->capacity)
    				printf ("%d (flow%d, cap%d)  ", vertexes[i]->ways[j]->vertex->number, vertexes[i]->ways[j]->flow, vertexes[i]->ways[j]->capacity);
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
int find_max_flow(graph * S, graph * T, graph ** vertexes, int size)
{
	int minwaylen = 0;
	graph ** minway = find_min_way(S, T, &minwaylen, vertexes, size);

	while (0 != minwaylen)
	{
		int sway = searchway(minway[0]->ways, minway[1]->number, minway[0]->ct);
		int minrestcapacity = minway[0]->ways[sway]->capacity - minway[0]->ways[sway]->flow;
		int i = 0;
		for (i = 1; i < minwaylen - 1; ++i) // finding the min capacity on the way
		{
			sway = searchway(minway[i]->ways, minway[i+1]->number, minway[i]->ct);
			if ((minway[i]->ways[sway]->capacity - minway[i]->ways[sway]->flow) < minrestcapacity)
				minrestcapacity = minway[i]->ways[sway]->capacity - minway[i]->ways[sway]->flow;
		}
		for (i = 0; i < minwaylen - 1; ++i) // increasing all the flows on the way
		{
			int searchway1 = searchway(minway[i]->ways, minway[i+1]->number, minway[i]->ct);
			minway[i]->ways[searchway1]->flow += minrestcapacity;
			int searchway2 = searchway(minway[i+1]->ways, minway[i]->number, minway[i+1]->ct);
			minway[i+1]->ways[searchway2]->flow -= minrestcapacity;
			if ((minway[i]->ways[searchway1]->capacity - minway[i]->ways[searchway1]->flow) > 0)
				minway[i]->ways[searchway1]->mark = NOTFULL;
			else
				minway[i]->ways[searchway1]->mark = FULL;
			if ((minway[i+1]->ways[searchway2]->capacity - minway[i+1]->ways[searchway2]->flow) > 0)
				minway[i+1]->ways[searchway2]->mark = NOTFULL;
			else
				minway[i+1]->ways[searchway2]->mark = FULL;
		}
		minwaylen = 0;
		if (NULL != minway)
			free(minway);
		minway = find_min_way(S, T, &minwaylen, vertexes, size);
	}
	if (NULL != minway)
		free(minway);
	int result = 0;
	int i = 0;
	for (i = 0; i < S->ct; ++i)
		result += S->ways[i]->flow;
	return result;
}
graph ** find_min_way (graph * start, graph * finish, int * length, graph ** vertexes, int size) /* print all the vertexes in width bypass order */
{
	queue * first = (queue *) calloc (1, sizeof(queue));
	first->vertex = start;
	first->vertex->widthparent = NULL;
	queue * last = first;
	first->vertex->widthvisited = 1;
	int i = 0; 
	while (NULL != first)
	{
		queue * temp = first;
		graph * current = first->vertex;
		if (last == first)
			last = NULL;
		first = first->next;
		free(temp);
		while (i < current->ct)
		{
			if ((0 == current->ways[i]->vertex->widthvisited) && (NOTFULL == current->ways[i]->mark))
			{
				current->ways[i]->vertex->widthvisited = 1;
				current->ways[i]->vertex->widthparent = current;
				if (NULL != last)
				{
					last->next = (queue *) calloc (1, sizeof(queue)); 
					last = last->next;
					last->vertex = current->ways[i]->vertex;
					last->next = NULL;
				}
				else
				{
					last = (queue *) calloc (1, sizeof(queue)); 
					last->vertex = current->ways[i]->vertex;
					last->next = NULL;
					first = last;
				}
				if (finish == last->vertex)
					break;
			}
			++i;
		}
		if (NULL == last)
			return NULL;
		if (last->vertex == finish)			
			break;
		i = 0;
	}
	graph ** minway = (graph **) calloc (1, sizeof(graph *));
	graph * back = last->vertex;
	while (NULL != back->widthparent)
	{
		minway = (graph **) realloc (minway, (*length + 1) * sizeof(graph *));
		minway[*length] = back;
		back = back->widthparent;
		(*length)++;
	}
	minway = (graph **) realloc (minway, (*length + 1) * sizeof(graph *));
	minway[*length] = back;
	(*length)++;
	graph ** tempgraph = (graph **) calloc (*length, sizeof(graph *));
	for (i = 0; i < *length; ++i)
		tempgraph[i] = minway[i];
	for (i = 0; i < *length; ++i)
		minway[i] = tempgraph[*length - i - 1];
	while (NULL != first)
	{
		queue * temp = first;
		first = first->next;
		free(temp);
	}
	free(tempgraph);
	for (i = 0; i < size; ++i)
	{
		graph * tmp = vertexes[i];
		while (NULL != vertexes[i])
		{
			vertexes[i]->widthvisited = 0;
			vertexes[i]->widthparent = NULL;			
			vertexes[i] = vertexes[i]->next;
		}
		vertexes[i] = tmp;
	}
	return minway;
}