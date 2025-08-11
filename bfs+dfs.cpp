#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

bool bfs(const vector<vector<int>> &graph, int start, int goal, vector<int> &path) {
    vector<bool> visited(graph.size(), false);
    vector<int> parent(graph.size(), -1);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

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
                q.push(neigh);
            }
        }
    }
    return false;
}

bool dfs(const vector<vector<int>> &graph, int start, int goal, vector<int> &path) {
    vector<bool> visited(graph.size(), false);
    vector<int> parent(graph.size(), -1);
    stack<int> s;

    visited[start] = true;
    s.push(start);

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
        graph[v].push_back(u); // undirected
    }

    int start, goal;
    cin >> start >> goal;

    vector<int> bfsPath, dfsPath;
    bool bfsFound = bfs(graph, start, goal, bfsPath);
    bool dfsFound = dfs(graph, start, goal, dfsPath);

    cout << "=== BFS Result ===\n";
    if (bfsFound) {
        cout << "Path length: " << bfsPath.size() - 1 << "\nPath: ";
        for (int p : bfsPath) cout << p << " ";
        cout << "\n";
    } else {
        cout << "No path found.\n";
    }

    cout << "=== DFS Result ===\n";
    if (dfsFound) {
        cout << "Path length: " << dfsPath.size() - 1 << "\nPath: ";
        for (int p : dfsPath) cout << p << " ";
        cout << "\n";
    } else {
        cout << "No path found.\n";
    }

    // Efficiency note
    if (bfsFound && dfsFound) {
        cout << "BFS found the shortest path.\n";
        if (dfsPath.size() < bfsPath.size())
            cout << "DFS unexpectedly found a shorter path (due to graph structure).\n";
    }

    return 0;
}
