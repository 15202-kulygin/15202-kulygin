#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <sys/time.h>

#define NUM_DIMS 2
#define M 2500
#define N 2500
#define K 2500
#define A(i, j) A[N*i+j]
#define B(i, j) B[K*i+j]
#define C(i, j) C[K*i+j]
#define AA(i, j) AA[n[1]*i+j]
#define BB(i, j) BB[nn[1]*i+j]
#define CC(i, j) CC[nn[1]*i+j]

void createTypes(int *n, int *nn, MPI_Datatype *typeb, MPI_Datatype *typec, MPI_Datatype *types) {
    MPI_Type_vector(n[1], nn[1], n[2], MPI_DOUBLE, &types[0]);

    MPI_Aint sizeofdouble, disp[2];
    int blen[2];
    MPI_Type_extent(MPI_DOUBLE, &sizeofdouble);
    blen[0] = 1;
    blen[1] = 1;
    disp[0] = 0;
    disp[1] = sizeofdouble * nn[1];
    types[1] = MPI_UB;
    MPI_Type_struct(2, blen, disp, types, typeb);
    MPI_Type_commit(typeb);

    MPI_Type_vector(nn[0], nn[1], n[2], MPI_DOUBLE, &types[0]);
    MPI_Type_struct(2, blen, disp, types, typec);
    MPI_Type_commit(typec);
}

void calcSubmatrix(int *dispb, int *countb, int *dispc, int *countc, int *p, int *nn) {
    for (int j = 0; j < p[1]; j++) {
        dispb[j] = j;
        countb[j] = 1;
    }

    for (int i = 0; i < p[0]; i++) {
        for (int j = 0; j < p[1]; j++) {
            dispc[i * p[1] + j] = (i * p[1] * nn[0] + j);
            countc[i * p[1] + j] = 1;
        }
    }
}

void calculate(int *n, double *A, double *B, double *C, int *p, MPI_Comm comm) {
    int *countc, *dispc, *countb, *dispb;
    MPI_Datatype typeb, typec, types[2];
    MPI_Comm pcomm;

    MPI_Comm_dup(comm, &pcomm);
    MPI_Bcast(n, 3, MPI_INT, 0, pcomm);
    MPI_Bcast(p, 2, MPI_INT, 0, pcomm);

    //Создаем решетку
    int periods[2] = {0};
    MPI_Comm comm_2D;
    MPI_Cart_create(pcomm, NUM_DIMS, p, periods, 0, &comm_2D);

    int threadCoords[2];
    int threadRank;
    MPI_Comm_rank(comm_2D, &threadRank);
    MPI_Cart_coords(comm_2D, threadRank, NUM_DIMS, threadCoords);
    //printf("Rank %d: %d,%d\n", threadRank, threadCoords[0], threadCoords[1]);

    MPI_Comm comm_1D[2];
    int remains[2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            remains[j] = (i == j);
        }
        MPI_Cart_sub(comm_2D, remains, &comm_1D[i]);
    }

    //Размер полосы
    int nn[2];
    nn[0] = n[0] / p[0];
    nn[1] = n[2] / p[1];

    double *AA, *BB, *CC;
    AA = (double *) calloc (nn[0] * n[1], sizeof(double));
    BB = (double *) calloc (n[1] * nn[1], sizeof(double));
    CC = (double *) calloc (nn[0] * nn[1], sizeof(double));

    if (threadRank == 0) {
        createTypes(n, nn, &typeb, &typec, types);

        dispb = (int *) calloc(p[1], sizeof(int));
        countb = (int *) calloc(p[1], sizeof(int));
        dispc = (int *) calloc(p[0] * p[1], sizeof(int));
        countc = (int *) calloc(p[0] * p[1], sizeof(int));
        calcSubmatrix(dispb, countb, dispc, countc, p, nn);
    }

    //Передаем горизонтальные полосы матрицы А
    if (threadCoords[1] == 0) {
        MPI_Scatter(A, nn[0] * n[1], MPI_DOUBLE, AA, nn[0] * n[1], MPI_DOUBLE, 0, comm_1D[0]);
    }

    //Горизонтальные полосы матрицы В
    if (threadCoords[0] == 0) {
        MPI_Scatterv(B, countb, dispb, typeb, BB, n[1] * nn[1], MPI_DOUBLE, 0, comm_1D[1]);
    }

    //Полосу АА по измерению у
    MPI_Bcast(AA, nn[0] * n[1], MPI_DOUBLE, 0, comm_1D[1]);
    //Полосу ВВ по измерению х
    MPI_Bcast(BB, n[1] * nn[1], MPI_DOUBLE, 0, comm_1D[0]);

    //Умножаем
    for (int i = 0; i < nn[0]; i++) {
        for (int j = 0; j < nn[1]; j++) {
            for (int k = 0; k < n[1]; k++) {
                CC(i, j) = CC(i, j) + AA(i, k) * BB(k, j);
            }
        }
    }

    //Собираем результат
    MPI_Gatherv(CC, nn[0] * nn[1], MPI_DOUBLE, C, countc, dispc, typec, 0, comm_2D);

    free(AA);
    free(BB);
    free(CC);
    MPI_Comm_free(&pcomm);
    MPI_Comm_free(&comm_2D);
    for (int i = 0; i < 2; i++) {
        MPI_Comm_free(&comm_1D[i]);
    }
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

void initMatrix(double *A, double *B, double *C) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            A(i, j) = 1;
        }
    }

    for (int j = 0; j < N; ++j) {
        for (int k = 0; k < K; ++k) {
            B(j, k) = 1;
        }
    }
}

bool checkResult(double *C) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < K; ++j) {
            if(C(i, j) != N) {
                return false;
            }
        }
    }

    return true;
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int threadCount;
    int threadRank;
    MPI_Comm_size(MPI_COMM_WORLD, &threadCount);
    MPI_Comm_rank(MPI_COMM_WORLD, &threadRank);

    int dims[NUM_DIMS] = {0}; //массив, в который помещается рекомендуемое число процессов вдоль каждого измерения.
    MPI_Dims_create(threadCount, NUM_DIMS, dims); //Функция определения оптимальной конфигурации сетки

    int n[3]; //размеры матриц
    double *A;
    double *B;
    double *C;
    if (threadRank == 0) {
        n[0] = M;
        n[1] = N;
        n[2] = K;

        A = (double *) calloc (M * N, sizeof(double));
        B = (double *) calloc (N * K, sizeof(double));
        C = (double *) calloc (M * K, sizeof(double));

        initMatrix(A, B, C);
    }

    double startTime = MPI_Wtime();
    calculate(n, A, B, C, dims, MPI_COMM_WORLD);
    double finishTime = MPI_Wtime();

    if(threadRank == 0) {
        printf("Time: %lf\nCheck result: %s\n", finishTime - startTime, checkResult(C) ? "good" : "bad");

        free(A);
        free(B);
        free(C);
    }

    MPI_Finalize();
    return 0;
}