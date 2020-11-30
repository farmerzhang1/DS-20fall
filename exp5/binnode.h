#include <cstddef>
using namespace std;
#ifndef BN_H
#define BN_H
template <typename T> struct BinNode {
    T data; //数值
    size_t index;
    BinNode<T>* parent;
    BinNode<T>* lc; BinNode<T>* rc; //父节点及左、右孩子
    int height; //高度（通用）
// 构造函数
    BinNode();
    BinNode ( T e, size_t i, BinNode<T>* p = nullptr, BinNode<T>* lc = nullptr, BinNode<T>* rc = nullptr, int h = 0);
// 操作接口
    //作为当前节点的左孩子插入新节点
    BinNode<T>* insertAsLC ( T const& , const size_t& );
    //作为当前节点的右孩子插入新节点
    BinNode<T>* insertAsRC ( T const& , const size_t& );
    // 比较器、判等器（各列其一，其余自行补充）
};
#endif