#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include "graph.h"
#ifndef GRAPH_IMPL_H
#define GRAPH_IMPL_H
template <typename T> Graph<T>::Graph (const size_t n) : size {n}, adjlist {n}, vertices {n} {}
template <typename T> Graph<T>::Graph () : size (0) {}

template <typename T> void Graph<T>::addEdge(index u, index v, weight w) {
    // some tests
    for (auto it = adjlist.at(u).begin(); it != adjlist.at(u).end(); ++it) if (it->first == v) return;
    adjlist.at(u).push_back ({v, w});
    adjlist.at(v).push_back ({u, w});
}
template <typename T> void Graph<T>::addVertex (const T& label) {
    // always add as the last (index is SIZE) vertex
    std::vector<edge> edges;
    adjlist.push_back (edges);
    vertex toadd(label, size++);
    vertices.push_back(toadd);
}
template <typename T> void Graph<T>::deleteEdge (const index u, const index v) {
    auto it_u = adjlist.at(u).end();
    auto it_v = adjlist.at(v).end();
    for (auto it = adjlist.at(u).begin(); it != adjlist.at(u).end(); ++it)
        if (it->first == v) { it_u = it; break; }
    for (auto it = adjlist.at(v).begin(); it != adjlist.at(v).end(); ++it)
        if (it->first == u) { it_v = it; break; }
    if (it_u != adjlist.at(u).end()) adjlist.at(u).erase(it_u);
    if (it_v != adjlist.at(v).end()) adjlist.at(v).erase(it_v);
}
template <typename T> void Graph<T>::deleteVertex (const index u) {
    // first remove all the edges from U
    //adjlist.erase (adjlist.begin() + u);
    adjlist.at(u).clear();
    for (auto it = adjlist.begin(); it != adjlist.end(); ++it) {
        auto to_remove = it->end();
        for (auto current = it->begin(); current != it->end(); ++current) {
            if (current->first == u) {
                to_remove = current;
                break;
            }
        }
        if (to_remove != it->end())
            it->erase (to_remove);
    }
    //size--;
}
template <typename T> void Graph<T>::BFS() {
    clear ();
    std::queue<index> Q;
    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        if (!it->visited) { // check every vertex
            Q.push (it->n);
            it->visited = true;
            while (!Q.empty ()) {
                index currentIndex = Q.front();
                std::cout << "BFS:\t" << vertices.at(currentIndex).label << std::endl;
                Q.pop();
                //std::vector<edge>* edges = adjlist.begin() + currentIndex;
                for (const auto& currentEdge : adjlist.at(currentIndex)) {
                    index neighborIndex = currentEdge.first;
                    if (!vertices.at(neighborIndex).visited) {
                        Q.push (neighborIndex); // BFS
                        vertices.at(neighborIndex).visited = true;
                    }
                }
            }
        }
    }
    std::cout << std::endl;
}
template <typename T> void Graph<T>::DFS() {
    clear ();
    std::stack<index> S;
    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        if (!it->visited) { // check every vertex
            S.push (it->n);
            it->visited = true;
            while (!S.empty ()) {
                index currentIndex = S.top();
                std::cout << "DFS:\t" << vertices.at(currentIndex).label << std::endl;
                S.pop();
                //std::vector<edge>* edges = adjlist.begin() + currentIndex;
                for (const auto& currentEdge : adjlist.at(currentIndex)) {
                    index neighborIndex = currentEdge.first;
                    if (!vertices.at(neighborIndex).visited) {
                        S.push (neighborIndex); // DFS
                        vertices.at(neighborIndex).visited = true;
                    }
                }
            }
        }
    }
    std::cout << std::endl;
}
template <typename T> void Graph<T>::clear () {
    for (auto& currentVertex : vertices)
        currentVertex.visited = false;
}
template <typename T> size_t Graph<T>::connectedNum () {
    clear ();
    std::stack<index> S;
    size_t count {0};
    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        if (!it->visited) { // check every vertex
            S.push (it->n);
            it->visited = true;
            count++;
            while (!S.empty ()) {
                index currentIndex = S.top();
                S.pop();
                //std::vector<edge>* edges = adjlist.begin() + currentIndex;
                for (auto& currentEdge : adjlist.at(currentIndex)) {
                    index neighborIndex = currentEdge.first;
                    if (!vertices.at(neighborIndex).visited) {
                        S.push (neighborIndex); // DFS
                        vertices.at(neighborIndex).visited = true;
                    }
                }
            }
        }
    }
    return count;
}
template <typename T> void Graph<T>::dijkstra (const index from) {
    // init
    clear ();
    for (auto& currentEdge : adjlist.at(from))
        vertices.at(currentEdge.first).distance = currentEdge.second;   // other vertices' distances are still infinity
    vertices.at(from).distance = 0;
    vertices.at(from).visited = true;
    for (index i = 0; i < vertices.size()-1; ++i) {   // find one shortest path every time
        index min = getMin();   //
        vertices.at(min).visited = true; // 這裡復用了一下visited, to represent that its shortest path has been found
        for (auto& currentEdge : adjlist.at(min)) {
            vertex& currentVertex = vertices.at(currentEdge.first);
            if (currentVertex.visited) continue;
            if (currentVertex.distance == maximum)
                currentVertex.distance = currentEdge.second + vertices.at(min).distance;    // addition on maximum values might overflow
            else
                currentVertex.distance = std::min (currentVertex.distance, vertices.at(min).distance + currentEdge.second);
        }
    }
    for (const auto& v : vertices) {
        std::cout << v.label << ":\t";
        (v.distance == maximum ? (std::cout << "inf") : (std::cout << v.distance)) << std::endl;
    }
}
template <typename T> void Graph<T>::print() const {
    for (auto it = adjlist.begin(); it != adjlist.end(); ++it) {
        std::cout << it - adjlist.begin() << ":\t";
        for (auto list_it = it->begin(); list_it != it->end(); ++list_it) {
            std::cout << list_it->first << " ";
        }
        std::cout << "\n";
    }
}

template <typename T> typename Graph<T>::index Graph<T>::getMin() const {
    weight min = maximum;
    index ind = 0;
    for (index i = 0; i < vertices.size(); ++i) {
        if (vertices.at(i).visited) continue;
        if (vertices.at(i).distance < min) {
            ind = i;
            min = vertices.at(i).distance;
        }
    }
    return ind;
}
#endif