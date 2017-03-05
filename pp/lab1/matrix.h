#ifndef MATRIX_H
#define MATRIX_H

#define MATRIX_SIZE 10
#define EPS 0.00001

void print_matrix(double * matrix, int height, int width);
void multiply_matrix_vector(double * m, double * v, int height, int width, double * result);
void subtract_vectors(double * v1, double * v2, int size, double * result);// v1 - v2
double schalar_multiply(double * v1, double * v2, int size);
double vector_norm(double * v, int size);
void multiply_vector_by_schalar(double * vector, double schalar, int size);


#endif