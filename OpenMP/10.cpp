// 10. Вычисление определённого интеграла методом Симпсона

#include <stdio.h>
#include <omp.h>
#include <math.h>

#define PI 3.14159265358979323846

// непрерываная функция
double f(double x)
{
    return 2.0 * (sin( (3.0 * x) + (PI / 4.0) ));
}

int main()
{
    int n = 1000000;         // Количество интервалов (должно быть четным)
    double a = 0.0, b = 1.0; // Границы интегрирования
    double h = (b - a) / n;  // Ширина интервалов
    double integral = 0.0;

    #pragma omp parallel for reduction(+ : integral)
    for (int i = 0; i <= n; i++)
    {
        double x = a + i * h;
        double factor = (i == 0 || i == n) ? 1 : (i % 2 == 0) ? 2 : 4;
        integral += factor * f(x);
    }

    integral *= h / 3;

    printf("Integral value: %lf\n", integral);

    return 0;
}
