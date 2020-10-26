#include <string>
#include <stack>
#include <ctype.h>
using namespace std;
/**
 * 中綴表達式S只由+-x(*)÷(/)以及單字母變量構成，不含whitedspace
**/
char orderBetween(char, char);
void convert(const string S, string &RPN) {
    stack<char> op;
    int i{0}, size{S.size()};
    while (i < size) {
        if (isalpha(S.at(i))) RPN.push_back(S.at(i++));
        else {
            switch (orderBetween(op.top(), S.at(i))) {
            case '<':
                op.push(S.at(i));
                i++;
                break;
            case '>':
                RPN.push_back(op.top());
                op.pop();
                break;
            }
        }
    }
}
int main(void) {
    string RPN, S{"1+2/3"};
    convert(S, RPN);
    return 0;
}