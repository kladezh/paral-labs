/*
* 2:
* В каждом из процессов, входящих в коммуникатор MPI_COMM_WORLD,
* прочесть одно целое число A и вывести его удвоенное значение.
* 
* Кроме того, для главного процесса (процесса ранга 0) вывести количество процессов,
* входящих в коммуникатор MPI_COMM_WORLD.
*/


#include <iostream>
#include <mpi.h>

//argc - хранит количество аргументов командной строки, переданных при запуске программы, argv - указатель на массив строк, представляющих аргументы командной строки
int main(int argc, char** argv) 
{
    // обязательная функция для обозначения начала параллельной программы. 
    // служит для инициализации среды выполнения MPI программы 
    MPI_Init(&argc, &argv); 

    int rank, size; //Все имеющиеся в параллельной программе процессы входят в состав создаваемого по умолчанию коммуникатора с идентификатором MPI_COMM_WORLD.
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //опр ранга всех процессов в данном коммуникаторе 
    MPI_Comm_size(MPI_COMM_WORLD, &size); //опр количества всех процессов

    if (rank == 0) //главный процесс имеет ранг 0
    {
        std::cout << "Rank: " << rank << "\n";
        std::cout << "Count of proccesses: " << size << std::endl;
        
        int A;

        for (int i = 1; i < size; i++) {
            std::cout << "Rank " << i << ": Enter int number A: ";
            std::cin >> A;

            MPI_Send(&A, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }
    else {
        int recv_A;

        MPI_Recv(&recv_A, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        int doubled_A = 2 * recv_A;

        std::cout << "Rank: " << rank << ", Doubled A = " << doubled_A << "\n";
    }


    //обязательная функция для обозначения конца параллельной области
    MPI_Finalize();
    return 0;
}

