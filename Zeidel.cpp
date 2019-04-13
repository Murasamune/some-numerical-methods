#include <iostream>
#include <Windows.h>
#include <math.h>

using namespace std;
const int N = 3;

int main()
{
	double x[N], a[N][N], aT[N][N], c[N], A[N][N], d[N];
	double epsilon = 0.001; // Погрешность

	// Условия задачи
	a[0][0] = 4.5; a[0][1] = -3.5; a[0][2] = 7.4;
	a[1][0] = 3.1; a[1][1] = -0.6; a[1][2] = -2.3;
	a[2][0] = 0.8; a[2][1] = 7.4; a[2][2] = -0.5;
	c[0] = 2.5; c[1] = -1.5; c[2] = 6.4;

	for (int i = 0; i < N; i++) // Дополнительные матрицы
    {
        for (int j = 0; j < N; j++)
        {
            A[i][j] = 0;
        }
        d[i] = 0;
    }


	// Транспонирование матрицы a, получаем матрицу aT
	for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            aT[i][j] = a[j][i];
        }
    }

    // Умножение матриц (A = aT*a, d = aT*c)
	for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                A[i][j] += aT[i][k] * a[k][j];
            }
            d[i] += aT[i][j] * c[j];
        }
    }

	// Начальное приближение к решению
	x[0] = 0; x[1] = 0; x[2] = 0;

	// Метод Зейделя
	double temp[N];
	bool trigger = true;
	int n1, n2;
	while (trigger == true)
	{
		for (int i = 0; i < N; i++)
		{
			temp[i] = x[i]; // Запоминаем вектор для вычисления нормы

			if (i == 0) // Подбор нумераций для составления формулы для каждого x
            {
                n1 = 1; n2 = 2;
            }
            else if (i == 1)
            {
                n1 = 0; n2 = 2;
            }
            else
            {
                n1 = 0; n2 = 1;
            }
			x[i] = d[i]/A[i][i] - (A[i][n1]/A[i][i])*x[n1] - (A[i][n2]/A[i][i])*x[n2];
		}

		double norm = 0;
		for (int i = 0; i < N; i++) // Вычисляем норму разности старого и нового вектора x
		{
			norm += pow(x[i] - temp[i], 2);
		}
		//cout << sqrt(norm) << endl;

		if (sqrt(norm) < epsilon) // Проверка
		{
			trigger = false;
		}
	}

	for (int i = 0; i < N; i++)
	{
		cout << i+1 << " " << x[i] << endl; // Вывод элементов x
	}

	system("pause");
	return 0;
}

