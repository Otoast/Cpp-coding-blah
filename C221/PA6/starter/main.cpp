#include "graph.h"

int main() {
    Graph g;
    vector<int> vertices = {0, 1, 2, 3, 4, 5};
    vector<tuple<int, int, int>> edges = {{0, 1, 12}, {0, 2, 8},
                                          {1, 2, 9}, {1, 3, 22}, {1, 5, 11},
                                          {2, 5, 14}, {2, 3, 16},
                                          {3, 5, 18}, {3, 4, 15},
                                          {4, 5, 3}};

    for (int i = 0; i < vertices.size(); i++) {
        g.addVertex(vertices[i]);
    }

    for (int i = 0; i < edges.size(); i++) {
        int u = get<0>(edges[i]);
        int v = get<1>(edges[i]);
        int w = get<2>(edges[i]);
        g.addEdge(v, u, w);
    }
   
    cout << "THIS IS GRAPH: " << endl;
    g.print();
    g.primMST();
}
