#include <bits/stdc++.h>


/*
API
ALL IN LONG
ford_bellman_graph(g, start = 0).
pairs in g - {vertex_id, weight}
return vector with distances from start to other vertexes


ford_bellman(n, edges, start = 0).
vectors in edges - {from, to, weight}
return vector with distances from start to other vertexes
*/


const long long INF = 9223372036000000000LL;
const long long UNDEF = INF;

vector<long long> ford_bellman(int n, vector <vector<long long>>& edges, int start = 0) {
    vector <long long> d(n, INF);
    d[start] = 0;
	for (int i=0; i<n-1; ++i) {
	    for (auto& e : edges) {
	        if (d[e[0]] < INF) {
	            d[e[1]] = min(d[e[1]], d[e[0]] + e[2]);
	        }
	    }
	}
	return d;
}

vector<long long> ford_bellman_graph(vector<vector<pair<long long, long long>>>& g, int start = 0) {
    int n = g.size();
    vector <vector<long long>> edges;
    for (int i = 0; i < n; ++i) {
        for (auto& e : g[i]) {
            edges.push_back({i, e.first, e.second});
        }
    }
    return ford_bellman(n, edges, start);
}