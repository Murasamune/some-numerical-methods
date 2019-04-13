#include <iostream>
#include <cmath>
#include <Windows.h>

using namespace std;

// Метод Ньютона для систем нелинейных уравнений

double F(double x, double y, int num) // Первая функция (уравнение) из заданной системы
{
    if (num == 1)
        return cos(y - 1) + x - 0.5;
    else
        return sin(x + y) - 1.5*x + 0.1;
}
double G(double x, double y, int num) // Вторая функция (уравнение) из заданной системы
{
    if (num == 1)
        return y - cos(x) - 3;
    else
        return pow(x, 2) + pow(y, 2) - 1;
}

double derriv_Fx (double x, double y, int num) // Производная первой функции по переменной x
{
    if (num == 1)
        return 1;
    else
        return cos(x + y) - 1.5;
}
double derriv_Fy (double x, double y, int num) // Производная первой функции по переменной y
{
    if (num == 1)
        return -sin(y - 1);
    else
        return cos(x + y);
}

double derriv_Gx (double x, double y, int num) // Производная второй функции по переменной x
{
    if (num == 1)
        return sin(x);
    else
        return 2 * x;
}
double derriv_Gy (double x, double y, int num) // Производная второй функции по переменной y
{
    if (num == 1)
        return 1;
    else
        return 2 * y;
}

double determ (double x, double y, int num) // Определитель матрицы производных функций
{
    return derriv_Fx(x, y, num) * derriv_Gy(x, y, num) - derriv_Fy(x, y, num) * derriv_Gx(x, y, num);
}
double determ_x (double x, double y, int num) // Определитель матрицы производных по y
{
    return F(x, y, num) * derriv_Gy(x, y, num) - derriv_Fy(x, y, num) * G(x, y, num);
}
double determ_y (double x, double y, int num) // Определитель матрицы производных по x
{
    return derriv_Fx(x, y, num) * G(x, y, num) - F(x, y, num) * derriv_Gx(x, y, num);
}

int main()
{
    double epsilon = 0.001; // Погрешность
    double x = 1; // Начальные условия
    double y = 1;
    int num = 1; // Выбор системы уравнений

    double a, b;
    int n = 0; // Счетчик
    bool trigger = false;
    while (trigger == false) // Алгоритм метода Ньютона
    {
        a = x;
        b = y;

        x = a - determ_x(a, b, num)/determ(a, b, num);
        y = b - determ_y(a, b, num)/determ(a, b, num);

        n++;
        double norm = sqrt(pow(x - a, 2) + pow(y - b, 2));
        cout << norm << endl;
        if (sqrt(pow(x - a, 2) + pow(y - b, 2)) < epsilon) // Проверка (сравниваем норму и погрешность)
            trigger = true;
    }

    cout << "steps " << n << endl; // Вывод шагов
    cout << "x = " << x << endl; // x
    cout << "y = " << y << endl; // y
    return 0;
}
