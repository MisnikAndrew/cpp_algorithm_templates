#include <bits/stdc++.h>

/*
API
ALL IN LONG

remove_first(num) - remove first digit of num and return result
first_digit(num) - get first digit of num
count_numbers(num, max_digit) - return number of integers from [0..num] all of which have digits <= max_digit
*/

long long remove_first(long long num) {
    long long w = 1;
    while (w * 10LL < num) {
        w *= 10LL;
    }
    return num % w;
}

long long first_digit(long long num) {
    while (num >= 10) {
        num /= 10;
    }
    return num;
}

long long count_numbers(long long num, long long max_digit) {
    if (num < 10) {
        return min(num + 1, max_digit + 1);
    }
    long long less = 1;
    long long f = first_digit(num);
    long long removed = remove_first(num);
    while (num >= 10) {
        num /= 10;
        less *= max_digit + 1;
    }
    if (f > max_digit) {
        return (max_digit + 1) * less;
    } else {
        return f * less + count_numbers(removed, max_digit);
    }
}
