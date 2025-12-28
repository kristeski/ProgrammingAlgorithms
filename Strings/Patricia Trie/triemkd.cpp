#include <bits/stdc++.h>
using namespace std;

int id(char c) {
    static string az = "абвгдѓежзѕијклљмнњопрстќуфхцчџш";
    for (int i = 0; i < 31; ++i)
        if (az[i] == c) return i;
    return -1;
}

struct Tnode {
    Tnode* chi[31];
    string lab;
    bool endow;

    Tnode() {
        for (int i = 0; i < 31; ++i) chi[i] = nullptr;
        lab = "";
        endow = false;
    }
};

Tnode root;
string tmp;

void inw(const string& s) {
    Tnode* curr = &root;
    int pos = 0, n = s.size();

    while (pos < n) {
        int idx = id(s[pos]);
        if (idx == -1) return;

        if (!curr->chi[idx]) {
            Tnode* leaf = new Tnode();
            leaf->lab = s.substr(pos);
            leaf->endow = true;
            curr->chi[idx] = leaf;
            return;
        }

        Tnode* child = curr->chi[idx];
        string& lab = child->lab;

        int lcp = 0;
        while (pos + lcp < n && lcp < (int)lab.size() && s[pos + lcp] == lab[lcp])
            ++lcp;

        if (lcp == (int)lab.size()) {
            pos += lcp;
            curr = child;
            continue;
        }

        Tnode* mid = new Tnode();
        mid->lab = lab.substr(0, lcp);

        child->lab = lab.substr(lcp);
        mid->chi[id(child->lab[0])] = child;

        curr->chi[idx] = mid;

        if (pos + lcp == n) {
            mid->endow = true;
        }
        else {
            Tnode* leaf = new Tnode();
            leaf->lab = s.substr(pos + lcp);
            leaf->endow = true;
            mid->chi[id(leaf->lab[0])] = leaf;
        }
        return;
    }

    curr->endow = true;
}

bool isw(const string& s) {
    Tnode* curr = &root;
    int pos = 0, n = s.size();

    while (pos < n) {
        int idx = id(s[pos]);
        if (idx == -1 || !curr->chi[idx]) return false;

        Tnode* child = curr->chi[idx];
        string& lab = child->lab;

        for (int i = 0; i < (int)lab.size(); ++i) {
            if (pos >= n || s[pos] != lab[i]) return false;
            ++pos;
        }
        curr = child;
    }
    return curr->endow;
}

void preorder(Tnode* curr) {
    if (curr->endow) cout << tmp << '\n';
    for (int i = 0; i < 31; ++i) {
        if (curr->chi[i]) {
            tmp.append(curr->chi[i]->lab);
            preorder(curr->chi[i]);
            tmp.resize(tmp.size() - curr->chi[i]->lab.size());
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    while(n--) {
        string s;
        cin >> s;
        inw(s);
    }
    preorder(&root);
    return 0;
}