#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"



// mpicc -std=c99 main.c -lm

// mpecc -mpilog -o mpetest mpitest.c

// mpirun -np 2 ./a.out qwe.matrix


void gather_vector(double * piece, int * process_lines_information, int max_lines_per_process, int process_count, double * result)
{
	int result_size = (0 == MATRIX_SIZE % process_count) ? MATRIX_SIZE : max_lines_per_process * process_count;

	double * result_with_trash = (double *) calloc (result_size, sizeof(double));
	MPI_Allgather(piece, max_lines_per_process, MPI_DOUBLE, result_with_trash, max_lines_per_process, MPI_DOUBLE, MPI_COMM_WORLD); 
	int j = 0;
	for (int i = 0; i < process_count; ++i)
	{
		for (int k = 0; k <= process_lines_information[2*i+1] - process_lines_information[2*i]; ++k)
		{
			result[j++] = result_with_trash[i*max_lines_per_process + k];
		}
	}
	free(result_with_trash);
}



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
	double * vector_u = (double *) calloc(MATRIX_SIZE, sizeof(double));
	double * vector_b = (double *) calloc(MATRIX_SIZE, sizeof(double));
	double * vector_x = (double *) calloc(MATRIX_SIZE, sizeof(double));
	double * vector_y = (double *) calloc(MATRIX_SIZE, sizeof(double));
	for (int i = 0; i < MATRIX_SIZE; ++i)
	{
		//vector_b[i] = i + 1;
		 vector_b[i] = 11;
		//vector_u = 2*PI*i / MATRIX_SIZE;
	}
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

	int process_lines_information[2*process_count]; // массив, содержащий информацию о начальных и конечных строках ВСЕХ процессов (чтобы потом выбрать нужные куски из результирующего вектора)
	for (int i = 0; i < process_count; ++i)
	{
		process_lines_information[2*i] = i * lines_per_process;
		process_lines_information[2*i+1] = (i == process_count - 1) ? MATRIX_SIZE - 1 : process_lines_information[2*i] + lines_per_process - 1;	
	}	
	int start_line = process_lines_information[2*current_process];
	int final_line = process_lines_information[2*current_process+1];

	
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
	double parameter = 0.01;
	while (criterion > EPS)
	{
		multiply_matrix_vector(matrix_piece, vector_x, piece_size, MATRIX_SIZE, vector_Ax_piece); // A*x(n) (кусочек)
		subtract_vectors(vector_Ax_piece, vector_b + start_line, piece_size, vector_y_piece); // A*x(n) - b = y(n) (кусочек)
		gather_vector(vector_y_piece, process_lines_information, max_lines_per_process, process_count, vector_y); // собираем y(n)
		multiply_matrix_vector(matrix_piece, vector_y, piece_size, MATRIX_SIZE, vector_Ay_piece); // A*y(n) (кусочек)

		criterion = vector_norm(vector_y, MATRIX_SIZE) / b_norm;
		
		if (0 == current_process)
		{
			print_matrix(vector_y, MATRIX_SIZE, 1);
		}

		multiply_vector_by_schalar(vector_y_piece, parameter, piece_size); // y(n) = t * y(n) (кусочек)
		subtract_vectors(vector_x + start_line, vector_y_piece, piece_size, vector_x_piece); 
		gather_vector(vector_x_piece, process_lines_information, max_lines_per_process, process_count, vector_x); // собираем x(n+1)
	}

	if (0 == current_process)
	{
		printf("Result :\n");
		print_matrix(vector_x, MATRIX_SIZE, 1);	
	}


	// double * result_piece = (double *) calloc (piece_size, sizeof(double));
	// multiply_matrix_vector(matrix_piece, vector_b, piece_size, MATRIX_SIZE, result_piece);
	// double * result = (double *) calloc (MATRIX_SIZE, sizeof(double));
	// gather_vector(result_piece, process_lines_information, max_lines_per_process, process_count, result);
	
	
	// free(vector_x_piece);
	// free(vector_y_piece);
	// free(vector_b);
	// free(vector_y);
	// free(vector_x);
	// free(matrix_piece);
	// free(result);
	MPI_Finalize();
	
}






// получаем скалярный квадрат параллельно
// double * schalar_pieces = (double *) calloc (process_count, sizeof(double));
// double single_schalar_piece = schalar_multiply(vector_b + start_line, vector_b + start_line, piece_size);
// MPI_Allgather(&single_schalar_piece, 1, MPI_DOUBLE, schalar_pieces, 1, MPI_DOUBLE, MPI_COMM_WORLD);
// double schalar_mpl = 0;
// for (int i = 0; i < process_count; ++i)
// {
// 	schalar_mpl += schalar_pieces[i];
// }