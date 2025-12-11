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

    vector<string> lines;
    string line;
    ifstream fin("inputlist.txt");
    bool b = true;
    while (getline(fin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.rfind("#!comment:", 0) == 0 || line.rfind("#", 0) == 0) continue;
        for (auto& c : line) {
            c = tolower(c);
            if (c > 122 || c < 97) {
                b = false;
                break;
            }
        }
        if(b) lines.push_back(line);
        b = true;
    }
    for (auto& s : lines) inw(s);
    return 0;
}