#include "my_string.h"
#include <string.h>
#include <iostream>
MyString::MyString(char* str) {
    length = strlen(str);
    if (length > capacity) capacity = length + 1;
    p = new char[capacity]; // null terminate
    strcpy(p, str);
}

MyString::MyString(char* str, size_t len) {
    length = strlen(str);
    if (length > capacity) capacity = length + 1;
    p = new char[capacity]; // null terminate
    strncpy(p, str, len);
    p[len] = '\0';
}

void MyString::resize() {
    if (!p) return;
    char* q = new char[length+1];
    strcpy(q, p);
    delete [] p;
    p = new char[capacity *= 2];
    strcpy(p, q);
}

MyString::~MyString() {
    if (p) delete [] p;
}
MyString::MyString(){
    p = new char[capacity];
}

void MyString::clear() {
    *p = '\0';
    length = 0;
}

size_t MyString::size() const { return length; }

int* MyString::buildNext() const {
    if (!p) return nullptr;
    int i{1}, j{0};
    int* next = new int[length];
    next[0] = -1;
    while(i < length) {
        if (j < 0 || p[i] == p[j]) {
            i++;
            j++;
            next[i] = j;
        }
        else j = next[j];
    }
    for (int i = 0; i < length; i++) cout << next[i] << ' ';
    cout << endl;
    return next;
}

int MyString::find(const MyString& s, const size_t start = 0) const {
    int* next = s.buildNext();
    int i{start}, j{0}, m{length}, n{s.length};
    while (i < m && j < n) {
        if (j < 0 || p[i] == s.p[j]) { i++; j++; }
        else j = next[j];
    }
    return j < n ? -1 : i-j;
}

MyString MyString::substr(const size_t start, const size_t end = 10000000) const {
    size_t endd = end;
    if (endd > length) endd = length;
    return MyString(p + start, endd - start);
}

void MyString::replace (const MyString& s, const MyString& t) {
    int index = 0;
    size_t slen = s.length, tlen = t.length;
    while ((index = find(s, index)) != -1) {
        remove(index, slen);
        insert(index, t);
        index += tlen;
    }
}

void MyString::remove(size_t index, const size_t len = 1) {
    strcpy(p + index, p + index + len);
    length -= len;
}

void MyString::insert(const size_t index, const MyString& s) {
    if (index > length) throw invalid_argument("index out of range");
    while (length + s.length > capacity) resize();
    char* q = p + length + s.length;
    char* r = p + length;
    while (r >= p + index) {
        *q = *r;
        q--; r--;
    }
    q++; r++;
    int i = 0;
    while (i < s.length) { p[i+index] = s.p[i]; i++; }
    length += s.length;
}

void MyString::concatenate(const MyString& s) {
    while (length + s.length > capacity) resize();
    strcat(p, s.p);
}

ostream& operator<<(ostream& os, const MyString& s) {
    os << s.p;
    return os;
}

istream& operator>>(istream& is, MyString& s) {
    s.clear();
    is >> s.p;
    s.length = strlen(s.p);
    return is;
}

int main(void) {
    MyString aa("testabcdefgaaabc");
    cout << aa << endl;
    cout << aa.substr(1, 3) << endl;
    aa.insert(8, "\"test\"");
    cout << aa << endl;
    aa.remove(9, 6);
    cout << aa << endl;
    aa.replace("abcdefghabcde", "ws replaced ws");
    cout << aa << endl;
}