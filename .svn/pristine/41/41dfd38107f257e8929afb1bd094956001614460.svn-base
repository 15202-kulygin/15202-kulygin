#include <stdio.h>
#include <stdlib.h>
#define HEIGHT 5
#define WIDTH 5
#define SLINE 0
#define SCOL 0

typedef struct graff {
	int n;
	int step;
} gr;

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
			printf ("%d ", graf[i][j].step);
		printf ("\n");
	}
}

int count (gr ** graf, int i, int j)
{
	int ct = 0;
	int k = 0;
	if ((graf[i+2][j+1].step == 0) && (i+2 < HEIGHT) && (j+1 < WIDTH) && (i+2 > -1) && (j+1 > -1))
		ct++;
	if ((graf[i+2][j-1].step == 0) && (i+2 < HEIGHT) && (j-1 < WIDTH) && (i+2 > -1) && (j-1 > -1))
		ct++;
	if ((graf[i+1][j+2].step == 0) && (i+1 < HEIGHT) && (j+2 < WIDTH) && (i+1 > -1) && (j+2 > -1))
		ct++;
	if ((graf[i+1][j-2].step == 0) && (i+1 < HEIGHT) && (j-2 < WIDTH) && (i+1 > -1) && (j-2 > -1))
		ct++;
	if ((graf[i-1][j+2].step == 0) && (i-1 < HEIGHT) && (j+2 < WIDTH) && (i-1 > -1) && (j+2 > -1))
		ct++;
	if ((graf[i-1][j-2].step == 0) && (i-1 < HEIGHT) && (j-2 < WIDTH) && (i-1 > -1) && (j-2 > -1))
		ct++;
	if ((graf[i-2][j+1].step == 0) && (i-2 < HEIGHT) && (j+1 < WIDTH) && (i-2 > -1) && (j+1 > -1))
		ct++;
	if ((graf[i-2][j-1].step == 0) && (i-2 < HEIGHT) && (j-1 < WIDTH) && (i-2 > -1) && (j-1 > -1))
		ct++;
	return ct;
}

int visited (gr ** graf)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < HEIGHT; ++i)
	{
		for (j = 0; j < WIDTH; ++j)
			if (graf[i][j].visit == 0)
				return 0; 
	}
	return 1;
}

int horse (gr ** graf, int line, int col, int step)
{	
	
	if ((line >= HEIGHT) || (col >= WIDTH) || (line < 0) || (col < 0))
		return 0;
	if (0 != graf[line][col].step)
		return 0;
    printf("ON THE POSITION %d %d STEP %d NOW\n", line, col, step);
	graf[line][col].step = step;
	if (visited(graf) == 1)
		return 1;
	if (horse(graf, line+2, col+1, step+1) == 1)
		return 1;
	if (horse(graf, line+2, col-1, step+1) == 1)
		return 1;
	if (horse(graf, line+1, col+2, step+1) == 1)
		return 1;
	if (horse(graf, line+1, col-2, step+1) == 1)
		return 1;
	if (horse(graf, line-1, col+2, step+1) == 1)
		return 1;
	if (horse(graf, line-1, col-2, step+1) == 1)
		return 1;
	if (horse(graf, line-2, col+1, step+1) == 1)
		return 1;
	if (horse(graf, line-2, col-1, step+1) == 1)
		return 1;
	graf[line][col].step = 0;
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
	int i = 0;
	int j = 0;
	gr ** graf = creategraf(HEIGHT, WIDTH);
	print(graf);
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
