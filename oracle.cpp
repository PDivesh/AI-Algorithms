#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Graph {
    int n;
    vector<vector<int>> adj;
    Graph(int nodes) : n(nodes), adj(nodes) {}
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); 
    }
};

vector<int> oracle_path(const Graph &g, int start, int goal) {
    vector<int> parent(g.n, -1);
    queue<int> q;
    q.push(start);
    parent[start] = start;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == goal) break;
        for (int v : g.adj[u]) {
            if (parent[v] == -1) {
                parent[v] = u;
                q.push(v);
            }
        }
    }

    vector<int> path;
    if (parent[goal] == -1) return path;

    for (int cur = goal; cur != start; cur = parent[cur]) {
        path.push_back(cur);
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
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

    vector<int> path = oracle_path(g, start, goal);

    if (path.empty()) {
        cout << "No path found by oracle.\n";
    } else {
        cout << "Path length: " << (path.size() - 1) << "\n";
        cout << "Path: ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i] << (i + 1 < path.size() ? " -> " : "\n");
        }
    }

    return 0;
}
