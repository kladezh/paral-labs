// 6: В подчинённых процессах чётного ранга ввести целое число, в процессах нечётного ранга ввести вещественное число.
// В каждом подчинённом процессе вывести удвоенное значение введённого числа.
// В главном процессе не выполнять никаких действий.

#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank % 2 == 0 && rank != 0)
    {
        int int_number;
        printf("Процесс %d: Введите целое число: ", rank);
        scanf_s("%d", &int_number);

        int doubled_number = 2 * int_number;
        printf("Процесс %d: Удвоенное значение = %d\n", rank, doubled_number);
    }

    MPI_Finalize();
    return 0;
}
