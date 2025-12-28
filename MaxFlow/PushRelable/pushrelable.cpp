#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;

struct Edge {
    int to, rev, cap, flow;
};

int n, m, s, t;
vector<vector<Edge>> g;
vector<int> h, excess;

void addEdge(int u, int v, int c) {
    g[u].push_back({ v, (int)g[v].size(), c, 0 });
    g[v].push_back({ u, (int)g[u].size() - 1, 0, 0 }); // reverse edge
}

void push(int u) {
    for (auto& e : g[u]) {
        if (excess[u] == 0) break;
        if (e.cap - e.flow > 0 && h[u] == h[e.to] + 1) {
            int df = min(excess[u], e.cap - e.flow);
            e.flow += df;
            g[e.to][e.rev].flow -= df;
            excess[u] -= df;
            excess[e.to] += df;
        }
    }
}

void relabel(int u) {
    int mh = INF;
    for (auto& e : g[u]) {
        if (e.cap - e.flow > 0) {
            mh = min(mh, h[e.to]);
        }
    }
    if (mh < INF) h[u] = mh + 1;
}

int maxflow() {
    h.assign(n, 0);
    excess.assign(n, 0);
    h[s] = n;

    for (auto& e : g[s]) {
        e.flow = e.cap;
        g[e.to][e.rev].flow -= e.cap;
        excess[e.to] += e.cap;
        excess[s] -= e.cap;
    }

    queue<int> q;
    for (int i = 0; i < n; i++)
        if (i != s && i != t && excess[i] > 0)
            q.push(i);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        int old_excess = excess[u];
        push(u);
        if (excess[u] > 0) {
            relabel(u);
            q.push(u);
        }
    }

    return excess[t];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> s >> t;
    g.assign(n, vector<Edge>());

    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        addEdge(u, v, c);
    }

    cout << maxflow() << '\n';
}