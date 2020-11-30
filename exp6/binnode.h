#include <cstddef>
#ifndef BN_H
#define BN_H

template <typename T> struct BinNode {
    T data; //数值
    BinNode<T>* parent;
    BinNode<T>* lc; BinNode<T>* rc;//父节点及左右孩子
    int height; //
    ~BinNode();
// 构造函数
    BinNode();
    BinNode ( T e, BinNode<T>* p = nullptr, BinNode<T>* lc = nullptr, BinNode<T>* rc = nullptr, int h = 0);
// 操作接口
    //作为当前节点的左孩子插入新节点
    BinNode<T>* insertAsLC ( T const& );
    //作为当前节点的右孩子插入新节点
    BinNode<T>* insertAsRC ( T const& );
    // 作为当前节点的中孩子（
    BinNode<T>* attachAsRC ( BinNode<T>* );
    BinNode<T>* attachAsLC ( BinNode<T>* );
};
#endif