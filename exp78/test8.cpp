#include "graph_impl.h"
#include <iostream>
// 該測試原圖可在ppt第106頁找到。
void test8 () {
    Graph<int> g;
    int vn = 5; // number of vertices
    for (int i = 0; i < vn; ++i) g.addVertex (i);
    g.addEdge (0, 1, 10);
    g.addEdge (0, 3, 30);
    g.addEdge (3, 4, 60);
    g.BFS();
    g.DFS();
    std::cout << g.connectedNum() << std::endl;
    g.dijkstra(3);
}

int main(void) {
    test8();
    return 0;
}