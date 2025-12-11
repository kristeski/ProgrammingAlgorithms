#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 1;

int main(){ 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n, q;
    cin >> n >> q;
    vector<int> lg(n + 5);
    lg[1] = 0;
    for(int i = 2; i <= n + 4; i++) 
        lg[i] = lg[i/2] + 1;
    vector<vector<int>> up(n + 1, vector<int>(lg[n] + 1));
    for(int i = 1; i <= n; i++)
        cin >> up[i][0];
    for(int j = 1; j <= lg[n]; j++)
        for(int i = 1; i + (1 << (j - 1)) <= n; i++)
            up[i][j] = min(up[i][j - 1], up[i + (1 << (j - 1))][j-1]);
    auto qry = [&](int l, int r) -> int {
        int len = r - l + 1;
        return min(up[l][lg[len]], up[r - (1 << lg[len]) + 1][lg[len]]);
    };    
    while(q--) {
        int a, b;
        cin >> a >> b;
        cout << qry(a, b) << '\n';
    }
}