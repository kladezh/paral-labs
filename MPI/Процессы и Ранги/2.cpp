// 2: Пересылка вещественных чисел в подчинённые процессы

#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double number;
    if (rank == 0)
    {
        printf("Введите вещественное число: ");
        scanf("%lf", &number);
        for (int i = 1; i < size; i++)
        {
            MPI_Send(&number, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Recv(&number, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Процесс %d: Полученное вещественное число = %lf\n", rank, number);
    }

    MPI_Finalize();
    return 0;
}
