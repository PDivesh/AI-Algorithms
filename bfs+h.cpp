#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
using namespace std;

struct Node {
    int id;
    vector<int> path; 
};

int main() {
    int n, e;
    cin >> n >> e;

    vector<vector<int>> graph(n);
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int start, goal, beam_width;
    cin >> start >> goal >> beam_width;

    queue<Node> q;
    unordered_set<int> visited;

    q.push({start, {start}});
    visited.insert(start);

    while (!q.empty()) {
        vector<Node> level_nodes;

        while (!q.empty()) {
            level_nodes.push_back(q.front());
            q.pop();
        }
        sort(level_nodes.begin(), level_nodes.end(),
             [&](const Node &a, const Node &b) {
                 return abs(a.id - goal) < abs(b.id - goal);
             });

        if ((int)level_nodes.size() > beam_width)
            level_nodes.resize(beam_width);

        for (auto &node : level_nodes) {
            if (node.id == goal) {
                cout << "Path length: " << node.path.size() - 1 << "\nPath: ";
                for (int v : node.path) cout << v << " ";
                cout << "\n";
                return 0;
            }

            for (int nei : graph[node.id]) {
                if (!visited.count(nei)) {
                    visited.insert(nei);
                    auto new_path = node.path;
                    new_path.push_back(nei);
                    q.push({nei, new_path});
                }
            }
        }
    }

    cout << "No path found.\n";
    return 0;
}
