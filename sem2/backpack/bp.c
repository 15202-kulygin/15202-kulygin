#include <stdio.h>
#include <stdlib.h>
#define W 13
#define N 5

int maximum(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

void collect (int ** A, int * w, int * bp, int i, int j)
{
	if (A[i][j] == 0)
		return;
	if (A[i-1][j] == A[i][j])
		collect(A, w, bp, i-1, j);
	else
	{
		collect(A, w, bp, i-1, j - w[i-1]); 
		bp[i-1] = 1;
	}
}

int main ()
{
	int w[N] = {3, 4, 5, 8, 9};
	int p[N] = {1, 6, 4, 7, 6};
	int ** A = (int **) calloc (N+1, sizeof(int *));
	int i = 0;
	for (i = 0; i < N+1; ++i)
	{
		A[i] = (int *) calloc (W+1, sizeof(int));
	}
	for (i = 0; i <= W; ++i)
		A[0][i] = 0;
	for (i = 0; i <= N; ++i)
		A[i][0] = 0;
	int j = 0;
	for (i = 1; i <= N; ++i)
		for (j = 1; j <= W; ++j)
		{
			if (j >= w[i-1])
				A[i][j] = maximum(A[i-1][j], A[i-1][j-w[i-1]]+p[i-1]);
			else
				A[i][j] = A[i-1][j];
		}
	/*for (i = 0; i <= N; ++i)
	{
		for (j = 0; j <= W; ++j)
			printf("%2d ", A[i][j]);
		printf("\n");
	}*/
	int bp[N] = {0, 0, 0, 0, 0};
	collect(A, w, bp, N, W);
	int price = 0;
	for (i = 0; i < N; ++i)
	{
		if (bp[i] == 1)
		{
			price += p[i];
			printf ("%d-th thing collected\n", i+1);
		}
	}
	printf ("Max price: %d\n", price);
	free (A);
	return 0;
}