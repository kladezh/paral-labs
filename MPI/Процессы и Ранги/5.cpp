// 5: Пересылка ненулевого числа в главный процесс

#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int number;
    if (rank != 0)
    {
        printf("Процесс %d: Введите целое число: ", rank);
        scanf("%d", &number);
        if (number != 0)
        {
            MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Status status;
        int recv_number;
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(&recv_number, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            printf("Процесс %d: Получено число = %d от процесса %d\n", rank, recv_number, status.MPI_SOURCE);
        }
    }

    MPI_Finalize();
    return 0;
}
