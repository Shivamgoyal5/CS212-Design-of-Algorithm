// ford fulkerson via bfs

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Helper function to perform BFS to find an augmenting path
bool bfs(const vector<vector<int> >& residualGraph, int s, int t, vector<int>& parent) {
    int n = residualGraph.size();
    vector<bool> visited(n, false);
    queue<int> q;

    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; v++) {
            // If there is an available capacity and the node v is not visited
            if (!visited[v] && residualGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;

                if (v == t) return true;  // Found a path to the sink
            }
        }
    }
    return false;  // No augmenting path found
}

// Ford-Fulkerson algorithm to compute maximum flow
int fordFulkerson(vector<vector<int> >& graph, int s, int t) {
    int n = graph.size();
    vector<vector<int> > residualGraph = graph;  // Create a residual graph
    vector<int> parent(n);  // To store the path

    int maxFlow = 0;

    // Augment the flow while there is an augmenting path
    while (bfs(residualGraph, s, t, parent)) {
        // Find the maximum flow in the path found by BFS
        int pathFlow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        // Update residual capacities of the edges and reverse edges along the path
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        // Add path flow to the overall flow
        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main() {
    int n;  // Number of vertices
    cout << "Enter the number of vertices: ";
    cin >> n;

    vector<vector<int> > graph(n, vector<int>(n));
    cout << "Enter the capacity matrix (0 if no edge exists):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout<<"capacity between node "<<i<<" and "<<j<<":";
            cin >> graph[i][j];
        }
    }

    int source = 0;
    int sink = n - 1;

    cout << "The maximum possible flow is " << fordFulkerson(graph, source, sink) << endl;
}
