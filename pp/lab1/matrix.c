#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void print_matrix(double * matrix, int height, int width)
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			printf("%.1f ", matrix[i*width + j]);
		}
		printf("\n");
	}
	printf("\n");
}
void multiply_matrix_vector(double * m, double * v, int height, int width, double * result, int displacement)
{
	//printf("Check1 %d %d\n", lines_per_process, height);
	for (int i = 0; i < height; ++i)
	{
		result[i] = 0;
		for (int j = 0; j < width; ++j)
		{
			result[i] += m[i*width + j + displacement] * v[j];
		}
	}
}
void subtract_vectors(double * v1, double * v2, int size, double * result)// v1 - v2
{
	for (int i = 0; i < size; ++i)
	{
		result[i] = v1[i] - v2[i];
	}
}
void add_vectors(double * v1, double * v2, int size, double * result)// v1 + v2
{
	for (int i = 0; i < size; ++i)
	{
		result[i] = v1[i] + v2[i];
	}
}
double vector_norm(double * v, int size)
{
	double result = 0;
	for (int i = 0; i < size; ++i)
	{
		result += v[i] * v[i];
	}
	return sqrt(result);
}
void multiply_vector_by_schalar(double * vector, double schalar, int size)
{
	for (int i = 0; i < size; ++i)
	{
		vector[i] *= schalar;
	}
}