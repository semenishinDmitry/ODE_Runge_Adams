//
// Created by dmitry on 24.12.18.
//

#include "operators.h"
#include <vector>
#include <iostream>

using namespace std;

vector<double> operator +(const vector<double> &left, const vector<double> &right){
    if(left.size() != right.size()){
        cout<<"Размеры векторов не совпадают при сложении"<<endl;
        exit(1);
    }
    vector<double> result(left.size());
    for(int i = 0; i < left.size(); ++i){
        result[i] = left[i] + right[i];
    }
    return result;
}

vector<double> operator /(const vector<double> &left, double right){
    vector<double> result(left.size());
    for(int i = 0; i < left.size(); ++i){
        result[i] = left[i] / right;
    }
    return result;
}

vector<double> operator *(double left, vector<double> & right){
    vector<double> result(right.size());
    for(int i = 0; i < right.size(); ++i){
        result[i] = left * right[i];
    }
    return result;
}