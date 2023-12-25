#include <bits/stdc++.h>

/*
API
ALL IN LONG

mst_dsu(g) - constructor
mst_dsu(edges) - constructor from vector of edges ({v1, v2, cost})

mst_dsu.calc() - calculate cost and result edges
(long long) mst_dsu.cost - get cost after calculation
(vector <pair<long long, long long>>) mst_dsu.res - get result edges after calculation
*/

const long long INF = 9223372036000000000LL;

struct mst_dsu {
    long long cost;
    vector <pair<long long, long long>> res;




    vector<vector<pair<long long, long long>>> g;
    vector<int> p;

    int dsu_get (int v) {
    	return (v == p[v]) ? v : (p[v] = dsu_get (p[v]));
    }

    void dsu_unite (int a, int b) {
    	a = dsu_get (a);
    	b = dsu_get (b);
    	if (rand() & 1)
    		swap (a, b);
    	if (a != b)
    		p[a] = b;
    }

    mst_dsu(vector<vector<pair<long long, long long>>> graph) {
        g = graph;
        calc();
    }

    mst_dsu(int n, vector<vector<long long>> edges) {
        g.resize(n);
        for (auto& e : edges) {
            g[e[1]].push_back({e[2], e[0]});
            g[e[2]].push_back({e[1], e[0]});
        }
        calc();
    }

    void calc() {
        vector <vector<long long>> edges;
        int n = g.size();
        for (int i = 0; i < n; ++i) {
            for (auto& v : g[i]) {
                edges.push_back({v.second, i, v.first});
            }
        }
        sort(edges.begin(), edges.end());
        int m = edges.size();
        cost = 0;

        sort (g.begin(), g.end());
        p.resize (n);
        for (int i=0; i<n; ++i)
        	p[i] = i;
        for (int i=0; i<m; ++i) {
            long long l = edges[i][0];
            long long a = edges[i][1];
            long long b = edges[i][2];
        	if (dsu_get(a) != dsu_get(b)) {
        		cost += l;
        		res.push_back ({a, b});
        		dsu_unite (a, b);
        	}
        }
    }
};
