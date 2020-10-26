#include <stdlib.h>
using namespace std;
double func(double x) {
    size_t i;
    double count;
    for (i = 0, count = 0.0; i < SqPoly.last; ++i) {
        count += coef * pow(x, SqPoly.data[i].exp);
    }
    return count;
}