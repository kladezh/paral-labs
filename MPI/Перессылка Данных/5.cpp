// 5: В процессах чётного ранга ввести целое число, в процессах нечётного ранга ввести вещественное число. В каждом процессе вывести удвоенное значение введённого числа.

#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double number;
    if (rank % 2 == 0)
    {
        int int_number;
        printf("Процесс %d: Введите целое число: ", rank);
        scanf_s("%d", &int_number);
        number = 2 * int_number;
    }
    else
    {
        printf("Процесс %d: Введите вещественное число: ", rank);
        scanf_s("%lf", &number);
        number *= 2;
    }

    printf("Процесс %d: Удвоенное значение = %lf\n", rank, number);

    MPI_Finalize();
    return 0;
}
