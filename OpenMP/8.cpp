// 8. Вычисление определённого интеграла методом прямоугольников

#include <stdio.h>
#include <omp.h>

double f(double x)
{
    // Здесь вставьте вашу функцию f(x)
    return x * x; // Пример: x^2
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

    printf("Значение интеграла: %lf\n", integral);

    return 0;
}
