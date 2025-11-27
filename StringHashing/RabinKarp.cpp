#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define ll long long
#define vll vector<ll>
#define rep(i, n) for(int i = 0; i < n; i++)
#define rep1(i, n) for(int i = 1; i < n; i++)

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s, s1;
    cin >> s >> s1;
    const ll p = 31, M = 1e9 + 9;
    int n = s.size(), n1 = s1.size();

    vll p_p(max(n, n1)), h(n + 1); h[0] = 0;
    p_p[0] = 1;

    rep1(i, p_p.size())
        p_p[i] = (p_p[i - 1] * p) % M;

    rep(i, n) 
        h[i + 1] = (h[i] + (s[i] - 'a' + 1) * p_p[i]) % M;

    ll h_s = 0;
    rep(i, n1)
        h_s = (h_s + (s1[i] - 'a' + 1) * p_p[i]) % M;

    vi oc;
    rep(i, n - n1 + 1)
        if((h[i + n1] - h[i] + M) % M == (h_s * p_p[i]) % M)
            oc.push_back(i);

    for(int i : oc)
        cout << i << " ";
    return 0;
}