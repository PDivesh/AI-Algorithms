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

pair<int, vector<int>> branch_and_bound_heuristic(
    const Graph &g, int start, int goal, const vector<int> &heuristic) 
{
    int best_cost = INT_MAX;
    vector<int> best_path;

    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({start, 0, heuristic[start], {start}});

    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();

        if (cur.f >= best_cost) continue;

        if (cur.node == goal) {
            if (cur.g < best_cost) {
                best_cost = cur.g;
                best_path = cur.path;
            }
            continue;
        }

        for (auto &e : g.adj[cur.node]) {
            if (find(cur.path.begin(), cur.path.end(), e.to) == cur.path.end()) {
                int new_g = cur.g + e.cost;
                int new_f = new_g + heuristic[e.to];
                if (new_f < best_cost) {
                    vector<int> new_path = cur.path;
                    new_path.push_back(e.to);
                    pq.push({e.to, new_g, new_f, new_path});
                }
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

    vector<int> heuristic(nodes);
    for (int i = 0; i < nodes; i++) {
        cin >> heuristic[i];
    }

    int start, goal;
    cin >> start >> goal;

    auto [cost, path] = branch_and_bound_heuristic(g, start, goal, heuristic);

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
