#include <bits/stdc++.h>

/*
API
ALL IN LONG
djkstra(g, start).

return an array with distances from start to all other vertexes
pairs in g - {vertex_id, weight}
*/

long long UNDEF = -1;
vector <long long> djkstra(vector<vector<pair<long long,long long>>>& g, int start = 0) {
    int n = g.size();
    const long long INF = 9223372036000000000LL;
	vector <long long> d(n, INF);
	vector <long long> p(n);
	d[start] = 0;
	priority_queue <pair<long long,long long>> q;
	q.push ({0, start});
	while (!q.empty()) {
		long long v = q.top().second;
		long long cur_d = -q.top().first;
		q.pop();
		if (cur_d > d[v])  continue;
		for (int j=0; j<g[v].size(); ++j) {
			long long to = g[v][j].first;
			long long len = g[v][j].second;
			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
				p[to] = v;
				q.push ({-d[to], to});
			}
		}
	}
	for (int i = 0; i < n; ++i) {
	    if (d[i] == INF) {
	        d[i] = UNDEF;
	    }
	}
	return d;
}
