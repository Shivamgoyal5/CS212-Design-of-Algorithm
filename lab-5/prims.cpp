#include<bits/stdc++.h>

using namespace std;
using Edge = tuple<int, int, int>;

tuple<vector<Edge>, int> Prims(const vector<vector<int>>& graphMat) {
    int n = graphMat.size();
    vector<bool> visited(n, false);
    vector<Edge> mst;
    int totWeight = 0;

    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    pq.push(make_tuple(0, 0, -1));

    while (!pq.empty() && mst.size() < n - 1) {
        Edge topEdge = pq.top();
        pq.pop();

        int w = get<0>(topEdge);
        int v = get<1>(topEdge);
        int u = get<2>(topEdge);

        if (visited[v]) {
            continue;
        }
        visited[v] = true;

        if (u != -1) {
            mst.push_back(make_tuple(u, v, w));
            totWeight += w;
        }

        for (int i = 0; i < n; i++) {
            if (!visited[i] && graphMat[v][i] != numeric_limits<int>::max()) {
                pq.push(make_tuple(graphMat[v][i], i, v));
            }
        }
    }

    return make_tuple(mst, totWeight);
}

int main() {
    vector<vector<int>> graphMat = {
        {0, 4, 3, numeric_limits<int>::max()},
        {4, 0, 1, 2},
        {3, 1, 0, 4},
        {numeric_limits<int>::max(), 2, 4, 0}
    };

    tuple<vector<Edge>, int> result = Prims(graphMat);
    vector<Edge> mst = get<0>(result);
    int totWeight = get<1>(result);

    cout << "Prim's MST edges:" << endl;
    for (const auto& edge : mst) {
        int from = get<0>(edge);
        int to = get<1>(edge);
        int weight = get<2>(edge);
        cout << from << " - " << to << " : " << weight << endl;
    }

    cout << "Total weight: " << totWeight << endl;

    return 0;
}