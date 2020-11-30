#include "binnode.h"
#include <vector>
#include <string>
#ifndef BT_H
#define BT_H
using namespace std;
template <typename T> class BinTree {
private:
    int _size;
    BinNode<T>* _root;
    template <typename VST> void preorder (BinNode<T>* n, VST visit);
    template <typename VST> void inorder (BinNode<T>* n, VST visit);
    template <typename VST> void postorder (BinNode<T>* n, VST visit);
    void delsub (BinNode<T>*, const T&);
    bool getpath (BinNode<T>*, string&, const T&);
    bool get_index_path (BinNode<T>*, string&, const size_t&);
    void freenode (BinNode<T>*);
public:
    BinTree() : _size(0), _root(nullptr) {}
    //holy shit
    BinTree(vector<T>&);
    int size() const { return _size; }
    BinNode<T>* root() const { return _root; }
    template <typename VST> void preTraverseTree (VST visit);
    template <typename VST> void inTraverseTree (VST visit);
    template <typename VST> void postTraverseTree (VST visit);
    template <typename VST> void layerTraverseTree (VST visit);
    //delete all nodes(and their children) with value val
    //if val cannot be found, do nothing
    void delSubtree (const T& val);
    //return nearest common ancestor as described
    //null if i1 or i2 not found
    BinNode<T>* nearest_common_ancestor (const size_t, const size_t);
    //return a string of path (lrlrrrl par example)
    //return nothing if no val founded
    //binary tree is unique
    string path (const T& val);
    //only INTEGER is supported!
    int diff();
};
#endif