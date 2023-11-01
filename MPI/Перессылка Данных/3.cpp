/*
* 3.
* В главном процессе прочесть вещественное число X и вывести его противоположное значение, 
* в каждом из остальных процессов (подчинённых процессов, ранг которых больше 0) вывести его ранг.
*/

#include <iostream>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) { // главный процесс
        double X;
        std::cout << "Enter the real number: ";
        std::cin >> X;

        std::cout << "Opposite number = " << -X << std::endl;
    }
    
    MPI_Barrier(MPI_COMM_WORLD);

    if (rank != 0) { // подчиненные процессы
        std::cout << "Rank: " << rank;
    }
    std::cout << std::endl;

    MPI_Finalize();
    return 0;
}
