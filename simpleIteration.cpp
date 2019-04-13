#include <iostream>
#include <Windows.h>
#include <cmath>

using namespace std;
// Метод простых итераций решения систем линейных уравнений
int main()
{
	double a[4][4], c[4], x[4], x_old[4];
	double epsilon = 0.001; // Погрешность

	// Начальные условия
	a[0][0] = 0.05; a[0][1] = -0.06; a[0][2] = -0.12; a[0][3] = 0.14;
	a[1][0] = 0.04; a[1][1] = -0.12; a[1][2] = 0.08; a[1][3] = 0.11;
	a[2][0] = 0.34; a[2][1] = 0.08; a[2][2] = -0.06; a[2][3] = 0.14;
	a[3][0] = 0.11; a[3][1] =0.12 ; a[3][2] = 0; a[3][3] = -0.03;

	c[0] = -2.17; c[1] = 1.4; c[2] = -2.1; c[3] = -0.8;



	// Начальное приближение (выбираем любое)
	x_old[0] = 2; x_old[1] = 1; x_old[2] = 3; x_old[3] = 9;

	x[0] = 0; x[1] = 0; x[2] = 0; x[3] = 0;
	bool trigger = true;
	double norm = 0; // Норма
	int n = 0; // Счетчик
	while (trigger == true)
	{
		n++;
		for(int i = 0; i < 4; i++) // Считаем новый вектор x
		{
			for(int j = 0; j < 4; j++)
			{
				x[i] += a[i][j]*x_old[j];
			}
			x[i] += c[i];
		}

		for(int i = 0; i < 4; i++) // Считаем норму разности нового вектора x и старого x_old
		{
			norm += pow(x[i] - x_old[i], 2);
		}
		norm = sqrt(norm);

		if(norm < epsilon) // Проверка
			trigger = false;
		else
			norm = 0;

		for(int i = 0; i < 4; i++) // Обновление векторов
		{
			x_old[i] = x[i];
			x[i] = 0;
		}
	}

	cout << "n = " << n << endl; // Вывод количества шагов

	for(int i = 0; i < 4; i++) // Вывод полученного вектора
	{
		cout << x_old[i] << endl;
	}

	system ("pause");
	return 0;
}
