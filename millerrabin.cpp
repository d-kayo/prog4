#include <bits/stdc++.h>

using u64 = uint64_t;
using u128 = __uint128_t; 


u64 power(u64 base, u64 exp, u64 mod) {
    u64 res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (u128)res * base % mod;
        base = (u128)base * base % mod;
        exp /= 2;
    }
    return res;
}


bool miller_test(u64 n, u64 a, u64 d, int s) {
    u64 x = power(a, d, n);
    if (x == 1 || x == n - 1)
        return true;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return true;
    }
    return false;
}


bool is_prime(u64 n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;


    u64 d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }


    static const std::vector<u64> bases = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37
    };

    for (u64 a : bases) {
        if (n == a) return true;
        if (!miller_test(n, a, d, s)) return false;
    }
    return true;
}

int main() {
    u64 num = 1000000007; 
    if (is_prime(num))
        std::cout << num << " is prime." << std::endl;
    else
        std::cout << num << " is composite." << std::endl;
    return 0;
}