// 8. Вычисление определённого интеграла методом прямоугольников

#include <stdio.h>
#include <omp.h>
#include <math.h>

// непрерываная функция
double f(double x)
{
    return 3.0 * (log((2.0 * x) + 1.0)); // 3*ln(2x + 1)
}

int main()
{
    int n = 1000000;         // Количество прямоугольников
    double a = 0.0, b = 1.0; // Границы интегрирования
    double h = (b - a) / n;  // Ширина прямоугольников
    double integral = 0.0;

    #pragma omp parallel for reduction(+ : integral)
    for (int i = 0; i < n; i++)
    {
        double x = a + i * h;
        integral += f(x) * h;
    }

    printf("Intergal value: %lf\n", integral);

    return 0;
}
