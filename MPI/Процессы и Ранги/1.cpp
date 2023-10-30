// 1: Пересылка целых чисел в главный процесс

#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int numbers[size];
    int recv_number;

    if (rank != 0)
    {
        printf("Процесс %d: Введите целое число: ", rank);
        scanf("%d", &numbers[rank]);
        MPI_Send(&numbers[rank], 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else
    {
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(&recv_number, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            numbers[i] = recv_number;
        }

        printf("Числа в порядке возрастания рангов: ");
        for (int i = 1; i < size; i++)
        {
            printf("%d ", numbers[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
