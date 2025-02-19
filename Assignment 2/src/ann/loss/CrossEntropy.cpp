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
    bool mean_reduced = (this->m_eReduction == REDUCE_MEAN);
    double loss = cross_entropy(X, t, mean_reduced);

    this->m_aYtarget = t;
    this->m_aCached_Ypred = X;
    // cout << "CE forward: Loss = " << loss << endl;
    return loss;
}
xt::xarray<double> CrossEntropy::backward() {
    //YOUR CODE IS HERE
    const double epsilon = 1e-7;
    xt::xarray<double> DY = - this->m_aYtarget / (this->m_aCached_Ypred + epsilon);
    // cout << "CE backward: DY = " << xt::view(DY, 0) << endl;
    return DY;
}