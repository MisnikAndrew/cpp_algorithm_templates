#include <bits/stdc++.h>

/*
API
ALL IN LONG

haha(string s, long long p, long long module) - register hashing for string s with powers of p modulo mod
get(l, r) - get hash of substring s[l..r] of registered string
*/

vector<pair<long long, long long>> hash_pairs;
vector<vector<long long>> hash_powers;

struct haha {
    vector <long long> hashes;
    int find = -1;
    long long mod;
    long long p;

    long long get_num(char c) {
        if (c >= 'a' && c <= 'z') {
            return c - 'a' + 1;
        }
        if (c >= 'A' && c <= 'Z') {
            return c - 'A' + 27;
        }
        if (c >= '0' && c <= '9') {
            return c - '0' + 53;
        }
    }

    haha(string& s, long long prod, long long module) {
        p = prod;
        mod = module;
        int a = s.size();
        for (int i = 0; i < hash_pairs.size(); ++i) {
            if (p == hash_pairs[i].first && mod == hash_pairs[i].second) {
                find = i;
                break;
            }
        }
        if (find == -1) {
            hash_pairs.push_back({p, mod});
            vector <long long> pows(a + 1);
            pows[0] = 1;
            pows[1] = p;
            for (int i = 2; i <= a; ++i) {
                pows[i] = (pows[i - 1] * p) % mod;
            }
            find = hash_powers.size();
            hash_powers.push_back(pows);
        } else {
            if (a + 1 > hash_powers[find].size()) {
                int last_size = powers[find].size();
                hash_powers[find].resize(a + 1);
                for (int i = last_size; i <= a; ++i) {
                    hash_powers[find].push_back((hash_powers[find].back() * p) % mod);
                }
            }
        }

        hashes.resize(a + 1);
        hashes[0] = get_num(s[0]);
        for (int i = 1; i < a; ++i) {
            hashes[i] = (hashes[i - 1] * p + get_num(s[i])) % mod;
        }
    }

    long long get(int l, int r) {
        if (!l) {
            return hashes[r];
        }
        return (hashes[r] + mod * mod - hashes[l - 1] * hash_powers[find][r - l + 1]) % mod;
    }

};
