#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;
#define vi vector<int>
#define ll long long
#define vll vector<ll>
#define rep(i, n) for(int i = 0; i < n; i++)
#define rep1(i, n) for(int i = 1; i < n; i++)


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s; string goodmask; int k;
    cin >> s >> goodmask >> k;
    int n = s.size();

    vi good(26);
    rep(i,26) good[i] = (goodmask[i] == '1');

    const ll p = 31, M = 1000000009LL; 
    
    vll p_p(n + 1);
    p_p[0] = 1;
    rep1(i, n + 1) p_p[i] = (p_p[i-1] * p) % M;

    vll h(n+1); h[0] = 0;
    rep(i,n) 
        h[i+1] = (h[i] + (ll)(s[i] - 'a' + 1) * p_p[i]) % M;

    unordered_set<ll> seen;

    rep(i, n){
        int bad = 0;
        for (int j = i; j < n; ++j) {
            if (!good[s[j]-'a']) bad++;
            if (bad > k) break;
            ll raw = (h[j + 1] - h[i] + M) % M;
            ll h_val = (((h[j + 1] - h[i] + M) % M) * p_p[n - i] % M);
            seen.insert(h_val);
        }
    }

    cout << (int)seen.size() << '\n';
    return 0;
}
