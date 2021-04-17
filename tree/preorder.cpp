#include <stack>
#include <iostream>

using namespace std;
struct binnode {
    binnode* lc;
    binnode* rc;
    int data;
    binnode() : lc(nullptr), rc(nullptr), data(0) {}
};

void preorder (binnode* root) {
    stack<binnode*> S;
    binnode* node = root;
    while (node) {
        cout << node->data << " ";
        if (node->rc)
            S.push(node->rc);
        node = node->lc;
    }
    while (!S.empty()) {
        node = S.top(); S.pop();
        while (node) {
            cout << node->data << " ";
            if (node->rc)
                S.push(node->rc);
            node = node->lc;
        }
    }
}
void preorder1 (binnode* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder1(root->lc); preorder1(root->rc);
}
int main(void) {
    binnode root, l, r, ll, lr, rl, rr, lll;
    root.data = 123;
    l.data = 44; r.data = 42; ll.data = 43; lr.data = 444; rl.data = 425; rr.data = 87; lll.data = 243;
    root.lc = &l; root.rc = &r;
    l.lc = &ll; l.rc = &lr;
    r.lc = &rl; r.rc = &rr;
    ll.lc = &lll;
    preorder(&root);
    preorder1(&root);
    return 0;
}