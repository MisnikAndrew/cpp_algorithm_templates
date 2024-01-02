#include <bits/stdc++.h>

/*
API
ALL IN LONG

construction - SegTreeChangeManyMax t(size)
add(l, r, val) - add val to a[l..r] (1 - index)
max(l, r) - return max of a[l..r] (1 - index)
*/

struct SegTreeChangeManyMax {

    SegTreeChangeManyMax(int sz) {
        localSz = sz;
        t.resize(4 * sz + 5);
    }

    long long localMax (int v, int tl, int tr, int l, int r) {
        if (l == tl && r == tr) {
            return t[v].first;
        }

        int mid = (tl + tr) / 2;
        if (r <= mid) {
            long long ans = localMax(2 * v, tl, mid, l, r);
            return ans += t[v].second;
        } else if (l >= mid) {
            long long ans = localMax(2 * v + 1, mid, tr, l, r);
            return ans += t[v].second;
        }

        long long max_left = localMax(2 * v, tl, mid, l, mid);
        long long max_right = localMax(2 * v + 1, mid, tr, mid, r);
        long long ans = std::max(max_left, max_right);
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
            t[v].first = std::max(t[2 * v].first, t[2 * v + 1].first) + t[v].second;
            return;
        } else if (l >= mid) {
            localAdd(2 * v + 1, mid, tr, l, r, val);
            t[v].first = std::max(t[2 * v].first, t[2 * v + 1].first) + t[v].second;
            return;
        }

        localAdd(2 * v, tl, mid, l, mid, val);
        localAdd(2 * v + 1, mid, tr, mid, r, val);
        t[v].first = std::max(t[2 * v].first, t[2 * v + 1].first) + t[v].second;
        return;
    }

    long long max(int l, int r) {
        return localMax(1, 0, localSz, l-1, r);
    }

    void add(int l, int r, long long val) {
        localAdd(1, 0, localSz, l-1, r, val);
    }

    vector<pair<long long, long long>> t;
    int localSz;
};
