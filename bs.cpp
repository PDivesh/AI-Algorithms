#include <bits/stdc++.h>
using namespace std;

struct Node {
    int id;
    int cost;
    vector<int> path;
};

bool compareNode(const Node &a, const Node &b) {
    return a.cost < b.cost;
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

    int start, goal, beamWidth;
    cin >> start >> goal >> beamWidth;

    queue<Node> q;
    q.push({start, 0, {start}});
    vector<bool> visited(n, false);
    visited[start] = true;

    while (!q.empty()) {
        vector<Node> candidates;

        while (!q.empty()) {
            Node current = q.front();
            q.pop();
            if (current.id == goal) {
                cout << "Path length: " << current.path.size() - 1 << "\nPath: ";
                for (int v : current.path) cout << v << " ";
                cout << "\n";
                return 0;
            }
            for (int neighbor : graph[current.id]) {
                if (find(current.path.begin(), current.path.end(), neighbor) == current.path.end()) {
                    Node next = {neighbor, current.cost + 1, current.path};
                    next.path.push_back(neighbor);
                    candidates.push_back(next);
                }
            }
        }
        sort(candidates.begin(), candidates.end(), compareNode);
        for (int i = 0; i < min(beamWidth, (int)candidates.size()); i++) {
            q.push(candidates[i]);
        }
    }

    cout << "No path found\n";
    return 0;
}
