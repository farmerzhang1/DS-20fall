#include "bintree.h"
#include "binnode.h"
#include <iostream>
#include <queue>
using namespace std;
template <typename T> BinNode<T>::BinNode() : parent ( nullptr ), lc ( nullptr ), rc ( nullptr ), height ( 0 ) { }
template <typename T> BinNode<T>::BinNode ( T e, size_t i, BinNode<T>* p, BinNode<T>* lc, BinNode<T>* rc, int h) : data ( e ), index(i), parent ( p ), lc ( lc ), rc ( rc ), height ( h ) { }

template <typename T> BinNode<T>* BinNode<T>::insertAsLC(T const& e, const size_t& i) {
    return lc = new BinNode<T>(e, i, this);
}
template <typename T> BinNode<T>* BinNode<T>::insertAsRC(T const& e, const size_t& i) {
    return rc = new BinNode<T>(e, i, this);
}
template <typename T> BinTree<T>::BinTree(vector<T>& values) {
    _root = nullptr;
    BinNode<T>* n{_root};
    BinNode<T>* p{nullptr};
    for (auto it = values.begin(); it != values.end(); ++it) {
        p = nullptr;
        n = _root;
        while (n) //build BST by vector values (should use insert)
            if (*it < n->data) n = (p=n)->lc;   //go left
            else n = (p=n)->rc;                 //else go right
        if (!p) _root = new BinNode<T>(*it, it-values.begin());    //first one
        else {
            // insert
            if (*it < p->data) p->insertAsLC(*it, it-values.begin());
            else p->insertAsRC(*it, it-values.begin());
        }
    }
}

template <typename T> template <typename VST> void BinTree<T>::preTraverseTree (VST visit) {
    preorder (_root, visit);
}

template <typename T> template <typename VST> void BinTree<T>::preorder (BinNode<T>* n, VST visit) {
    if (!n) return;
    visit(n);
    preorder (n->lc, visit);
    preorder (n->rc, visit);
}
template <typename T> template <typename VST> void BinTree<T>::inTraverseTree (VST visit) {
    inorder (_root, visit);
}
template <typename T> template <typename VST> void BinTree<T>::inorder (BinNode<T>* n, VST visit) {
    if (!n) return;
    inorder (n->lc, visit);
    visit(n);
    inorder (n->rc, visit);
}
template <typename T> template <typename VST> void BinTree<T>::postTraverseTree (VST visit) {
    postorder (_root, visit);
}
template <typename T> template <typename VST> void BinTree<T>::postorder (BinNode<T>* n, VST visit) {
    if (!n) return;
    postorder (n->lc, visit);
    postorder (n->rc, visit);
    visit(n);
}
template <typename T> template <typename VST> void BinTree<T>::layerTraverseTree (VST visit) {
    BinNode<T>* n;
    if (!_root) return;
    queue<BinNode<T>*> bnodes;
    bnodes.push(_root);
    while (!bnodes.empty()) {
        n = bnodes.front();
        bnodes.pop();
        if (n->lc) bnodes.push(n->lc);
        if (n->rc) bnodes.push(n->rc);
        visit (n);
    }
}

//only an interface
template <typename T> void BinTree<T>::delSubtree (const T& val) {
    delsub (_root, val);
}

template <typename T> void BinTree<T>::delsub (BinNode<T>* p, const T& val) {
    if (!p) return;
    if (p->data == val) { freenode (p); return; } // recursively free subtree
    delsub (p->lc, val);
    delsub (p->rc, val);
}
template <typename T> void BinTree<T>::freenode (BinNode<T>* n) {
    if (!n) return;
    BinNode<T>* p = n->parent;
    if (p) (p->lc == n) ? p->lc = nullptr : p->rc = nullptr;
    freenode (n->lc);
    freenode (n->rc);
    delete n;
}
template <typename T> BinNode<T>* BinTree<T>::nearest_common_ancestor (const size_t i1, const size_t i2) {
    string p1, p2;
    size_t i{0};
    BinNode<T>* n = _root;
    get_index_path (_root, p1, i1);     //find path to i1
    get_index_path (_root, p2, i2);     //find path to i2
    if (p1.empty() || p2.empty()) return nullptr;
    while (i < p1.size()&&p1.at(i) == p2.at(i)) {      //follow it until first difference, which is what we are looking for
        n = p1.at(i) == 'l' ? n->lc : n->rc;
        i++;
    }
    return n;
}

template <typename T> string BinTree<T>::path (const T& val) {
    string p;
    getpath (_root, p, val);
    return p;
}
template <typename T> bool BinTree<T>::get_index_path (BinNode<T>* node, string& path, const size_t& index) {
    if (!node) return false;
    if (node->index == index) return true;
    if (get_index_path(node->lc, path.append("l"), index)) return true;
    else path.pop_back(); // backtracking
    if (get_index_path(node->rc, path.append("r"), index)) return true;
    else path.pop_back();
    return false;
}

template <typename T> bool BinTree<T>::getpath (BinNode<T>* node, string& path, const T& val) {
    if (!node) return false;
    if (node->data == val) return true;
    if (getpath(node->lc, path.append("l"), val)) return true;
    else path.pop_back(); // backtracking
    if (getpath(node->rc, path.append("r"), val)) return true;
    else path.pop_back();
    return false;
}
template <typename T> int BinTree<T>::diff() {
    if (!_root) return -1; // if not a valid tree
    int min{_root->data}, max{_root->data};
    // learn lambda expression!
    inTraverseTree ([&min](auto p) {if (min > p->data) min = p->data; });
    preTraverseTree ([&max](auto p) {if (max < p->data) max = p->data; });
    return max - min;
}

int main(void) {
    vector<int> vec {1,2,100,5,33,-3,14,-4,-1,6,-2};
    BinTree<int> bt (vec);
    auto print = [](auto p) { cout << "data: " << p->data << "  \tid: " << p->index << endl; };
    //traverse
    bt.layerTraverseTree(print);
    cout << endl;
    bt.preTraverseTree(print);
    cout << endl;
    bt.inTraverseTree(print);
    cout << endl;
    bt.postTraverseTree(print);
    cout << endl;

    bt.delSubtree(5);

    bt.preTraverseTree(print);
    cout << endl;
    int val = -2;
    cout << "path to val:\t" << bt.path (val) << endl;
    cout << "max - min = \t" << bt.diff() << endl;
    print (bt.nearest_common_ancestor(10, 10));
    return 0;
}