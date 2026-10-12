#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>
#include <cassert>
 
 
#define pb push_back
using namespace std;
using ll = long long;
using lll = __int128;
using ld = long double;
 
#define pqueue priority_queue
#define int long long
 
const int mod = (int)(1e9+7);
const vector<vector<int>> dir = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
 
bool valid(int x, int y, int n, int m) {
    return x >= 0 && x < n && y >= 0 && y < m;
}
 
ld pi = 3.1415926535897932384;
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define read(x) for(int i=0;i<x.size();i++)cin >> x[i];
 
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
 
vi par;
vi level;
vector<vector<int>> up;
vector<int> diff;
int lg;
 
int maxOverall = 0;
 
void dfs(int node, int parN, int lev, vvi& g){
    par[node] = parN;
    level[node] = lev;
    for(int nei : g[node]){
        if(nei == parN)continue;
 
        dfs(nei, node, lev+1, g);
    }
}
 
int lca(int x, int y){
    if(level[x] < level[y])swap(x, y);
    int dis = level[x] - level[y];
 
    for(int i=0;i<lg;i++){
        if((1 << i) & dis)
            x = up[x][i];
    }
    if(x == y)return x;
 
    for(int i=lg-1;i>=0;i--){
        if(up[x][i] != up[y][i]){
            x = up[x][i];
            y = up[y][i];
        }
    }
    return up[x][0];
}
 
int jump(int x, int amt){
    for(int i=0;i<lg;i++){
        if((1<<i) & amt)
            x = up[x][i];
 
        if(x == -1)
            return x;
    }
    return x;
}
 
int disBetween(int a, int b){
    int x = lca(a, b);
    return level[a] - level[x] + level[b] - level[x];
}
 
int maxFound = 0;
 
int test(int node, int par, vvi& g){
    int sum = 0;
    for(int nei : g[node]){
        if(nei != par)
            sum += test(nei, node, g);
    }
    int x = sum + diff[node];
    maxFound = max(maxFound, x);
 
    return x;
}
 
int can(int mid, vvi& a, vvi& g){
    diff.assign(g.size(), 0);
 
    for(vi& b : a){
        int t = b[0];
        int u = b[1];
        int dest = b[2];
 
        if(t > mid) continue;
 
        int originalLca = lca(u, dest);
 
        int dis1 = level[u] - level[originalLca];
        int dis2 = level[dest] - level[originalLca];
        int total = dis1 + dis2;
 
        int elapsed = mid - t;
 
        int cur;
 
        if(elapsed >= total){
            cur = dest;
        }
        else if(elapsed <= dis1){
            cur = jump(u, elapsed);
        }
        else{
            cur = jump(dest, total - elapsed);
        }
 
        int x = lca(u, cur);
 
        diff[u]++;
        diff[cur]++;
        diff[x]--;
 
        if(par[x] != -1)
            diff[par[x]]--;
    }
 
    maxFound = 0;
    test(0, -1, g);
 
    return maxFound;
}
 
 
void solve() {
    int n, m; cin >> n >> m;
    vvi g(n);
    for(int i=0;i<n-1;i++){
        int u, v;cin >> u >> v;
        u--;v--;
 
        g[u].pb(v);
        g[v].pb(u);
    }
    par.assign(n, 0);
    level.assign(n, 0);
    dfs(0, -1, 0, g);
 
    lg = (int) (log(n) / log(2)) + 1;
    up.assign(n, vector<int>(lg, -1));
    for(int i=0;i<n;i++)up[i][0] = par[i];
    for(int j=1;j<lg;j++){
        for(int i=0;i<n;i++){
            if(up[i][j-1] != -1)
                up[i][j] = up[up[i][j-1]][j-1];
        }
    }
 
    vvi e(m);
    for(int i=0;i<m;i++){
        int t, a, b;cin >> t >> a >> b;
        a--;b--;
        e[i] = {t, a, b};
    }
 
    int hi = 1000000000LL + n - 1;
    maxOverall = can(hi, e, g);

    int l = 0, r = hi;
    int ans = hi;

    while(l <= r){
        int mid = l + (r-l)/2;
 
        int amt = can(mid, e, g);
        if(amt == maxOverall){
            ans = mid;
            r = mid-1;
        }
        else{
            l = mid+1;
        }
    }
    cout << ans << endl;
 
}
 
signed main() {
 
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int tc = 1;
    //cin >> tc;
 
    while(tc-- != 0)
        solve();
 
    return 0;
}
