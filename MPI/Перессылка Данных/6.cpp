// 6: 
// В подчинённых процессах чётного ранга ввести целое число, в процессах нечётного ранга ввести вещественное число.
// В каждом подчинённом процессе вывести удвоенное значение введённого числа.
// В главном процессе не выполнять никаких действий.

#include <iostream>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) { // используем главный процесс для ввода данных
        int int_num;

        // вводим данные для четных рангов
        std::cout << "EVEN RANKS\n";
        for (int i = 2; i < size; i += 2) { 
            std::cout << "For rank " << i << " enter int number: ";
            std::cin >> int_num;

            MPI_Send(&int_num, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        double real_num;

        // вводим данные для нечетных рангов
        std::cout << "\nODD RANKS\n";
        for (int i = 1; i < size; i += 2) {
            std::cout << "For rank " << i << " enter real number: ";
            std::cin >> real_num;

            MPI_Send(&real_num, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
        }

    }

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank != 0) {
        if (rank % 2 == 0) { // четный ранг
            int recv_number;

            MPI_Recv(&recv_number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            std::cout << "Rank " << rank << ": number = " << 2 * recv_number << std::endl;
        }
        else if (rank % 2 != 0) { // нечетный
            double recv_number;

            MPI_Recv(&recv_number, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            std::cout << "Rank " << rank << ": number = " << 2.0 * recv_number << std::endl;
        }
    }
    
    MPI_Finalize();
    return 0;
}
