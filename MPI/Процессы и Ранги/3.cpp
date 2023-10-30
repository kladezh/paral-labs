// 3: Пересылка четырех целых чисел в главный процесс

#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int numbers[4];
    int recv_numbers[4];

    if (rank != 0)
    {
        printf("Процесс %d: Введите четыре целых числа: ", rank);
        for (int i = 0; i < 4; i++)
        {
            scanf("%d", &numbers[i]);
        }
        MPI_Send(numbers, 4, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else
    {
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(recv_numbers, 4, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Числа от процесса %d: %d %d %d %d\n", i, recv_numbers[0], recv_numbers[1], recv_numbers[2], recv_numbers[3]);
        }
    }

    MPI_Finalize();
    return 0;
}
