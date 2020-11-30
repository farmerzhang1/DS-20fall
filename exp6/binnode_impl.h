#include "binnode.h"
#include <exception>
#include <stdexcept>
#include <iostream>
using namespace std;
#ifndef BN_I_H
#define BN_I_H
template <typename T> BinNode<T>::~BinNode() {}
template <typename T> BinNode<T>::BinNode() : parent ( nullptr ), lc ( nullptr ), rc ( nullptr ), height ( 0 ) { }
template <typename T> BinNode<T>::BinNode ( T e, BinNode<T>* p, BinNode<T>* lc, BinNode<T>* rc, int h) : data ( e ), parent ( p ), lc ( lc ), rc ( rc ), height ( h ) { }

template <typename T> BinNode<T>* BinNode<T>::insertAsLC(T const& e) {
    return lc = new BinNode<T>(e, this);
}
template <typename T> BinNode<T>* BinNode<T>::insertAsRC(T const& e) {
    return rc = new BinNode<T>(e, this);
}

template <typename T> BinNode<T>* BinNode<T>::attachAsLC ( BinNode<T>* lc) {
    if (this->lc) {
        cerr << "this->lc is not nullptr!" << endl;
        exit(EXIT_FAILURE);
    }
    return this->lc = lc;
}

template <typename T> BinNode<T>* BinNode<T>::attachAsRC ( BinNode<T>* rc) {
    if (this->rc) {
        cerr << "this->rc is not nullptr!" << endl;
        exit(EXIT_FAILURE);
    }
    return this->rc = rc;
}
#endif