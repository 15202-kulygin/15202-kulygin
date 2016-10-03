
#include "fibo.h"


int heuristic (graph * first, graph * second)
{
	return abs(first->x - second->x) + abs(first->y - second->y);
}
void addheap (node * toadd, HEAP * H)
{
	toadd->data->mark = OPENED;
	if (NULL == H->min)
	{
		H->min = toadd;
		H->min->left = H->min;
		H->min->right = H->min;
	}
	else 
	{
      	toadd->right = H->min->right;
      	toadd->right->left = toadd;
      	toadd->left = H->min;
      	H->min->right = toadd;
    }
	if (toadd->Fvalue < H->min->Fvalue)
		H->min = toadd;
	else if (toadd->Fvalue == H->min->Fvalue)
		if (toadd->Gvalue < H->min->Gvalue)
			H->min = toadd;
	H->rootsct++;
}
node * extractheap (HEAP * H)
{
	if (NULL == H->min)
		return NULL;
	//printf("IN EXTRACT WITH MIN %d\n", H->min->Fvalue);
	if (H->min->childct != 0) // linking Hmins childs with the roots
	{
		node * start = H->min->child;
		H->min->child = H->min->child->right;
		while (H->min->child != start)
		{
			H->min->child->parent = NULL;
			H->min->child = H->min->child->right;
		}
		H->min->child->parent = NULL;
		H->min->right->left = H->min->child->left;
		H->min->child->left->right = H->min->right;
		H->min->right = H->min->child;
		H->min->right->left = H->min;
		H->min->child = NULL;
		H->rootsct += H->min->childct;
		H->min->childct = 0;
	}
	if (H->min == H->min->right) // if Hmin is the last in the heap
	{
		//printf("FUK U\n");
		node * temp = H->min;
		H->min->data->mark = CLOSED;
		H->min = NULL;
		H->rootsct = 0;
		return temp;
	}
	else
	{
		H->min->left->right = H->min->right; //extracting and closing Hmin
		H->min->right->left = H->min->left;
		node * temp = H->min->right; // the child of the extracted node became Hmin
		H->min->right = NULL;
		H->min->left = NULL;
		H->min->data->mark = CLOSED;
		node * result = H->min;
		H->min = temp;
		H->rootsct--;
		/// CONSOLIDATING
		int max_degree = 0; // searching for max degree in root list
		int i = 0;
		for (i = 0; i < H->rootsct; ++i)
		{
			if (H->min->childct > max_degree)
				max_degree = H->min->childct;
			H->min = H->min->right;
		}
		node ** degree_pointers = (node **) calloc ((max_degree+1)*2, sizeof(node *)); // array of max degree root pointers
		for (i = 0; i < max_degree*2; ++i)
		{
			degree_pointers[i] = NULL;
		}
		int maincounter = H->rootsct;
		for (i = 0; i < maincounter; ++i) // CONSOLIDATING ACTUALLY
		{
			if (NULL == degree_pointers[H->min->childct]) // if there were no roots with similar degree
			{
				degree_pointers[H->min->childct] = H->min;
			}
			else
			{
				while (NULL != degree_pointers[H->min->childct])
				{
					node * toswap = degree_pointers[H->min->childct];
					if (H->min->Fvalue > toswap->Fvalue) // if current root is more than previous -- swap them
					{
						graph * tempdata = H->min->data;
						H->min->data = toswap->data;
						toswap->data = tempdata;
					}
					// current H min is now the root with less Fvalue
					H->rootsct--;
					toswap->left->right = toswap->right;
					toswap->right->left = toswap->left;
					toswap->right = NULL;
					toswap->left = NULL;
					toswap->parent = H->min;
					if (NULL == H->min->child) //if current root has no children
					{
						H->min->child = toswap;
						toswap->right = toswap;
						toswap->left = toswap;
					}
					else // if current root has children
					{
						H->min->child->right->left = toswap;
						toswap->right = H->min->child->right;
						H->min->child->right = toswap;
						toswap->left = H->min->child;
					}
					degree_pointers[H->min->childct] = NULL;
					H->min->childct++;
				}
			}
			H->min = H->min->right;
		}
		for (i = 0; i < max_degree + 1; ++i)
		{
			if ((NULL != degree_pointers[i]) && (degree_pointers[i]->Fvalue < H->min->Fvalue))
				H->min = degree_pointers[i];
		}
		free(degree_pointers);
		return result;
	}
}
node * createnodeheap (graph * current, graph * end, int cur_weight)
{
	node * new = (node *) calloc (1, sizeof(node));
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	new->child = NULL;
	new->data = current;
	new->Hvalue = heuristic(current, end);
	new->Gvalue = cur_weight;
	new->Fvalue = new->Gvalue + new->Hvalue;
	new->childct = 0;
	new->mark = IS_TRUE;
	return new;
}
void changevalueheap(HEAP * heap, node * current, int newvalue) 
{
	current->Gvalue = newvalue;
	current->Fvalue = newvalue + current->Hvalue;
	node * par = current->parent;
	if ((NULL != par) && (current->Fvalue < par->Fvalue))
	{
		cut_to_root(heap, current, par);
		cascade_cut(heap, par);
	}
}
void cut_to_root(HEAP * heap, node * current, node * par) // utility for changevalueheap
{
	if (par->childct == 1)
		par->child = NULL;
	else
		par->child = par->child->right;
	par->childct--;
	current->parent = NULL;
	current->mark = IS_FALSE;
	addheap(current, heap);
}
void cascade_cut(HEAP * heap, node * current) // utility for changevalueheap
{
	node * par = current->parent;
	if (NULL != par)
	{
		if (par->mark == IS_FALSE)
			par->mark = IS_TRUE;
		else
		{
			cut_to_root(heap, current, par);
			cascade_cut(heap, par);
		}
	}
}
int distance (graph * startvertex, graph * endvertex)
{
	node * start = createnodeheap(startvertex, endvertex, 0);
	HEAP * heap = (HEAP *) calloc (1, sizeof(HEAP));
	heap->rootsct = 0;
	addheap(start, heap);
	while (NULL != heap->min)
	{
		node * extracted = extractheap(heap); 
		//printf("extracted %d %d\n", extracted->data->x, extracted->data->y);
		//printf("Gvalue %d\n", extracted->Gvalue);
		if (extracted->data == endvertex)
		{
			deleteheap(heap);
			free(heap);
			int result = extracted->Gvalue; 
			free(extracted);
			return result;
		}
		int i = 0;
		for (i = 0; i < extracted->data->ct; ++i)
		{
			if (extracted->data->ways[i]->vertex->mark == NOT_ADDED)
			{
				node * toadd = createnodeheap(extracted->data->ways[i]->vertex, endvertex, extracted->data->ways[i]->weight + extracted->Gvalue);
				addheap(toadd, heap);
				//printf("added %d %d with Gvalue %d\n", toadd->data->x, toadd->data->y, toadd->Gvalue);
			}
			else if (extracted->data->ways[i]->vertex->mark == CLOSED)
				continue;
			else
			{
				
				//printf("childct %d %d %d\n", heap->min->childct, heap->min->right->childct, heap->min->right->right->childct);
				//if ((NULL != heap->min->child) && (NULL != heap->min->right->right->child))
					//printf("children %d %d, %d %d\n", heap->min->child->data->x, heap->min->child->data->y, heap->min->right->right->child->data->x, heap->min->right->right->child->data->y);
				//printf("proverka %d %d\n", heap->min->data->x, heap->min->data->y);
				//printf("check %d %d\n", extracted->data->ways[i]->vertex->x, extracted->data->ways[i]->vertex->y);
				node * found = findheap(heap->min, extracted->data->ways[i]->vertex, heap->rootsct);
				//printf("%d weight\n", extracted->data->ways[i]->weight);
				changevalueheap(heap, found, extracted->data->ways[i]->weight + extracted->Gvalue);
			}
		}
		free(extracted);
	}
	deleteheap(heap);
	free(heap);
	return -1;
}
node * findheap(node * start, graph * vertex, int rootsct) // find a node, that contains the search vertex
{
	int i = 0;
	for (i = 0; i < rootsct + 1; ++i)
	{
		if ((start->data->x == vertex->x) && (start->data->y == vertex->y))
			return start;
		if (NULL != start->child)
		{
			node * check = findheap(start->child, vertex, start->childct);
			if (NULL != check)
				if ((check->data->x == vertex->x) && (check->data->y == vertex->y))
					return check;
		}
		start = start->right;
	}
	return NULL;
}
void deleteheap (HEAP * heap)
{
	int i = 0;
	for (i = 0; i < heap->rootsct; ++i)
	{
		int k = 0;
		for (k = 0; k < heap->min->childct; ++k)
		{
			node * temp = heap->min->child->right;
			deletechildtree(heap->min->child);
			heap->min->child = temp;
		}
		node * temp = heap->min->right;
		free(heap->min);
		heap->min = temp;
	}

}
void deletechildtree (node * start)
{
	if (NULL == start)
		return;
	if (NULL != start->child)
	{
		int i = 0;
		for (i = 0; i < start->childct; ++i)
		{
			node * temp = start->child->right;
			deletechildtree(start->child);
			start->child = temp;
		}
	}
	if (start == start->left)
	{
		free(start);
		return;
	}
	else
	{
		start->right->left = start->left;
		start->left->right = start->right;
		free(start);
		return;
	}
}





