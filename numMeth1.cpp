#include <iostream>
#include <math.h>
#include <cmath>
#include <windows.h>

using namespace std;

// Глава 5, работа 1, номер 6

const int N = 1; // Необходимое количество ячеек в массивах границ отрезков, содержащих корни. Для F1 - 2, F2 - 4, F3 - 3, F4 - 1
const double PI = 3.14159265;

// Функции из номера
double F1(double x)
{
    return 2*atan(x) - 1/(2*pow(x, 3));
};
double F2(double x)
{
    return pow(x, 4) - 18*pow(x, 2) + 6;
};
double F3(double x)
{
    return pow(x, 2) * pow(2, x) - 1;
};
double F4(double x)
{
    return tan(x) - x - 1;
};

// Первые производные функций
// Переменная numbOfFunc - это порядковый номер функции, производную которой хотим получить
double Derriv1(int numbOfFunc, double x)
{
    switch(numbOfFunc)
    {
        case 1:
        {
            return 2/(1+pow(x, 2)) + 3/(2*pow(x, 4));
            break;
        }
        case 2:
        {
            return 4*pow(x, 3) - 36*x;
            break;
        }
        case 3:
        {
            return 2*x*pow(2, x) + pow(x, 2)*pow(2, x)*log(2);
            break;
        }
        case 4:
        {
            return 1/pow(cos(x), 2) - 1;
            break;
        }
    }
};

// Вторые производные функций
// Переменная numbOfFunc - это порядковый номер функции, производную которой хотим получить
double Derriv2(int numbOfFunc, double x)
{
    switch(numbOfFunc)
    {
        case 1:
        {
            return -4*x/pow(1+pow(x, 2), 2) - 6/pow(x, 5);
            break;
        }
        case 2:
        {
            return 12*pow(x, 2) - 36;
            break;
        }
        case 3:
        {
            return pow(2, x+1) + x*pow(2, x+1)*log(2) + x*log(2)*pow(2, x+1) + pow(x, 2)*pow(2, x)*pow(log(2), 2);
            break;
        }
        case 4:
        {
            return 2*sin(x)/pow(cos(x), 3);
            break;
        }
    }
};

double epsilon = 0.01; // Погрешность

void Dichotomy(double (*func) (double), double a[], double b[]) // Метод дихотомии
{
    int n = 0; // Счетчик шагов
    double ksi; // Новая точка
    for (int i = 0; i < N; i++)
    {
        while (abs(b[i] - a[i]) >= epsilon)
        {
            n++;
            ksi = (a[i] + b[i])/2;
            if(func(a[i]) * func(ksi) < 0)
                b[i] = ksi;
            else
                a[i] = ksi;
        }
        ksi = (a[i] + b[i])/2;
        cout << i << " " << ksi << endl; // i - порядковый номер отрезка, в котором содержится корень ksi. Отрезки считаем слева направо
    }
    cout << n << " steps at all" << endl << "\n" << endl; // Общее число шагов
};

void PropParts(int numbOfFunc, double (*func) (double), double a[], double b[]) // Метод пропорциональных частей (хорд)
{
    int n = 0; // Счетчик шагов
    double ksi; // Новая точка
    for (int i = 0; i < N; i++)
    {
        bool trigger = false;
        ksi = (a[i] + b[i]) / 2;
        if (func(a[i]) * Derriv2(numbOfFunc, a[i]) < 0)
        {
            while(trigger == false)
            {
                n++;
                a[i] = ksi;
                ksi = a[i] - func(a[i])*(b[i] - a[i])/(func(b[i]) - func(a[i]));

                if (abs((ksi - a[i])) < epsilon)
                    trigger = true;
            }
        }
        else
        {
            while(trigger == false)
            {
                n++;
                b[i] = ksi;
                ksi = b[i] - func(b[i])*(a[i] - b[i])/(func(a[i]) - func(b[i]));

                if (abs((ksi - b[i])) < epsilon)
                    trigger = true;
            }
        }
        cout << i << " " << ksi << endl; // i - порядковый номер отрезка, в котором содержится корень ksi. Отрезки считаем слева направо
    }
    cout << n << " steps at all" << endl << "\n" << endl; // Общее число шагов
};

void Newton(int numbOfFunc, double (*func) (double), double a[], double b[]) // Метод Ньютона (касательных)
{
    int n = 0; // Счетчик шагов
    double ksi, delta; // Новая точка ksi и переменная delta, которая понадобится в реализации метода
    for (int i = 0; i < N; i++)
    {
        bool trigger = false;
        if (func(a[i]) * Derriv2(numbOfFunc, a[i]) > 0)
            ksi = a[i];
        else
            ksi = b[i];

        while (trigger == false)
        {
            n++;
            delta = func(ksi)/Derriv1(numbOfFunc, ksi);
            ksi = ksi - delta;
            if (abs(delta) < epsilon)
                trigger = true;
        }
        cout << i << " " << ksi << endl; // i - порядковый номер отрезка, в котором содержится корень ksi. Отрезки считаем слева направо
    }
    cout << n << " steps at all" << endl << "\n" << endl; // Общее число шагов
};

double WomboCombo(int numbOfFunc, double (*func) (double), double a[], double b[]) // Смешанный метод хорд и касательных
{
    int n = 0;
    for (int i = 0; i < N; i++)
    {
        bool trigger = false;
        while (trigger == false)
        {
            n++;
            if (func(a[i]) * Derriv2(numbOfFunc, a[i]) < 0)
            {
                a[i] = a[i] - func(a[i])*(a[i] - b[i])/(func(a[i]) - func(b[i]));
            }
            else
            {
                a[i] = a[i] - func(a[i])/Derriv1(numbOfFunc, a[i]);
            }
            if (func(b[i]) * Derriv2(numbOfFunc, b[i]) < 0)
            {
                b[i] = b[i] - func(b[i])*(b[i] - a[i])/(func(b[i]) - func(a[i]));
            }
            else
            {
                b[i] = b[i] - func(b[i])/Derriv1(numbOfFunc, b[i]);
            }

            if (abs(a[i] - b[i]) < 2*epsilon)
                trigger = true;
        }
        cout << i << " " << (a[i] + b[i])/2 << endl; // i - порядковый номер отрезка, в котором содержится корень. Отрезки считаем слева направо
    }
    cout << n << " steps at all" << endl << "\n" << endl; // Общее число шагов
};

int main()
{
    double a[N], b[N]; // Массивы границ отрезков, в которых лежат корни
    int M; // Порядковый номер функции, нужен для вывода правильной производной
/*
    // Для F1
    M = 1;
    a[0] = 0.5; a[1] = -0.5;
    b[0] = 1; b[1] = -1;

    // Для F2
    M = 2;
    a[0] = 0; a[1] = 0; a[2] = 3; a[3] = -3;
    b[0] = 1; b[1] = -1; b[2] = 5; b[3] = -5;

    // Для F3
    M = 3;
    a[0] = -5; a[1] = -3; a[2] = 0;
    b[0] = -3; b[1] = -1; b[2] = 1.5;
*/
    // Для F4
    M = 4;
    a[0] = -3*PI/2;
    b[0] = -PI/2;


    // Метод половинного деления (дихотомии)
    Dichotomy(F4, a, b);

    // Метод пропорциональных частей (хорд), первое число является порядковым номером функции
    PropParts(M, F4, a, b);

    // Метод Ньютона (касательных)
    Newton(M, F4, a, b);

    // Комбинированный метод хорд и касательных, первое число является порядковым номером функции
    WomboCombo(M, F4, a, b);

    system("pause");
    return 0;
}
