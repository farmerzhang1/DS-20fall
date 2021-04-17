#include <limits>
#include <vector>
#ifndef GRAPH_H
#define GRAPH_H

template <typename T>
class Graph {
private:
    // index starts from 0
    using index = size_t;
    using weight = unsigned int;
    using edge = std::pair<index, weight>;
    static const weight maximum = std::numeric_limits<weight>::max();
    struct vertex {
        T label; index n; bool visited; weight distance;
        vertex (const T& _label, const index _n) : label(_label), n (_n), distance (maximum) {
            visited = false;
        }
    };

    size_t size;
    std::vector<std::vector<edge>> adjlist;
    std::vector<vertex> vertices;
    weight getWeight (const index u, const index v) const;
    index getMin () const;
    void addEdge(const index u, const index v, const weight w);
    void addVertex(const T& label);
    void deleteEdge(const index u, const index v);
    void deleteVertex(const index u);
    void print () const;
    // make each vertex unvisited (visited = false)
    void clear ();
public:
    Graph (const size_t n);
    Graph ();
    void BFS();
    void DFS();
    // return the shortest path from FROM to every other vertices
    void dijkstra(const index from);
    size_t connectedNum ();
    // some tests
    // friend void test8();
};
#endif