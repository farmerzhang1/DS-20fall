#include <string>
using namespace std;
bool palindrome(string s) {
    size_t len = s.size(), i;
    for (i = 0; i < len/2; i++) {
        if (s[i] != s[len-i-1]) return false;
    }
    return true;
}