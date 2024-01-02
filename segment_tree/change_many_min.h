#include <bits/stdc++.h>

/*
API
ALL IN LONG

construction - SegTreeChangeManyMin t(size)
add(l, r, val) - add val to a[l..r] (1 - index)
min(l, r) - return min of a[l..r] (1 - index)
*/

struct SegTreeChangeManyMin {

    SegTreeChangeManyMin(int sz) {
        localSz = sz;
        t.resize(4 * sz + 5);
    }

    long long localMin (int v, int tl, int tr, int l, int r) {
        if (l == tl && r == tr) {
            return t[v].first;
        }

        int mid = (tl + tr) / 2;
        if (r <= mid) {
            long long ans = localMin(2 * v, tl, mid, l, r);
            return ans += t[v].second;
        } else if (l >= mid) {
            long long ans = localMin(2 * v + 1, mid, tr, l, r);
            return ans += t[v].second;
        }

        long long min_left = localMin(2 * v, tl, mid, l, mid);
        long long min_right = localMin(2 * v + 1, mid, tr, mid, r);
        long long ans = std::min(min_left, min_right);
        return ans += t[v].second;
    }

    void localAdd (int v, int tl, int tr, int l, int r, long long val) {
        if (l == tl && r == tr) {
            t[v].second += val;
            t[v].first += val;
            return;
        }

        int mid = (tl + tr) / 2;
        if (r <= mid) {
            localAdd(2 * v, tl, mid, l, r, val);
            t[v].first = std::min(t[2 * v].first, t[2 * v + 1].first) + t[v].second;
            return;
        } else if (l >= mid) {
            localAdd(2 * v + 1, mid, tr, l, r, val);
            t[v].first = std::min(t[2 * v].first, t[2 * v + 1].first) + t[v].second;
            return;
        }

        localAdd(2 * v, tl, mid, l, mid, val);
        localAdd(2 * v + 1, mid, tr, mid, r, val);
        t[v].first = std::min(t[2 * v].first, t[2 * v + 1].first) + t[v].second;
        return;
    }

    long long min(int l, int r) {
        return localMin(1, 0, localSz, l-1, r);
    }

    void add(int l, int r, long long val) {
        localAdd(1, 0, localSz, l-1, r, val);
    }

    vector<pair<long long, long long>> t;
    int localSz;
};
