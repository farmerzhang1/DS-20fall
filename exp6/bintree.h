#include "binnode_impl.h"
#include <vector>
#include <string>
#ifndef BT_H
#define BT_H
template <typename T> class BinTree {
private:
    int _size;
    BinNode<T>* _root;
public:
    BinTree();
    BinTree(const T&);
    ~BinTree();
    int size();
    BinNode<T>* root() const;
    // insert into empty tree
    BinNode<T>* insertAsRoot ( const T& );
};
#endif