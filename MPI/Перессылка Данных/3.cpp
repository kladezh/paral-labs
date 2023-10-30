// 3: В главном процессе прочитать вещественное число X и вывести его противоположное значение. В каждом из остальных процессов вывести его ранг.

#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        double X;
        printf("Введите вещественное число X: ");
        scanf_s("%lf", &X);

        double neg_X = -X;
        printf("Главный процесс: Противоположное значение X = %lf\n", neg_X);
    }
    else
    {
        printf("Процесс %d: Мой ранг = %d\n", rank, size);
    }

    MPI_Finalize();
    return 0;
}
