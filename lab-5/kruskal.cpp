#include<bits/stdc++.h>
using namespace std;

using Edge = tuple<int, int, int>;

class UnionFind {
    private:
        vector<int> parent, rank;

    public:
        UnionFind(int n) : parent(n), rank(n, 0) {
            for (int i = 0; i < n; i++) parent[i] = i;
        }

        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x]; 
        }

        void unite(int x, int y) {
            int upX = find(x), upY = find(y);
            if (upX != upY) {  
                if (rank[upX] < rank[upY]) {
                    parent[upX] = upY;
                } else if (rank[upX] > rank[upY]) {
                    parent[upY] = upX;
                } else {
                    parent[upY] = upX;
                    rank[upX]++;
                }
            }
        }
};

tuple<vector<Edge>, int> Kruskal(vector<Edge>& graphEdges, int V) {
    sort(graphEdges.begin(), graphEdges.end(), 
        [](const Edge& a, const Edge& b) { return get<2>(a) < get<2>(b); });

    UnionFind uf(V);
    vector<Edge> mst;
    int totWeight = 0;

    for (const auto& edge : graphEdges) {
        int u = get<0>(edge), v = get<1>(edge), w = get<2>(edge);
        if (uf.find(u) != uf.find(v)) {
            uf.unite(u, v);
            mst.push_back(edge);
            totWeight += w;
        }
    }

    return {mst, totWeight};
}

int main() {
    vector<Edge> graphEdges = {{0, 1, 4}, {0, 2, 3}, {1, 2, 1}, {1, 3, 2}, {2, 3, 4}};
    int V = 4;

    tuple<vector<Edge>, int> result = Kruskal(graphEdges, V);
    vector<Edge> mst = get<0>(result);
    int totWeight = get<1>(result);

    cout << "Kruskal's MST edges:" << endl;
    for (const auto& edge : mst) {
        cout << get<0>(edge) << " - " << get<1>(edge) << " : " << get<2>(edge) << endl;
    }
    cout << "Total weight: " << totWeight << endl;

    return 0;
}