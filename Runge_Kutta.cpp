//
// Created by dmitry on 23.12.18.
//

#include <vector>
#include <iostream>
#include "operators.h"
//#include "start_usl.h"
#include "begin.h"

using namespace std;
extern  double h;

//vector<double>(*f)(vector<double> &, double)

vector<double> Runge_Kutta(vector<double> X_0, double t){
    int my_size = X_0.size();
    vector<double> k_1(my_size);
    vector<double> k_2(my_size);
    vector<double> k_3(my_size);
    vector<double> k_4(my_size);
    vector<double> X;
    vector<double> tmp = f(X_0, t);
    k_1 = h * tmp;
    tmp = f(X_0 + k_1 / 2.0, t + h / 2.0);
    k_2 = h * tmp;
    tmp = f(X_0 + k_2 / 2.0, t + h / 2.0);
    k_3 = h * tmp;
    tmp = f(X_0 + k_3, t + h);
    k_4 = h * tmp;
    X = X_0 + (k_1 + 2.0 * k_2 + 2.0 * k_3 + k_4) / 6.0;
    return X;
}
