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
    size_t N = X.shape()[0];
    double loss = 0;
    // For hard label
    if (t.dimension() == 1) {
        for (int i = 0; i < N; i++) {
            size_t target = t(i);
            loss -= log(X(i, target));
        }
    }
    // For soft label 
    else {
        for (int i = 0; i < X.shape()[0]; i++) {
            auto t_i = xt::view(t, i, xt::all());
            auto logX_i = xt::log(xt::view(X, i, xt::all()));
            auto product = t_i * logX_i;
            loss -= xt::sum(product)();
        }
    }
    
    if (this->m_eReduction == REDUCE_MEAN) {
        loss /= N;
    }

    this->m_aYtarget = t;
    this->m_aCached_Ypred = X;
    // cout << "CE forward: X = " << xt::view(X, 0) << endl;
    // cout << "CE forward: Loss = " << loss << endl;
    return loss;
}
xt::xarray<double> CrossEntropy::backward() {
    //YOUR CODE IS HERE
    const double epsilon = 1e-7;
    size_t N = this->m_aCached_Ypred.shape()[0];
    xt::xarray<double> DY = xt::zeros<double>(this->m_aCached_Ypred.shape());
    for (size_t i = 0; i < N; i++) {
        auto t = xt::view(this->m_aYtarget, i, xt::all());
        auto y = xt::view(this->m_aCached_Ypred, i, xt::all());
        xt::view(DY, i, xt::all()) = -t / (y + epsilon);
    }
    if (this->m_eReduction == REDUCE_MEAN) {
        DY /= N;
    }
    // cout << "CE backward: DY = " << xt::view(DY, 0) << endl;
    return DY;
}