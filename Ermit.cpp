#include <iostream>
#include <cmath>
#include <cstdlib>
#include "stdio.h"

using namespace std;

const int N = 5;
int K[N] = {3, 2, 3, 1, 2};  // кратности узлов

double testfunc (double x){
    return pow(x, 3);
};
double derrfact_testfunc (int i, double x){
    if (i == 1){
        return 3*pow(x, 2);
    }
    else if (i == 2){
        return 6*x/2;
    }
};

double func7 (double x){
    return 3*x - cos(x) - 1;
};
double derrfact_func7 (int i, double x){
    if (i == 1){
        return 3 + sin(x)/2;
    }
    else if (i == 2){
        return cos(x)/6;
    }
};

double func17 (double x){
    return x*x+1-tan(x);
};
double derrfact_func17 (int i, double x){
    if (i == 1){
        return (2*x - 1/pow(cos(x), 2))/2;
    }
    else if (i == 2){
        return (2 - 2*tan(x)/pow(cos(x), 2))/6;
    }
};

double Pn (double x, double C[]){
    int h = 0;
    double res = C[0];
    for (int i = 0; i < N; i++){
        h += K[i];
    }
    for (int i = 1; i < h; i++){
        res += C[i]*pow(x, i);
    }
    return res;
};

int main()
{
    double X[N];  // узлы
    int h = 0;
    cout << "Dot X" << endl;
    for (int i = 0; i < N; i++){
        X[i] = i*2 - 2; // просто так могу
        h += K[i];  // высота матрицы Z
        cout << X[i] << endl;
    }
    cout << endl;

    double Z1[h];
    double Z2[h][h];

    int j = 0;
    for (int i = 0; i < N; i++){
        double temp = K[i];
        while (temp != 0){
            Z1[j] = X[i];
            cout << Z1[j] << "  ";
            j++;
            temp--;
        }
    }
    cout << endl << endl;

    for (int i = 0; i < h; i++){
        Z2[i][0] = func7(Z1[i]);      // !!!!!!!!!!!
    }

    for (int i = 1; i < h; i++){
        for (int j = 0; j < h-i; j++){
            if ((Z2[j+1][i-1] == Z2[j][i-1]) && (i < 3)){
                Z2[j][i] = derrfact_func7(i, Z2[j][i-1]);  // !!!!!!!!!!!!!!!!!
            }
            else {
                Z2[j][i] = (Z2[j+1][i-1] - Z2[j][i-1]) / (Z1[j+i]- Z1[j]);
            }
        }
    }

    for (int i = 0; i < h; i++){
        for (int j = 0; j < h-i; j++){
            printf("%10.4f", Z2[i][j]);
        }
        cout << endl;
    }
    cout << endl;

    double C[h];
    cout << '\n' << "Constants C" << endl;
    for (int i = 0; i < h; i++){
        C[i] = Z2[0][i];
        printf("C[%d]: %10.4f\n", i, Z2[0][i]);
    }
    cout << endl;

    for (int i = 0; i < N; i++){
        printf("%8.4f\t%8.4f\n", func17(X[i]), Pn(X[i], C));
    }
/*
    double res = 0;
    for (int i = 0; i < h; i++){
        res += C[i]*pow(2, i);
    }
    cout << res;

    */

    //system("pause");
    return 0;
}
