#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "matrix.h"

//gcc -fopenmp 2var.c matrix.c -lm

//hm

int main(int argc, char ** argv)
{
	printf("Number of threads : ");
	int number_of_threads = 0;
	scanf("%d", &number_of_threads);
	if (1 > number_of_threads)
	{
		printf("Wrong number of threads\n");
		return -1;
	}
	omp_set_num_threads(number_of_threads);

	double * matrix = (double *) calloc (MATRIX_SIZE*MATRIX_SIZE, sizeof(double));
	double * vector_b = (double *) calloc(MATRIX_SIZE, sizeof(double));
	double * vector_x = (double *) calloc(MATRIX_SIZE, sizeof(double));
	double * vector_y = (double *) calloc(MATRIX_SIZE, sizeof(double));
	double * vector_u = (double *) calloc(MATRIX_SIZE, sizeof(double));
	
	for (int i = 0; i < MATRIX_SIZE; ++i)
	{
		for (int j = 0; j < MATRIX_SIZE; ++j)
		{
			matrix[i*MATRIX_SIZE + j] = (i == j) ? 2 : 1;
		}
		//vector_b[i] = MATRIX_SIZE + 1;
		vector_u[i] = sin(2*PI*i / MATRIX_SIZE);
		vector_x[i] = 0;
		vector_y[i] = 0;
	}
	multiply_matrix_vector(matrix, vector_u, MATRIX_SIZE, MATRIX_SIZE, vector_b);
	// print_matrix(vector_b, MATRIX_SIZE, 1);
	// print_matrix(matrix, MATRIX_SIZE, MATRIX_SIZE);
	double criterion = 1;
	double b_norm = vector_norm(vector_b, MATRIX_SIZE);
	double parameter = 0.001;
	
	double s = 0;

	double start = omp_get_wtime();
	#pragma omp parallel 
	{
		while (criterion > EPS)
		{
			
			//#pragma omp for reduction(+:s) schedule(dynamic,16)
			#pragma omp for reduction(+:s) 
			for (int i = 0; i < MATRIX_SIZE; ++i) // y = A*x(n)
			{
				//#pragma omp parallel for --- не стоит, так даже долше, тк каждый поток может начат поpождат еще потоки
				for (int j = 0; j < MATRIX_SIZE; ++j)
				{
					vector_y[i] += matrix[i*MATRIX_SIZE + j] * vector_x[j];
				}
				vector_y[i] -= vector_b[i]; // y = A*x(n) - b
				s += vector_y[i]*vector_y[i]; // counting norm

				vector_y[i] *= parameter;
				vector_x[i] -= vector_y[i];
			}
			#pragma omp single 
			{
				criterion = sqrt(s) / b_norm;
				//printf("criterion %.6f\n", criterion);
				s = 0;
			}
		}
	}
	double finish = omp_get_wtime();

	
	printf("Result :\n");
	print_matrix(vector_x, MATRIX_SIZE, 1);
	printf("%.3fs time\n", finish - start);
	// printf("Check :\n");
	// print_matrix(vector_u, MATRIX_SIZE, 1);
	// printf("Expected result :\n");
	// print_matrix(vector_u, MATRIX_SIZE, 1);	
	// subtract_vectors(vector_x, vector_u, MATRIX_SIZE, vector_x);
	// print_matrix(vector_x, MATRIX_SIZE, 1);
	
	free(matrix);
	free(vector_x);
	free(vector_b);
	free(vector_y);
	free(vector_u);
	
}