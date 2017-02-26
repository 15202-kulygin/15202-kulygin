#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

// mpicc -std=c99 main.c

// mpecc -mpilog -o mpetest mpitest.c

// mpirun -np 2 ./a.out qwe.matrix

void print_matrix(float * matrix, int height, int width)
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

int main(int argc, char ** argv)
{
	if (2 > argc)
	{
		printf("Put in the input file name\n");
		return -1;
	}
	FILE * input_file = fopen(argv[1], "r");
	if (NULL == input_file)
	{
		printf("Cannot open input file\n");
		return -1;
	}
	int matrix_size = -1;
	fscanf(input_file, "%d", &matrix_size);
	float * matrix = (float *) calloc(matrix_size * matrix_size, sizeof(float));
	float * vector_b = (float *) calloc(matrix_size, sizeof(float));
	for (int i = 0; i < matrix_size * matrix_size; ++i)
	{
		fscanf(input_file, "%f", &matrix[i]);
	}
	for (int i = 0; i < matrix_size; ++i)
	{
		fscanf(input_file, "%f", &vector_b[i]);
	}
	fclose(input_file);
	//print_matrix(matrix, matrix_size, matrix_size);
	//print_matrix(vector_b, matrix_size, 1);


	int process_count, current_process;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &process_count);
	MPI_Comm_rank(MPI_COMM_WORLD, &current_process);
	if (process_count > matrix_size)
	{
		printf("Too much processes\n");
		return -1;
	}
	int lines_per_process = -1;
	if (0 == matrix_size / process_count) // если матрица делится на одинаковые части по всем процессам
	{
		lines_per_process = matrix_size / process_count;
	}
	else // если число строк матрицы не кратно числу процессов 
	{
		lines_per_process = (matrix_size / process_count) + 1;
	}
	int start_line = current_process * lines_per_process;
	int final_line = start_line + lines_per_process - 1;
	if (final_line > matrix_size - 1) // если вылезли за край матрицы (в случае последнего кусочка) - устанавливаем номер последней строки в соответствии с последней строкой исходной матрицы
	{
		final_line = matrix_size - 1;
	}
	float * matrix_piece = (float *) calloc (matrix_size * lines_per_process, sizeof(float));
	for (int i = 0; i <= final_line - start_line; ++i) // заполняем кусочную матрицу
	{
		for (int j = 0; j < matrix_size; ++j)
		{
			matrix_piece[i*matrix_size + j] = matrix[(start_line + i) * matrix_size + j];
		}
	}
	int result_piece_size = final_line - start_line + 1;
	float * result_piece = (float *) calloc (result_piece_size, sizeof(float));
	for (int i = 0; i < result_piece_size; ++i) // заполняем кусочный результат умножения
	{
		result_piece[i] = 0;
		for (int j = 0; j < matrix_size; ++j)
		{
			result_piece[i] += matrix_piece[i * matrix_size + j] * vector_b[j];
		}
	}
	/*if (0 == current_process)
	{
		printf("Matrix in process %d : \n", current_process);
		print_matrix(matrix_piece, result_piece_size, matrix_size);
		printf("Result piece :\n");
		print_matrix(result_piece, result_piece_size, 1);
	}*/

	float * result = (float *) calloc (matrix_size, sizeof(float));
	MPI_Allgather(result_piece, result_piece_size, MPI_FLOAT, result, result_piece_size, MPI_FLOAT, MPI_COMM_WORLD);
	if (0 == current_process)
	{
		printf("Result vector :\n");
		print_matrix(result, matrix_size, 1);
	}
	MPI_Finalize();
	
}