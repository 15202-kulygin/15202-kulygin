#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <sys/time.h>

//mpicc -std=c99 lab3.c
//mpirun -np 2 ./a.out

#define DIMENSION_NUMBER 2
#define M 100
#define N 100
#define K 100
#define A_piece(i, j) A_piece[matrix_sizes[1]*i+j]
#define B_piece(i, j) B_piece[piece_sizes[1]*i+j]
#define C_piece(i, j) C_piece[piece_sizes[1]*i+j]

void createTypes(int *matrix_sizes, int *piece_sizes, MPI_Datatype *typeb, MPI_Datatype *typec, MPI_Datatype *types) {
    MPI_Type_vector(matrix_sizes[1], piece_sizes[1], matrix_sizes[2], MPI_DOUBLE, &types[0]);

    MPI_Aint sizeofdouble, disp[2];
    int blen[2];
    MPI_Type_extent(MPI_DOUBLE, &sizeofdouble);
    blen[0] = 1;
    blen[1] = 1;
    disp[0] = 0;
    disp[1] = sizeofdouble * piece_sizes[1];
    types[1] = MPI_UB;
    MPI_Type_struct(2, blen, disp, types, typeb);
    MPI_Type_commit(typeb);

    MPI_Type_vector(piece_sizes[0], piece_sizes[1], matrix_sizes[2], MPI_DOUBLE, &types[0]);
    MPI_Type_struct(2, blen, disp, types, typec);
    MPI_Type_commit(typec);
}

void calcSubmatrix(int *dispb, int *countb, int *dispc, int *countc, int *dimensions, int *piece_sizes) {
    for (int j = 0; j < dimensions[1]; j++) {
        dispb[j] = j;
        countb[j] = 1;
    }

    for (int i = 0; i < dimensions[0]; i++) {
        for (int j = 0; j < dimensions[1]; j++) {
            dispc[i * dimensions[1] + j] = (i * dimensions[1] * piece_sizes[0] + j);
            countc[i * dimensions[1] + j] = 1;
        }
    }
}

