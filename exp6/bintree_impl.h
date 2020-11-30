#include "bintree.h"
#include "binnode.h"
#ifndef BT_I_H
#define BT_I_H
template <typename T> BinNode<T>* BinTree<T>::insertAsRoot(const T& e) {
    return _root = new BinNode<T>(e);
}
template <typename T> BinNode<T>* BinTree<T>::root() const { return _root; }

template <typename T> BinTree<T>::BinTree(): _root(nullptr), _size(0) {}
template <typename T> BinTree<T>::BinTree(const T& e): _size(1) { _root = new BinNode<T>(e); }
template <typename T> BinTree<T>::~BinTree() {}
#endif