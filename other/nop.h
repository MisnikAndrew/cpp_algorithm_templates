#include <bits/stdc++.h>

/*
API
ALL IN LONG

nop(vector<long long> s1, vector<long long> s2) - construct & calculate
nop.ans - return length of longest common subsequence of given vectors (after construction)
*/

struct nop {
    long long ans = 0;
    vector <pair<int, int>> pos; // TODO: add positions calculation

    vector <long long> a;
    vector <long long> b;


    nop(vector<long long>& s1, vector <long long>& s2) {
        a = s1;
        b = s2;
        if (a.size() > b.size()) {
            swap(a, b);
        }
        calc();
    }

    void calc() {
        int n = a.size();
        int m = b.size();
        vector<long long> prev(n + 1, 0LL);
        vector<long long> cur(n + 1, 0LL);

        for (int idx2 = 0; idx2 < n + 1; idx2++) {
            cur[idx2] = 0;
        }

        for (int idx1 = 1; idx1 < m + 1; idx1++) {
            for (int idx2 = 1; idx2 < n + 1; idx2++) {
                if (b[idx1 - 1] == a[idx2 - 1]) {
                    cur[idx2] = 1 + prev[idx2 - 1];
                }
                else
                    cur[idx2] = max(cur[idx2 - 1], prev[idx2]);
            }
            prev = cur;
        }
        ans = cur[n];
    }
};