void calculate(int * matrix_sizes, double *A, double *B, double *C, int * dimensions, MPI_Comm comm) {
    int *countc, *dispc, *countb, *dispb;
    MPI_Datatype typeb, typec, types[2];
    MPI_Comm pcomm;

    MPI_Comm_dup(comm, &pcomm);
    MPI_Bcast(matrix_sizes, 3, MPI_INT, 0, pcomm); // broadcast массивов остальным процессам
    MPI_Bcast(dimensions, 2, MPI_INT, 0, pcomm);

    //Создаем решетку
    int periods[2] = {0, 0}; // для cart create
    MPI_Comm comm_2D; // коммуникатор решётки
    MPI_Cart_create(pcomm, DIMENSION_NUMBER, dimensions, periods, 0, &comm_2D); // определяем коммуникатор решётки

    int threadCoords[2];
    int threadRank;
    MPI_Comm_rank(comm_2D, &threadRank);
    MPI_Cart_coords(comm_2D, threadRank, DIMENSION_NUMBER, threadCoords); // определяем координаты процесса в решетке
    //printf("Rank %d: %d,%d\n", threadRank, threadCoords[0], threadCoords[1]);

    MPI_Comm comm_1D[2]; // разделенные коммуникаторы
    int remains[2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            remains[j] = (i == j);
        }
        MPI_Cart_sub(comm_2D, remains, &comm_1D[i]); // получим dimensions[0] коммуникаторов по dimensions[1] процессов И dimensions[1] коммуникаторов по dimensions[0] процессов
    }

    //размер полосы процесса
    int piece_sizes[2];
    piece_sizes[0] = matrix_sizes[0] / dimensions[0];
    piece_sizes[1] = matrix_sizes[2] / dimensions[1];

    double *A_piece, *B_piece, *C_piece;
    A_piece = (double *) calloc (piece_sizes[0] * matrix_sizes[1], sizeof(double));
    B_piece = (double *) calloc (matrix_sizes[1] * piece_sizes[1], sizeof(double));
    C_piece = (double *) calloc (piece_sizes[0] * piece_sizes[1], sizeof(double));

    if (threadRank == 0) {
        createTypes(matrix_sizes, piece_sizes, &typeb, &typec, types);

        dispb = (int *) calloc(dimensions[1], sizeof(int));
        countb = (int *) calloc(dimensions[1], sizeof(int));
        dispc = (int *) calloc(dimensions[0] * dimensions[1], sizeof(int));
        countc = (int *) calloc(dimensions[0] * dimensions[1], sizeof(int));
        calcSubmatrix(dispb, countb, dispc, countc, dimensions, piece_sizes);
    }

    //Передаем горизонтальные полосы матрицы А
    if (threadCoords[1] == 0) {
        MPI_Scatter(A, piece_sizes[0] * matrix_sizes[1], MPI_DOUBLE, A_piece, piece_sizes[0] * matrix_sizes[1], MPI_DOUBLE, 0, comm_1D[0]);
    }

    //Горизонтальные полосы матрицы В
    if (threadCoords[0] == 0) {
        MPI_Scatterv(B, countb, dispb, typeb, B_piece, matrix_sizes[1] * piece_sizes[1], MPI_DOUBLE, 0, comm_1D[1]);
    }

    //Полосу АА по измерению у
    MPI_Bcast(A_piece, piece_sizes[0] * matrix_sizes[1], MPI_DOUBLE, 0, comm_1D[1]);
    //Полосу ВВ по измерению х
    MPI_Bcast(B_piece, matrix_sizes[1] * piece_sizes[1], MPI_DOUBLE, 0, comm_1D[0]);

    //Умножаем
    for (int i = 0; i < piece_sizes[0]; i++) {
        for (int j = 0; j < piece_sizes[1]; j++) {
            for (int k = 0; k < matrix_sizes[1]; k++) {
                C_piece(i, j) = C_piece(i, j) + A_piece(i, k) * B_piece(k, j);
            }
        }
    }

    //Собираем результат
    MPI_Gatherv(C_piece, piece_sizes[0] * piece_sizes[1], MPI_DOUBLE, C, countc, dispc, typec, 0, comm_2D);

    free(A_piece);
    free(B_piece);
    free(C_piece);
    MPI_Comm_free(&pcomm);
    MPI_Comm_free(&comm_2D);
    MPI_Comm_free(&comm_1D[0]);
    MPI_Comm_free(&comm_1D[1]);
    if (threadRank == 0) {
        free(countc);
        free(dispc);
        free(countb);
        free(dispb);
        MPI_Type_free(&typeb);
        MPI_Type_free(&typec);
        MPI_Type_free(&types[0]);
    }
}

void initialize(double *A, double *B) 
{
    for (int i = 0; i < M; ++i) 
    {
        for (int j = 0; j < N; ++j) 
        {
            A[N*i + j] = 1;
        }
    }

    for (int i = 0; i < N; ++i) 
    {
        for (int j = 0; j < K; ++j) 
        {
            B[K*i + j] = 1;
        }
    }
}

int check(double *C) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < K; ++j) {
            if(C[K*i + j] != N) {
                return 0;
            }
        }
    }

    return 1 ;
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int threadCount;
    int threadRank;
    MPI_Comm_size(MPI_COMM_WORLD, &threadCount);
    MPI_Comm_rank(MPI_COMM_WORLD, &threadRank);

    int dimensions[DIMENSION_NUMBER]; //массив, для конфигурации решётки
    MPI_Dims_create(threadCount, DIMENSION_NUMBER, dimensions); //функция определения оптимальной конфигурации сетки

    int matrix_sizes[3]; //размеры матриц
    double * A, * B, * C;
    if (threadRank == 0) {
        matrix_sizes[0] = M;
        matrix_sizes[1] = N;
        matrix_sizes[2] = K;

        A = (double *) calloc (M * N, sizeof(double));
        B = (double *) calloc (N * K, sizeof(double));
        C = (double *) calloc (M * K, sizeof(double));

        initialize(A, B);
    }


    calculate(matrix_sizes, A, B, C, dimensions, MPI_COMM_WORLD);

    if(threadRank == 0) {
        printf("Check result: %s\n", check(C) == 1 ? "good" : "bad");

        free(A);
        free(B);
        free(C);
    }

    MPI_Finalize();
    return 0;
}