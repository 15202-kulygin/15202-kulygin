#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MATRIX_SIZE 10
#define EPS 0.00001

// mpicc -std=c99 main.c

// mpecc -mpilog -o mpetest mpitest.c

// mpirun -np 2 ./a.out qwe.matrix

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
double * multiply_matrix_vector(double * m, double * v, int height, int width, int lines_per_process)
{
	double * result = (double *) calloc (lines_per_process, sizeof(double));
	print_matrix(m, height, width);
	//???????????????????????????
	for (int i = 0; i < height; ++i)
	{
		result[i] = 0;
		for (int j = 0; j < width; ++j)
		{
			result[i] += m[i*width + j] * v[i];
		}
	}
	for (int i = height; i < lines_per_process; ++i)
	{
		result[i] = 0;
	}
	return result;
}
/*double * subtract_vector(double * v1, double * v2, int size)// v1 - v2
{
	double * result = (double *) calloc (size, sizeof(double));
	for (int i = 0; i < size; ++i)
	{
		result[i] = v1[i] - v2[i];
	}
	return result;
}
double multiply_schalar(double * v1, double * v2, int size)
{
	double * result = 0;
	for (int i = 0; i < size; ++i)
	{
		result += v1[i] * v2[i];
	}
	return result;
}
double vector_norm(double * v, int size)
{
	double result = 0;
	for (int i = 0; i < size; ++i)
	{
		result += v[i] * v[i];
	}
	return sqrt(result);
}*/


int main(int argc, char ** argv)
{ 	

	double * vector_b = (double *) calloc(MATRIX_SIZE, sizeof(double));
	double * vector_x = (double *) calloc(MATRIX_SIZE, sizeof(double));
	for (int i = 0; i < MATRIX_SIZE; ++i)
	{
		vector_b[i] = i + 1;
		vector_x[i] = 0;
	}
	int process_count, current_process;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &process_count);
	MPI_Comm_rank(MPI_COMM_WORLD, &current_process);
	if (process_count > MATRIX_SIZE)
	{
		printf("Too much processes\n");
		return -1;
	}
	int lines_per_process = -1;
	if (0 == MATRIX_SIZE / process_count) // если матрица делится на одинаковые части по всем процессам
	{
		lines_per_process = MATRIX_SIZE / process_count;
	}
	else // если число строк матрицы не кратно числу процессов 
	{
		lines_per_process = (MATRIX_SIZE / process_count) + 1;
	}
	int start_line = current_process * lines_per_process;
	int final_line = start_line + lines_per_process - 1;
	if (final_line > MATRIX_SIZE - 1) // если вылезли за край матрицы (в случае последнего кусочка) - устанавливаем номер последней строки в соответствии с последней строкой исходной матрицы
	{
		final_line = MATRIX_SIZE - 1;
	}
	double * matrix_piece = (double *) calloc (MATRIX_SIZE * lines_per_process, sizeof(double));
	for (int i = 0; i <= final_line - start_line; ++i) // заполняем кусочную матрицу
	{
		for (int j = 0; j < MATRIX_SIZE; ++j)
		{
			//matrix_piece[i*MATRIX_SIZE + j] = matrix[(start_line + i) * MATRIX_SIZE + j];
			// --------------- making identity matrix
			if (j == start_line + i) 
			{
				matrix_piece[i*MATRIX_SIZE + j] = 1;
			}
			else
			{
				matrix_piece[i*MATRIX_SIZE + j] = 0;	
			}
			// --------------- q
			/*// --------------- 1 var matrix
			if (j == start_line + i) 
			{
				matrix_piece[i*MATRIX_SIZE + j] = 2;
			}
			else
			{
				matrix_piece[i*MATRIX_SIZE + j] = 1;	
			}
			//---------------- q*/
		}
	}
	int result_piece_size = final_line - start_line + 1;
	double * result_piece = multiply_matrix_vector(matrix_piece, vector_b, result_piece_size, MATRIX_SIZE, lines_per_process);
	if (2 == current_process)
		print_matrix(result_piece, result_piece_size, 1);
	//-------------- begin
	//double * vector_y_past = (double *) calloc (MATRIX_SIZE, sizeof(double));

	//-------------- end
	double * result = (double *) calloc (MATRIX_SIZE, sizeof(double));
	//MPI_Allgather(result_piece, result_piece_size, MPI_DOUBLE, result, result_piece_size, MPI_DOUBLE, MPI_COMM_WORLD);
	/*if (0 == current_process)
	{
		printf("Result vector :\n");
		print_matrix(result, MATRIX_SIZE, 1);
	}*/
	free(vector_b);
	free(matrix_piece);
	free(result_piece);
	free(result);
	MPI_Finalize();
	
}