// 2: В каждом из процессов прочитать целое число A и вывести его удвоенное значение. Для главного процесса вывести количество процессов.

#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int A;
    printf("Процесс %d: Введите целое число A: ", rank);
    scanf_s("%d", &A);

    int doubled_A = 2 * A;

    if (rank == 0)
    {
        printf("Количество процессов: %d\n", size);
    }

    printf("Процесс %d: Удвоенное значение A = %d\n", rank, doubled_A);

    MPI_Finalize();
    return 0;
}
