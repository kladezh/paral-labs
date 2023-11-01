/*
* 5. 
* В каждом подчинённом процессе дано целое число, 
* причём только для одного процесса это число отлично от нуля. 
* Переслать ненулевое число в главный процесс 
* и вывести в главном процессе полученное число и ранг процесса, переславшего это число. 
* 
* Для приёма сообщения в главном процессе использовать функцию MPI_Recv с параметром MPI_ANY_SOURCE.
*/

#include <iostream>
#include <mpi.h>
#include <random>

#define NOT_NULL_RANK 4

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) // главный процесс
    {
        MPI_Status status;
        int recv_number;

        MPI_Recv(&recv_number, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        int source_rank = status.MPI_SOURCE;

        std::cout << "From rank [" << source_rank << "] number = " << recv_number << std::endl;
    }
    else // подчиненный процесс
    {
        int number = rank == NOT_NULL_RANK ? 17 : 0;

        if (number != 0) {
            MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
