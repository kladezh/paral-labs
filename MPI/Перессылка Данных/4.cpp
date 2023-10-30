// 4: В процессах чётного ранга ввести целое число и вывести его удвоенное значение. В процессах нечётного ранга не выполнять никаких действий.

#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank % 2 == 0)
    {
        int number;
        printf("Процесс %d: Введите целое число: ", rank);
        scanf_s("%d", &number);

        int doubled_number = 2 * number;
        printf("Процесс %d: Удвоенное значение = %d\n", rank, doubled_number);
    }

    MPI_Finalize();
    return 0;
}
