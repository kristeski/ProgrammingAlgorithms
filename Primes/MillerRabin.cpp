#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;

ull mod_mul(ull a, ull b, ull mod) {
    ull res = 0;
    a %= mod;

    while (b) {
        if (b & 1)
            res = (res + a) % mod;

        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

ull mod_pow(ull a, ull d, ull mod) {
    ull res = 1;

    while (d) {
        if (d & 1)
            res = mod_mul(res, a, mod);

        a = mod_mul(a, a, mod);
        d >>= 1;
    }
    return res;
}

bool isPrime(ull n) {
    if (n < 2) return false;

    for (ull p : {2ULL,3ULL,5ULL,7ULL,11ULL,13ULL,17ULL}) {
        if (n == p) return true;
        if (n % p == 0) return false;
    }

    ull d = n - 1;
    int s = 0;

    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    auto witness = [&](ull a) {
        ull x = mod_pow(a, d, n);

        if (x == 1 || x == n-1) return false;

        for (int i = 1; i < s; ++i) {
            x = mod_mul(x, x, n);
            if (x == n-1) return false;
        }

        return true;
    };

    for (ull a : {2ULL,3ULL,5ULL,7ULL,11ULL,13ULL,17ULL})
        if (witness(a)) return false;

    return true;
}

int main() {
    ull n;
    cin >> n;
    cout << (isPrime(n) ? "prime\n" : "composite\n");
}
