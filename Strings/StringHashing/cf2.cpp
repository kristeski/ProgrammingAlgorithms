#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define ll long long
#define vll vector<ll>
#define rep(i, n) for(int i = 0; i < n; i++)
#define rep1(i, n) for(int i = 1; i < n; i++)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = (int)s.size();
    const ll p = 31;
    const ll MOD1 = 1000000007LL;
    const ll MOD2 = 1000000009LL;

    vll p1(n+1), p2(n+1);
    p1[0] = p2[0] = 1;
    rep1(i, n + 1) {
        p1[i] = (p1[i-1] * p) % MOD1;
        p2[i] = (p2[i-1] * p) % MOD2;
    }

    string rs = s;
    reverse(rs.begin(), rs.end());
    vll h1(n+1), h2(n+1), hr1(n+1), hr2(n+1);
    h1[0] = h2[0] = hr1[0] = hr2[0] = 0;

    rep(i,n) {
        h1[i+1] = (h1[i] * p + (s[i] - 'a' + 1)) % MOD1;
        h2[i+1] = (h2[i] * p + (s[i] - 'a' + 1)) % MOD2;
        hr1[i+1] = (hr1[i] * p + (rs[i] - 'a' + 1)) % MOD1;
        hr2[i+1] = (hr2[i] * p + (rs[i] - 'a' + 1)) % MOD2;
    }

    auto get_hash = [&](const vll &H1, const vll &H2, int l, int r)->pair<ll,ll> {
        int len = r - l + 1;
        ll x1 = (H1[r+1] - (H1[l] * p1[len]) % MOD1 + MOD1) % MOD1;
        ll x2 = (H2[r+1] - (H2[l] * p2[len]) % MOD2 + MOD2) % MOD2;
        return {x1, x2};
    };

    vector<unsigned char> deg((size_t)n * (size_t)n, 0);
    vi ans(n+1, 0);

    for (int len = 1; len <= n; ++len) {
        for (int l = 0; l + len - 1 < n; ++l) {
            int r = l + len - 1;
            int rl = n - 1 - r;
            int rr = n - 1 - l;
            if (get_hash(h1, h2, l, r) == get_hash(hr1, hr2, rl, rr)) {
                unsigned char curDeg = 1;
                if (len > 1) {
                    int left_len = len / 2;
                    int left_l = l;
                    int left_r = l + left_len - 1;
                    curDeg = 1 + deg[left_l * n + left_r];
                }
                deg[l * n + r] = curDeg;
                ans[curDeg] += 1;
            }
        }
    }

    for (int k = 1; k <= n; ++k) {
        if (k > 1) cout << ' ';
        cout << ans[k];
    }
    cout << '\n';
    return 0;
}
