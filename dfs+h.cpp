#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

bool dfsWithHistory(const vector<vector<int>> &graph, int start, int goal,
                    vector<int> &path, vector<int> &history) {
    vector<bool> visited(graph.size(), false);
    vector<int> parent(graph.size(), -1);
    stack<int> s;

    visited[start] = true;
    s.push(start);
    history.push_back(start);

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
                history.push_back(neigh);
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

    vector<int> path, history;
    if (dfsWithHistory(graph, start, goal, path, history)) {
        cout << "Path length: " << path.size() - 1 << "\nPath: ";
        for (int p : path) cout << p << " ";
        cout << "\nVisited order: ";
        for (int h : history) cout << h << " ";
        cout << "\n";
    } else {
        cout << "No path found.\nVisited order: ";
        for (int h : history) cout << h << " ";
        cout << "\n";
    }

    return 0;
}
