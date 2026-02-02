#pragma once
#include <bits/stdc++.h>
using namespace std;

struct bNum {
    string subtract(const string &a, const string &b) {
        string sa = strip(a);
        string sb = strip(b);
        int i = (int)(sa.size()) - 1;
        int j = (int)(sb.size()) - 1;
        int borrow = 0;
        string res;
        while (i >= 0) {
            int da = sa[i--] - '0' - borrow;
            int db = j >= 0 ? sb[j--] - '0' : 0;
            if (da < db) {
                da += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            int diff = da - db;
            res.push_back((char)('0' + diff));
        }
        reverse(res.begin(), res.end());
        return strip(res);
    }
    string add(const string &a, const string &b) {
        string sa = strip(a);
        string sb = strip(b);
        int i = (int)(sa.size()) - 1;
        int j = (int)(sb.size()) - 1;
        int carry = 0;
        string res;
        while (i >= 0 || j >= 0 || carry) {
            int da = i >= 0 ? sa[i--] - '0' : 0;
            int db = j >= 0 ? sb[j--] - '0' : 0;
            int sum = da + db + carry;
            carry = sum / 10;
            res.push_back((char)('0' + (sum % 10)));
        }
        reverse(res.begin(), res.end());
        return strip(res);
    }
    
    string multiply(const string &a, const string &b) {
        string sa = strip(a);
        string sb = strip(b);
        if (sa == "0" || sb == "0") return "0";
        vector<int> prod(sa.size() + sb.size(), 0);
        for (int i = (int)(sa.size()) - 1; i >= 0; --i) {
            for (int j = (int)(sb.size()) - 1; j >= 0; --j) {
                int p = (sa[i] - '0') * (sb[j] - '0');
                int pos = i + j + 1;
                int sum = prod[pos] + p;
                prod[pos] = sum % 10;
                prod[pos - 1] += sum / 10;
            }
        }
        string res;
        size_t i = 0;
        while (i < prod.size() && prod[i] == 0) ++i;
        for (; i < prod.size(); ++i) res.push_back((char)('0' + prod[i]));
        return res.empty() ? "0" : res;
    }

    string divide(const string &a, const string &b) {
        string sa = strip(a);
        string sb = strip(b);
        if (sb == "0") return "Division by zero";
        if (compare(sa, sb) < 0) return "0";
        string quotient;
        string current;
        for (char c : sa) {
            current.push_back(c);
            current = strip(current);
            int q = 0;
            while (compare(current, sb) >= 0) {
                current = subtract(current, sb);
                ++q;
            }
            quotient.push_back((char)('0' + q));
        }
        return strip(quotient);
    }

    string modul(const string &s, const string &M) {
        string sa = strip(s);
        string sb = strip(M);
        sb = strip(divide(sa, M));
        sb = strip(multiply(sb, M));
        sa = strip(subtract(sa, sb));
        return sa;
    }
    private:
    string strip(const string &s) {
        size_t pos = s.find_first_not_of('0');
        if (pos == string::npos) 
            return "0";
        return s.substr(pos);
    }
    int compare(const string &a, const string &b) {
        string sa = strip(a);
        string sb = strip(b);
        if (sa.size() != sb.size()) 
            return sa.size() < sb.size() ? -1 : 1;
        if (sa == sb) 
            return 0;
        return sa < sb ? -1 : 1;
    }
};
bNum big;