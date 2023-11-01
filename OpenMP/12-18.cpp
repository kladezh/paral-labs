// 12. Вычисление числа П^2/6

#include <stdio.h>
#include <omp.h>

#define PI 3.14159265358979323846

int main()
{
    int n = 1000000; // Количество итераций (увеличьте, чтобы улучшить точность)
    double pi_square_over_6 = 0.0;

    #pragma omp parallel for reduction(+ : pi_square_over_6)
    for (int i = 1; i <= n; i++)
    {
        pi_square_over_6 += 1.0 / (i * i);
    }

    pi_square_over_6 *= PI * PI / 6.0;

    printf("Value of PI^2/6: %lf\n", pi_square_over_6);

    return 0;
}
