#include <bits/stdc++.h>

/*
API
ALL IN LONG


z_func(s) - calculates z-function and return array with size = |s|

z[i] = max k that s[0 .. k - 1] = s[i .. k - 1 + i]
*/

vector<int> z_func(string s) {
	int n = (int) s.length();
	vector<int> z (n);
	for (int i=1, l=0, r=0; i<n; ++i) {
		if (i <= r)
			z[i] = min (r-i+1, z[i-l]);
		while (i+z[i] < n && s[z[i]] == s[i+z[i]])
			++z[i];
		if (i+z[i]-1 > r)
			l = i,  r = i+z[i]-1;
	}
	return z;
}
