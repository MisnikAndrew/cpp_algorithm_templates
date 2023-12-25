/*
API
ALL IN LONG

construction - SegTreeChangeManyGetOne t(size)
add(l, r, val) - add val to all elements with positions [l; r] (1 - index)
get(pos) - get value of a[pos] (1 - index)
*/

struct SegTreeChangeManyGetOne {

    SegTreeChangeManyGetOne(int sz) {
        localSz = sz;
        t.resize(4 * sz + 5);
    }

    void localAdd(int v, int tl, int tr, int l, int r, long long add) {
    	if (l > r)
		return;
	if (l == tl && tr == r)
		t[v] += add;
	else {
		int tm = (tl + tr) / 2;
		localAdd (v*2, tl, tm, l, min(r,tm), add);
		localAdd (v*2+1, tm+1, tr, max(l,tm+1), r, add);
	}
    }

    long long localGet(int v, int tl, int tr, int pos) {
	if (tl == tr)
		return t[v];
	int tm = (tl + tr) / 2;
	if (pos <= tm)
		return t[v] + localGet (v*2, tl, tm, pos);
	else
		return t[v] + localGet (v*2+1, tm+1, tr, pos);
}

    void add(int l, int r, long long val) {
        localAdd(1, 1, localSz, l, r, val);
    }

    long long get(int pos) {
        return localGet(1, 1, localSz, pos);
    }

    vector <long long> t;
    int localSz;
    const long long INF = 9223372036000000000LL;
};
