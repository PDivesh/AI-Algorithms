#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

struct Edge {
    int to;
    int cost;
};

struct State {
    int node;
    int g; 
    vector<int> path;
    bool operator>(const State &other) const {
        return g > other.g; 
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

pair<int, vector<int>> branch_and_bound_history(const Graph &g, int start, int goal) {
    int best_cost = INT_MAX;
    vector<int> best_path;

    vector<int> best_to_node(g.n, INT_MAX);

    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({start, 0, {start}});
    best_to_node[start] = 0;

    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();

        if (cur.g >= best_cost) continue; 

        if (cur.node == goal) {
            best_cost = cur.g;
            best_path = cur.path;
            continue;
        }

        for (auto &e : g.adj[cur.node]) {
            int new_g = cur.g + e.cost;
            if (new_g < best_to_node[e.to]) { 
                best_to_node[e.to] = new_g;
                vector<int> new_path = cur.path;
                new_path.push_back(e.to);
                pq.push({e.to, new_g, new_path});
            }
        }
    }

    if (best_path.empty()) return {-1, {}};
    return {best_cost, best_path};
}

int main() {
    int nodes, edges;
    cin >> nodes >> edges;
    Graph g(nodes);

    for (int i = 0; i < edges; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        g.addEdge(u, v, c);
    }

    int start, goal;
    cin >> start >> goal;

    auto [cost, path] = branch_and_bound_history(g, start, goal);

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
