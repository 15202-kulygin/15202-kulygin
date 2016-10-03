
#include <stdio.h>
#include <stdlib.h>
#define SIZE 6

void print (int ** graf) /* print a graph as a matrix */
{
	int i = 0;
	int j = 0;
	printf ("\n");
	for (i = 0; i < SIZE; ++i)
	{
		for (j = 0; j < SIZE; ++j)
			printf ("%d ", graf[i][j]);
		printf ("\n");
	}
}
void scan (int ** graf) /* scan a graph as a matrix */
{
	int i = 0;
	int j = 0;
	for (i = 0; i < SIZE; ++i)
		for (j = 0; j < SIZE; ++j)
			scanf ("%d ", &graf[i][j]);
}
int iscycled (int ** graf) 
{
	int i = 0;
	int j = 0;
	int notnull = 0;
	int ct = 0;
	for (j = 0; j < SIZE; ++j)
	{
		notnull = 0;
		for (i = 0; i < SIZE; ++i)
			if (1 == graf[i][j])
			{
				notnull = 1;
				break;
			}
		if (notnull == 0)
			ct++;	
	}
	if (0 == ct)
		return 1;
	else
		return 0;
}
void topsort (int ** graf) /* do a topological sort of a graph */
{
	int i = 0;
	int j = 0;
	int checked = 0;
	for (j = 0; j < SIZE; ++j)
		if (graf[i][j] == 2)
			checked++;
	if (SIZE == checked)
	{
		printf ("END\n");
		return;
	}
	int nullct = 0;
	int isnull = 0;
	j = 0;
	while (1 != isnull)
	{
		nullct = 0;
		isnull = 0;
		for (i = 0; i < SIZE; ++i)
			if (0 == graf[i][j])
				nullct++;
		if (SIZE == nullct)
			isnull = 1;
		else 
		{	
			isnull = 0;
			++j;
		}
	}
	printf ("%c ", 'A'+j);
	for (i = 0; i < SIZE; ++i)
		graf[j][i] = 0;
	for (i = 0; i < SIZE; ++i)
		graf[i][j] = 2;
	topsort(graf);
	return;
}
void freegraf (int ** graf)
{
	int i = 0;
	for (i = 0; i < SIZE; ++i)
	{
		free(graf[i]);
		graf[i] = NULL;
	}
	free(graf);
	graf = NULL;
}
int main() 
{
	int ** graf = calloc (SIZE, sizeof(int *));
	int i = 0;
	int j = 0;
	for (i = 0; i < SIZE; ++i)
	{
		graf[i] = calloc (SIZE, sizeof (int));
		for (j = 0; j < SIZE; ++j)
			graf[i][j] = 0;
	}
	printf ("Put in the graph as a matrix:\n");
	scan(graf);
	if (1 == iscycled(graf))
	{
		printf ("The graph is cycled\n");
		freegraf(graf);
		return -1;
	}
	topsort(graf);
	freegraf(graf);
	graf = NULL;
	return 0;
}

/*
0 1 1 0 0 0
0 0 1 0 0 0
0 0 0 0 0 1
0 0 1 0 1 0
0 0 0 0 0 0
0 0 0 0 1 0
*/
