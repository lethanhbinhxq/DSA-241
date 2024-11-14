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
    xt::xarray<double> expX = xt::exp(X);
    xt::xarray<double> sumExpX = xt::sum(expX, {this->m_nAxis}, xt::keep_dims);
    xt::xarray<double> Y = expX / sumExpX;
    if (this->m_trainable) {
        this->m_aCached_Y = Y;
    }
    // cout << "Layer: " << getname() << endl;
    // cout << "Softmax Forward" << endl;
    // cout << "Shape X = " << shape2str(X.shape()) << endl;
    // cout << "Shape Y = " << shape2str(Y.shape()) << endl;
    cout << "Softmax forward: Y = " << xt::view(Y, 0) << endl;
    return Y;
}
xt::xarray<double> Softmax::backward(xt::xarray<double> DY) {
    //YOUR CODE IS HERE
    // cout << "DY = " << DY << endl;
    xt::xarray<double> diagY = xt::diag(this->m_aCached_Y);
    // cout << "Shape m_aCached_Y = " << shape2str(m_aCached_Y.shape()) << endl;
    // cout << "Shape diagY = " << shape2str(diagY.shape()) << endl;
    // cout << "Shape transpose: " << shape2str(xt::transpose(this->m_aCached_Y).shape()) << endl;

    // cout << "Shape delta Y = " << shape2str(DY.shape()) << endl;

    // xt::xarray<double> outer = xt::linalg::tensordot(this->m_aCached_Y, xt::transpose(this->m_aCached_Y), 0);

    xt::xarray<double> outer = xt::linalg::tensordot(this->m_aCached_Y, xt::transpose(this->m_aCached_Y), 1);

    // cout << "Shape outer = " << shape2str(outer.shape()) << endl;
    xt::xarray<double> DZ = xt::linalg::tensordot(diagY - outer, DY, 1);
    // cout << "Softmax Backward" << endl;
    // cout << "Shape DY = " << shape2str(DY.shape()) << endl;
    // cout << "Shape DX: " << shape2str(DZ.shape()) << endl;
    cout << "Softmax backward: " << xt::view(DZ, 0) << endl;
    return DZ;

    // return outer;
}

string Softmax::get_desc(){
    string desc = fmt::format("{:<10s}, {:<15s}: {:4d}",
                    "Softmax", this->getname(), m_nAxis);
    return desc;
}
