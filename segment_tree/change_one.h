#include <bits/stdc++.h>

/*
API
ALL IN LONG

construction - SegTreeChangeOne t(size, func) (func can be one of {"max", "min", "sum", "gcd"})
add(pos, val) - add val to a[pos] (1 - index)
init(pos, new_val) - set a[pos] = new_val (1 - index)
Depends on func:
sum(l, r)  - calc sum of elements with positions [l; r] (1 - index)
max(l, r)  - calc max of elements with positions [l; r] (1 - index)
min(l, r)  - calc min of elements with positions [l; r] (1 - index)
gcd(l, r)  - calc gcd of elements with positions [l; r] (1 - index)
*/

struct SegTreeChangeOne {
    long long myGcd(long long a, long long b) {
        if (a==-1) return b;
        if (b==-1) return a;
        return std::gcd(a,b);
    }

    SegTreeChangeOne(int sz, string function) {
        localSz = sz;
        t.resize(4 * sz + 5);
        func = function;
    }

    long long localMin (int v, int tl, int tr, int l, int r) {
    	if (l > r)
    		return INF;
    	if (l == tl && r == tr)
    		return t[v];
    	int tm = (tl + tr) / 2;
    	return std::min(localMin (v*2, tl, tm, l, std::min(r,tm)), localMin (v*2+1, tm+1, tr, std::max(l,tm+1), r));
    }

    long long localMax (int v, int tl, int tr, int l, int r) {
    	if (l > r)
    		return -INF;
    	if (l == tl && r == tr)
    		return t[v];
    	int tm = (tl + tr) / 2;
    	return std::max(localMax (v*2, tl, tm, l, std::min(r,tm)), localMax (v*2+1, tm+1, tr, std::max(l,tm+1), r));
    }

    int it = 0;

    long long localSum (int v, int tl, int tr, int l, int r) {
    	if (l > r)
    		return 0;
    	if (l == tl && r == tr)
    		return t[v];
    	int tm = (tl + tr) / 2;
    	return localSum (v*2, tl, tm, l, std::min(r,tm)) + localSum (v*2+1, tm+1, tr, std::max(l,tm+1), r);
    }

    long long localGcd (int v, int tl, int tr, int l, int r) {
    	if (l > r)
    		return -1;
    	if (l == tl && r == tr)
    		return t[v];
    	int tm = (tl + tr) / 2;
    	return myGcd(localGcd (v*2, tl, tm, l, std::min(r,tm)), localGcd (v*2+1, tm+1, tr, std::max(l,tm+1), r));
    }

    void localAdd (int v, int tl, int tr, int pos, long long val) {
    	if (tl == tr)
    		t[v] += val;
    	else {
    		int tm = (tl + tr) / 2;
    		if (pos <= tm)
    			localAdd (v*2, tl, tm, pos, val);
    		else
    			localAdd (v*2+1, tm+1, tr, pos, val);
    		if (func == "sum") {
    		    t[v] = t[v*2] + t[v*2+1];
    		}
    		if (func == "max") {
    		    t[v] = std::max(t[v*2], t[v*2+1]);
    		}
    		if (func == "min") {
    		    t[v] = std::min(t[v*2], t[v*2+1]);
    		}
    		if (func == "gcd") {
    		    t[v] = myGcd(t[v*2], t[v*2+1]);
    		}
    	}
    }

    void localInit (int v, int tl, int tr, int pos, long long new_val) {
    	if (tl == tr)
    		t[v] = new_val;
    	else {
    		int tm = (tl + tr) / 2;
    		if (pos <= tm)
    			localInit (v*2, tl, tm, pos, new_val);
    		else
    			localInit (v*2+1, tm+1, tr, pos, new_val);
    		if (func == "sum") {
    		    t[v] = t[v*2] + t[v*2+1];
    		}
    		if (func == "max") {
    		    t[v] = std::max(t[v*2], t[v*2+1]);
    		}
    		if (func == "min") {
    		    t[v] = std::min(t[v*2], t[v*2+1]);
    		}
    		if (func == "gcd") {
    		    t[v] = myGcd(t[v*2], t[v*2+1]);
    		}
    	}
    }



    long long min(int l, int r) {
        return localMin(1, 1, localSz, l,r);
    }

    long long max(int l, int r) {
        return localMax(1, 1, localSz, l,r);
    }

    long long sum(int l, int r) {
        return localSum(1, 1, localSz, l,r);
    }

    long long gcd(int l, int r) {
        return localGcd(1, 1, localSz, l,r);
    }

    void add(int pos, long long val) {
        localAdd(1, 1, localSz, pos, val);
    }

    void init(int pos, long long new_val) {
        localInit(1, 1, localSz, pos, new_val);
    }

    vector <long long> t;
    int localSz;
    const long long INF = 9223372036000000000LL;
    string func;
};
