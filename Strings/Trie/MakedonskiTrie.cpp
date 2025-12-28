#include <bits/stdc++.h>
using namespace std;
struct Tnode {
    Tnode* chi[26];
    bool endow;
    Tnode() {
        for (int i = 0; i < 26; i++)
            chi[i] = NULL;
        endow = false;
    }
};
Tnode root;
void inw(string s) {
    reverse(s.begin(), s.end());
    Tnode* curr = &root;
    while (s.size()) {
        if (!curr->chi[s.back() - 'a'])
            curr->chi[s.back() - 'a'] = new Tnode();
        curr = curr->chi[s.back() - 'a'];
        s.pop_back();
    }
    curr->endow = true;
}
bool isw(string s) {
    reverse(s.begin(), s.end());
    Tnode* curr = &root;
    while (s.size()) {
        if (!curr->chi[s.back() - 'a'])
            return false;
        curr = curr->chi[s.back() - 'a'];
        s.pop_back();
    }
    return curr->endow;
}
string tmp;
void preorder(Tnode* curr) {
    if (curr->endow)
        cout << tmp << endl;
    for (int i = 0; i < 26; i++)
        if (curr->chi[i]) {
            tmp.push_back((char)(i + 'a'));
            preorder(curr->chi[i]);
            tmp.pop_back();
        }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    // vector<int> prosti(1001, 0);
    // for(int i = 2; i <= 1000; i++) {
    //     if(!prosti[i]) prosti[i] = i;
    //     for(int j = 2 * i; j <= 1000; j += i)
    //         prosti[j] = prosti[i];
    // }
    // vector<int> a, b;
    // for(int i = 2; i <= 1000; i++)
    //     if(i == prosti[i]) a.push_back(i);
    // auto is_prime = [&](int x) -> bool {
    //     if(x <= 3) return true;
    //     if(!(x % 2)) return false;
    //     for(int i = 3; i * i <= x; i += 2)
    //         if(!(x % i)) return false;
    //     return true;
    // };
    // for(int i = 2; i <= 1000; i++)
    //     if(is_prime(i)) b.push_back(i);
    // if(a.size() == b.size()) {
    //     for(int i = 0; i < a.size(); i++) {
    //         if(a[i] != b[i]) {
    //             cout << "NE";
    //             return 0;
    //         }
    //     }
    //     cout << "DA";
    //     return 0;
    // }
    // cout << "NE";
    return 0;
}