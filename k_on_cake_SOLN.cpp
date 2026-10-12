// Intended: group by value, add an edge d -> v for every multiple v of d
// (harmonic sieve, ~M ln M edges), then run Dinic with capacities.
#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    // edges are collected first, then packed into CSR arrays for cache-friendly traversal
    int n;
    vector<array<int, 3>> raw;
    vector<int> start, to, cap, rev, lvl, it, q;
    Dinic(int n) : n(n) {}
    void add(int u, int v, int c) { raw.push_back({u, v, c}); }
    void build() {
        start.assign(n + 1, 0);
        for (auto& r : raw) { start[r[0] + 1]++; start[r[1] + 1]++; }
        for (int i = 0; i < n; i++) start[i + 1] += start[i];
        int m = start[n];
        to.resize(m); cap.resize(m); rev.resize(m);
        vector<int> pos(start.begin(), start.end() - 1);
        for (auto& r : raw) {
            int a = pos[r[0]]++, b = pos[r[1]]++;
            to[a] = r[1]; cap[a] = r[2]; rev[a] = b;
            to[b] = r[0]; cap[b] = 0; rev[b] = a;
        }
        raw.clear(); raw.shrink_to_fit();
        lvl.assign(n, 0); it.assign(n, 0); q.assign(n, 0);
    }
    bool bfs(int s, int t) {
        fill(lvl.begin(), lvl.end(), -1);
        int qh = 0, qt = 0;
        q[qt++] = s; lvl[s] = 0;
        while (qh < qt && lvl[t] < 0) {
            int u = q[qh++];
            for (int e = start[u]; e < start[u + 1]; e++)
                if (cap[e] > 0 && lvl[to[e]] < 0) { lvl[to[e]] = lvl[u] + 1; q[qt++] = to[e]; }
        }
        return lvl[t] >= 0;
    }
    int dfs(int u, int t, int f) {
        if (u == t) return f;
        int pushed = 0;
        for (int& e = it[u]; e < start[u + 1]; e++) {
            int v = to[e];
            if (cap[e] > 0 && lvl[v] == lvl[u] + 1) {
                int r = dfs(v, t, min(f - pushed, cap[e]));
                if (r > 0) {
                    cap[e] -= r; cap[rev[e]] += r; pushed += r;
                    if (pushed == f) return pushed;  // keep it[u] at e: edge may still have capacity
                }
            }
        }
        return pushed;
    }
    long long run(int s, int t) {
        build();
        long long fl = 0;
        while (bfs(s, t)) {
            for (int i = 0; i < n; i++) it[i] = start[i];
            fl += dfs(s, t, INT_MAX);
        }
        return fl;
    }
};

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    const int M = 100000;
    vector<int> cnt(M + 1, 0), pc(M + 1, 0);
    for (int i = 0, x; i < n; i++) { scanf("%d", &x); cnt[x]++; }
    for (int j = 0, x; j < k; j++) { scanf("%d", &x); pc[x]++; }
    // S = 0, T = 1, guest class d -> 2 + d, cake class v -> 3 + M + v
    int S = 0, T = 1, P = 2, C = 3 + M;
    Dinic D(C + M + 1);
    for (int d = 1; d <= M; d++)
        if (pc[d]) {
            D.add(S, P + d, pc[d]);
            for (int v = d; v <= M; v += d)
                if (cnt[v]) D.add(P + d, C + v, INT_MAX);
        }
    for (int v = 1; v <= M; v++)
        if (cnt[v]) D.add(C + v, T, cnt[v]);
    printf("%lld\n", D.run(S, T));
}
