#include "my_string.h"
#include <string.h>
MyString::MyString(char* str) {
    _size = strlen(str);
    p = new char[_size+1]; // null terminate
    strcpy(p, str);
}

MyString::~MyString() {
    if (p) delete [] p;
}

void MyString::clear() {
    delete [] p;
    _size = 0;
    p = nullptr;
}

size_t MyString::size() const { return _size; }

int* MyString::buildNext() {
    if (!p) return nullptr;
    int i{1}, j{0};
    int* next = new int[_size];
    next[0] = -1;
    while(i < _size) {
        if (j < 0 || p[i] == p[j]) {
            i++;
            j++;
            next[i] = j;
        }
        else j = next[j];
    }
    return next;
}

int MyString::find(MyString& s) const {
    int* next = s.buildNext();
    int i{0}, j{0}, m{_size}, n{s._size};
    while (i < m && j < n) {
        if (j < 0 || p[i] == s.p[j]) { i++; j++; }
        else j = next[j];
    }
    return j < n ? -1 : i-j;
}

MyString MyString::substr(size_t start, size_t end) const {
    
}