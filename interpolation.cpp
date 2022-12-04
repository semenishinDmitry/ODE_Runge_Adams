//
// Created by dmitry on 23.12.18.
//

#include "interpolation.h"
#include <vector>
#include <iostream>
#include<algorithm>
#include<cmath>
#include "operators.h"
//#include "start_usl.h"
#include "begin.h"


using  namespace std;

extern double h;


template <typename Type>
vector<Type> operator-(const vector<Type> &a, const vector<Type> &b) {
    if (a.size() != b.size()) {
        cout << "sizes of vectors are not equal to each other!!!";
        exit(0);
    }
    vector<Type> result(a.size());
    for (int i = 0; i < (int)a.size(); ++i) {
        result[i] = a[i] - b[i];
    }
    return result;
}

template<typename Type>
vector<Type> operator-=(vector<Type> & a, const vector<Type> & b) {
    if (a.size() != b.size()) {
        cout << "sizes of vectors are not equal to each other!!!";
        exit(0);
    }
    for (int i = 0; i < (int)a.size(); ++i) {
        a[i] -= b[i];
    }
    return a;
}

template<typename Type>
vector<Type> operator+=(vector<Type> & a, const vector<Type> & b) {
    if (a.size() != b.size()) {
        cout << "sizes of vectors are not equal to each other!!!";
        exit(0);
    }
    for (int i = 0; i < (int)a.size(); ++i) {
        a[i] += b[i];
    }
    return a;
}

template<typename Type>
vector<Type> operator/=(vector<Type> & a, double h) {
    for (int i = 0; i < (int)a.size(); ++i) {
        a[i] /= h;
    }
    return a;
}

//Gaussian method to solve equation system
vector<double> Gauss(double **A, int n) {
    vector<double> x(n);
    double max;
    int index;
    const double eps = 0.0000001;
    int k = 0;
    vector<double> y(n);
    for (int i = 0; i < n; ++i) {
        y[i] = A[n][i];
    }
    while (k < n)
    {
        max = abs(A[k][k]);
        index = k;
        for (int i = k + 1; i < n; ++i) {
            if (abs(A[i][k]) > max) {
                max = abs(A[i][k]);
                index = i;
            }
        }
        if (max < eps)
        {
            cout << "It's impossible to find the solution"<<endl;
            return y;
        }
        double temp;
        for (int j = 0; j < n; ++j) {
            temp = A[k][j];
            A[k][j] = A[index][j];
            A[index][j] = temp;
        }
        temp = y[k];
        y[k] = y[index];
        y[index] = temp;
        for (int i = k; i < n; ++i) {
            temp = A[i][k];
            if (abs(temp) < eps) continue;
            for (int j = 0; j < n; ++j) {
                A[i][j] = A[i][j] / temp;
            }
            y[i] = y[i] / temp;
            if (i == k)  continue;
            for (int j = 0; j < n; ++j)
                A[i][j] = A[i][j] - A[k][j];
            y[i] = y[i] - y[k];
        }
        k++;
    }
    for (k = n - 1; k >= 0; --k)
    {
        x[k] = y[k];
        for (int i = 0; i < k; i++)
            y[i] = y[i] - A[i][k] * x[k];
    }
    return x;
}



vector<double> our_func(vector<double> unknown, double t, double** X, int size_x, int size_y, vector<double> B){
    vector<double> res(size_y);
    vector<double> tmp_vec(size_y);
    vector<double> tmp(size_y);
    for(int i = 0; i < size_y; ++i){res[i] = X[i][size_x - 1];}
    for(int k = 1; k < size_x; ++ k){
        for(int l = 0; l < size_y; ++l){tmp[l] = X[l][size_x - k];}
        tmp_vec = f(tmp, t - (k - 1) * h);
        res += h * B[k] *tmp_vec;
    }
    res -= unknown;
    tmp = f(unknown, t + h);
    res += h * B[0] * tmp;
    return res;
}


vector<double> interpolation( vector<double> & x_0, int max_n, double t, double** X, int size_x, int size_y, vector<double> B) {
    const double eps = 0.000001; // stop constant
    double norma = 0;
    int size = (int)x_0.size();
    double ** A = new double *[size + 1];
    for (int i = 0; i < size + 1; ++i) {      // coefficent matrix
        A[i] = new double[size];
    }
    vector<double> tmp(size);
    vector<double> x_new(size);
    const double h_new = 0.01; // constant for differentiation
    for (int m = 0; m < max_n; ++m) {
        for (int i = 0; i < size; ++i) {  //loop for differentiation
            x_0[i] += h_new;
            tmp = our_func(x_0, t, X, size_x, size_y, B); // tmp is a vector of df/dx_i
            x_0[i] -= 2 * h_new;
            tmp -= our_func(x_0, t, X, size_x, size_y, B);
            x_0[i] += h_new;
            tmp /= (2 * h_new);
            for (int j = 0; j < size; ++j) {
                A[j][i] = tmp[j];
            }
        }
        tmp = our_func(x_0, t, X, size_x, size_y, B);
        for (int j = 0; j < size; ++j) { //constant terms
            A[size][j] = -tmp[j];
            for (int i = 0; i < size; ++i) {
                A[size][j] += (A[j][i] * x_0[i]);
            }
        }
        x_new = Gauss(A, size);
        tmp = (x_0 - x_new); //to find norma
        for (int i = 0; i < tmp.size(); ++i) {
            tmp[i] = abs(tmp[i]);
        }
        norma = *max_element(tmp.begin(), tmp.end());
        if (norma < eps) {
            return x_new;
        }
        x_0 = x_new;
    }
    return x_0;
}




