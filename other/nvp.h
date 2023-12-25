#include <bits/stdc++.h>

/*
API
ALL IN LONG

nvp(vector<long long> m) - construct & calculate
nvp.ans - return length of longest increasing subsequence of given vector (after construction)
nvp.pos - return positions of longest increasing subsequence of given vector (after construction)
*/

const long long INF = 9223372036000000000LL;

struct nvp {
    long long ans = 0;
    vector <int> pos;

    vector <long long> a;


    nvp(vector<long long> m) {
        a = m;
        calc();
    }

    void calc() {
        int n = a.size();
        vector <long long> d(n + 1);
        vector <long long> p(n + 1);
        vector <long long> prev(n + 1);
        p[0] = -1;
        d[0] = -INF;
        for (int i=1; i<=n; ++i)
            d[i] = INF;

        for (int i=0; i<n; i++) {
            long long j = (long long) (upper_bound (d.begin(), d.end(), a[i]) - d.begin());
            if (d[j-1] < a[i] && a[i] < d[j]) {
                d[j] = a[i];
                p[j] = i;
                prev[i] = p[j - 1];
                ans = max(ans, j);
            }
        }
        pos.clear();
        long long cur = p[ans];
        while (cur != -1) {
            pos.push_back(cur);
            cur = prev[cur];
        }
        reverse(pos.begin(), pos.end());
    }
};