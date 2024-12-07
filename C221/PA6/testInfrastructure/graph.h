#include <iostream>
#include <vector>
#include <list>
#include <climits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Graph {
    private:
        unordered_map<int, unordered_map<int, int>> adjList;

    public:
        Graph() {};

        bool contains_vertex(int u) {
            return adjList.find(u) != adjList.end();
        }
        bool contains_edge(int u, int v) {
            return (
                adjList.find(u) != adjList.end() &&
                adjList[u].find(v) != adjList[u].end()
            );
        }

        void addVertex(int u) {
            adjList.insert({u , unordered_map<int, int>()});
        }

        void addEdge(int u, int v, int w) {
            if (!contains_vertex(u)) addVertex(u);
            if (!contains_vertex(v)) addVertex(v);
            adjList[u][v] = w;
            adjList[v][u] = w;
        }

        void removeEdge(int u, int v) {
            if (!contains_edge(u, v)) throw std::runtime_error("Edge doesn't exist.");
            adjList[u].erase(v);
            adjList[v].erase(u);
            
        }

        void removeVertex(int id) {
            if (!contains_vertex(id)) throw std::runtime_error("Vertex doesn't exist"); 
            for (auto it = adjList[id].begin(); it != adjList[id].end(); ++it) {
                int key = it->first;
                adjList[key].erase(id);
            }
            adjList.erase(id);
        }

        int numVertices() {
            return adjList.size();
        }

        int getEdgeWeight(int u, int v) {
            return (contains_edge(u, v)) ? adjList[u][v] : -1;
        }

        vector<pair<int, int>> primMST() {
            unordered_set<int> visitedNodes = {};
            typedef pair<int, int> Edge;
            priority_queue<pair<int, Edge>, vector<pair<int, Edge>>, std::greater< pair<int, Edge> > > pq; 
            pq.push({0, Edge(adjList.begin()->first, adjList.begin()->first)}); // Has the smallest edge + an edge as a pair
            vector<pair<int, int>> p;
            
            while (!pq.empty()) { // Continues until pq is empty
                Edge e = pq.top().second; // Don't need weight
                pq.pop();
                if (visitedNodes.find(e.first) == visitedNodes.end() || visitedNodes.find(e.second) == visitedNodes.end())  { // If there is at least one node that isnt connected, makes it an edge
                    p.push_back(e);
                    visitedNodes.insert(e.first);
                    visitedNodes.insert(e.second);
                }
                int key = e.second; // The extending edge that hasn't seen anything / Not been visited typically (ex: u -> v, key is v)

                unordered_map <int, int> keyEdges = adjList[key]; // All edges connected to by key
                for (auto it = keyEdges.begin(); it != keyEdges.end(); ++it) // Loops through every edge connected to vertex
                    if (visitedNodes.find(it->first) == visitedNodes.end())  pq.push({it->second, Edge(key, it->first)}); // If vertex isn't already connected adds it to potential edges to connect
                 // In the end adds all potential connecting nodes to priority queue
            } // Loops on every edge eventually, only adds edges to p if they are smallest possible and at least one of the nodes hasn't been connected.
            
            p.erase(p.begin()); // Takes out the first element which is a self loop
            return p;
        }


};