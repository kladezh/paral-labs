// 1. Вычисление скалярного произведения двух векторов

#include <iostream>
#include <stdio.h>
#include <omp.h>

using namespace std;

// вектор будет длины 100, следовательно необходимо 100 иттераций
#define N 100

int main()
{
    int i;
    double result = 0;
    double A[N], B[N];

    // Заполнение векторов A и B
    for (i = 0; i < N; i++)
    {
        A[i] = i;
        B[i] = 2 * i;
    }

    // указываем количество потоков, на которые будем делить иттерации
    omp_set_num_threads(6);

    // Вычисление скалярного произведения

    // основная директива для определения параллельной области
    #pragma omp parallel
    {                                 
        // каждый поток делает свое количество иттераций result объединяет все суммы в единое число
        #pragma omp for reduction(+ : result) // переменная result является private
        for (i = 0; i < N; i++)
        {
            // для result в каждой иттерации создаются локальные переменные, 
            // затем значения, полученные в потоках суммируются и запоминаются в исходной переменной 
            // (исходную переменную в конкретный момент может изменять только один поток), чтобы избежать гонки потоков
            result += A[i] * B[i]; 

            // отделяемая директива (может использоваться как в блоках директивы, так и в параллельных областях)
            #pragma omp critical 
            {
                // функция использует 1 поток для постоянного выводв номера потока (остальные потоки не участвуют)
                std::cout << "\nThread num: " << omp_get_thread_num(); 
            }
        }

        // определяет блок параллельного фрагмента, который должен быть выполнен единожды основным потоком (0); все остальные потоки ожидают завершения выполнения данного блока
        #pragma omp single 
        {
            // единожды выводит общее количество потоков
            std::cout << "\nThreads count: " << omp_get_num_threads();
        }
    }

    // вывод общей суммы
    std::cout << "\nScalar product: " << result; 

    return 0;
}
