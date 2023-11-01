/*
* 7.
* В каждом процессе чётного ранга (включая главный) дано целое число N (> 0) и набор из N вещественных чисел. 
* Вывести в каждом из этих процессов сумму чисел из данного набора. 
* В процессах нечётного ранга не выполнять никаких действий.
*/

#include <iostream>
#include <vector>
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

    if (rank % 2 == 0) { // четные процессы

        if (rank == MAIN_RANK) { // главный процесс    
            int send_N; // целое число N > 0
            std::vector<double> send_data; // массив из N вещественных чисел

            // отправляем данные только четным процессам
            for (int rank_i = 2; rank_i < size; rank_i += 2) {
                    send_N = random_gen.number(1, 10);

                    send_data.resize(send_N);

                    for (int i = 0; i < send_data.size(); i++) {
                        send_data[i] = random_gen.number(1.0, 10.0);
                    }

                    MPI_Send(&send_N, 1, MPI_INT, rank_i, MAIN_RANK, MPI_COMM_WORLD);
                    MPI_Send(send_data.data(), send_N, MPI_DOUBLE, rank_i, MAIN_RANK, MPI_COMM_WORLD);
            }
        }
        else { // подчиненные процессы
            int recv_N;
            std::vector<double> recv_data;

            MPI_Recv(&recv_N, 1, MPI_INT, MAIN_RANK, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            recv_data.resize(recv_N);

            MPI_Recv(recv_data.data(), recv_N, MPI_DOUBLE, MAIN_RANK, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

             // Вычисление суммы вещественных чисел
            double sum = 0.0;
            for (double x: recv_data) {
                sum += x;
            }

            // Вывод результата в каждом четном процессе
            std::string output;
            std::cout << "Rank: " << rank << ", N: " << recv_N << ", Sum: " << sum << std::endl;
        }
    }
    else { // нечетные процессы
        // ничего не делать...
    }
   
    MPI_Finalize();

    return 0;
}
