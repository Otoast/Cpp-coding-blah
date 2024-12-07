#define TEST
#include <iostream>
#include "graph.h"
using namespace std;

int testDijkstra() {
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

    vector<pair<int, int>> arr = g.dijkstra(0);

    vector<int> v = {0, 4, 12, 19, 21, 11, 9, 8, 14};
    for(int i = 0; i < v.size(); i++) {
        if(arr[i].first != v[i]){
            cout << "Failed" << endl;
            return 0;
        }
    }

    cout << "Passed" << endl;
    return 10;
}

int comparePaths(string expected, string actual) {
    if (actual != expected && actual != expected.substr(0, expected.size() - 1)) {
        cout << "Failed" << endl;
        return 0;
    }
    return 1;
}

int testShortestPathConnectedGraph() {
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

    string path1 = g.printShortestPath(0, 1);
    string expectedPath1 = "0 1 ";
    if (comparePaths(path1, expectedPath1) == 0) {
        return 0;
    }

    string path2 = g.printShortestPath(0, 2);
    string expectedPath2 = "0 1 2 ";
    if (comparePaths(path2, expectedPath2) == 0) {
        return 0;
    }
    
    string path3 = g.printShortestPath(0, 3);
    string expectedPath3 = "0 1 2 3 ";
    if (comparePaths(path3, expectedPath3) == 0) {
        return 0;
    }

    string path4 = g.printShortestPath(0, 4);
    string expectedPath4 = "0 7 6 5 4 ";
    if (comparePaths(path4, expectedPath4) == 0) {
        return 0;
    }

    string path5 = g.printShortestPath(0, 5);
    string expectedPath5 = "0 7 6 5 ";
    if (comparePaths(path5, expectedPath5) == 0) {
        return 0;
    }

    string path6 = g.printShortestPath(0, 6);
    string expectedPath6 = "0 7 6 ";
    if (comparePaths(path6, expectedPath6) == 0) {
        return 0;
    }

    string path7 = g.printShortestPath(0, 7);
    string expectedPath7 = "0 7 ";
    if (comparePaths(path7, expectedPath7) == 0) {
        return 0;
    }

    string path8 = g.printShortestPath(0, 8);
    string expectedPath8 = "0 1 2 8 ";
    if (comparePaths(path8, expectedPath8) == 0) {
        return 0;
    }

    cout << "Passed" << endl;
    
    return 8;
}

int testShortestPathNotReachable() {
    Graph g(6);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 8);
    g.addEdge(1, 3, 5);
    g.addEdge(1, 4, 6);
    g.addEdge(3, 4, 3);
    g.addEdge(3, 5, 2);
    g.addEdge(4, 5, 1);

    string path2 = g.printShortestPath(0, 2);
    string expectedPath2 = "";
    if (path2 != expectedPath2) {
        cout << "Failed" << endl;
        return 0;
    }

    cout << "Passed" << endl;
    
    return 2;
}

int main(){
    int score = 0;
    try {
        cout << "Test Dijkstra" << endl;
        score += testDijkstra();
        cout << endl;

        cout << "Test Shortest Path (Connected Graph):" << endl;
        score += testShortestPathConnectedGraph();
        cout << endl;

        cout << "Test Shortest Path (Disconnected):" << endl;
        score += testShortestPathNotReachable();
        cout << endl;
    } catch (const std::exception& e) {
        cout << e.what() << endl;
    }
    
    cout << "Final score: " << score << " / 20" << endl;
    return 0;
}