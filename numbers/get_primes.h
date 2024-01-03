#include <bits/stdc++.h>

/*
API

get_primes(n) - return vector with all primes from 2 to n
*/

vector <int> get_primes(int a) {
    vector <bool> isPrime(a + 1, true);
    for (int i = 2; i <= a; ++i) {
        if (isPrime[i]) {
            for (int j = 2; j * i <= a; ++j) {
                isPrime[i * j] = false;
            }
        }
    }
    vector <int> ans;
    for (int i = 2; i <= a; ++i) {
        if (isPrime[i]) {
            ans.push_back(i);
        }
    }
    return ans;
}
