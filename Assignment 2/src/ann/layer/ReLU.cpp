/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   ReLU.cpp
 * Author: ltsach
 * 
 * Created on August 25, 2024, 2:44 PM
 */

#include "layer/ReLU.h"
#include "sformat/fmt_lib.h"
#include "ann/functions.h"

ReLU::ReLU(string name) {
    if(trim(name).size() != 0) m_sName = name;
    else m_sName = "ReLU_" + to_string(++m_unLayer_idx);
}

ReLU::ReLU(const ReLU& orig) {
    m_sName = "ReLU_" + to_string(++m_unLayer_idx);
}

ReLU::~ReLU() {
}

xt::xarray<double> ReLU::forward(xt::xarray<double> X) {
    //YOUR CODE IS HERE
    xt::xarray<bool> mask = (X >= 0);
    if (this->m_trainable) {
        m_aMask = mask;
    }
    xt::xarray<double> Y = mask * X;
    Y = xt::where(xt::abs(Y) < 1e-15, 0, Y);
    // cout << "Layer: " << getname() << endl;
    // cout << "ReLU Forward" << endl;
    // cout << "Shape X = " << shape2str(X.shape()) << endl;
    // cout << "Shape Y = " << shape2str(Y.shape()) << endl;
    cout << "ReLu forward: Y = " << xt::view(Y, 0) << endl;
    // cout << "Mask = " << xt::view(mask, 0) << endl;
    // cout << "Mask = " << mask << endl;
    return Y;
}
xt::xarray<double> ReLU::backward(xt::xarray<double> DY) {
    //YOUR CODE IS HERE
    // cout << "ReLU Backward" << endl;
    // cout << "Shape mask = " << shape2str(m_aMask.shape()) << endl;
    // cout << "Shape DY = " << shape2str(DY.shape()) << endl;
    xt::xarray<double> DX = this->m_aMask * DY;
    DX = xt::where(xt::abs(DX) < 1e-15, 0, DX);
    // cout << "Shape DY = " << shape2str(DY.shape()) << endl;
    // cout << "Shape DX = " << shape2str(DX.shape()) << endl;
    cout << "ReLu backward" << xt::view(DX, 0) << endl;
    // cout << "Mask = " << m_aMask << endl;
    // cout << "DY = " << DY << endl;
    return DX;
}

string ReLU::get_desc(){
    string desc = fmt::format("{:<10s}, {:<15s}:",
                    "ReLU", this->getname());
    return desc;
}