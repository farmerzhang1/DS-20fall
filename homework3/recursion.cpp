int g(unsigned int m, unsigned int n) {
    return m ? g(m - 1, 2 * n) + n: 0;
}
#include <iostream>
/*
g(5, 2)
g(4, 4) + 2
g(3, 8) + 4
g(2, 16) + 8
g(1, 32) + 16
g(0, 64) + 32
*/
int main(void) {
    std::cout << g(5, 2);
}