#include "graph.h"

int main() {
    int n = 9;
    Graph g(n);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);

    g.addEdge(2, 3, 7);
    g.addEdge(2, 5, 4);
    g.addEdge(2, 8, 2);

    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);

    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);
    string path1 = g.printShortestPath(0, 3);
    vector<pair<int, int>> arr = g.dijkstra(0);

    vector<int> v = {0, 4, 12, 19, 21, 11, 9, 8, 14};
    for(int i = 0; i < v.size(); i++) {
        cout << arr.at(i).first << " ";
    }


    return 0;
}