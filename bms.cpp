#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

struct Edge {
    int from, to;
};

bool randomPath(const vector<vector<int>> &graph, int start, int goal, vector<int> &path) {
    path.clear();
    path.push_back(start);

    int current = start;
    int limit = graph.size() * 2; 
    while (limit--) {
        if (current == goal) return true;

        if (graph[current].empty()) return false;

        int next = graph[current][rand() % graph[current].size()];

        if (path.size() > graph.size() * 3) return false;

        path.push_back(next);
        current = next;
    }
    return current == goal;
}

int main() {
    srand(time(0));

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
    int attempts = 0;
    while (true) {
        attempts++;
        if (randomPath(graph, start, goal, path)) {
            cout << "Path found after " << attempts << " attempts.\n";
            cout << "Path length: " << path.size() - 1 << "\n";
            cout << "Path: ";
            for (int p : path) cout << p << " ";
            cout << "\n";
            break;
        }
    }

    return 0;
}
