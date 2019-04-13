// Интерполирование кубическими сплайнами
#include <iostream>
#include "cstdlib"
#include "cmath"
#include "stdio.h"
using namespace std;
const int N = 4;
double func7 (double x){
    return 3*x - cos(x) - 1;
};

double func17 (double x){
    return x*x+1-tan(x);
};

double S (int i, double x, double xi, double C[][]){
    return C[i][0] + C[i][1]*(x - xi) + C[i][2]*pow(x - xi, 2)/2 + C[i][3]*pow(x - xi, 3)/6;
};
int main()
{
    int a = -6, b = 6;
    //int a = -1.2, b = 1.2
    double X[N];
    for (int i = 0; i < N; i++){
        X[i] = a + i*(b-a)/3;
        cout << X[i] << "  ";
    }
    cout << endl << endl;

    double C[N][4];
    for (int i = 0; i < N; i++){
        C[i][0] = func7(X[i]);
        C[i][1]
        C[i][2]
        C[i][3]
    }
    return 0;
}
