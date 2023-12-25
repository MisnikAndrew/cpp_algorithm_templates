#include <bits/stdc++.h>

/*
API
ALL IN LONG

phi(n) - calculates euler function of n
Phi(n) = count of numbers [1; n] coprime with n
*/


long long phi (long long n) {
	long long result = n;
	for (long long i=2; i*i<=n; ++i)
		if (n % i == 0) {
			while (n % i == 0)
				n /= i;
			result -= result / i;
		}
	if (n > 1)
		result -= result / n;
	return result;
}