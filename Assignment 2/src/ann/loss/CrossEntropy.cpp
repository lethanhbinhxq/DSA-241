/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   CrossEntropy.cpp
 * Author: ltsach
 * 
 * Created on August 25, 2024, 2:47 PM
 */

#include "loss/CrossEntropy.h"
#include "ann/functions.h"

CrossEntropy::CrossEntropy(LossReduction reduction): ILossLayer(reduction){
    
}

CrossEntropy::CrossEntropy(const CrossEntropy& orig):
ILossLayer(orig){
}

CrossEntropy::~CrossEntropy() {
}

double CrossEntropy::forward(xt::xarray<double> X, xt::xarray<double> t){
    //YOUR CODE IS HERE
    double loss = 0;
    // if (t.dimension() == 1) {
    //     for (int i = 0; i < X.shape()[0]; i++) {
    //         int target = t(i, 0);
    //         loss -= log(X(i, target));
    //     }
    // } 
    // else {
        for (int i = 0; i < X.shape()[0]; i++) {
            auto t_i = xt::view(t, i);
            auto logX_i = xt::log(xt::view(X, i));
            auto product = t_i * logX_i;
            // cout << "t_i = " << t_i(0) << endl;
            // cout << "X = " << X(0) << endl;
            // cout << "logX_i = " << logX_i(0) << endl;
            // cout << "product = " << product(0) << endl;
            loss -= xt::sum(product)();
        }
    // }
    
    if (this->m_eReduction == REDUCE_MEAN) {
        loss /= X.shape(0);
    }

    this->m_aYtarget = t;
    this->m_aCached_Ypred = X;
    // cout << "CE forward: X = " << xt::view(X, 0) << endl;
    cout << "CE forward: Loss = " << loss << endl;
    return loss;
}
xt::xarray<double> CrossEntropy::backward() {
    //YOUR CODE IS HERE
    const double epsilon = 1e-10;
    int N = this->m_aCached_Ypred.shape(0);

    xt::xarray<double> delta_Y = - (this->m_aYtarget) / (this->m_aCached_Ypred + epsilon);
    // cout << "N = " << N << endl;
    // cout << "m_aYtarget = " << xt::view(m_aYtarget, 0) << endl;
    // cout << "m_aCached_Ypred = " << xt::view(m_aCached_Ypred, 0) << endl;

    if (this->m_eReduction == REDUCE_MEAN) {
        delta_Y /= N;
    }
    cout << "CE backward: " << xt::view(delta_Y, 0) << endl;
    // cout << "CE Backward" << endl;
    // cout << "Shape DY = " << shape2str(delta_Y.shape()) << endl;
    return delta_Y;
}