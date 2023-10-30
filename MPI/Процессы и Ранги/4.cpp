// 4: Пересылка чисел в разные процессы

#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N;
    if (rank == 0)
    {
        printf("Введите целое число N (от 0 до %d): ", size - 2);
        scanf("%d", &N);
        int numbers[N];
        for (int i = 0; i < N; i++)
        {
            printf("Введите число %d: ", i + 1);
            scanf("%d", &numbers[i]);
        }
        for (int i = 1; i < size - 1; i++)
        {
            MPI_Send(&numbers[i - 1], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        int last_number = numbers[N - 1];
        for (int i = size - 1; i > N; i--)
        {
            MPI_Send(&last_number, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }
    else
    {
        int number;
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Процесс %d: Получено число = %d\n", rank, number);
    }

    MPI_Finalize();
    return 0;
}
