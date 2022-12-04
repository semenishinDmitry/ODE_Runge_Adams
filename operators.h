//
// Created by dmitry on 24.12.18.
//

#ifndef NUMBER9_2_0_OPERATORS_H
#define NUMBER9_2_0_OPERATORS_H
#pragma once
#include <vector>
using namespace std;
vector<double> operator +(const vector<double> &, const vector<double> &);
vector<double> operator *(double , vector<double> & r);
vector<double> operator /(const vector<double> &, double );

#endif //NUMBER9_2_0_OPERATORS_H
