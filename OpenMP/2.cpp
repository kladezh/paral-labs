// 2. Умножение матрицы на вектор при разделении данных по строкам

#include <stdio.h>
#include <omp.h>

#define N 100 
#define M 100

int main()
{
    int i, j;
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

// Вычисление произведения матрицы на вектор
#pragma omp parallel for private(j)
    for (i = 0; i < N; i++)
    {
        C[i] = 0;
        for (j = 0; j < M; j++)
        {
            C[i] += A[i][j] * B[j];
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
