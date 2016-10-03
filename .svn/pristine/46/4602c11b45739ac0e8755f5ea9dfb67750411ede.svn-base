#include <stdio.h>
#include <stdlib.h>
#define HEIGHT 20
#define WIDTH 20
#define SLINE 0
#define SCOL 0

typedef struct graff {
	int n;
	int step;
} gr;

typedef struct ne {
	int l;
	int c;
	int n;
} nei;

gr ** creategraf (int height, int width)
{
	gr ** graf = calloc (HEIGHT, sizeof(gr *));
	int i = 0;
	int j = 0;
	for (i = 0; i < HEIGHT; ++i)
	{
		graf[i] = calloc (WIDTH, sizeof (gr));
		for (j = 0; j < WIDTH; ++j)
		{
			graf[i][j].n = 0;
			graf[i][j].step = 0;
		}
	}
	return graf;
}

void print (gr ** graf) /* print a graph as a matrix */
{
	int i = 0;
	int j = 0;
	printf ("\n");
	for (i = 0; i < HEIGHT; ++i)
	{
		for (j = 0; j < WIDTH; ++j)
			printf ("%2d ", graf[i][j].step);
		printf ("\n");
	}
}

int count (gr ** graf, int i, int j)
{
	int ct = 0;
	int addline = 0;
	int addcol = 0;
	for (addline = -2; addline <= 2; addline++)
		for (addcol = -2; addcol <= 2; addcol++)
		{
			if ((addline == 0) || (addcol == 0) || (0 == (abs(addline)+abs(addcol))%2))
				continue;
			else
				if ((i+addline < HEIGHT) && (j+addcol < WIDTH) && (i+addline > -1) && (j+addcol > -1))
					if (graf[i+addline][j+addcol].step == 0)
						ct++;
		}
	return ct;
}

int horse (gr ** graf, int line, int col, int step)
{	
	if ((line >= HEIGHT) || (col >= WIDTH) || (line < 0) || (col < 0))
		return 0;
	if (0 != graf[line][col].step)
		return 0;
    //printf("ON THE POSITION %d %d STEP %d NOW\n", line, col, step);
	graf[line][col].step = step;
	if (step == HEIGHT*WIDTH)
		return 1;
	int addline = 0;
	int addcol = 0;
	int size = 0;
	nei * arr = (nei *) calloc (1, sizeof(nei));
	for (addline = -2; addline <= 2; addline++)
		for (addcol = -2; addcol <= 2; addcol++)
		{
			if ((addline == 0) || (addcol == 0) || (0 == (abs(addline)+abs(addcol))%2))
				continue;
			else
				if ((line+addline > -1) && (col+addcol > -1) && (line+addline < HEIGHT) && (col+addcol < WIDTH))
					if (graf[line+addline][col+addcol].step == 0)
					{
						arr = (nei *) realloc (arr, (size+1)*sizeof(nei));
						arr[size].l = line + addline;
						arr[size].c = col + addcol;
						arr[size].n = count(graf, line+addline, col+addcol);
						size++;
					}
		}
		//printf("%d size\n", size);
	if (0 == size)
	{
		free(arr);
		return 0;
	}
	int i = 0;
	int j = 0;
	for (i = 0; i < size-1; ++i)
		for (j = 0; j < size-i-1; ++j)
		{
			if (arr[j].n > arr[j+1].n)
			{
				int temp;
				temp = arr[j].n;
				arr[j].n = arr[j+1].n;
				arr[j+1].n = temp;
				temp = arr[j].c;
				arr[j].c = arr[j+1].c;
				arr[j+1].c = temp;
				temp = arr[j].l;
				arr[j].l = arr[j+1].l;
				arr[j+1].l = temp;
			}
		}
	
	for (i = 0; i < size; ++i)
	{	
		if (horse(graf, arr[i].l, arr[i].c, step+1) == 1)
			{
				free (arr);
				return 1;
			}
	}
	graf[line][col].step = 0;
	free(arr);
	return 0;
}

void freegraf (gr ** graf)
{
	int i = 0;
	for (i = 0; i < HEIGHT; ++i)
	{
		free(graf[i]);
		graf[i] = NULL;
	}
	free(graf);
	graf = NULL;
}

int main ()
{
	gr ** graf = creategraf(HEIGHT, WIDTH);
	//print(graf);
	int sline = SLINE;
	int scol = SCOL;
	int step = 1;
	if (1 == horse(graf, sline, scol, step))
		print(graf);
	else
		printf("NO WAY\n");	
	freegraf(graf);
	return 0;
}
