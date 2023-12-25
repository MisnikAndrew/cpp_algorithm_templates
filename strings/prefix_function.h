#include <bits/stdc++.h>

/*
API
ALL IN LONG

pref_func(s) - calculates prefix-function and return array with size = |s|

pref_func[i] = max k that s[0 .. k - 1] = s[i - k + 1 .. i]
*/

vector<int> pref_func (string s) {
	int n = (int) s.length();
	vector<int> pi (n);
	for (int i=1; i<n; ++i) {
		int j = pi[i-1];
		while (j > 0 && s[i] != s[j])
			j = pi[j-1];
		if (s[i] == s[j])  ++j;
		pi[i] = j;
	}
	return pi;
}
