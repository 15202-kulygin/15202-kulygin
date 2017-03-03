#include <mpi.h>
#include <stdio.h>

#define N 10

// mpicc –o test mpitest.c
// mpecc -mpilog -o mpetest mpitest.c

// mpirun –np 4 a
// mpiexec –n 4 a

int main(int argc,char *argv[])
{ 
	int size, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	//printf ("Hello from process #%d of %d\n",rank,size);
	int array [N];
	int i = 0;
	for (i = 0; i < N; ++i)
	{
		array[i] = rank;
	}
	/*printf("Array before replacing : \n");
	for (i = 0; i < N; ++i)
	{
		printf("%d ", array[i]);
	}*/
	printf("\n\n");
	MPI_Sendrecv_replace(array, N, MPI_INT, (rank+1)%size, 123, (rank+size-1)%size, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	printf("Array in process %d after replacing : \n", rank);
	for (i = 0; i < N; ++i)
	{
		printf("%d ", array[i]);
	}
	printf("\n\n");
	MPI_Finalize();
	return 0;
}