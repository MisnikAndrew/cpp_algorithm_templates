#include <bits/stdc++.h>

/*
API
ALL IN LONG

construction - SegTreeChangeManyInitMany t(size, func) (func can be one of {"max", "min", "sum"})
add(l, r, val) - add val to a[l..r] (1 - index)
init(l, r, new_val) - set all values a[l..r] to new_val (1 - index)
Depends on func:
sum(l, r)  - calc sum of elements with positions [l; r] (1 - index)
max(l, r)  - calc max of elements with positions [l; r] (1 - index)
min(l, r)  - calc min of elements with positions [l; r] (1 - index)
*/

struct SegTreeChangeManyInitMany {
    SegTreeChangeManyInitMany(int sz, string func) {
        localSz = sz;
        if (func == "sum") {
            localFunc = 1;
        }
        if (func == "min") {
            localFunc = 2;
        }
        if (func == "max") {
            localFunc = 3;
        }

        t.resize(4 * sz + 5);
        lset.resize(4 * sz + 5);
        ladd.resize(4 * sz + 5);
        uset.resize(4 * sz + 5);
        uadd.resize(4 * sz + 5);
    }

    void localPush (long long k, long long l, long long r) {
        long long mid = (l+r)/2;
        if (uset[k]) {
            t[k*2] = lset[k] * (localFunc == 1 ? (mid-l+1) : 1);
            t[k*2+1] = lset[k] * (localFunc == 1 ? (r-mid) : 1);

            lset[k*2] = lset[k];
            lset[k*2+1] = lset[k];
            lset[k] = 0;

            ladd[k*2] = 0;
            ladd[k*2+1] = 0;

            uset[k] = false;
            uset[k*2] = true;
            uset[k*2+1] = true;
        }

        if (uadd[k]) {
            t[k*2] += ladd[k] * (localFunc == 1 ? (mid-l+1) : 1);
            t[k*2+1] += ladd[k] * (localFunc == 1 ? (r-mid) : 1);

            ladd[k*2] += ladd[k];
            ladd[k*2+1] += ladd[k];
            ladd[k] = 0;

            uadd[k] = false;
            uadd[k*2] = true;
            uadd[k*2+1] = true;
        }
    }

    void localAdd(long long a, long long b, long long x, long long l, long long r, long long k) {
        if (b < l || r < a) {
            return;
        }
        if (a <= l && r <= b) {
            t[k] += x * (localFunc == 1 ? (r-l+1) : 1);
            ladd[k] += x;
            uadd[k] = true;
            return;
        }

        localPush(k, l, r);
        long long mid = (l+r)/2;
        localAdd(a, b, x, l, mid, k*2);
        localAdd(a, b, x, mid+1, r, k*2+1);
        switch (localFunc) {
            case 1:
                t[k] = t[k*2] + t[k*2+1];
                return;
            case 2:
                t[k] = std::min(t[k*2], t[k*2+1]);
                return;
            case 3:
                t[k] = std::max(t[k*2], t[k*2+1]);
                return;
            default:
                exit(1);
        }
    }

    void localSet (long long a, long long b, long long x, long long l, long long r, long long k) {
        if (b < l || r < a) {
            return;
        }
        if (a <= l && r <= b) {
            t[k] = x * (localFunc == 1 ? (r-l+1) : 1);
            ladd[k] = 0;
            uadd[k] = false;
            lset[k] = x;
            uset[k] = true;
            return;
        }

        localPush(k, l, r);
        long long mid = (l+r)/2;
        localSet(a, b, x, l, mid, k*2);
        localSet(a, b, x, mid+1, r, k*2+1);
        switch (localFunc) {
            case 1:
                t[k] = t[k*2] + t[k*2+1];
                return;
            case 2:
                t[k] = std::min(t[k*2], t[k*2+1]);
                return;
            case 3:
                t[k] = std::max(t[k*2], t[k*2+1]);
                return;
            default:
                exit(1);
        }
    }

    long long localCalc (long long a, long long b, long long l, long long r, long long k) {
        if (b < l || r < a) {
            return (localFunc == 1 ? 0 : (localFunc == 2 ? INF : -INF));
        }
        if (a <= l && r <= b) {
            return t[k];
        }
        localPush(k, l, r);
        long long mid = (l+r)/2;
        switch (localFunc) {
            case 1:
                return localCalc(a, b, l, mid, k*2) + localCalc(a, b, mid+1, r, k*2+1);
            case 2:
                return std::min(localCalc(a, b, l, mid, k*2), localCalc(a, b, mid+1, r, k*2+1));
            case 3:
                return std::max(localCalc(a, b, l, mid, k*2), localCalc(a, b, mid+1, r, k*2+1));
            default:
                exit(1);
        }
    }


    long long sum(int l, int r) {
        return localCalc(l, r, 1, localSz, 1);
    }

    long long min(int l, int r) {
        return localCalc(l, r, 1, localSz, 1);
    }

    long long max(int l, int r) {
        return localCalc(l, r, 1, localSz, 1);
    }

    void add(int l, int r, long long val) {
        localAdd(l, r, val, 1, localSz, 1);
    }

    void init(int l, int r, long long new_val) {
        localSet(l, r, new_val, 1, localSz, 1);
    }

    vector<long long> t;
    vector<long long> lset;
    vector<long long> ladd;
    vector<bool> uset;
    vector<bool> uadd;
    const long long INF = 9223372036000000000LL;
    int localSz;
    int localFunc;
};
