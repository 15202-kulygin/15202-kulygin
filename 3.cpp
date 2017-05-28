#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<sys/time.h>
#include <mpi.h>

#define in 60
#define jn 60
#define kn 60
#define a 1

int I;
int J;
int K;

double Fresh(double, double, double);

double Ro(double, double, double);

/* Выделение памяти для 3D пространства для текущей и предыдущей итерации */
double *(F[2]);
double *(buffer[2]);
double hx, hy, hz;

double Fi, Fj, Fk, F1;
double X = 2.0;
double Y = 2.0;
double Z = 2.0;
double e = 0.00001;
int L0 = 1;
int L1 = 0;
int f, tmpF;
int threadRank = 0;
int threadCount = 0;
double owx;
double owy;
double owz;

int *perThreads;
int *offsets;

double c = 2 / owx + 2 / owy + 2 / owz + a;
MPI_Request sendRequest[2] = {};
MPI_Request recRequest[2] = {};

/* Функция определения точного решения */
double Fresh(double x, double y, double z) {
    double res;
    res = x + y + z;
    return res;
}

/* Функция задания правой части уравнения */
double Ro(double x, double y, double z) {
    double d;
    d = -a * (x + y + z);
    return d;
}

void Inic(int *perThreads, int *offsets, int threadRank) {
    for (int i = 0, startLine = offsets[threadRank]; i <= perThreads[threadRank] - 1 ; i++, startLine++) {
        for (int j = 0; j <= jn; j++) {
            for (int k = 0; k <= kn; k++) {
                if ((startLine != 0) && (j != 0) && (k != 0) && (startLine != in) && (j != jn) && (k != kn)) {
                    F[0][i*J*K + j*K + k] = 0;
                    F[1][i*J*K + j*K + k] = 0;
                }
                else {
                    F[0][i*J*K + j*K + k] = Fresh(startLine * hx, j * hy, k * hz);
                    F[1][i*J*K + j*K + k] = Fresh(startLine * hx, j * hy, k * hz);
                }
            }
        }
    }

}

void calcEdges() {
    for(int j = 1; j < jn; ++j) {
        for(int k = 1; k < kn; ++k) {

            if(threadRank != 0) {
                int i = 0;
                Fi = (F[L0][(i + 1)*J*K + j*K + k] + buffer[0][j*K + k]) / owx;
                Fj = (F[L0][i * J * K + (j + 1) * K + k] + F[L0][i * J * K + (j - 1) * K + k]) / owy;
                Fk = (F[L0][i * J * K + j * K + (k + 1)] + F[L0][i * J * K + j * K + (k - 1)]) / owz;
                F[L1][i*J*K + j*K + k] = (Fi + Fj + Fk - Ro((i + offsets[threadRank]) * hx, j * hy, k * hz)) / c;
                if (fabs(F[L1][i*J*K + j*K + k] - Fresh((i + offsets[threadRank]) * hx, j * hy, k * hz)) > e) {
                    f = 0;
                }
            }

            if(threadRank != threadCount - 1) {
                int i = perThreads[threadRank] - 1;
                Fi = (buffer[1][j*K + k] + F[L0][(i - 1)*J*K + j*K + k]) / owx;
                Fj = (F[L0][i * J * K + (j + 1) * K + k] + F[L0][i * J * K + (j - 1) * K + k]) / owy;
                Fk = (F[L0][i * J * K + j * K + (k + 1)] + F[L0][i * J * K + j * K + (k - 1)]) / owz;
                F[L1][i*J*K + j*K + k] = (Fi + Fj + Fk - Ro((i + offsets[threadRank]) * hx, j * hy, k * hz)) / c;
                if (fabs(F[L1][i*J*K + j*K + k] - Fresh((i + offsets[threadRank]) * hx, j * hy, k * hz)) > e) {
                    f = 0;
                }
            }

        }
    }
}

void sendData() {
    if(threadRank != 0) {//1
        MPI_Isend(&(F[L0][0]), K*J, MPI_DOUBLE, threadRank - 1, 0, MPI_COMM_WORLD, &sendRequest[0]); //низ
        MPI_Irecv(buffer[0], K*J, MPI_DOUBLE, threadRank - 1, 1, MPI_COMM_WORLD, &recRequest[1]);
    }
    if(threadRank != threadCount - 1) { //0
        MPI_Isend(&(F[L0][(perThreads[threadRank] - 1)*J*K]), K*J, MPI_DOUBLE, threadRank + 1, 1, MPI_COMM_WORLD, &sendRequest[1]); //верх
        MPI_Irecv(buffer[1], K*J, MPI_DOUBLE, threadRank + 1, 0, MPI_COMM_WORLD, &recRequest[0]);
    }
}

