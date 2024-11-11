#include<bits/stdc++.h>
using namespace std;

using Edge = tuple<int, int, int>;

class UnionFind {
    private:
        vector<int> parent, rank;

    public:
        UnionFind(int n) : parent(n), rank(n, 0) {
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }
        }

        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        void unite(int x, int y) {
            int upX = find(x), upY = find(y);
            if (rank[upX] < rank[upY]) {
                parent[upX] = upY;
            } else if (rank[upX] > rank[upY]) {
                parent[upY] = upX;
            } else {
                parent[upY] = upX;
                rank[upX]++;
            }
        }
};

bool isSpanningTree(const vector<Edge>& edges, int numVertices) {
    if (edges.size() != numVertices - 1) return false;

    UnionFind checkMST(numVertices);
    for (const auto& edge : edges) {
        int u = get<0>(edge), v = get<1>(edge);
        if (checkMST.find(u) == checkMST.find(v)) {
            return false;
        }
        checkMST.unite(u, v);
    }

    set<int> components;
    for (int i = 0; i < numVertices; ++i) {
        components.insert(checkMST.find(i));
    }

    return components.size() == 1;
}

vector<Edge> makeEdgeList(const vector<vector<pair<int, int>>>& adjList) {
    vector<Edge> edges;
    for (int u = 0; u < adjList.size(); u++) {
        for (const auto& ele : adjList[u]) {
            if (u < ele.first) { 
                edges.emplace_back(u, ele.first, ele.second);
            }
        }
    }
    return edges;
}

vector<Edge> makeEdgeMat(const vector<vector<int>>& adjMatrix) {
    vector<Edge> edges;
    int n = adjMatrix.size();
    for (int u = 0; u < n; ++u) {
        for (int v = u + 1; v < n; ++v) { 
            if (adjMatrix[u][v] != 0) {  
                edges.emplace_back(u, v, adjMatrix[u][v]);
            }
        }
    }
    return edges;
}

int main() {
    int inputType;
    cout << "Choose input type (0 for Adjacency List, 1 for Adjacency Matrix): ";
    cin >> inputType;
        
    if (inputType != 0 && inputType != 1) {
        cout << "Invalid input type" << endl;
        return -1;
    }


    int numVertices;
    cout << "Enter number of vertices: ";
    cin >> numVertices;

    vector<Edge> edges;

    if (inputType == 0) {
        vector<vector<pair<int, int>>> adjList(numVertices);
        int numEdges;
        cout << "Enter number of edges: ";
        cin >> numEdges;

        cout << "Enter edges in the format (u v weight):" << endl;
        for (int i = 0; i < numEdges; ++i) {
            int u, v, weight;
            cin >> u >> v >> weight;
            adjList[u].emplace_back(v, weight);
            adjList[v].emplace_back(u, weight); 
        }

        edges = makeEdgeList(adjList);

    } else if (inputType == 1) {
        vector<vector<int>> adjMatrix(numVertices, vector<int>(numVertices, 0));

        cout << "Enter adjacency matrix:" << endl;
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                cin >> adjMatrix[i][j];
            }
        }

        edges = makeEdgeMat(adjMatrix);
    }

    bool isMst = isSpanningTree(edges, numVertices);
    cout << "Is valid spanning tree: " << (isMst ? "Yes" : "No") << endl;

    return 0;
}
