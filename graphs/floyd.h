#include <bits/stdc++.h>

/*
API
ALL IN LONG
floyd(g).

pairs in g - {vertex_id, weight}

return matrix with distances between all vertexes
*/

const long long INF = 9223372036000000000LL;

vector <vector<long long>> floyd(vector<vector<pair<long long, long long>>> g) {
    int n = g.size();
    vector <vector<long long>> ans(n, vector <long long> (n, INF));
    for (int i = 0; i < g.size();i++) {
        for (auto& v : g[i]) {
            ans[i][v.first] = min(ans[i][v.first], v.second);
        }
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (ans[i][k] < INF && ans[k][j] < INF) {
                    ans[i][j] = min(ans[i][j], ans[i][k] + ans[k][j]);
                }
            }
        }
    }
    return ans;
}