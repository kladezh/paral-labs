// 1. Вычисление скалярного произведения двух векторов

#include <iostream>
#include <stdio.h>
#include <omp.h>

using namespace std;

#define N 100 // вектор будет длины 100, следовательно необходимо 100 иттераций

int main()
{
    int i;
    double result = 0;
    double A[N], B[N]; 

    // Заполнение векторов A и B (пример)
    for (i = 0; i < N; i++)
    {
        A[i] = i;
        B[i] = 2 * i;
    }

    omp_set_num_threads(6); //указываем количество потоков 

    // Вычисление скалярного произведения
#pragma omp parallel //распараллеливаем все иттерации  на 6 потоков, вход в параллельную область
    {
#pragma omp for reduction(+ : result) // каждый поток делает свое количество иттераций result объединяет все суммы в единое число
        for (i = 0; i < N; i++)
        {
            result += A[i] * B[i]; //формула для нахождения скалярного произведения

#pragma omp critical
            {
                std::cout << "\nThread num: " << omp_get_thread_num(); //функция использует 1 поток для постоянного выводв номера потока (остальные потоки не участвуют)
            }
        }

#pragma omp single
        {
            std::cout << "\nThreads count: " << omp_get_num_threads(); //единожды выводит общее количество потоков 
        }
    }

    std::cout << "\nScalar product: " << result; //вывод общей суммы

    return 0;
}
