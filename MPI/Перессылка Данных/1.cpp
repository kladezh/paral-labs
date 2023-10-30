// 1: В каждом из процессов прочитать вещественное число и вывести его противоположное значение.

#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double number; 
    if (rank == 0)
    {
        printf("Input real number: ");
        scanf_s("%lf", &number);
    }

    MPI_Bcast(&number, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double neg_number = -number;

    printf("Process rank %d: Opposite value = %lf\n", rank, neg_number);

    MPI_Finalize();
    return 0;
}
