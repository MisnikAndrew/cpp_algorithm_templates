#include <bits/stdc++.h>

/*
API
ALL IN LONG

manacher(string s) - return pair of vectors d1 and d2
d1[i] - length of palindrome with center in i-th symbol
d2[i] - length of palindrome with center between (i-1)-th and i-th symbols

example: "aaaaa" -> {{1, 2, 3, 2, 1}, {0, 1, 2, 2, 1}}
*/

pair <vector<int>, vector<int>> manacher(string s) {
  int n = s.size();
  vector<int> d1 (n);
  int l=0, r=-1;
  for (int i=0; i<n; ++i) {
    int k = i>r ? 1 : min (d1[l+r-i], r-i+1);
    while (i+k < n && i-k >= 0 && s[i+k] == s[i-k])  ++k;
    d1[i] = k;
    if (i+k-1 > r)
      l = i-k+1,  r = i+k-1;
  }
  vector<int> d2 (n);
  l=0, r=-1;
  for (int i=0; i<n; ++i) {
    int k = i>r ? 0 : min (d2[l+r-i+1], r-i+1);
    while (i+k < n && i-k-1 >= 0 && s[i+k] == s[i-k-1])  ++k;
    d2[i] = k;
    if (i+k-1 > r)
      l = i-k,  r = i+k-1;
  }
  return {d1, d2};
}
