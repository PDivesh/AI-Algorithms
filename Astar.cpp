#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>
using namespace std;

struct Edge {
    int to, cost;
};

struct State {
    int node;
    int g; 
    int f; 
    vector<int> path;
    bool operator>(const State &other) const {
        return f > other.f; 
    }
};

struct Graph {
    int n;
    vector<vector<Edge>> adj;
    Graph(int nodes) : n(nodes), adj(nodes) {}
    void addEdge(int u, int v, int cost) {
        adj[u].push_back({v, cost});
        adj[v].push_back({u, cost}); 
    }
};

int heuristic(int node, int goal, const vector<pair<int,int>> &coords) {
    int dx = coords[node].first - coords[goal].first;
    int dy = coords[node].second - coords[goal].second;
    return (int)round(sqrt(dx*dx + dy*dy)); 
}

pair<int, vector<int>> astar(const Graph &g, int start, int goal, const vector<pair<int,int>> &coords) {
    vector<int> best_g(g.n, INT_MAX);
    priority_queue<State, vector<State>, greater<State>> pq;

    int h_start = heuristic(start, goal, coords);
    pq.push({start, 0, h_start, {start}});
    best_g[start] = 0;

    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();

        if (cur.node == goal) {
            return {cur.g, cur.path}; 
        }

        for (auto &e : g.adj[cur.node]) {
            int new_g = cur.g + e.cost;
            if (new_g < best_g[e.to]) {
                best_g[e.to] = new_g;
                int h = heuristic(e.to, goal, coords);
                vector<int> new_path = cur.path;
                new_path.push_back(e.to);
                pq.push({e.to, new_g, new_g + h, new_path});
            }
        }
    }

    return {-1, {}};
}

int main() {
    int nodes, edges;
    cin >> nodes >> edges;
    Graph g(nodes);

    vector<pair<int,int>> coords(nodes);
    for (int i = 0; i < nodes; i++) {
        cin >> coords[i].first >> coords[i].second;
    }

    for (int i = 0; i < edges; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        g.addEdge(u, v, c);
    }

    int start, goal;
    cin >> start >> goal;

    auto [cost, path] = astar(g, start, goal, coords);

    if (cost == -1) {
        cout << "No path found.\n";
    } else {
        cout << "Cost: " << cost << "\nPath: ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i] << (i + 1 < path.size() ? " -> " : "\n");
        }
    }
    return 0;
}
