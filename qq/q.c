#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 4
#define WIDTH 4

int func (char matrix[HEIGHT][WIDTH])
{
	int result = 0;
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			printf("%c ", matrix[i][j]);
		}
		printf("\n");
	}
	return result;
}


int main ()
{
	char matrix[HEIGHT][WIDTH];
	int matrix_count = 0;
	char symbol = ' ';
	FILE * input_file = fopen("matr.txt", "r");
	while (fscanf(input_file, "%c", symbol) != EOF)
	{
		
		for (int i = 0; i < HEIGHT; ++i)
		{	
			for (int j = 0; j < WIDTH; ++j)
			{
				matrix[i][j] = symbol;
				fscanf(input_file, "%c", symbol);			
			}
		}
		matrix_count++;
	}
	func(matrix);
	
	fclose(input_file);
}