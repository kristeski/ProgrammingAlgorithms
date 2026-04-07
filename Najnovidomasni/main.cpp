#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    int a, b, rez = 1, M;
    cin >> a >> b >> M;
    for (;b; b>>=1) {
        if (b & 1)
            rez = (rez * a) % M;
        a = (a * a) % M;
    }
    cout << rez << endl;
}
