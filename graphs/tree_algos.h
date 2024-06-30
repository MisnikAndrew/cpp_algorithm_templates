#include <bits/stdc++.h>

/*
API

0-index or 1-index, doesn't matter

centroid(g) - return vector of vertex numbers which are centroids of given tree
// centroid - each component is <=n/2 size after deleting vertex
O(n) complexity

centers(g) - return vector of vertex numbers which are centers of given tree
// center - maximal distance from vertex is minimal
O(n) complexity

diameter(g) - return diameter of given tree
// diameter - maximal distance between two vertexes in graph

g - vector of vectors of edges
*/

void dfsImplCentroids(int v, int parent, const vector<vector<int>> &g, vector<int> &subtree_size, vector<int> &centroids, int n) {
    subtree_size[v] = 1;
    bool is_centroid = true;
    for (int u : g[v]) {
        if (u == parent) continue;
        dfsImplCentroids(u, v, g, subtree_size, centroids, n);
        subtree_size[v] += subtree_size[u];
        if (subtree_size[u] > n / 2) is_centroid = false;
    }
    if ((n - subtree_size[v]) > n / 2) is_centroid = false;
    if (is_centroid) centroids.push_back(v);
}

vector<int> centroids(const vector<vector<int>> &g) {
    int n = g.size();
    vector<int> subtree_size(n);
    vector<int> centroids;
    dfsImplCentroids(0, -1, g, subtree_size, centroids, n);
    return centroids;
}

std::vector<int> centers(const std::vector<std::vector<int>>& g) {
    int n = g.size();
    std::vector<int> degree(n, 0);
    std::vector<int> leaves;

    for (int i = 0; i < n; ++i) {
        degree[i] = g[i].size();
        if (degree[i] == 1) {
            leaves.push_back(i);
        }
    }

    int processed = leaves.size();
    while (processed < n) {
        std::vector<int> new_leaves;
        for (int leaf : leaves) {
            for (int neighbor : g[leaf]) {
                --degree[neighbor];
                if (degree[neighbor] == 1) {
                    new_leaves.push_back(neighbor);
                }
            }
            --degree[leaf];
        }
        processed += new_leaves.size();
        leaves = std::move(new_leaves);
    }

    return leaves;
}


pair<int, int> bfsImplDiameter(int start, const vector<vector<int>>& g) {
    int n = g.size();
    vector<int> distance(n, -1);
    queue<int> q;

    q.push(start);
    distance[start] = 0;
    int farthestNode = start;
    int maxDistance = 0;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor : g[node]) {
            if (distance[neighbor] == -1) {
                q.push(neighbor);
                distance[neighbor] = distance[node] + 1;
                if (distance[neighbor] > maxDistance) {
                    maxDistance = distance[neighbor];
                    farthestNode = neighbor;
                }
            }
        }
    }

    return {farthestNode, maxDistance};
}

int diameter(const vector<vector<int>>& g) {
    pair<int, int> firstBFS = bfsImplDiameter(0, g);
    pair<int, int> secondBFS = bfsImplDiameter(firstBFS.first, g);
    return secondBFS.second;
}