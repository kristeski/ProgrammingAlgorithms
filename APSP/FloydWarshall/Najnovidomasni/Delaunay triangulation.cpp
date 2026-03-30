#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <algorithm>
#include <random>
#include <cmath>

using namespace std;

using ld = long double;
static const ld EPS = 1e-12L;

struct Point {
    ld x, y;
    int id;
};

struct Triangle {
    int a, b, c;
};

struct Edge {
    int u, v;

    Edge() : u(0), v(0) {}

    Edge(int _u, int _v) {
        if (_u > _v) swap(_u, _v);
        u = _u;
        v = _v;
    }

    bool operator<(const Edge& other) const {
        if (u != other.u) return u < other.u;
        return v < other.v;
    }
};

ld orient(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

Triangle make_triangle(const vector<Point>& pts, int a, int b, int c) {
    if (orient(pts[a], pts[b], pts[c]) < 0) swap(b, c);
    Triangle t;
    t.a = a;
    t.b = b;
    t.c = c;
    return t;
}

ld in_circle(const Point& a, const Point& b, const Point& c, const Point& p) {
    ld ax = a.x - p.x, ay = a.y - p.y;
    ld bx = b.x - p.x, by = b.y - p.y;
    ld cx = c.x - p.x, cy = c.y - p.y;

    ld det = (ax * ax + ay * ay) * (bx * cy - by * cx)
           - (bx * bx + by * by) * (ax * cy - ay * cx)
           + (cx * cx + cy * cy) * (ax * by - ay * bx);

    return det;
}

vector<array<int, 3>> delaunay_triangulation(vector<Point> input) {
    int n = (int)input.size();
    vector<array<int, 3>> empty_result;
    if (n < 3) return empty_result;

    std::mt19937 rng(712367);
    shuffle(input.begin(), input.end(), rng);

    ld minx = input[0].x, maxx = input[0].x;
    ld miny = input[0].y, maxy = input[0].y;

    for (size_t i = 0; i < input.size(); i++) {
        minx = min(minx, input[i].x);
        maxx = max(maxx, input[i].x);
        miny = min(miny, input[i].y);
        maxy = max(maxy, input[i].y);
    }

    ld dx = maxx - minx;
    ld dy = maxy - miny;
    ld delta = max(dx, dy);

    if (fabsl(delta) < EPS) delta = 1.0L;

    ld midx = (minx + maxx) / 2.0L;
    ld midy = (miny + maxy) / 2.0L;

    vector<Point> pts = input;
    pts.push_back(Point{midx - 20.0L * delta - 1.0L, midy - delta - 1.0L, -1});
    pts.push_back(Point{midx,                         midy + 20.0L * delta + 1.0L, -2});
    pts.push_back(Point{midx + 20.0L * delta + 1.0L, midy - delta - 1.0L, -3});

    int s1 = n;
    int s2 = n + 1;
    int s3 = n + 2;

    vector<Triangle> tris;
    tris.push_back(make_triangle(pts, s1, s2, s3));

    for (int i = 0; i < n; i++) {
        vector<int> bad;

        for (int t = 0; t < (int)tris.size(); t++) {
            Triangle cur = tris[t];
            if (in_circle(pts[cur.a], pts[cur.b], pts[cur.c], pts[i]) > EPS) {
                bad.push_back(t);
            }
        }

        map<Edge, int> cnt;
        for (int k = 0; k < (int)bad.size(); k++) {
            int id = bad[k];
            Triangle cur = tris[id];
            cnt[Edge(cur.a, cur.b)]++;
            cnt[Edge(cur.b, cur.c)]++;
            cnt[Edge(cur.c, cur.a)]++;
        }

        vector<char> is_bad(tris.size(), false);
        for (int k = 0; k < (int)bad.size(); k++) {
            is_bad[bad[k]] = true;
        }

        vector<Triangle> next;

        for (int t = 0; t < (int)tris.size(); t++) {
            if (!is_bad[t]) next.push_back(tris[t]);
        }

        for (map<Edge, int>::iterator it = cnt.begin(); it != cnt.end(); ++it) {
            if (it->second == 1) {
                next.push_back(make_triangle(pts, it->first.u, it->first.v, i));
            }
        }

        tris.swap(next);
    }

    vector<array<int, 3>> ans;

    for (int i = 0; i < (int)tris.size(); i++) {
        Triangle cur = tris[i];
        if (cur.a >= n || cur.b >= n || cur.c >= n) continue;

        array<int, 3> tri = {pts[cur.a].id, pts[cur.b].id, pts[cur.c].id};
        ans.push_back(tri);
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Point> pts(n);
    for (int i = 0; i < n; i++) {
        double x, y;
        cin >> x >> y;
        pts[i] = Point{(ld)x, (ld)y, i};
    }

    vector<array<int, 3>> tris = delaunay_triangulation(pts);

    cout << tris.size() << '\n';
    for (int i = 0; i < (int)tris.size(); i++) {
        cout << tris[i][0] << ' ' << tris[i][1] << ' ' << tris[i][2] << '\n';
    }

    return 0;
}