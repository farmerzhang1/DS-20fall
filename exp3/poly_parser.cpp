#include "bigfloat.h"
#include <stack>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
enum Operator{ ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE };
enum PARSE_RESULT { OK, UNKNOWN_VAR, MISSING_OPERATOR };
Operator optr2rank (char);
char orderBetween(char, char);
void aaaa(stack<double>&, stack<BigFloat>&, Operator);
void test(const char* poly, const double parameter);
void testttt();
void test_addition();
void test_subtraction();
void test_multiplication();
void test_division();
void test_base_conversion();
void test_polynomial();
bool isnum(const char*, const char* const);
int test_pass = 0, test_count = 0;
/*
 *example: 1/3 * x^5 - 456.79 * x^2 + 88 * x + 9
 *(好吧，其實也不用寫什麼例子，就是普通的加減乘除乘方階乘運算都可以)
 *x < 1024 && x > -1024
 *throw an invalid_argument if polynomial is illegal or x exceeds boundary.
 *return a Reverse Polish Notation representing the polynomial
*/
PARSE_RESULT parse(const char* polynomial, const double x, string& RPN) {
    if (x > 1024 || x < -1024) throw invalid_argument("x > 1024 || x < -1024");
    //this is being very useful!!! (* w *)
    const char* start = polynomial;
    ostringstream x_string;
    x_string << x;
    stack<char> op;
    double d;
    op.push('\0');
    while (!op.empty()) {
        while (*polynomial == ' ') polynomial++;
        if (isnum(polynomial, start)){
            const char* end = polynomial;
            if (*polynomial == '-') end++;
            while (isdigit(*end) || *end == '.') end++;
            RPN.append(polynomial, end);
            RPN.append(" ");
            polynomial = end;
        }
        else {
            if (*polynomial == 'x') {
                RPN.append(x_string.str());
                RPN.append(" ");
                polynomial++;
                continue;
            }
            switch (orderBetween(op.top(), *polynomial)) {
            case '<':
                op.push(*polynomial);
                polynomial++;
                break;
            case '=':
                op.pop();
                polynomial++;
                break;
            case '>':
                RPN.append(1, op.top());
                RPN.append(" ");
                op.pop();
                break;
            default:
                return PARSE_RESULT::UNKNOWN_VAR;
            }
        }
    }
    return PARSE_RESULT::OK;
}
bool isnum(const char* poly, const char* const start) {
    if (isdigit(*poly)) return true;
    if (*poly == '-') {
        if (isdigit(*(poly + 1))) {
            while (poly > start || *poly == ' ') poly--;
            if (poly == start) return true;
            if (!isdigit(*poly)) return false;
        }
        return false;
    }
    return false;
}

void parse_rpn(string& RPN, double& expected, double& actual) {
    stack<double> s;
    stack<BigFloat> ss;
    Operator op;
    double d, t;
    size_t i = 0, size{RPN.size()};
    while (i < size-1) {
        while (RPN.at(i) == ' ') i++;
        if (isdigit(RPN.at(i)) || RPN.at(i) == '-' && isdigit(RPN.at(i+1))) {
            d = strtod(RPN.substr(i).c_str(), nullptr);
            s.push(d);
            ss.push(BigFloat(d));
            if (RPN.at(i) == '-') i++;
            while (isdigit(RPN.at(i)) || RPN.at(i) == '.') i++;
        }
        else {
            op = optr2rank(RPN.at(i));
            i++;
            aaaa(s, ss, op);
        }
    }
    expected = s.top();
    actual = ss.top().to_double();
}
/*
 * 彈出兩個數，算一下再push回去。
 */
void aaaa(stack<double>& doubleStack, stack<BigFloat>& bfStack, Operator op) {
    double dfirst, dsecond;
    dsecond = doubleStack.top();
    doubleStack.pop();
    dfirst = doubleStack.top();
    doubleStack.pop();

    BigFloat bfsecond = bfStack.top();
    bfStack.pop();
    BigFloat bffirst = bfStack.top();
    bfStack.pop();

    switch (op) {
    case ADD:
        doubleStack.push(dfirst + dsecond);
        bfStack.push(bffirst + bfsecond);
        break;
    case SUB:
        doubleStack.push(dfirst - dsecond);
        bfStack.push(bffirst - bfsecond);
        break;
    case MUL:
        doubleStack.push(dfirst * dsecond);
        bfStack.push(bffirst * bfsecond);
        break;
    case DIV:
        doubleStack.push(dfirst / dsecond);
        bfStack.push(bffirst / bfsecond);
        break;
    case POW:
        doubleStack.push(pow(dfirst, dsecond));
        bfStack.push(bffirst ^ bfsecond.to_int());
        break;
    }
}

char orderBetween(char top, char current) {
    const int N_OPTR = 9;
    const char pri[N_OPTR][N_OPTR] = {
   /*                                                                           */
   /*           +      -      *      /      ^      !      (      )      \0 */
   /*  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
   /*  - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
   /*  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
   /*  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
   /*  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
   /*  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
   /*  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
   /*  ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
   /*  \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
    };
    return pri[optr2rank(top)][optr2rank(current)];
}

Operator optr2rank (char op) {
    switch (op) {
        case '+' : return ADD;
        case '-' : return SUB;
        case '*' : return MUL;
        case '/' : return DIV;
        case '^' : return POW;
        case '!' : return FAC;
        case '(' : return L_P;
        case ')' : return R_P;
        case '\0': return EOE;
        default  : exit ( -1 );
    }
}
int main(void) {
    testttt();
    return 0;
}

/*
 *this is an EASY test, using only part of the bits to calculate the approximate value of BigFloat
 *largest type maybe unsigned long long(or int128?), corresponding epsilon can be as small as 1e-12.
 */
void test(const char* poly, const double parameter = 0.0) {
    const double epsilon = 1e-12;
    double expected, actual;
    string rpn;
    parse(poly, parameter, rpn);
    cout << rpn << endl;
    parse_rpn(rpn, expected, actual);
    test_count++;
    cout << actual << endl;
    if (expected - actual < epsilon && actual - expected < epsilon) test_pass++;//cout << "test passed" << endl;
    else printf("test failed\nexpected: %.10lf\tactual: %.10lf\n\n", expected, actual);
}
void testttt() {
    test_addition();
    test_subtraction();
    test_multiplication();
    test_division();
    test_polynomial();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    test_base_conversion();
}
void test_addition() {
    test("-105.134+ (-641)");
    test("-345.23 + 500.134");
    test("-23 + 10.23456");
    test("324.145+624.123569");
    test("981.45679 +(-123.98725)");
    test("123.83+( 780.87)");
}
void test_subtraction() {
    test("-912.345 - 0.5");
    test("41.1 - 436.6");
    test("-41.1 -(-436.6)");
    test("515.623 - (-123.6)");
}
void test_multiplication() {
    test("198.884 * 0.0135");
    test("-198.884 * 0.0135");
    test("15.623 * (-23.99)");
    test("-881.678901 * (-0.2356)");
}
void test_division() {
    test("19.84 / 878.7");
    test("-486 / 2.3");
    test("123.456 / (-123.456)");
    test("-19.812 / (-581.1)");
}
void test_base_conversion() {
    cout << BigFloat(1023.99).to_base(10) << endl;
    cout << BigFloat(32).to_base(16) << endl;
}
void test_polynomial() {
    test("1.5 / 878 * x^4 - 5.3201 * x^3 + 13.456 * x^2 +53.13", 3.333);
    test("3/7 * x^3 - 1/3 * x^2 + 4", 1.4);
}