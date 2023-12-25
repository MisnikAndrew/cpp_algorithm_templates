#include <bits/stdc++.h>

/*
API
get_cycle(g).

return vector with vertexes from cycle
empty <=> no cycle
*/

vector<int> get_cycle(vector<vector<int>>& g) {
    int n = g.size();
    vector <int> p(n);
    vector <bool> used(n);
    queue <int> q;
    int find = -1;
    for (int i = 0; (find == -1) && (i < n); ++i) {
        if (!used[i]) {
            used[i] = true;
            p[i] = -1;
            q.push(i);
            while (!q.empty()) {
                int c = q.front();
                q.pop();
                for (auto v : g[c]) {
                    if (!used[v]) {
                        used[v] = true;
                        q.push(v);
                        p[v] = c;
                    } else {
                        p[v] = c;
                        find = v;
                        break;
                    }
                }
            }
        }
    }
    vector <int> ans;
    if (find != -1) {
        ans.push_back(find);
        int cur = p[find];
        while (cur != find) {
            ans.push_back(cur);
            cur = p[cur];
        }

    }
    reverse(ans.begin(), ans.end());
    return ans;
}
