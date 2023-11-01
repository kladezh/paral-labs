/*
* 2.
* В главном процессе дан набор вещественных чисел;
* количество чисел равно количеству подчинённых процессов.
* С помощью функции MPI_Send переслать по одному числу в каждый из подчинённых процессов
* (первое число в процесс 1, второе — в процесс 2, и т. д.) и вывести в подчинённых процессах полученные числа.
*/

#include <mpi.h>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    vector<double> numbers(size);
    double number;

    srand(time(NULL) + rank);  // Инициализация генератора случайных чисел

    if (rank == 0) {
        for (int i = 0; i < size; ++i) {
            numbers[i] = (rand() % 101) * 1.0;  // Заполнение случайными числами от 0 до 100
        }

        for (int i = 1; i < size; ++i) {
            MPI_Send(&numbers[i], 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
        }

        number = numbers[0];
    }
    else {
        MPI_Recv(&number, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    vector<double> all_numbers(size);
    MPI_Gather(&number, 1, MPI_DOUBLE, all_numbers.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Все числа из массива, начиная с нуля:" << endl;
        for (int i = 1; i < size; ++i) {
            cout << numbers[i] << "\t";
        }
        cout << endl;

        for (int i = 1; i < size; ++i) {
            cout << "Process with rank " << i << " recieved number: " << all_numbers[i] << endl;
        }

        cout << endl;
    }

    MPI_Finalize();

    return 0;
}
