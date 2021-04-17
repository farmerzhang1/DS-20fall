#include <random>
#include <string>
#include "graph_impl.h"
void test () {
    Graph<int> g;
    for (int i = 0; i < 30; ++i)
        g.addVertex(2 * i + 1);
    std::cout << "add " << g.size << " vertices" << std::endl;
    g.print();
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, g.size-1);
    int random_u, random_v;
    int edgenum = 500;
    for (int i = 0; i < edgenum; ++i) {
        random_u = distribution(generator);
        do {
            random_v = distribution(generator);
        } while (random_u == random_v);
        g.addEdge (random_u, random_v, 2 * i + 1);
    }
    std::cout << "add " << edgenum << " edges (might be duplicate, so the actual result should be smaller than " << edgenum <<" edges" << std::endl;
    g.print();
    int deletenum = 200;
    for (int i = 0; i < deletenum; ++i) {
        random_u = distribution(generator);
        do {
            random_v = distribution(generator);
        } while (random_u == random_v);
        g.deleteEdge(random_u, random_v);
    }
    std::cout << "remove " << deletenum <<" edges" << std::endl;
    g.print();
    std::cout << "delete vertex 3" << std::endl;
    // note that the adjlist[3] is not removed, only clear() is called
    g.deleteVertex(3);
    g.print();
}

int main(void) {
    test();
    return 0;
}