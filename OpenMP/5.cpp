// 5. Умножение матриц, ленточный алгоритм

#include <stdio.h>
#include <omp.h>

#define N 100
#define M 100

int main()
{
    int i, j, k;
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
    printf("Result:\n");
    for (i = 0; i < N; i++)
    {
        printf("%lf\n", C[i]);
    }

    return 0;
}
