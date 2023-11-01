/*
* 8. 
* В каждом процессе даны два числа: вещественное A и целое N, 
* причём набор чисел N содержит все значения от 0 до K − 1, где K — количество процессов. 
* 
* Используя функции MPI_Send и MPI_Recv (с параметром MPI_ANY_SOURCE), 
* выполнить в каждом процессе пересылку числа A в процесс N и вывести полученное число, 
* а также ранг процесса, из которого число было получено.
*/

#include <iostream>
#include <mpi.h>
#include <random>

#define MAIN_RANK 0

class RandomGenerator {
private:
    std::random_device _rd;
    std::mt19937 _gen;

public:
    RandomGenerator() : _gen(_rd()) {}

    template<class T>
    T number(T min, T max) {
        if constexpr (std::is_integral<T>::value) {
            std::uniform_int_distribution<T> dist(min, max);
            return dist(_gen);
        }
        else {
            std::uniform_real_distribution<T> dist(min, max);
            return dist(_gen);
        }
    }
};

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    auto random_gen = RandomGenerator();

    // Генерация числа A для каждого процесса
    double A = random_gen.number(1.0, 20.0);

    int K = size; // количество процессов
    int N = (rank + 1) % K; // номер следующего процесса (циклично)

    int source = (rank - 1 + K) % K; // номер предыдущего процесса (циклично)

    double recv_A;
    MPI_Status status;

    // Отправка числа A процессу N и получение числа от процесса-источника
    MPI_Sendrecv(
        &A, 1, MPI_DOUBLE, N, 0,           // отправить число A процессу N 
        &recv_A, 1, MPI_DOUBLE, source, 0, // получить число A из другого процесса
        MPI_COMM_WORLD, &status
    );

    // Вывод полученного числа и ранга отправителя
    std::cout << "Rank " << rank << " received number " << recv_A << " from rank " << source << std::endl;
    

    MPI_Finalize();

    return 0;
}
