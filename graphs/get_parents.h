#include <bits/stdc++.h>

/*
API

get_parents(g, root = 0).
g is an array of edges, root is number of root (in trees, for example)
Get array of parents in graph (parent(root) = -1)
*/


vector <int> get_parents(vector<vector<int>> g, int root = 0) {
    int n = g.size();
    vector <int> used(n);
    queue <int> q;
    vector <int> p(n);
    q.push(root);
    used[root] = true;
    p[root] = -1;
    while (!q.empty()) {
        int c = q.front();
        q.pop();
        for (auto& v : g[c]) {
            if (!used[v]) {
                used[v] = true;
                q.push(v);
                p[v] = c;
            }
        }
    }
    return p;
}