//
// Created by dmitry on 25.12.18.
//

#include "A_B.h"
//#include "start_usl.h"
#include "begin.h"

extern double h;

double f_A(int j, int n, double x){  //подынтегральная функция для А
    double res = x;
    for(int i = 1; i < n; ++i){
        res *=(x + i);
    }
    res /=(x + j);
    return res;
}

double  f_B(int j, int n, double x){  //подынтегральная функция для А
    double res = x * (x - 1);
    for (int i = 1; i < (n - 1); ++i){
        res *= (x + i);
    }
    res /= (x + j);
    return res;
}

vector<double> A_n_j(int n){
    vector<double> pre_A_n_j(n);
    pre_A_n_j[0] = 1.0;
    for(int i = 1; i < n; ++i){pre_A_n_j[0] /= i;}
    for(int j = 1; j < n; ++j){
        pre_A_n_j[j] = pre_A_n_j[j - 1] * (-1.0) / j * (n - j);  //вычислили коэффиценты перед интегралом
    }
    // pre'шки нормально считает вроде как
    // интегралы еще надо
    int m = 1000;
    double h_integr = 1.0 / m;
    double integr = 0.0;
    vector<double> B(n);
    for(int j = 0; j < n; ++j){
        for (int i = 0; i < m; ++i){
            integr +=f_A(j, n, h_integr * i + h / 2.0);
        }
        integr *= h_integr;
        B[j] = pre_A_n_j[j] * integr;
        integr = 0.0;
    }
    return B;
}


vector<double> B_n_j(int n){
    vector<double> pre_B_n_j(n);
    pre_B_n_j[0] = 1.0;
    for(int i = 1; i < n; ++i){pre_B_n_j[0] /= i;}
    pre_B_n_j[1] = pre_B_n_j[0] * (-1.0) * (n - 1);
    for(int j = 2; j < n; ++j){
        pre_B_n_j[j] = pre_B_n_j[j - 1] * (-1.0) / j * (n - j);
    }
    // pre'шки нормально считает вроде как
    // интегралы еще надо
    int m = 1000;
    double h_integr = 1.0 / m;
    double integr = 0.0;
    vector<double> B(n);
    for(int j = 0; j < n; ++j){
        for (int i = 0; i < m; ++i){
            integr += f_B(j - 1, n, h_integr * i + h / 2.0);
        }
        integr *= h_integr;
        B[j] = pre_B_n_j[j] * integr;
        integr = 0.0;
    }
    return B;
}