void calcCenter() {
    for (int i = 1; i < perThreads[threadRank] - 1; ++i) {
        for (int j = 1; j < jn; ++j) {
            for (int k = 1; k < kn; ++k) {
                Fi = (F[L0][(i + 1)*J*K + j*K + k] + F[L0][(i - 1)*J*K + j*K + k]) / owx;
                Fj = (F[L0][i * J * K + (j + 1) * K + k] + F[L0][i * J * K + (j - 1) * K + k]) / owy;
                Fk = (F[L0][i * J * K + j * K + (k + 1)] + F[L0][i * J * K + j * K + (k - 1)]) / owz;
                F[L1][i*J*K + j*K + k] = (Fi + Fj + Fk - Ro((i + offsets[threadRank]) * hx, j * hy, k * hz)) / c;
                if (fabs(F[L1][i*J*K + j*K + k] - Fresh((i + offsets[threadRank]) * hx, j * hy, k * hz)) > e) {
                    f = 0;
                }
            }
        }
    }
}

void recData() {
    if(threadRank != 0) {
        MPI_Wait(&recRequest[1], MPI_STATUS_IGNORE);
        MPI_Wait(&sendRequest[0], MPI_STATUS_IGNORE);
    }
    if(threadRank != threadCount - 1) {
        MPI_Wait(&recRequest[0], MPI_STATUS_IGNORE);
        MPI_Wait(&sendRequest[1], MPI_STATUS_IGNORE);
    }
}

void findMaxDiff() {
    double max = 0.0;

    for (int i = 1; i < perThreads[threadRank] - 2; i++) {
        for (int j = 1; j < jn; j++) {
            for (int k = 1; k < kn; k++) {
                if ((F1 = fabs(F[L1][i*J*K + j*K + k] - Fresh((i + offsets[threadRank]) * hx, j * hy, k * hz))) > max) {
                    max = F1;
                }
            }
        }
    }

    double tmpMax = 0;
    MPI_Allreduce(&max, &tmpMax, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);

    if(threadRank == 0) {
        max = tmpMax;
        printf("Max differ = %lf\n", max);
    }
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &threadCount);
    MPI_Comm_rank(MPI_COMM_WORLD, &threadRank);

    if(threadRank == 0) {
        printf("Thread count: %d\n", threadCount);
    }

    perThreads = new int[threadCount]();
    offsets = new int[threadCount]();
    for(int i = 0, height = kn + 1, tmp = threadCount - (height % threadCount), currentLine = 0; i < threadCount; ++i) {
        offsets[i] = currentLine;
        perThreads[i] = i < tmp ? (height / threadCount) : (height / threadCount + 1);
        currentLine += perThreads[i];
    }

    I = perThreads[threadRank];
    J = (jn + 1);
    K = (kn + 1);

    F[0] = new double[I * J * K]();
    F[1] = new double[I * J * K]();

    buffer[0] = new double[K*J]();
    buffer[1] = new double[K*J]();

    /* Размеры шагов */
    hx = X / in;
    hy = Y / jn;
    hz = Z / kn;

    owx = pow(hx, 2);
    owy = pow(hy, 2);
    owz = pow(hz, 2);
    c = 2 / owx + 2 / owy + 2 / owz + a;

    Inic(perThreads, offsets, threadRank);

    double start = MPI_Wtime();

    do {
        f = 1;
        L0 = 1 - L0;
        L1 = 1 - L1;

        //обмениваемся краями
        sendData();

        //считаем середину
        calcCenter();


        //Ждем получения всех данных
        recData();

        //считаем края
        calcEdges();

        MPI_Allreduce(&f, &tmpF, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
        f = tmpF;
    }
    while (f == 0);

    double finish = MPI_Wtime();

    if(threadRank == 0) {
        printf("Time: %lf\n", finish - start);
    }

    findMaxDiff();

    delete[] buffer[0];
    delete[] buffer[1];
    delete[] F[0];
    delete F[1];
    delete[] offsets;
    delete[] perThreads;

    MPI_Finalize();
    return 0;
}