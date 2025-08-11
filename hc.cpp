#include <iostream>
#include <vector>
#include <limits>
using namespace std;

struct Edge {
    int to, cost;
};

struct Graph {
    int n;
    vector<vector<Edge>> adj;
    Graph(int nodes) : n(nodes), adj(nodes) {}
    void addEdge(int u, int v, int cost) {
        adj[u].push_back({v, cost});
        adj[v].push_back({u, cost}); // undirected
    }
};

vector<int> hillClimb(const Graph &g, int start, int goal, const vector<int> &heuristic) {
    vector<int> path;
    vector<bool> visited(g.n, false);
    int current = start;
    visited[current] = true;
    path.push_back(current);

    while (current != goal) {
        int bestNext = -1;
        int bestH = numeric_limits<int>::max();

        // pick neighbor with smallest heuristic
        for (auto &e : g.adj[current]) {
            if (!visited[e.to] && heuristic[e.to] < bestH) {
                bestH = heuristic[e.to];
                bestNext = e.to;
            }
        }

        if (bestNext == -1) {
            break; // stuck at local optimum
        }

        current = bestNext;
        visited[current] = true;
        path.push_back(current);
    }
    return path;
}

int main() {
    int nodes, edges;
    cin >> nodes >> edges;
    Graph g(nodes);

    // read edges
    for (int i = 0; i < edges; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        g.addEdge(u, v, c);
    }

    // read heuristic
    vector<int> h(nodes);
    for (int i = 0; i < nodes; i++) cin >> h[i];

    int start, goal;
    cin >> start >> goal;

    vector<int> path = hillClimb(g, start, goal, h);

    if (path.back() != goal) {
        cout << "Stuck at local optimum.\nPath: ";
    } else {
        cout << "Reached goal.\nPath: ";
    }
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i] << (i + 1 < path.size() ? " -> " : "\n");
    }
}
