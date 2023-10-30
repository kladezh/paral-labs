// 4. Умножение матрицы на вектор при блочном разделении данных

#include <stdio.h>
#include <omp.h>

#define N 100
#define M 100
#define BLOCK_SIZE 10

int main()
{
    int i, j, k;
    double A[N][M], B[M], C[N];

    // Заполнение матрицы A и вектора B (пример)
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            A[i][j] = i + j;
        }
        B[i] = i;
    }

// Вычисление произведения матрицы на вектор с блочным разделением
#pragma omp parallel for private(j, k)
    for (i = 0; i < N; i += BLOCK_SIZE)
    {
        for (j = 0; j < M; j++)
        {
            for (k = i; k < i + BLOCK_SIZE; k++)
            {
                C[k] += A[k][j] * B[j];
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
