#include <bits/stdc++.h>

/*
API

0-index or 1-index, doesn't matter

bfs<true>(int n) - construct DIRECTED graph with n vertexes
bfs<false>(int n) - construct UNDIRECTED graph with n vertexes

bfs.add_edge(from, to) - add edge from -> to to graph (and to -> from if undirected)

bfs.dist(sources) - return vector of distances from closest of vertexes from sources

bfs.dist(v1, v2) - return distance from v1 to v2 (-1 if unreachable)

bfs.path(v1, v2) - return vector of path from v1 to v2 (empty if unreachable)

bfs.get_comps() - return array of component numbers in graph (comp[i] = comp[j] <=> i and j in one component) (ONLY UNDIRECTED)

bfs.get_cycle() - return vector with vertexes from cycle (empty <=> no cycle)

bfs.get_parents(root = 0) - return array of parents in graph (root is number of root, parent(root) = -1)
*/

template <bool directed = true>
struct bfs {
    int n;
    vector<vector<int>> edges;
    bfs() {}
    bfs(int N) {
        n = N;
        edges.resize(n+1);
    }

    void add_edge(int from, int to) {
        edges[from].push_back(to);
        if (!directed) edges[to].push_back(from);
    }

    vector<int> dist(vector<int> sources) {
        vector<int> res(n+1, -1);
        queue<int> q;
        for (int i : sources) {
            res[i] = 0;
            q.push(i);
        }
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int i : edges[cur]) {
                if (res[i] == -1) {
                    res[i] = res[cur]+1;
                    q.push(i);
                }
            }
        }
        return res;
    }

    int dist(int source, int dest) {
        return dist({source})[dest];
    }

    vector<int> path(int source, int dest) {
        vector<int> res(n+1, -1);
        vector<int> before(n+1);
        queue<int> q;
        res[source] = 0;
        q.push(source);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int i : edges[cur]) {
                if (res[i] == -1) {
                    res[i] = res[cur]+1;
                    before[i] = cur;
                    q.push(i);
                }
            }
        }
        if (res[dest] == -1) return {};
        vector<int> path = {dest};
        while (path.back() != source) path.push_back(before[path.back()]);
        reverse(path.begin(), path.end());
        return path;
    }

    vector <int> get_comps() {
        vector <int> used(n + 1);
        queue <int> q;
        vector <int> comp(n + 1);
        int cur = 0;
        for (int i = 0; i < n + 1; ++i) {
            if (!used[i]) {
                comp[i] = cur;
                used[i] = true;
                q.push(i);
                while (!q.empty()) {
                    int c = q.front();
                    q.pop();
                    for (auto& v : edges[c]) {
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

    vector<int> get_cycle() {
        vector <int> p(n + 1);
        vector <bool> used(n + 1);
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
                    for (auto v : edges[c]) {
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

    vector <int> get_parents(int root = 0) {
        vector <int> used(n + 1);
        queue <int> q;
        vector <int> p(n + 1);
        q.push(root);
        used[root] = true;
        p[root] = -1;
        while (!q.empty()) {
            int c = q.front();
            q.pop();
            for (auto& v : edges[c]) {
                if (!used[v]) {
                    used[v] = true;
                    q.push(v);
                    p[v] = c;
                }
            }
        }
        return p;
    }
};
