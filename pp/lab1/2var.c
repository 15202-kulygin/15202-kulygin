#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"



// mpicc -std=c99 2var.c matrix.c -lm

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
	
	
	
	// double * vector_b = (double *) calloc(MATRIX_SIZE, sizeof(double));
	// double * vector_x = (double *) calloc(MATRIX_SIZE, sizeof(double));
	
	// for (int i = 0; i < MATRIX_SIZE; ++i)
	// {
	// 	//vector_b[i] = i + 1;
	// 	vector_b[i] = MATRIX_SIZE + 1;
	// }
	
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
	double * vector_x_piece = (double *) calloc (max_lines_per_process, sizeof(double));
	double * vector_b_piece = (double *) calloc (max_lines_per_process, sizeof(double));
	for (int i = 0; i <= final_line - start_line; ++i) // заполняем кусочную матрицу
	{
		vector_b_piece[i] = MATRIX_SIZE + 1;
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
	double b_norm;
	double b_norm_piece = 0;
	for (int i = 0; i < piece_size; ++i)
		b_norm_piece += vector_b_piece[i]*vector_b_piece[i]; 
	MPI_Allreduce(&b_norm, &b_norm_piece , 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD); 
	b_norm = sqrt(b_norm);
	
	double parameter = 0.00001;
	double norm = 0.0;

	double * vector_y_piece = (double *) calloc (max_lines_per_process, sizeof(double));
	


	while (criterion > EPS)
	{
		
		multiply_matrix_vector(matrix_piece, vector_x, piece_size, MATRIX_SIZE, vector_y_piece); // A*x(n) (кусочек)
		subtract_vectors(vector_y_piece, vector_b + start_line, piece_size, vector_y_piece); // A*x(n) - b = y(n) (кусочек)

		for (int i = 0; i < piece_size; ++i) // собиаем кусочек суммы для номы
			norm += vector_y_piece[i]*vector_y_piece[i];
		MPI_Reduce(&norm, &criterion , 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
		norm = 0;
		
		if (0 == current_process)
		{
			//print_matrix(vector_y, MATRIX_SIZE, 1);
			//printf("criterion %.6f\n", criterion);
			criterion = criterion / b_norm;
			printf("criterion %.6f\n", criterion);
		}
		
		MPI_Bcast(&criterion, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		
		
		
		multiply_vector_by_schalar(vector_y_piece, parameter, piece_size); // y(n) = t * y(n) (кусочек)
		subtract_vectors(vector_x + start_line, vector_y_piece, piece_size, vector_y_piece); //!!!!!
		MPI_Allgatherv(vector_y_piece, piece_size, MPI_DOUBLE, vector_x, recvcounts, displacements, MPI_DOUBLE, MPI_COMM_WORLD); // собираем x(n+1)
	}
	






	if (0 == current_process) // print кусков с barrier надо сделат!!
	{

		printf("Result :\n");
		print_matrix(vector_x, MATRIX_SIZE, 1);
	}



	
	free(recvcounts);
	free(displacements);
	free(vector_b_piece);
	free(vector_y_piece);
	free(vector_x_piece);
	free(matrix_piece);
 	MPI_Finalize();
	
 }



