#include <bits/stdc++.h>

/*
API
ALL IN LONG

construction - SegTreeChangeMany t(size, func) (func can be one of {"max", "min", "sum"})
add(l, r, val) - add val to a[l..r] (1 - index)
Depends on func:
sum(l, r)  - calc sum of elements with positions [l; r] (1 - index)
max(l, r)  - calc max of elements with positions [l; r] (1 - index)
min(l, r)  - calc min of elements with positions [l; r] (1 - index)
*/

struct SegTreeChangeMany {
    SegTreeChangeMany(int sz, string func) {
        localSz = sz;
        if (func == "max") {
            localFunc = 1;
        }
        if (func == "min") {
            localFunc = 2;
        }
        if (func == "sum") {
            localFunc = 3;
        }
        t.resize(4 * sz + 5);
    }

    long long localCalc (int v, int tl, int tr, int l, int r) {
        if (l == tl && r == tr) {
            return t[v].first;
        }

        int mid = (tl + tr) / 2;
        if (r <= mid) {
            return localCalc(2 * v, tl, mid, l, r) + t[v].second * (localFunc == 3 ? (long long)(r - l) : 1);
        } else if (l >= mid) {
            return localCalc(2 * v + 1, mid, tr, l, r) + t[v].second * (localFunc == 3 ? (long long)(r - l) : 1);
        }
        switch (localFunc) {
            case 1:
                return std::max(localCalc(2 * v, tl, mid, l, mid), localCalc(2 * v + 1, mid, tr, mid, r)) + t[v].second;
            case 2:
                return std::min(localCalc(2 * v, tl, mid, l, mid), localCalc(2 * v + 1, mid, tr, mid, r)) + t[v].second;
            case 3:
                return localCalc(2 * v, tl, mid, l, mid) + localCalc(2 * v + 1, mid, tr, mid, r) + (t[v].second * (long long)(r - l));
            default:
                exit(1);
        }
    }

    void localUpdate(int v, int tl, int tr, int l, int r, long long val) {
        if (l == tl && r == tr) {
            t[v].second += val;
            if (localFunc == 3) {
                t[v].first += (val * (long long)(tr - tl));
            } else {
                t[v].first += val;
            }
            return;
        }

        int mid = (tl + tr) / 2;
        if (r <= mid) {
            localUpdate(2 * v, tl, mid, l, r, val);
        } else if (l >= mid) {
            localUpdate(2 * v + 1, mid, tr, l, r, val);
        } else {
            localUpdate(2 * v, tl, mid, l, mid, val);
            localUpdate(2 * v + 1, mid, tr, mid, r, val);
        }
        switch (localFunc) {
            case 1:
                t[v].first = std::max(t[2 * v].first, t[2 * v + 1].first) + t[v].second;
                return;
            case 2:
                t[v].first = std::min(t[2 * v].first, t[2 * v + 1].first) + t[v].second;
                return;
            case 3:
                t[v].first = (t[2 * v].first + t[2 * v + 1].first) + (t[v].second * (long long)(tr - tl));
                return;
            default:
                exit(1);
        }
        return;
    }

    long long sum(int l, int r) {
        return localCalc(1, 0, localSz, l-1, r);
    }

    long long max(int l, int r) {
        return localCalc(1, 0, localSz, l-1, r);
    }

    long long min(int l, int r) {
        return localCalc(1, 0, localSz, l-1, r);
    }

    void add(int l, int r, long long val) {
        localUpdate(1, 0, localSz, l-1, r, val);
    }

    vector<pair<long long, long long>> t;
    int localSz;
    int localFunc;
};
