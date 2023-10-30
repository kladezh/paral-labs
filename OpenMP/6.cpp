// 6. Умножение матриц, блочные схемы распределения данных

#include <stdio.h>
#include <omp.h>

#define N 100
#define M 100
#define BLOCK_SIZE 10

int main()
{
    int i, j, k, ii, jj, kk;
    double A[N][M], B[M], C[N];

    // Заполнение матрицы A и вектора B (пример)
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            A[i][j] = i + j;
        }
    }
    for (i = 0; i < M; i++)
    {
        B[i] = i;
    }

// Вычисление произведения матрицы на вектор с блочной схемой
#pragma omp parallel for private(j, k, ii, jj, kk)
    for (ii = 0; ii < N; ii += BLOCK_SIZE)
    {
        for (jj = 0; jj < M; jj += BLOCK_SIZE)
        {
            for (i = ii; i < ii + BLOCK_SIZE; i++)
            {
                for (j = jj; j < jj + BLOCK_SIZE; j++)
                {
                    C[i] += A[i][j] * B[j];
                }
            }
        }
    }

    // Вывод результата
    printf("Результат умножения матрицы на вектор:\n");
    for (i = 0; i < N; i++)
    {
        printf("%lf ", C[i]);
    }

    return 0;
}
