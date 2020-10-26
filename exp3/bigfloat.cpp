#include "bigfloat.h"
#include <math.h>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
inline char convert(int n);
BigFloat::BigFloat(const double& num) {
    if (num < 0) negative = true;
    int floor{static_cast<int>(num)}, foo;
    double decimal = num - floor; // a decimal number in [0, 1)
    if (negative) { floor = -floor; decimal = -decimal; }
    if (floor >= 1024) floor %= 1024;
    size_t size{bits.size()}, i;
    for (i = 1, foo = 512; i <= INTLEN; i++) {
        bits.set(size-i, floor / foo);
        floor %= foo;
        foo /= 2;
    }
    for (i = 0; i < PRECISION; i++) {
        if (decimal == 0) break;
        if (decimal > 0.5) bits.set(size-i-1-INTLEN);
        decimal *= 2;
        if (decimal > 1.0) decimal -= 1.0;
    }
}
BigFloat::BigFloat(const bb& bits, bool negative) {
    this->bits = bits;
    this->negative = negative;
}
bool BigFloat::operator == (const BigFloat& bf) {
    if (negative != bf.negative) return false;
    for (int i = 0; i < INTLEN+PRECISION; i++)
        if (bits[i] != bf.bits[i]) return false;
    return true;
}
bool operator > (const bb& a, const bb& b) {
    size_t i = a.size();
    while (i >= 0 && a[i] == b[i]) i--;
    if (i+1 == 0) return false;
    return a[i];
}
bool BigFloat::operator > (const BigFloat& bf) {
    if (negative && !bf.negative) return false;
    if (!negative && bf.negative) return true;
    bool temp = bits > bf.bits;
    return negative ? !temp : temp;
}

bool operator < (const bb& a, const bb& b) {
    int i = a.size();
    while (i >= 0 && a[i] == b[i]) i--;
    if (i+1 == 0) return false;
    return b[i];
}

bool BigFloat::operator < (const BigFloat& bf) {
    if (negative && !bf.negative) return true;
    if (!negative && bf.negative) return false;
    bool temp = bits < bf.bits;
    return negative ? !temp : temp;
}
bool operator >= (const bb& a, const bb& b) { return !(a < b); }
bool BigFloat::operator >= (const BigFloat& bf) {
    return !(*this < bf);
}
bool operator <= (const bb& a, const bb& b) { return !(a > b); }
bool BigFloat::operator <= (const BigFloat& bf) {
    return !(*this > bf);
}
bb operator + (const bb& a, const bb& b) {
    bb temp;
    if (!a.any()) return b;
    if (!b.any()) return a;
    bool XOR, carry{false};
    size_t i, size{a.size()};
    for (size_t i = 0; i < size; i++) {
        XOR = a[i] ? !b[i] : b[i];
        temp[i] = carry ? !XOR : XOR;
        carry = (a[i] && b[i]) || (XOR && carry);
    }
    return temp;
}
bb operator += (bb &a, const bb &b) { return (a = a + b); }
BigFloat BigFloat::operator + (BigFloat& bf) {
    bool XOR, carry{false}, samesign{this->negative == bf.negative};
    if (samesign) {
        return BigFloat(bits+bf.bits, negative);
    }
    if (negative) {
        BigFloat aaa(bits, !negative);
        return bf - aaa;
    }
    BigFloat bbb(bf.bits, !bf.negative);
    return *this - bbb;
}
BigFloat BigFloat::operator -() { return BigFloat(this->bits, !this->negative); }
bb operator - (const bb& a, const bb& b) {
    if (a < b) throw invalid_argument("a must be greater than or equal to b");
    size_t i, size = a.size();
    bool XOR;
    bb temp{a};
    bool bi;
    for (i = 0; i < size; i++) {
        bi = b.test(i);
        XOR = temp[i] ? !bi : bi;
        if (!temp[i] && bi) {
            size_t j = i+1;
                while(!temp[j]) temp.flip(j++);
                temp.flip(j);
        }
        temp[i] = XOR;
    }
    return temp;
}
bb& operator -= (bb& a, const bb& b) { return (a = a - b); }
// this is a little complicated 不過我也不想改了哈哈
BigFloat BigFloat::operator - (BigFloat& bf) {
    bb temp = this->bits;
    bool XOR, samesign{this->negative == bf.negative};
    if (samesign) {
        if (!negative) {
            if (*this >= bf) {
                for (size_t i = 0; i < INTLEN+PRECISION; i++) {
                    bool bitsi = bf.bits.test(i);
                    XOR = temp[i] ? !bitsi : bitsi;
                    if (!temp[i] && bitsi) {
                        size_t j = i+1;
                        while(!temp[j]) temp.flip(j++);
                        temp.flip(j);
                    }
                    temp[i] = XOR;
                }
                return BigFloat(temp, negative);
            }
            return -(bf - *this);
        }
    }
    BigFloat aaa(bf.bits, !bf.negative);
    return *this + aaa;
}
bb operator * (const bb&a, const bb& b) {
    bb temp;
    int precision = BigFloat::getPrecision();
    int intlen = BigFloat::getIntlen();
    for (size_t i = 0; i < precision; i++)
        if (b.test(i))
            temp += (a >> (precision-i));

    for (size_t i = 0; i < intlen; i++)
        if (b.test(i+precision))
            temp += (a << i);
    return temp;
}
bb& operator *= (bb& a, const bb& b) { return (a = a * b); }
int toint(const bb& b) {
    int intlen = BigFloat::getIntlen(), foo = 512, precision = BigFloat::getPrecision();
    int temp = 0;
    for (int i = 0; i < intlen; ++i) {
        temp += foo * (b.test(precision + intlen -i -1) ? 1 : 0);
        foo /= 2;
    }
    return temp;
}
/* m = number of ones in bf.
 * time complexity = O(mN)
 * 有點慢啊！！
 */
