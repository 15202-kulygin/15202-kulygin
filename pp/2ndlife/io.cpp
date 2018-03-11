#include <mpi.h>
#include <iostream>

int main (int argc, char ** argv)
{
	MPI_Init(&argc, &argv);

	int rank, size;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	while (1)
	{
		
		std::cerr << "Size = " << size << ", rank = " << rank << "\n"; // либо через flush
	}

	MPI_Finalize();
	return 0;
}


/*
mpicxx -v 1.cpp -o 1.exe - компиляция
запуск:
можно как обычную программу
или
mpiexec -n 1 ./1.exe



коммуникатор определяется:
группой, контекстом, топологией
*/
