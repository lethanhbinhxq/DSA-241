/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Softmax.cpp
 * Author: ltsach
 * 
 * Created on August 25, 2024, 2:46 PM
 */

#include "layer/Softmax.h"
#include "ann/functions.h"
#include "sformat/fmt_lib.h"
#include <filesystem> //require C++17
namespace fs = std::filesystem;

Softmax::Softmax(int axis, string name): m_nAxis(axis) {
    if(trim(name).size() != 0) m_sName = name;
    else m_sName = "Softmax_" + to_string(++m_unLayer_idx);
}

Softmax::Softmax(const Softmax& orig) {
    m_sName = "Softmax_" + to_string(++m_unLayer_idx);
}

Softmax::~Softmax() {
}

xt::xarray<double> Softmax::forward(xt::xarray<double> X) {
    //YOUR CODE IS HERE
    size_t N = X.shape()[0];
    // }
    xt::xarray<double> Y = softmax(X, this->m_nAxis);
    if (this->m_trainable) {
        this->m_aCached_Y = Y;
    }
    // cout << "Softmax forward: Y = " << xt::view(Y, 0) << endl;
    return Y;
}
xt::xarray<double> Softmax::backward(xt::xarray<double> DY) {
    //YOUR CODE IS HERE
    xt::xarray<double> M = diag_stack(this->m_aCached_Y) - outer_stack(this->m_aCached_Y, this->m_aCached_Y);
    xt::xarray<double> DX = matmul_on_stack(M, DY);
    // cout << "Softmax backward: " << xt::view(DX, 0) << endl;
    return DX;

    // return outer;
}

string Softmax::get_desc(){
    string desc = fmt::format("{:<10s}, {:<15s}: {:4d}",
                    "Softmax", this->getname(), m_nAxis);
    return desc;
}
