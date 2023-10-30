// 12. Вычисление числа П^2/6

#include <stdio.h>
#include <math.h>
#include <omp.h>

int main()
{
    int n = 1000000; // Количество итераций (увеличьте, чтобы улучшить точность)
    double pi_square_over_6 = 0.0;

#pragma omp parallel for reduction(+ : pi_square_over_6)
    for (int i = 1; i <= n; i++)
    {
        pi_square_over_6 += 1.0 / (i * i);
    }

    pi_square_over_6 *= M_PI * M_PI / 6.0;

    printf("Значение π^2/6: %lf\n", pi_square_over_6);

    return 0;
}
