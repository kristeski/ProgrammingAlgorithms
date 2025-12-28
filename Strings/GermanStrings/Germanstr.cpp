#include <bits/stdc++.h>
using namespace std;

struct Gstr {
    int len;
    union {
        char sh[12];
        struct {
            char pref[4];
            const char* ptr;
        } lg;
    };

    Gstr(const char* s) {
        len = strlen(s);
        if (len <= 12) {
            memcpy(sh, s, len);
            if (len < 12) sh[len] = 0;
        }
        else {
            memcpy(lg.pref, s, 4);
            lg.ptr = s;
        }
    }
};

bool operator==(const Gstr& a, const Gstr& b) {
    if (a.len != b.len) return false;
    if (a.len <= 12)
        return memcmp(a.sh, b.sh, a.len) == 0;
    if (memcmp(a.lg.pref, b.lg.pref, 4) != 0) return false;
    return strcmp(a.lg.ptr, b.lg.ptr) == 0;
}

Gstr operator+(const Gstr& a, const Gstr& b) {
    char* t = new char[a.len + b.len + 1];

    if (a.len <= 12) memcpy(t, a.sh, a.len);
    else memcpy(t, a.lg.ptr, a.len);

    if (b.len <= 12) memcpy(t + a.len, b.sh, b.len);
    else memcpy(t + a.len, b.lg.ptr, b.len);

    t[a.len + b.len] = 0;
    return Gstr(t);
}

void out(Gstr a) {
    if (a.len <= 12) {
        for (int i = 0; i < a.len; ++i) cout << a.sh[i];
    }
    else {
        for (int i = 0; i < a.len; ++i) cout << a.lg.ptr[i];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    Gstr a("adolf1488");
    Gstr b("adolfa1488");
    Gstr c("adolfadolfa1488");

    cout << (a == b) << '\n';
    cout << (a == c) << '\n';

    Gstr d = a + b;
    cout << (d == c) << '\n';

    out(a); cout << '\n';
    out(c);
    return 0;
}