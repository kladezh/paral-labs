// 6: Пересылка данных в главный процесс с использованием параметра MPI_ANY_SOURCE

#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N;
    MPI_Status status;
    int recv_number;

    if (rank == 0)
    {
        printf("Введите целое число N: ");
        scanf("%d", &N);
        int numbers[N];
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(&recv_number, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            numbers[status.MPI_SOURCE] = recv_number;
        }

        printf("Числа в порядке возрастания рангов: ");
        for (int i = 1; i < size; i++)
        {
            printf("%d ", numbers[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Процесс %d: Введите целое число: ", rank);
        scanf("%d", &recv_number);
        MPI_Send(&recv_number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
