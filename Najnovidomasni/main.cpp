#include <bits/stdc++.h>
using namespace std;

using ld = double;
using Pt = array<ld, 3>;
using Mat = array<array<ld, 3>, 3>;

const ld PI = acos(-1.0);

Pt apply(const Pt& p, const Mat& m) {
    Pt r{};
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            r[j] += p[k] * m[k][j];
        }
    }
    return r;
}

Mat multiply(const Mat& a, const Mat& b) {
    Mat c{};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

Mat rotate2D(ld angle) {
    ld c = cos(angle), s = sin(angle);
    return {{
        {{ c,  s, 0 }},
        {{-s,  c, 0 }},
        {{ 0,  0, 1 }}
    }};
}

Mat translate2D(ld tx, ld ty) {
    return {{
        {{1, 0, 0}},
        {{0, 1, 0}},
        {{tx, ty, 1}}
    }};
}

Mat scale2D(ld k) {
    return {{
        {{k, 0, 0}},
        {{0, k, 0}},
        {{0, 0, 1}}
    }};
}

vector<Pt> read_obj_vertices(const string& file_name) {
    ifstream fin(file_name);
    vector<Pt> v;

    if (!fin.is_open()) {
        cerr << "Cannot open file: " << file_name << '\n';
        return v;
    }

    string line;
    while (getline(fin, line)) {
        if (line.size() >= 2 && line[0] == 'v' && line[1] == ' ') {
            stringstream ss(line);
            char ch;
            ld x, y, z;
            ss >> ch >> x >> y >> z;
            v.push_back({x, y, 1});

        }
    }
    return v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Pt> verts = read_obj_vertices("square.obj");
    if (verts.empty()) {
        cerr << "No vertices found.\n";
        return 0;
    }

    ld angle = PI / 4.0;
    ld tx = 2.0, ty = 0.0;
    ld k = 4.0;

    Mat R = rotate2D(angle);
    Mat T = translate2D(tx, ty);
    Mat S = scale2D(k);

    Mat M = multiply(multiply(R, T), S);

    cout << fixed << setprecision(6);
    for (auto p : verts) {
        Pt q = apply(p, M);
        cout << q[0] << ' ' << q[1] << ' ' << q[2] << '\n';
    }

    return 0;
}