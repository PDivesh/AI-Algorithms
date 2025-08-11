#include <bits/stdc++.h>
using namespace std;

struct Node {
    int vertex;
    vector<int> path;
};

vector<int> beamSearchHistory(const vector<vector<int>>& graph, int start, int goal, int beamWidth) {
    queue<Node> q;
    set<int> visited;

    q.push({start, {start}});
    visited.insert(start);

    while (!q.empty()) {
        vector<Node> levelNodes;

        int levelSize = q.size();
        while (levelSize--) {
            Node current = q.front();
            q.pop();

            if (current.vertex == goal) {
                return current.path;
            }

            for (int neighbor : graph[current.vertex]) {
                if (!visited.count(neighbor)) {
                    vector<int> newPath = current.path;
                    newPath.push_back(neighbor);
                    levelNodes.push_back({neighbor, newPath});
                    visited.insert(neighbor);
                }
            }
        }

        sort(levelNodes.begin(), levelNodes.end(),
             [goal](const Node& a, const Node& b) {
                 return abs(a.vertex - goal) < abs(b.vertex - goal);
             });

        for (int i = 0; i < min(beamWidth, (int)levelNodes.size()); i++) {
            q.push(levelNodes[i]);
        }
    }
    return {};
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    int start, goal;
    cin >> start >> goal;

    int beamWidth;
    cin >> beamWidth; 

    vector<int> path = beamSearchHistory(graph, start, goal, beamWidth);

    if (!path.empty()) {
        cout << "Path length: " << path.size() - 1 << "\nPath: ";
        for (int node : path) cout << node << " ";
        cout << "\n";
    } else {
        cout << "No path found\n";
    }
    return 0;
}
