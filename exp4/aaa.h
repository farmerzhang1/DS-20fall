#include <iostream>
using namespace std;
/*
implementation: 定长顺序结构存储、堆分配存储和块链存储三选二
基本操作包括（但不限于）：
初始化：初始化串
销毁：销毁串，释放空间
清空：清为空串
求长度：返回串中的元素个数，称为串的长度
模式匹配：定位子串的位置，要求使用KMP算法实现
求子串：返回某个起始位置的某长度的子串
替换：Replace(&S, T, V)
    S是主串
    用V替换主串S中出现的所有与T相等的不重叠的子串
拼接：拼接两个串
遍历：输出给定串
*/
class MyString {
private:
    char* p = nullptr;
    size_t length = 0;
    const size_t capacity = 256;
    int* buildNext()const;
public:
    void remove(const size_t, const size_t);
    void insert(const size_t index, const MyString&);
    MyString(char* str, size_t len);
    MyString(char* str);
    MyString();
    ~MyString();
    void clear();
    size_t size() const;
    int find(const MyString&, const size_t) const;
    MyString substr(const size_t start, const size_t end) const;
    void replace(const MyString&, const MyString&);
    void concatenate(const MyString&);
    friend ostream& operator<<(ostream&, const MyString&);
    friend istream& operator>>(istream&, MyString&);
};