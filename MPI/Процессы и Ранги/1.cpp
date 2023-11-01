/*
* 1.
* В каждом подчинённом процессе дано целое число.
* Переслать эти числа в главный процесс, используя функции MPI_Send и MPI_Recv
* (стандартные блокирующие функции для передачи и приема сообщения), 
* и вывести их в главном процессе.Полученные числа выводить в порядке возрастания рангов переславших их процессов.
*/ 

#include <iostream>
#include <vector>
#include <random>
#include <mpi.h>

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

//argc - хранит количество аргументов командной строки, переданных при запуске программы, argv - указатель на массив строк, представляющих аргументы командной строки
int main(int argc, char** argv) 
{
    MPI_Init(&argc, &argv);

    int rank, size; //Все имеющиеся в параллельной программе процессы входят в состав создаваемого по умолчанию коммуникатора с идентификатором MPI_COMM_WORLD.
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //опр ранга всех процессов в данном коммуникаторе 
    MPI_Comm_size(MPI_COMM_WORLD, &size); //опр количества всех процессов


    if (rank != 0)//для процессов, которые не являются главными
    {
        RandomGenerator random;

        // генерируем рандомное число
        int number = random.number(0, 20);

        // процесс-отправитель (Адрес буфера памяти данных отправляемого сообщения, кол-во элементов, тип элементов, ранг процесса-получателя, значение для идентификации сообщений, коммуникатор)
        MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else // для главного процесса
    {   
        std::vector<int> numbers(size);
        int recv_number;

        for (int i = 1; i < size; i++)
        {
            // процесс-получатель (Адрес буфера памяти для приема сообщения, кол-во элементов, тип элементов, ранг процесса-отправителя, значение для идентификации сообщений, коммуникатор, указатель на структуру данных с информацией о результате)
            MPI_Recv(&recv_number, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            numbers[i] = recv_number; // собирает все целые числа, отправленные каждым не-главным процессом
        }
        // Функция MPI_Recv является блокирующей для процесса-получателя, 
        // т.е. его выполнение приостанавливается до завершения работы функции. 
        // Таким образом, если по каким-то причинам ожидаемое для приема сообщение будет отсутствовать, 
        // выполнение параллельной программы будет блокировано


        std::cout << "Numbers in ascending order of ranks:\n";
        for (int i = 1; i < size; i++)
        {
            std::cout << "[" << i << "] = " << numbers[i] << "\n";
        }
        std::cout << std::endl;
    }

    //обязательная функция для обозначения конца параллельной области
    MPI_Finalize();
    return 0;
}
