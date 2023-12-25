#include <bits/stdc++.h>

/*
API
ALL IN LONG

powmod(a, b, mod) - calculates (a^b)%mod (mod should be in [1, 2^32) )
*/

long long powmod(long long a,long long b,long long mod) {
    if (b==0 || a==1)  {if (mod==1) return 0; else return 1; }

    if (b%2==0) { long long k=powmod(a,b/2,mod); return (k*k)%mod; }
    else {long long k=powmod(a,b/2,mod); return ( (k*k) %mod *a)% mod; }
}
