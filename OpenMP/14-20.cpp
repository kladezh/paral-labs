// 14. Вычисление числа П/2 с помощью формулы Валлиса

#include <stdio.h>
#include <omp.h>

int main()
{
    int n = 1000000; // Количество итераций (увеличьте, чтобы улучшить точность)
    double pi_over_2 = 1.0;

    #pragma omp parallel for reduction(* : pi_over_2)
    for (int i = 1; i <= n; i++)
    {
        double numerator = 4.0 * i * i;
        double denominator = 4.0 * i * i - 1.0;
        pi_over_2 *= numerator / denominator;
    }

    pi_over_2 *= 2.0;

    printf("Value of PI/2: %lf\n", pi_over_2);

    return 0;
}
