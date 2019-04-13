// SimpleIter.cpp : Defines the entry point for the console application.
//
#include <math.h>
#include <iostream>
#include <cmath>
#include <windows.h>

using namespace std;

double F1(double x) // Первая функция
{
	return 2*x - log10(x) - 7;
};
double F2(double x) // Вторая функция
{
	return pow(x, 3) - 3*pow(x, 2) + 6*x - 5;
};

double epsilon = 0.001; // Погрешность

void SimpleIteration(double (*func) (double), double x, double L) // Метод простых итераций
{
	int n = 0; // Счетчик шагов
	double x_old;
	do
	{
		n++;
		x_old = x;
		x = x_old - L * func(x_old);
	} while (abs(x - x_old) >= epsilon);
	cout << x << endl; // Вывод ответа
	cout << n << " steps at all" << endl; // Вывод количества шагов
};

int main()
{
	// Входные данные для F1
	double x1 = 3;
	double L1 = 0.01;

	// Входные данные для F2
	double x2 = -0.5;
	double L2 = 0.01;

	SimpleIteration(F2, x2, L2);

	system("pause");
	return 0;
}

