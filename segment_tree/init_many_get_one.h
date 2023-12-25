#include <bits/stdc++.h>

/*
API
ALL IN LONG

construction - SegTreeInitManyGetOne t(size)
init(l, r, new_val) - set a[i] = new_val for i in [l;r] (1 - index)
get(pos) - get value of a[pos] (1 - index)
*/

struct SegTreeInitManyGetOne {

    SegTreeInitManyGetOne(int sz) {
        localSz = sz;
        t.resize(4 * sz + 5);
    }

    void push (int v) {
    	if (t[v] != -1) {
    		t[v*2] = t[v*2+1] = t[v];
    		t[v] = -1;
    	}
    }

    void localInit(int v, int tl, int tr, int l, int r, int new_val) {
    	if (l > r)
    		return;
    	if (l == tl && tr == r)
    		t[v] = new_val;
    	else {
    		push (v);
    		int tm = (tl + tr) / 2;
    		localInit (v*2, tl, tm, l, min(r,tm), new_val);
    		localInit (v*2+1, tm+1, tr, max(l,tm+1), r, new_val);
    	}
    }

    long long localGet(int v, int tl, int tr, int pos) {
    	if (tl == tr)
    		return t[v];
    	push(v);
    	int tm = (tl + tr) / 2;
    	if (pos <= tm)
    		return localGet (v*2, tl, tm, pos);
    	else
    		return localGet (v*2+1, tm+1, tr, pos);
    }

    void init(int l, int r, long long new_val) {
        localInit(1, 1, localSz, l, r, new_val);
    }

    long long get(int pos) {
        return localGet(1, 1, localSz, pos);
    }

    vector <long long> t;
    int localSz;
    const long long INF = 9223372036000000000LL;
};
