#include <bits/stdc++.h>

/*
API

get_comps(g).
g is an array of edges
Get array of component numbers in graph (comp[i] = comp[j] <=> i and j in one component)
*/

vector <int> get_comps(vector<vector<int>> g) {
    int n = g.size();
    vector <int> used(n);
    queue <int> q;
    vector <int> comp(n);
    int cur = 0;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            comp[i] = cur;
            used[i] = true;
            q.push(i);
            while (!q.empty()) {
                int c = q.front();
                q.pop();
                for (auto& v : g[c]) {
                    if (!used[v]) {
                        used[v] = true;
                        q.push(v);
                        comp[v] = cur;
                    }
                }
            }
            cur++;
        }
    }
    return comp;
}
