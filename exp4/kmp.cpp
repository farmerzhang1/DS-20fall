#include <string>
#include <iostream>

using namespace std;
int* buildNext(string&);
int kmp(string t, string p) {
    int* next = buildNext(p);
    int m{t.size()}, n{p.size()}, i{0}, j{0};
    while (i < m && j < n)
        if (j < 0 || t[i] == p[j])  // if j == -1, start over
            { i++; j++; }
        else j = next[j];           // mismatch, update j
    i -= n;
    return j < n ? -1 : i;
}

int* buildNext(string& s) {
    int size{s.size()}, i{1}, t{0};
    int* next = new int[size];
    next[0] = -1;
    while (i < size) {
        if (t < 0 || s[i] == s[t]) {
            i++;
            t++;
            next[i] = t;
        }
        else t = next[t];
    }
    return next;
}
void test(int expected, int actual) {if (expected != actual) cout << "expected " << expected << " actual " << actual << endl;}
int main(void) {
    test(2, kmp("this", "is"));
    test(0, kmp("wwwww", "ww"));
    test(6, kmp("aaaaaaaaabb", "aaab"));
    test(-1, kmp("aabaaa", "bb"));
    test(0, kmp("test", "test"));
    return 0;
}