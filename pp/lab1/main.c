#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"



// mpicc -std=c99 main.c matrix.c -lm

// mpecc -mpilog -o mpetest mpitest.c

// mpirun -np 2 ./a.out 


int main(int argc, char ** argv)
{ 	
	int process_count, current_process;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &process_count);
	MPI_Comm_rank(MPI_COMM_WORLD, &current_process);
	if (process_count > MATRIX_SIZE)
	{
		printf("Too many processes\n");
		return -1;
	}
	double * matrix = (double *) calloc (MATRIX_SIZE*MATRIX_SIZE, sizeof(double));
	for (int i = 0; i < MATRIX_SIZE; ++i)
	{
		for (int j = 0; j < MATRIX_SIZE; ++j)
		{
			matrix[i*MATRIX_SIZE + j] = (i == j) ? 2 : 1;
		}
	}
	double * vector_u = (double *) calloc(MATRIX_SIZE, sizeof(double));
	double * vector_b = (double *) calloc(MATRIX_SIZE, sizeof(double));
	double * vector_x = (double *) calloc(MATRIX_SIZE, sizeof(double));
	double * vector_y = (double *) calloc(MATRIX_SIZE, sizeof(double));
	for (int i = 0; i < MATRIX_SIZE; ++i)
	{
		//vector_b[i] = i + 1;
		//vector_b[i] = MATRIX_SIZE + 1;
		vector_u[i] = sin(2*PI*i / MATRIX_SIZE);
	}
	multiply_matrix_vector(matrix, vector_u, MATRIX_SIZE, MATRIX_SIZE, vector_b);
	int lines_per_process = -1;
	int max_lines_per_process = -1;
	if ((0 == MATRIX_SIZE % process_count) || (1 == MATRIX_SIZE / process_count))// если матрица делится на одинаковые части по всем процессам ИЛИ число процессов больше половины размера матрицы
	{
		lines_per_process = MATRIX_SIZE / process_count;
		if (0 == MATRIX_SIZE % process_count)
		{
			max_lines_per_process = lines_per_process;
		}
		else
		{
			max_lines_per_process = MATRIX_SIZE % process_count + 1;
		}
	}
	else // если число строк матрицы не кратно числу процессов И число процессов меньше половины размера матрицы (т.е. по крайней мере во все процессы, кроме последнего, уходит хотя бы по 2 строки)
	{
		lines_per_process = (MATRIX_SIZE / process_count) + 1;
		max_lines_per_process = lines_per_process;
	}

	int * recvcounts = (int *) calloc (process_count, sizeof(int));
	int * displacements = (int *) calloc (process_count, sizeof(int)); // массивы, содержащие информацию о начальных и конечных строках ВСЕХ процессов (чтобы потом выбрать нужные куски из результирующего вектора)
	for (int i = 0; i < process_count; ++i)
	{
		displacements[i] = i * lines_per_process; // по сути - стартовая строка для каждого процесса
		int current_final_line = (i == process_count - 1) ? MATRIX_SIZE - 1 : displacements[i] + lines_per_process - 1; // конечная строка для каждого процесса
		recvcounts[i] = current_final_line - displacements[i] + 1;	
	}	
	int start_line = displacements[current_process];
	int final_line = displacements[current_process] + recvcounts[current_process] - 1;

	
	double * matrix_piece = (double *) calloc (MATRIX_SIZE * max_lines_per_process, sizeof(double));
	for (int i = 0; i <= final_line - start_line; ++i) // заполняем кусочную матрицу
	{
		for (int j = 0; j < MATRIX_SIZE; ++j)
		{
			// // --------------- IDENTITY MATRIX 
			// matrix_piece[i*MATRIX_SIZE + j] = (j == start_line + i) ? 1 : 0;
			
			// --------------- 1 VAR MATRIX
			matrix_piece[i*MATRIX_SIZE + j] = (j == start_line + i) ? 2 : 1;
		}
	}
	// if (0 == current_process)
	// 	print_matrix(vector_x, MATRIX_SIZE, 1);

	double criterion = 1;

	int piece_size = final_line - start_line + 1;
	double * vector_Ax_piece = (double *) calloc (max_lines_per_process, sizeof(double));
	double * vector_Ay_piece = (double *) calloc (max_lines_per_process, sizeof(double));
	double * vector_y_piece = (double *) calloc (max_lines_per_process, sizeof(double));
	double * vector_x_piece = (double *) calloc (max_lines_per_process, sizeof(double));
	double b_norm = vector_norm(vector_b, MATRIX_SIZE);
	double parameter = 0.00001;
	while (criterion > EPS)
	{
		multiply_matrix_vector(matrix_piece, vector_x, piece_size, MATRIX_SIZE, vector_Ax_piece); // A*x(n) (кусочек)
		subtract_vectors(vector_Ax_piece, vector_b + start_line, piece_size, vector_y_piece); // A*x(n) - b = y(n) (кусочек)
		MPI_Allgatherv(vector_y_piece, piece_size, MPI_DOUBLE, vector_y, recvcounts, displacements, MPI_DOUBLE, MPI_COMM_WORLD);
		
		criterion = vector_norm(vector_y, MATRIX_SIZE) / b_norm;
		
		if (0 == current_process)
		{
			//print_matrix(vector_y, MATRIX_SIZE, 1);
			printf("criterion %.6f\n", criterion);
		}

		multiply_vector_by_schalar(vector_y_piece, parameter, piece_size); // y(n) = t * y(n) (кусочек)
		subtract_vectors(vector_x + start_line, vector_y_piece, piece_size, vector_x_piece); 
		MPI_Allgatherv(vector_x_piece, piece_size, MPI_DOUBLE, vector_x, recvcounts, displacements, MPI_DOUBLE, MPI_COMM_WORLD); // собираем x(n+1)
	}

	if (0 == current_process)
	{
		printf("Result :\n");
		print_matrix(vector_x, MATRIX_SIZE, 1);
		// printf("Expected result :\n");
		// print_matrix(vector_u, MATRIX_SIZE, 1);	
		// subtract_vectors(vector_x, vector_u, MATRIX_SIZE, vector_x);
		// print_matrix(vector_x, MATRIX_SIZE, 1);
	}


	// double * result_piece = (double *) calloc (piece_size, sizeof(double));
	// multiply_matrix_vector(matrix_piece, vector_b, piece_size, MATRIX_SIZE, result_piece);
	// double * result = (double *) calloc (MATRIX_SIZE, sizeof(double));
	// собрать

	free(matrix);
	free(vector_x_piece);
	free(vector_y_piece);
	free(vector_Ax_piece);
	free(vector_Ay_piece);
	free(vector_b);
	free(vector_y);
	free(vector_x);
	free(vector_u);
	free(matrix_piece);
	//free(result);
 	MPI_Finalize();
	
 }



