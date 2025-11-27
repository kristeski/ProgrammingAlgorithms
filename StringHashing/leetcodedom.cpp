#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    string longestDupSubstring(string s) {
        const long long p = 31;
        const long long MOD = 1000000009LL;
        int n = s.size();
        if (n == 0) return "";

        vector<long long> p_p(n + 1), h(n + 1);
        p_p[0] = 1; h[0] = 0;
        for (int i = 1; i <= n; ++i) {
            p_p[i] = (p_p[i - 1] * p) % MOD;
            h[i] = (h[i - 1] * p + (s[i - 1] - 'a' + 1)) % MOD;
        }

        auto get_hs = [&](int l, int r)-> long long {
            int len = r - l + 1;
            long long res = (h[r + 1] - (h[l] * p_p[len]) % MOD + MOD) % MOD;
            return res;
        };

        int lo = 1, hi = n - 1;         
        int best_len = 0, best_pos = -1;

        while (lo <= hi) {
            int md = (lo + hi) / 2;
            bool found = false;
            unordered_map<long long, vector<int>> mp;
            mp.reserve(n * 2);

            for (int i = 0; i + md <= n; i++) {
                long long hs = get_hs(i, i + md - 1);
                auto it = mp.find(hs);
                if (it != mp.end()) {
                    
                    for (int prev : it->second) {
                        
                        if (s.compare(prev, md, s, i, md) == 0) {
                            best_len = md;
                            best_pos = prev;
                            found = true;
                            break;
                        }
                    }
                    if (found) break;
                    it->second.push_back(i);
                } else {
                    mp[hs] = {i};
                }
            }

            if (found) lo = md + 1;
            else hi = md - 1;
        }

        if (best_len == 0) return "";
        return s.substr(best_pos, best_len);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Solution tc;
    string s;
    cin >> s;
    cout << tc.longestDupSubstring(s);
}
// zadacata ne e resliva bez double hash poradi kolizii
// mojata implementacija e so 1 hash i proverki na podstringovi
// za da se izbegne gresen rezultat pri kolizija na hash