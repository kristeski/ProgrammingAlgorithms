#include <bits/stdc++.h>
using namespace std;

struct Tnode {
    Tnode* chi[26];
    string lab;       
    bool endow;       

    Tnode() {
        for (int i = 0; i < 26; ++i) chi[i] = nullptr;
        lab = "";
        endow = false;
    }
};

Tnode root; 
string tmp;

void inw(const string &s) {
    const string &str = s; 
    Tnode* curr = &root;
    int pos = 0; 
    int n = (int)str.size();

    while (pos < n) {
        int idx = str[pos] - 'a';
        if (!curr->chi[idx]) {
            Tnode* leaf = new Tnode();
            leaf->lab = str.substr(pos); 
            leaf->endow = true;
            curr->chi[idx] = leaf;
            return;
        }

        Tnode* child = curr->chi[idx];
        string &lab = child->lab;

        int lcp = 0;
        while (pos + lcp < n && lcp < (int)lab.size() && str[pos + lcp] == lab[lcp])
            ++lcp;

        if (lcp == (int)lab.size()) {
            pos += lcp;
            curr = child;
            continue;
        }

        Tnode* mid = new Tnode();
        mid->lab = lab.substr(0, lcp); 

        child->lab = lab.substr(lcp);

        mid->chi[child->lab[0] - 'a'] = child;
        mid->endow = false;

        curr->chi[idx] = mid;

        if (pos + lcp == n) {
            mid->endow = true;
            return;
        } else {
            Tnode* leaf = new Tnode();
            leaf->lab = str.substr(pos + lcp);
            leaf->endow = true;
            mid->chi[leaf->lab[0] - 'a'] = leaf;
            return;
        }
    }

    curr->endow = true;
}


bool isw(const string &s) {
    Tnode* curr = &root;
    int pos = 0;
    int n = (int)s.size();

    while (pos < n) {
        int idx = s[pos] - 'a';
        if (!curr->chi[idx]) return false;
        Tnode* child = curr->chi[idx];
        string &lab = child->lab;
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
    for (int i = 0; i < 26; ++i) {
        if (curr->chi[i]) {
            tmp.append(curr->chi[i]->lab);
            preorder(curr->chi[i]);
            tmp.resize(tmp.size() - curr->chi[i]->lab.size());
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    vector<string> lines;
    string line;
    ifstream fin("inputlist.txt");
    bool b = true;
    while (getline(fin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.rfind("#!comment:", 0) == 0 || line.rfind("#", 0) == 0) continue;
        for (auto &c : line) {
            c = tolower(c);
            if (c > 'z' || c < 'a') { b = false; break; }
        }
        if (b) lines.push_back(line);
        b = true;
    }

    for (auto &s : lines) inw(s);

    preorder(&root);


    return 0;
}