BigFloat BigFloat::operator * (const BigFloat& bf) {
    bb temp;
    for (size_t i = 0; i < PRECISION; i++)
        if (bf.bits.test(i))
            temp += (bits >> (PRECISION-i));

    for (size_t i = 0; i < INTLEN; i++)
        if (bf.bits.test(i+PRECISION))
            temp += (bits << i);

    return BigFloat(temp, negative ? !bf.negative : bf.negative);
}
BigFloat& BigFloat::operator *= (const BigFloat& bf) { return (*this = *this * bf); }
/*
 *好像也不用區分了，就先對齊(最高位的1移到最前面，除數保證至少一個是1)
 *最開始的結果的index是權重2^0(which is PRECISION)位，除數左移index++，被除數左移index--
 *對齊後，被除數大於除數的話就直接相減，當前bits[index]為1，若小於，除數右移一位（會丟掉最後一位！）相減，index--
 *再把被除數移到最高，減小index
 *重複直到index為0。
 */
BigFloat BigFloat::operator / (const BigFloat& bf) {
    if (!bf.bits.any()) throw invalid_argument("divided by zero");
    if (!bits.any()) return BigFloat(0);
    bb temp, dividend = this->bits, divisor = bf.bits;
    int index = PRECISION;
    while (!divisor.test(PRECISION + INTLEN-1)) { divisor <<= 1; index++; }
    while (!dividend.test(PRECISION + INTLEN-1)) { dividend <<= 1; index--; }
    while (index >= 0) {
        if (dividend >= divisor) {
            dividend -= divisor;
            temp[index] = true;
        }
        else {
            dividend -= (divisor >> 1);
            if (index == 0) break;
            temp.set(index-1);
        }
        if (!dividend.any()) return BigFloat(temp, negative ? !bf.negative : bf.negative);
        while (!dividend.test(PRECISION + INTLEN-1)) { dividend <<= 1; index--; }
    }
    return BigFloat(temp, negative ? !bf.negative : bf.negative);
}
BigFloat BigFloat::operator ^ (const int& power) {
    BigFloat temp = *this;
    int p = power;
    while (--p) {
        temp *= *this;
    }
    return temp;
}
istream& operator >> (istream & is, BigFloat &bf) {
    double temp;
    is >> temp;
    bf = BigFloat(temp);
    return is;
}
/*
 * 給你暈厥
 * 這個有夠麻煩
 * now we're leaving it
 * bakdfkadlkfjad;f$%*%@$^%JHKGSaejhtq34
 */
ostream& operator << (ostream & os, const BigFloat &bf) {
    os << bf.bits << '\n' << bf.to_double() << endl;
    return os;
}
int BigFloat::to_int () const {
    int temp = 0, foo, i;
    size_t size = bits.size();
    for (i = 0, foo = 512; i < INTLEN; ++i) {
        temp += (bits.test(size - i - 1) ? 1 : 0) * foo;
        foo /= 2;
    }
    return temp;
}
double BigFloat::to_double () const {
    size_t size{bits.size()};
    unsigned long long foo{512};
    double temp = 0;
    string aa;
    size_t i;
    for (i = 0; i < BigFloat::INTLEN; ++i) {
        temp += foo * (bits.test(size - i - 1) ? 1 : 0);
        foo /= 2;
    }
    for (foo = 2, i = 0; i < 63; ++i) {
        temp += (bits.test(size-i-1-BigFloat::INTLEN) ? 1 : 0) / (double)foo; // can't use this... foo may be too large
        foo *= 2;
    }
    if (negative) temp = -temp;
    return temp;
}
/**
 *  使用double dabble algorithm
 *  就是瘋狂左移然後調整(adjust, if the number designated by the byte exceeds base, carry)
 */
/**
 * 完全放棄樓上的算法！！！（指double dabble, 'cause it only applies to integer values）
 * 從現在開始我只知道二進制
 * 要convert to另一進制都是拿當前bits(00000.xxxx)乘base，分成商和餘數，然後迭代。
 */
string BigFloat::to_base (const int base) const {
    if (base < 3 || base > 1024) throw invalid_argument("base out of range.");
    bool temp_negative = negative;
    const BigFloat ddd(base);
    bb Base = ddd.bits;
    vector<int> decimal;
    stack<int> integer;
    ostringstream conversion;
    int aaa{to_int()}, n{bits.size() * 2 / base};
    bb bbb = bits;
    for (int i = 0; i < INTLEN; ++i) bbb[PRECISION+i] = false;
    aaa = aaa > 0 ? aaa : -aaa;
    while (aaa) {
        integer.push(aaa % base);
        aaa /= base;
    }
    while (n--) {
        bbb *= Base;
        decimal.push_back(toint(bbb));
        for (int i = 0; i < INTLEN; ++i) bbb[PRECISION+i] = false;
    }
    while (!integer.empty()) {
        conversion << convert(integer.top()) << (base <= 36 ? "" : " ");
        integer.pop();
    }
    conversion << '.';
    for (auto p = decimal.begin(); p != decimal.end(); ++p)
        conversion << convert(*p) << (base <= 36 ? "" : " ");
    conversion << '(' << base << ')';
    return conversion.str();
}
inline char convert(int n) {
    return n < 10 ? '0' + n : 'a' + n - 10;
}