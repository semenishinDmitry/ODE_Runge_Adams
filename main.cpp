#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
//#include "start_usl.h"
#include "begin.h"
#include "Runge_Kutta.h"
#include "A_B.h"
#include "extrapolation.h"
#include "interpolation.h"

using namespace std;


 double finish = 5.0;
// vector<double> X_0 = {1.0-1.5 * mu, mu / 20.0, 0.001 * mu, mu / 20.0};
vector<double> X_0 = {0.0, 3.0, -9.0, -8.0, 0.0};
 double h = 0.0001;

int main() {
    //Runge- Kutta
    ofstream output("rk.dat");
    cout<<fixed;
    vector<double> tmp = Runge_Kutta(X_0, 0.0);
    for(int i = 1; i < int(finish / h); ++i){
        output<< h * i<<"      ";
        tmp = Runge_Kutta(tmp, h * i);
        for(int j = 0; j < X_0.size(); ++j){output<<tmp[j]<<"      ";}
        output<<endl;
    }

    //extrapolation
    ofstream out_ext("ae.dat");
    cout<<fixed;
    int n = 6; //количество шагов
    vector<double> A = A_n_j(n);
    int size_y = X_0.size();
    double **A_new = new double* [size_y]; //массив, в котором будет по n столбцов
    for(int i = 0; i < size_y; ++i){
        A_new[i] = new double[n];
    }
    vector<double> tmp_begin = Runge_Kutta(X_0, 0.0);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < size_y; ++j){
            A_new[j][i] = tmp_begin[j];
        }
        tmp_begin = Runge_Kutta(tmp_begin, h * (i + 1));
    }
    //задали разгон
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < size_y; ++j) {
            out_ext<<h * i<<"      ";
            out_ext<<A_new[j][i]<<"      ";
        }
        out_ext<<endl;
    }//все ок, вывели разгон;

    int how_many_extr = int(finish / h) - n;  // оставшееся количество шагов
    for(int i = n; i < how_many_extr; ++i){
        out_ext<<h * i<<"      ";  // выводим время
        tmp = extrapolation(h * (i - 1), A_new, n, size_y, A); //получаем новый вектор
        for(int k = 0; k < size_y; ++k){out_ext<<tmp[k]<<"      ";} //выводим его
        out_ext<<endl;
        //сместим столбцы массива
        for(int l = 0 ; l < n - 1; ++l){
            for(int m = 0; m < size_y; ++m){
                A_new[m][l] = A_new[m][l + 1];
            }
        }
        for(int k = 0; k < size_y; ++k){A_new[k][n - 1] = tmp[k];} // внесли новый вектор в нашу матрицу
    }


    //interpolation

    ofstream out_int("ai.dat");
    cout<<fixed;
    int n_int = 6; //количество шагов
    vector<double> B = B_n_j(n_int);
    double **B_new = new double* [size_y]; //массив, в котором будет по n столбцов
    for(int i = 0; i < size_y; ++i){
        B_new[i] = new double[n_int];
    }
    vector<double> tmp_begin_int = Runge_Kutta(X_0, 0.0);
    for(int i = 0; i < n_int; ++i){
        for(int j = 0; j < size_y; ++j){
            B_new[j][i] = tmp_begin_int[j];
        }
        tmp_begin_int = Runge_Kutta(tmp_begin_int, h * (i + 1));
    }
    //задали разгон
    for(int i = 0; i < n_int; ++i){
        for(int j = 0; j < size_y; ++j) {
            out_int<<h * i<<"      ";
            out_int<<B_new[j][i]<<"      ";
        }
        out_int<<endl;
    }//все ок, вывели разгон;
    vector<double> podacha(size_y);
    int how_many_int = int(finish / h) - n_int;  // оставшееся количество шагов
    for(int i = n_int; i < how_many_int; ++i){
        out_int<<h * i<<"      ";  // выводим время
        for(int z = 0; z < size_y; ++z){podacha[z] = B_new[z][n_int - 1];}
        tmp = interpolation(podacha, 1000 ,h * (i - 1), B_new, n, size_y, B); //получаем новый вектор
        for(int k = 0; k < size_y; ++k){out_int<<tmp[k]<<"      ";} //выводим его
        out_int<<endl;
        //сместим столбцы массива
        for(int l = 0 ; l < n - 1; ++l){
            for(int m = 0; m < size_y; ++m){
                B_new[m][l] = B_new[m][l + 1];
            }
        }
        for(int k = 0; k < size_y; ++k){B_new[k][n - 1] = tmp[k];} // внесли новый вектор в нашу матрицу
    }

    return 0;
}