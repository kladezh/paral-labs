/*
* 5.
* В процессах чётного ранга (включая главный) ввести целое число, в процессах нечётного ранга ввести вещественное число.
* В каждом процессе вывести удвоенное значение введённого числа.
*/

#include <mpi.h>
#include <iostream>
#include <vector>

using namespace std;

int process_even_rank(int rank, int number) {
    return number * 2;
}

double process_odd_rank(int rank, double number) {
    return number * 2.0;
}

int main(int argc, char** argv) {
    srand(time(NULL));

    MPI_Init(&argc, &argv);

    // Получение ранга текущего процесса
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Получение размера коммуникатора MPI_COMM_WORLD
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Переменные для хранения результатов
    int result_int;
    double result_double;

    if (rank == 0) {
        // Процесс с рангом 0 читает свой собственный ввод и выполняет свои операции
        int number;
        cout << "Enter an integer for the process with rank " << rank << ": ";
        cin >> number;
        result_int = process_even_rank(rank, number);

        // Затем он читает ввод для других процессов и отправляет его им
        for (int i = 1; i < size; ++i) {
            if (i % 2 == 0) {
                cout << "Enter an integer for the process with rank " << i << ": ";
                cin >> number;
                MPI_Send(&number, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
            else {
                double real_number;
                cout << "Enter a real number for the process with rank " << i << ": ";
                cin >> real_number;
                MPI_Send(&real_number, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            }
        }

        // Выводит свои собственные результаты
        cout << "Process with rank " << rank << " received the number " << result_int / 2 << "\n";
        cout << "Doubled value: " << result_int << "\n";

        // Запрашивает и выводит результаты от других процессов
        for (int i = 1; i < size; ++i) {
            if (i % 2 == 0) {
                MPI_Recv(&result_int, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                cout << "Process with rank " << i << " received the number " << result_int / 2 << "\n";
                cout << "Doubled value: " << result_int << "\n";
            }
            else {
                MPI_Recv(&result_double, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                cout << "Process with rank " << i << " received the number " << result_double / 2.0 << "\n";
                cout << "Doubled value: " << result_double << "\n";
            }
        }
    }
    else {
        // Каждый процесс получает свой ввод от процесса с рангом 0 и выполняет свои операции
        if (rank % 2 == 0) {
            int number;
            MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            result_int = process_even_rank(rank, number);
            // Отправляет результаты обратно в процесс с рангом 0
            MPI_Send(&result_int, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
        else {
            double number;
            MPI_Recv(&number, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            result_double = process_odd_rank(rank, number);
            // Отправляет результаты обратно в процесс с рангом 0
            MPI_Send(&result_double, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();

    return 0;
}
