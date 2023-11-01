// 9. Вычисление определённого интеграла методом трапеций

#include <stdio.h>
#include <omp.h>
#include <math.h>

// непрерываная функция
double f(double x)
{
    return (4.0 * x * x) - (3.0 * x) + 2.0; // 4x^2 - 3x + 2
}

int main()
{
    int n = 1000000;         // Количество интервалов
    double a = 0.0, b = 1.0; // Границы интегрирования
    double h = (b - a) / n;  // Ширина интервалов
    double integral = 0.0;

    #pragma omp parallel for reduction(+ : integral)
    for (int i = 1; i < n; i++)
    {
        double x = a + i * h;
        integral += f(x);
    }

    integral += (f(a) + f(b)) / 2; // Добавляем крайние точки

    integral *= h;

    printf("Intergal value: %lf\n", integral);

    return 0;
}
