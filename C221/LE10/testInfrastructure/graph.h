#include <iostream>
#include <vector>
#include <list>
#include <climits>
#include <queue>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class Graph {
    private:
        int n;
        typedef pair<int, int> Edge;
        vector<list<Edge>> v;
        
    public:
            Graph(int size = 2) {
            n = size;
            v.resize(size);
        }

        void addEdge(int x, int y, int w) {
            int biggerNum = (x > y) ? x : y;
            if (v.size() < biggerNum) {
                v.resize(biggerNum);
                n = biggerNum;
            }

            auto it = v.at(x).begin();
            bool updatedVal = false;
            for (it; it != v.at(x).end(); ++it) {
                if (it->first == y) {
                    it->second = w;
                    updatedVal = true;
                }
                
            }
            if (!updatedVal) v.at(x).push_back(Edge(y, w));

            it = v.at(y).begin();
            updatedVal = false;
            for (it; it != v.at(y).end(); ++it) {
                if (it->first == x) {
                    it->second = w;
                    updatedVal = true;
                }
                
            }
            if (!updatedVal) v.at(y).push_back(Edge(x, w));

        }

        void print() {
            for(int i = 0; i < n; i++) {
                cout << "Node " << i << " is connected to: ";
                for (pair<int,int> j : v[i]) {
                    if(j.first != -1){
                        cout << j.first << " : "<< j.second<<", ";
                    }
                }
                cout << endl;
            }
        }

        vector<pair<int, int>> dijkstra(int startNode) {
            std::unordered_set<int> visitedEdges = {};
            std::unordered_set<int> seenEdges = {startNode};

            std::unordered_map<int, int> parent;
            std::unordered_map<int, int> weight;
            vector<pair<int, int>> p(n);

            // Have to do opposite order so that u can use priority queue
            priority_queue<Edge, vector<Edge>, std::greater<Edge>> pq;    pq.push(Edge(0, startNode));
            while (!pq.empty()) {
                int currEdge = pq.top().second;
                int currWeight = pq.top().first;
                // cout << "Current edge: "  << currEdge << "Weight is: " << currWeight << endl;
                pq.pop();
                list<Edge> adjEdges = v.at(currEdge);
                auto it = adjEdges.begin();
                for (it; it != adjEdges.end(); ++it) {
                    int otherEdge = it->first;
                    int otherWeight = it->second;
                    // cout << "Looking at.. " << otherEdge << " " ;
                    if (visitedEdges.find(otherEdge) == visitedEdges.end()) { // If edge hasn't been visted before...
                        bool seenB4 = seenEdges.find(otherEdge) != seenEdges.end(); // Checks to see if edge has been seen before
                        if (!seenB4 || weight[otherEdge] > currWeight + otherWeight) { // And if edge hasn't been seen before (inf weight) OR Edge has been seen before (has a weight) and is smallest
                            // cout << "UPDATING: Seen before: " << seenB4 << " | Updating to weight " << currWeight << " + " << otherWeight << " | ";
                            parent[otherEdge] = currEdge;
                            weight[otherEdge] = otherWeight + currWeight;   // Updates with smallest Weight
                            pq.push(Edge(weight[otherEdge], otherEdge)); // Pushes to priority queue to be visited
                    
                            if (!seenB4) seenEdges.insert(otherEdge); 
                            // else cout << "Hasn't been seen before." << endl;
                        }
                    } // else cout << "Visited before." << endl;// If it has been visited continue
                    // cout << endl;
                } // Loop ends when all adjacent nodes are seen and noted

                visitedEdges.insert(currEdge); 
            }
            for (int edge = 0; edge < n; ++ edge) {
                if (visitedEdges.find(edge) == visitedEdges.end()) { p.at(edge) = Edge(INT32_MIN, INT16_MIN); } // If edge hasn't been seen before give it a neg weight, to note edge doesn't span it
                else p.at(edge) = Edge(weight[edge], parent[edge]);
            }
            return p;
        }

        string printShortestPath(int startNode, int endNode) {
            auto spanTree = dijkstra(startNode); 
            std::unordered_set<int> visitedEdges = {};
            int currNode = endNode;
            deque<int> order;
            while (currNode != startNode) {
                if (visitedEdges.find(currNode) != visitedEdges.end()) return ""; // A cycle has occured
                else if (spanTree.at(currNode).first == INT32_MIN) return ""; // The node is part of its own forest, the start node doesn't span to it
                visitedEdges.insert(currNode);
                order.push_back(currNode);
                currNode = spanTree.at(currNode).second; // makes currNode the parent of the child node
                // Loops until reaches startNode

            }
            order.push_back(startNode);
            string s = "";
            while (!order.empty()) {
                    int v = order.back();
                    s += std::to_string(order.back()) + " ";
                    order.pop_back();
            }
            return s;
           
        }
};



