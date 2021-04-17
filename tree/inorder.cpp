#include <stack>
#include <iostream>

using namespace std;
struct binnode {
    binnode* lc;
    binnode* rc;
    binnode* parent;
    int data;
    binnode() : lc(nullptr), rc(nullptr), parent(nullptr), data(0) {}
};

void inorder (binnode* root) {
    stack<binnode*> S;
    binnode* node = root;
    while (true) {
        while (node) {
            S.push(node);
            node = node->lc;
        }
        if (S.empty()) break;
        node = S.top(); S.pop();
        cout << node->data << " ";
        node = node->rc;
    }
}
// we can get implement an iterator
binnode* successor (binnode* node) {
    if (node->rc) {
        node = node->rc;
        while (node->lc) node = node->lc;
    }
    else {
        while (node->parent->rc == node) node = node->parent;
        node = node->parent;
    }
    return node;
}

void inorder1(binnode* root) {
    if (!root) return;
    inorder1(root->lc);
    cout << root->data << " ";
    inorder1(root->rc);
}

int main(void) {
    binnode root, l, r, ll, lr, rl, rr, lll;
    root.data = 123;
    l.data = 44; r.data = 42; ll.data = 43; lr.data = 444; rl.data = 425; rr.data = 87; lll.data = 243;
    root.lc = &l; root.rc = &r;
    l.lc = &ll; l.rc = &lr;
    r.lc = &rl; r.rc = &rr;
    ll.lc = &lll;
    inorder(&root);
    cout << endl;
    inorder1(&root);
    return 0;
}