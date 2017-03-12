#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void print_reversed_matrix(int ** m, int N, int M)
{
	for (int i = 0; i < N; ++i)
	{

		if (0 == (i + 1)%2)
		{
			for (int j = 0; j < M; ++j)
			{
				printf("%d ", m[i][j]);
			}
			printf("\n");
		}
		else
		{
			for (int j = M - 1; j >= 0; --j)
			{
				printf("%d ", m[i][j]);
			}
			printf("\n");
		}
		
	}
}


int main()
{
	int N, M;
	printf("N:\n");
	scanf("%d", &N);
	printf("M:\n");
	scanf("%d", &M);
	int ** matrix = (int **) calloc (N, sizeof(int *));
	for (int i = 0; i < N; ++i)
	{
		matrix[i] = (int *) calloc (M, sizeof(int));
	}
	printf("Matrix:\n");
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			scanf("%d", &matrix[i][j]);
		}
	}
	print_reversed_matrix(matrix, N, M);
	
}
