#include "BigNum.hpp"
#include <bits/stdc++.h>
using namespace std;
static string strip(const string& s) {
    size_t pos = s.find_first_not_of('0');
    if (pos == string::npos) return "0";
    return s.substr(pos);
}

static int cmp(const string& a, const string& b) {
    string sa = strip(a);
    string sb = strip(b);
    if (sa.size() != sb.size()) return (sa.size() < sb.size()) ? -1 : 1;
    if (sa == sb) return 0;
    return (sa < sb) ? -1 : 1;
}

struct BigOps {
    bNum op;

    string add(const string& a, const string& b) {
        return strip(op.add(a, b));
    }

    string sub(const string& a, const string& b) {
        return strip(op.subtract(a, b));
    }

    string mul(const string& a, const string& b) {
        return strip(op.multiply(a, b));
    }
};

struct PrimeFactory {
    BigOps B;

    vector<string> primes;  
    vector<string> nextMul;  
    vector<string> step;     

    void advance_if_equal(const string& candidate) {
        for (size_t i = 0; i < primes.size(); ++i) {
            while (cmp(nextMul[i], candidate) == 0) {
                nextMul[i] = B.add(nextMul[i], step[i]);
            }
        }
    }

    string min_nextMul() const {
        string mn = nextMul[0];
        for (size_t i = 1; i < nextMul.size(); ++i) {
            if (cmp(nextMul[i], mn) < 0) mn = nextMul[i];
        }
        return mn;
    }

    vector<string> generate_first_k(int K) {
        vector<string> out;
        if (K <= 0) return out;

        out.push_back("2");
        if (K == 1) return out;

        primes.clear();
        nextMul.clear();
        step.clear();

        string n = "3";

        while ((int)out.size() < K) {
            if (primes.empty()) {
                out.push_back(n);

                primes.push_back(n);
                step.push_back(B.add(n, n));     
                nextMul.push_back(B.mul(n, n));  

                n = B.add(n, "2");
                continue;
            }

            string mn = min_nextMul();

            int rel = cmp(n, mn);
            if (rel < 0) {
                out.push_back(n);

                primes.push_back(n);
                step.push_back(B.add(n, n));      
                nextMul.push_back(B.mul(n, n));   
            } else if (rel == 0) {
                advance_if_equal(n);
            } else {
                for (size_t i = 0; i < primes.size(); ++i) {
                    while (cmp(nextMul[i], n) < 0) {
                        nextMul[i] = B.add(nextMul[i], step[i]);
                    }
                    while (cmp(nextMul[i], n) == 0) {
                        nextMul[i] = B.add(nextMul[i], step[i]);
                    }
                }
            }

            n = B.add(n, "2");
        }

        return out;
    }
};

int main() {
    PrimeFactory pf;
    int K = 25;
    auto primes = pf.generate_first_k(K);

    for (auto &p : primes) {
        cout << p << "\n";
    }
    return 0;
}
