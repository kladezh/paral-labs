/*
* 3:
* В главном процессе прочесть вещественное число X и вывести его противоположное значение, 
* в каждом из остальных процессов (подчинённых процессов, ранг которых больше 0) вывести его ранг. 
*/

#include <iostream>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) { // главный процесс
        double number;

        std::cout << "Main proccess \n";
        std::cout << "Enter real number: ";
        std::cin >> number;

        std::cout << "Opposite value = " << -number << "\n" << std::endl;
    }

    MPI_Barrier(MPI_COMM_WORLD); // процессы ждут пока главный процесс считает консоль

    if (rank != 0) { // подчиненные процессы
        std::cout << "Sub proccess [Rank = " << rank << "]" << std::endl;
    }

    MPI_Finalize();
    return 0;
}
