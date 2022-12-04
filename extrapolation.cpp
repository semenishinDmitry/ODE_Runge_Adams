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

//Экстраполяционный метод Адамса
vector<double> extrapolation(double t, double** X, int size_x, int size_y, vector<double> A){
    vector<double> X_new(size_y);
    //size_x - то n, которое выбираем для Адамса
    //A - вектор коэффицентов
    //h - шаг в диффуре
    for(int i = 0 ; i < size_y; ++i){X_new[i] = X[i][size_x - 1];}
    vector<double> tmp_vect(size_y);
    vector<double> tmp_vect_mul(size_y);
    for(int j = 0; j < size_x; ++j){
        for(int k = 0; k < size_y; ++k){tmp_vect[k] = X[k][size_x - j - 1];}
        tmp_vect_mul = f(tmp_vect, t - j * h);
        X_new = X_new + h * A[j] * tmp_vect_mul;
    }
    return X_new;
}