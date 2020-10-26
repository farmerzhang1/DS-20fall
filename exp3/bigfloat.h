#ifndef BF_H
#define BF_H
#include <iostream>
#include <bitset>
#include <string>
using namespace std;
/*
 * big float need only represent real number from -2^10 to 2^10(both exclusive).
 * the biggest integer less than 1024 (100 0000 0000) is
 * 11 1111 1111
 * biggest floating-point number less than 1024 is
 * 11 1111 1111.111...111(with PRECISION bits after the decimal point)
*/
class BigFloat {
private:
    static const size_t PRECISION = 100;
    static const size_t INTLEN = 10;
    // in bits, [0, PRECISION) is decimal, [PRECISION, PRECISION+INTLEN) is integer
    // should've used one more bit for 2's complement!!!
    bitset<PRECISION + INTLEN> bits;
    bool negative = false;
public:
    BigFloat(const double&);
    BigFloat(const bitset<PRECISION + INTLEN>&, bool negative);
    BigFloat operator + (BigFloat&);
    BigFloat operator - (BigFloat&);
    BigFloat operator -();
    BigFloat operator / (const BigFloat&);
    BigFloat operator * (const BigFloat&);
    BigFloat& operator *= (const BigFloat&);
    // 應該用快速冪
    BigFloat operator ^ (const int&);

    int to_int ()const;
    double to_double ()const;
    string to_base (const int) const;
    bool operator == (const BigFloat&);
    bool operator > (const BigFloat&);
    bool operator < (const BigFloat&);
    bool operator >= (const BigFloat&);
    bool operator <= (const BigFloat&);
    friend istream& operator >> (istream& is, BigFloat&);
    friend ostream& operator << (ostream& os, const BigFloat&);
    constexpr static const size_t& getPrecision() { return PRECISION; }
    constexpr static const size_t& getIntlen() { return INTLEN; }
};
typedef bitset<BigFloat::getPrecision()+BigFloat::getIntlen()> bb;
#endif