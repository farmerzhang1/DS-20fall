#include <bitset>
#include <random>
#include <ctime>
#include <iostream>
using namespace std;
class GeneticAlgorithm {
private:
    //range of the function
    double lower_bound, upper_bound;
    //length of bitset
    static const int LEN = 15;
    //mutation probability
    static constexpr const double MP = 1.0 / LEN;
    //maximum generation of evolution
    static const int MAXGEN = 100;
    //size of population
    static const int PSIZE = 10;
    struct Solution{
        bitset<LEN>* bits;
        double y;
    };
    Solution population[PSIZE * 2];
public:
    GeneticAlgorithm(double lower_bound, double upper_bound) {
        this->lower_bound = lower_bound;
        this->upper_bound = upper_bound;
        default_random_engine randomEngine{static_cast<unsigned int>(time(0))};
        uniform_int_distribution<unsigned int> randomInt{};
        double x;
        for (int i = 0; i < PSIZE; i++) {
            population[i].bits = new bitset<LEN>(randomInt(randomEngine));
            decode(population[i].bits, x);
            // cout << *population[i].bits << ' ' << x << endl;
        }
    }
    void printPop();
    /**
     *f(x), x∈[lower_bound, upper_bound]
     *x = lower_bound + decimal(bits) × (upper_bound - lower_bound) / (2^LEN - 1)
    **/
    void decode(const bitset<LEN>* bits, double& x_0) {
        x_0 = lower_bound + bits->to_ulong() * (upper_bound - lower_bound) / (pow(2, LEN) - 1);
    }
    double func(const bitset<LEN>* bits) {
        double x_0;
        decode (bits, x_0);
        return x_0 * x_0 - 3 * x_0 + 2;
    }
    void evaluate(Solution* p, double (*ptrf) (const bitset<LEN>*)) {
        p->y = func(p->bits);
    }
};

int main(void) {
    GeneticAlgorithm ga(0.0, 1.0);
}