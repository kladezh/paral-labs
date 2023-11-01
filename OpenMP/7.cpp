// 7. Умножение матриц (варианты распараллеливания вложенных циклов)

#include <stdio.h>
#include <omp.h>

#define N 100
#define M 100

int main()
{
    int i, j;
    double A[N][M], B[M], C[N];

    // Заполнение матрицы A
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            A[i][j] = i + j;
        }
    }

    // Заполенение вектора B
    for (i = 0; i < M; i++)
    {
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
    printf("Result:\n");
    for (i = 0; i < N; i++)
    {
        printf("%lf ", C[i]);
    }

    return 0;
}
