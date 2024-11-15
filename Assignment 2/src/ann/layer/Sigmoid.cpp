/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Sigmoid.cpp
 * Author: ltsach
 * 
 * Created on August 25, 2024, 2:45 PM
 */

#include "layer/Sigmoid.h"
#include "sformat/fmt_lib.h"
#include "ann/functions.h"

Sigmoid::Sigmoid(string name) {
    if(trim(name).size() != 0) m_sName = name;
    else m_sName = "Sigmoid_" + to_string(++m_unLayer_idx);
}

Sigmoid::Sigmoid(const Sigmoid& orig) {
    m_sName = "Sigmoid_" + to_string(++m_unLayer_idx);
}

Sigmoid::~Sigmoid() {
}
xt::xarray<double> Sigmoid::forward(xt::xarray<double> X) {
    //YOUR CODE IS HERE
    xt::xarray<double> Y = 1 / (1 + xt::exp(-X));
    if (this->m_trainable) {
        this->m_aCached_Y = Y;
    }
    // cout << "Layer: " << getname() << endl;
    // cout << "Forward" << endl;
    // cout << "Shape X = " << shape2str(X.shape()) << endl;
    // cout << "Shape Y = " << shape2str(Y.shape()) << endl;
    // cout << "Sigmoid forward: Y = " << xt::view(Y, 0) << endl;
    return Y;
}
xt::xarray<double> Sigmoid::backward(xt::xarray<double> DY) {
    //YOUR CODE IS HERE
    xt::xarray<double> DX = DY * this->m_aCached_Y * (1 - this->m_aCached_Y);
    // cout << "Backward" << endl;
    // cout << "Shape DY = " << shape2str(DY.shape()) << endl;
    // cout << "Shape DX = " << shape2str(DX.shape()) << endl;
    // cout << "Sigmoid backward: " << xt::view(DX, 0) << endl;
    return DX;
}

string Sigmoid::get_desc(){
    string desc = fmt::format("{:<10s}, {:<15s}:",
                    "Sigmoid", this->getname());
    return desc;
}