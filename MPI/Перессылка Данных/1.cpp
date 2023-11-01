/*
* 1:
* В каждом из процессов, входящих в коммуникатор MPI_COMM_WORLD, 
* прочесть одно вещественное число и вывести его противоположное значение.
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

    if (rank == 0) // главный процесс 
    {
        double number;

        for (int i = 1; i < size; i++) {
            std::cout << "For "<< i << " process input real number: ";
            std::cin >> number;

            MPI_Send(&number, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
        }
    }
    else { // подчиненные процессы
        double recv_number;

        MPI_Recv(&recv_number, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        double neg_number = -recv_number;

        std::cout << "Process rank " << rank << ": Opposite value = " << neg_number << std::endl;
    }

    MPI_Finalize();
    return 0;
}
