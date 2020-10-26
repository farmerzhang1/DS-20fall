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
    size_t _size = 0;
    void resize();
    int* buildNext();
public:
    MyString(char* str);
    MyString(){}
    ~MyString();
    void clear();
    size_t size() const;
    int find(MyString&) const;
    MyString substr(size_t start, size_t end) const;
    void replace(MyString&, MyString&);
    void concatenate(MyString&);
    friend ostream& operator<<(ostream&, const MyString&);
};