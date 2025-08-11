#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>
#include <limits>
using namespace std;

struct Step {
    int node;
    vector<int> path;
};

int heuristic(int current, int goal) {

    return abs(goal - current);
}

void hillClimbWithHistory(const vector<vector<int>>& graph, int start, int goal) {
    unordered_set<int> visited;
    vector<int> path;
    int current = start;
    visited.insert(current);
    path.push_back(current);

    while (current != goal) {
        vector<int> neighbors = graph[current];

        neighbors.erase(remove_if(neighbors.begin(), neighbors.end(),
                                  [&](int n){ return visited.count(n); }),
                        neighbors.end());

        if (neighbors.empty()) {
            cout << "No path found (stuck in local maximum)." << endl;
            return;
        }

        int nextNode = neighbors[0];
        int bestH = heuristic(nextNode, goal);
        for (int n : neighbors) {
            int h = heuristic(n, goal);
            if (h < bestH) {
                bestH = h;
                nextNode = n;
            }
        }

        visited.insert(nextNode);
        path.push_back(nextNode);
        current = nextNode;
    }

    cout << "Path length: " << path.size() - 1 << endl;
    cout << "Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << (i + 1 < path.size() ? " -> " : "\n");
    }
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

    hillClimbWithHistory(graph, start, goal);

    return 0;
}
