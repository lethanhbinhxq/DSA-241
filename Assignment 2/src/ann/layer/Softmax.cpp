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
    xt::xarray<double> Y = xt::zeros<double>(X.shape());
    for (size_t i = 0; i < N; i++) {
        auto x_i = xt::view(X, i, xt::all());
        auto e_x = xt::exp(x_i);
        auto sum_e = xt::sum(e_x)();
        auto y_i = e_x / sum_e;
        xt::view(Y, i, xt::all()) = e_x / sum_e;
    }
    if (this->m_trainable) {
        this->m_aCached_Y = Y;
    }
    // cout << "Softmax forward: Y = " << xt::view(Y, 0) << endl;
    // cout << "Shape X = " << shape2str(X.shape()) << endl;
    // cout << "Shape Y = " << shape2str(Y.shape()) << endl;
    return Y;
}
xt::xarray<double> Softmax::backward(xt::xarray<double> DY) {
    //YOUR CODE IS HERE
    size_t N = DY.shape()[0];
    xt::xarray<double> DX = xt::zeros<double>(DY.shape());
    for (size_t i = 0; i < N; i++) {
        auto y_i = xt::view(this->m_aCached_Y, i, xt::all());
        auto dy_i = xt::view(DY, i, xt::all());
        auto diag_y = xt::diag(y_i);
        auto outer = xt::linalg::outer(y_i, xt::transpose(y_i));
        xt::view(DX, i, xt::all()) = xt::linalg::tensordot((diag_y - outer), dy_i, {1}, {0});
    }
    // cout << "Softmax backward: " << xt::view(DX, 0) << endl;
    return DX;

    // return outer;
}

string Softmax::get_desc(){
    string desc = fmt::format("{:<10s}, {:<15s}: {:4d}",
                    "Softmax", this->getname(), m_nAxis);
    return desc;
}
