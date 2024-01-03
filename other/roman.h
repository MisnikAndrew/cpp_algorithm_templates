#include <bits/stdc++.h>

/*
API
romanToInt(s) - convert string s from roman representation to integer
intToRoman(num) - return roman representation of num
*/

int romanToInt(string s) {
    map <char, int> w({
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}
    });
    int ans = 0;
    int a = s.size();
    for (int i = 0; i < a; ++i) {
        if (i + 1 < a && w[s[i + 1]] > w[s[i]]) {
            ans -= w[s[i]];
        } else {
            ans += w[s[i]];
        }
    }
    return ans;
}

string intToRoman(int num) {
    vector <string> ones = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    vector <string> tens = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    vector <string> hundreds = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    vector <string> thousands = {"", "M", "MM", "MMM"};
    string ans = thousands[num / 1000] + hundreds[num % 1000 / 100];
    return ans + tens[num % 100 / 10] + ones[num % 10];
}
