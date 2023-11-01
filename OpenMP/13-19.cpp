// 13. Вычисление числа П^2/12

#include <stdio.h>
#include <omp.h>

#define PI 3.14159265358979323846

int main()
{
    int n = 1000000; // Количество итераций (увеличьте, чтобы улучшить точность)
    double pi_square_over_12 = 0.0;

    #pragma omp parallel for reduction(+ : pi_square_over_12)
    for (int i = 1; i <= n; i++)
    {
        double term = (i % 2 == 0) ? -1.0 : 1.0;
        pi_square_over_12 += term / (i * i);
    }

    pi_square_over_12 *= PI * PI / 12.0;

    printf("Значение π^2/12: %lf\n", pi_square_over_12);

    return 0;
}
