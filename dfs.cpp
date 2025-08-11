#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

bool dfsUtil(const vector<vector<int>> &graph, int start, int goal, vector<int> &path) {
    vector<bool> visited(graph.size(), false);
    vector<int> parent(graph.size(), -1);
    stack<int> s;

    s.push(start);
    visited[start] = true;

    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (node == goal) {
            path.clear();
            for (int v = goal; v != -1; v = parent[v])
                path.push_back(v);
            reverse(path.begin(), path.end());
            return true;
        }

        for (int neigh : graph[node]) {
            if (!visited[neigh]) {
                visited[neigh] = true;
                parent[neigh] = node;
                s.push(neigh);
            }
        }
    }
    return false;
}

int main() {
    int nodes, edges;
    cin >> nodes >> edges;

    vector<vector<int>> graph(nodes);
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); 
    }

    int start, goal;
    cin >> start >> goal;

    vector<int> path;
    if (dfsUtil(graph, start, goal, path)) {
        cout << "Path length: " << path.size() - 1 << "\n";
        cout << "Path: ";
        for (int p : path) cout << p << " ";
        cout << "\n";
    } else {
        cout << "No path found.\n";
    }

    return 0;
}
