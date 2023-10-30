// 11. Вычисление числа ln 2

#include <stdio.h>
#include <math.h>
#include <omp.h>

int main()
{
    int n = 1000000; // Количество итераций (увеличьте, чтобы улучшить точность)
    double ln2 = 0.0;

#pragma omp parallel for reduction(+ : ln2)
    for (int i = 1; i <= n; i++)
    {
        double term = (i % 2 == 0) ? -1.0 : 1.0;
        ln2 += term / i;
    }

    printf("Значение ln 2: %lf\n", ln2);

    return 0;
}
