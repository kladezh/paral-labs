/*
* 6.
* В каждом подчинённом процессе дано целое число N, 
* причём для одного процесса это число больше нуля, 
* а для остальных равно нулю. 
* 
* В процессе с ненулевым N дан также набор из N чисел. 
* 
* Переслать данный набор чисел в главный процесс 
* и вывести в главном процессе полученные числа и ранг процесса, переславшего этот набор. 
*
* При приёме сообщения использовать параметр MPI_ANY_SOURCE.
*/

#include <iostream>
#include <vector>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N = 4;

    if (rank == 0) // главный процесс
    {
        MPI_Status status;
        std::vector<int> recv_numbers(N);

        MPI_Recv(recv_numbers.data(), N, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        int source_rank = status.MPI_SOURCE;

        std::cout << "From rank [" << source_rank << "] numbers:\n";
        for (int i = 0; i < recv_numbers.size(); i++) {
            std::cout << "[" << i << "] = " << recv_numbers[i] << "\n";
        }

        std::cout << std::endl;
    }
    else if (rank == N) // подчиненный процесс
    {
        std::vector<int> numbers(N);
        for (int i = 0; i < numbers.size(); i++) {
            numbers[i] = (i + 1) * 10;
        }

        MPI_Send(numbers.data(), N, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
