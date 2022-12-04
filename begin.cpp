//
// Created by dmitry on 25.12.18.
//



#include "begin.h"
#include <cmath>


std::vector<double> f (std::vector<double>  X, double t){
    std::vector<double> result(X.size());
    extern double mu;
    result[0] = X[1];
    result[1] = X[2];
    result[2] = X[3];
    result[3] = X[4];
    result[4] = -(15.0 * X[4] + 90.0 * X[3] + 270.0 * X[2] + 405.0 * X[1] + 243.0 * X[0]);
//    result [0] = - 0.5 *
//    result[0] = X[1];
//    result[1] = 2.0 * X[3] + X[0] - (1.0 - mu) * (X[0] + mu) / pow((pow((X[0] + mu),2.0) + X[2]), 1.5) -
//            mu * (X[0] - 1.0 + mu) / pow(pow(X[0] - 1.0 +mu, 2) + pow(X[2],2), 1.5);
//    result[2] = X[3];
//    result[3] = -2.0 * X[0] + X[2] - X[2] * (1.0 - mu) / pow(pow(X[0] + mu, 2) + pow(X[2],2),1.5) -
//            X[3] * mu / pow(pow((X[0] - 1 +mu),2) + pow(X[2], 2),1.5);
    return result;
}
/*
std::vector<double> f (std::vector<double>  X, double t){
    std::vector<double> result(X.size());
    result[0]=100.0*(X[1]-X[0]);
    result[1]=X[0]*(100.0-X[2])-X[1];
    result[2]=X[0]*X[1]-8.0*X[2]/3.0;

    return result;
}
*/