#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
#define rep(i, n) for(int i = 0; i < n; i++)
#define rep1(i, n) for(int i = 1; i <= n; i++)
#define vi vector<int>
#define vvi vector<vector<int>>
#define pb push_back
#define ll long long
template<typename T>
istream& operator >>(istream & is, vector<T> &v) {
    for (T& el : v) cin >> el;
    return is;
}
const int N = 2e5 + 1;
int dp[N][2];
int n, w;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        vi v(n);
        cin >> v;
        dp[0][0] = 0;
        dp[0][1] = 5e8;
        rep1(i, n) {
            if (i == 1) {
                dp[i][0] = dp[i - 1][1];
                dp[i][1] = dp[i - 1][0] + (v[i - 1] == 1);
            }
            else {
                dp[i][0] = min(dp[i - 2][1], dp[i-1][1]);
                dp[i][1] = min(dp[i - 1][0] , dp[i - 2][0] + (v[i - 2] == 1)) + (v[i - 1] == 1);
            }
        }
        cout << min(dp[n][0], dp[n][1]) << '\n';
    }
 
}