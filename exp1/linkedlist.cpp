#include <stdexcept>
#include <string>
#include <iostream>

template <typename T> struct Node {
    T data;
    Node* successor;
    Node* predecessor;
    Node(T e, Node* s = nullptr, Node* p = nullptr) : data(e), successor(s), predecessor(p){}
    Node(){}
    Node* insertSuccessor(Node* n) {//作為結點n的前驅插入
        if (!n) throw std::invalid_argument("Node cannot be null");
        n->successor = successor;
        n->predecessor = this;
        successor->predecessor = n;
        successor = n;
        return n;
    }
    Node* insertPredecessor(Node* n) {//作為結點n的後繼插入
        if (!n) throw std::invalid_argument("Node cannot be null");
        n->predecessor = predecessor;
        n->successor = this;
        predecessor->successor = n;
        predecessor = n;
        return n;
    }
};

template <typename T> class List {
    /*利用模板構造雙向鍊表*/
private:
    int _size;
    Node<T>* header;
    Node<T>* trailer;
public:
    List() { // constructor, with a header and a trailer.
        _size = 0;
        header = new Node<T>; trailer = new Node<T>;
        if (!header || !trailer) {
            std::cout << "Memory allocation failed" << std::endl;
            exit(1);
        }
        header->successor = trailer;
        header->predecessor = nullptr;
        trailer->successor = nullptr;
        trailer->predecessor = header;
    }

    ~List() { clear(); delete header; delete trailer; } // destructor, first clear(), then delete header and trailer.

    bool empty() const { return _size == 0; } // method is constant.

    int size() const { return _size; }

    void clear() {
        Node<T>* node = header->successor;
        Node<T>* prev;
        while (node != trailer) {
            prev = node;
            node = node->successor;
            delete prev;
        }
        _size = 0;
    }

    int getElement(const int index, T& value) const {
        if (index < 0 || index >= _size) throw std::invalid_argument("index out of range"); // check bounds.
        Node<T>* node = header->successor;
        for (int i = 0; i < _size; ++i, node = node->successor) {
            if (i == index) {
                value = node->data;
                return i;
            }
        }
    }

    Node<T>* operator[] (const int index) const { // rewrite operator[].
        if (index < 0 || index >= _size) throw std::invalid_argument("index out of range");
        Node<T>* node = header->successor;
        for (int i = 0; i < _size; ++i, node = node->successor) {
            if (i == index) {
                return node;
            }
        }
    }

    Node<T>* locateElement(const T e) const {
        for (auto node = header->successor; node != trailer; node = node->successor) {
            if (node->data == e) return node;
        }
        return nullptr;
    }

    Node<T>* predecessor(const Node<T>* node) const {
        if (!node) throw std::invalid_argument("Node cannot be null");
        return node->predecessor;
    }

    Node<T>* successor(const Node<T>* node) const {
        if (!node) throw std::invalid_argument("Node cannot be null");
        return node->successor;
    }

    Node<T>* insert(const int index, const T value) { // insert the value so that after insertion, the index is the given one.
        if (index < 0 || index > _size) throw std::invalid_argument("index out of range");// index can be equal to _size.
        Node<T>* node = header->successor;
        for (int i = 0; i < index; ++i) node = node->successor;// get to the position.
        Node<T>* temp = new Node<T>(value);
        if (!temp) exit(0);
        node->insertPredecessor(temp);
        _size++;
        return temp;
    }

    int remove(const int index) { // remove the given node
        if (index < 0 || index >= _size) throw std::invalid_argument("index out of range");
        Node<T>* node = header->successor;
        for (int i = 0; i < index; ++i) node = node->successor;
        node->predecessor->successor = node->successor;
        node->successor->predecessor = node->predecessor;
        delete node;
        return 1;
    }

    void debug(const Node<T>* node) {
        std::cout << node << "\t" << node->data << std::endl;
    }

    void traverse() {
        Node<T>* node = header->successor;
        while (node!= trailer) {
            debug(node);
            node = node->successor;
        }
        std::cout << std::endl;
    }

};

int main(void) {
    List<std::string> list;
    if (list.empty()) std::cout << "ald;fj;d" << std::endl;
    else std::cout << "rwa" << std::endl;
    list.insert(0, "this");
    list.insert(0, "is");
    list.insert(1, "a");
    list.insert(3, "test");
    list.insert(2, "what???");
    list.traverse();
    list.remove(0);
    list.traverse();
    return 0;
}