#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

struct State {
    int node;
    int cost;
    vector<int> path;
    bool operator>(const State &other) const {
        return cost > other.cost; 
    }
};

struct Graph {
    int n;
    vector<vector<int>> adj;
    Graph(int nodes) : n(nodes), adj(nodes) {}
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); 
    }
};

pair<int, vector<int>> branch_and_bound(const Graph &g, int start, int goal) {
    int best_cost = INT_MAX;
    vector<int> best_path;

    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({start, 0, {start}});

    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();

        // prune
        if (cur.cost >= best_cost) continue;

        if (cur.node == goal) {
            best_cost = cur.cost;
            best_path = cur.path;
            continue; 
        }

        for (int neigh : g.adj[cur.node]) {
            if (find(cur.path.begin(), cur.path.end(), neigh) == cur.path.end()) {
                vector<int> new_path = cur.path;
                new_path.push_back(neigh);
                pq.push({neigh, cur.cost + 1, new_path});
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
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int start, goal;
    cin >> start >> goal;

    auto [cost, path] = branch_and_bound(g, start, goal);

    if (cost == -1) {
        cout << "No path found.\n";
    } else {
        cout << "Path length: " << cost << "\n";
        cout << "Path: ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i] << (i + 1 < path.size() ? " -> " : "\n");
        }
    }
    return 0;
}
