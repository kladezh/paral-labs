// 5. Умножение матриц, ленточный алгоритм

#include <stdio.h>
#include <omp.h>

#define N 100
#define M 100

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

// Вычисление произведения матрицы на вектор с ленточным алгоритмом
#pragma omp parallel for private(j, k)
    for (i = 0; i < N; i++)
    {
        for (j = i; j < M; j++)
        {
            for (k = 0; k < N; k++)
            {
                C[i] += A[i][k] * B[k];
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
