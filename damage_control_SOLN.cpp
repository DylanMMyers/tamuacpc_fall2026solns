#include <bits/stdc++.h>
#define ll long long
#define ld double
using namespace std;
// Get-Content t.txt | .\coffee_spill.exe
// g++ coffee_spill.cpp -o coffee_spill

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    vector<vector<ld>> p(n, vector<ld>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> p[i][j];
            p[i][j] /= 100.0;
        }
    }
    vector<ll> v(k), t(k);
    for (int i = 0; i < k; i++) {
        cin >> v[i] >> t[i];
    }
    // dp over each item to establish the expected loss/cost of an item
    // c[T][K] tells us the expected loss if item K is on table at time T
    // this ensures that we don't double count an item which would've already lost value
    // we can do this since k is small
    vector<vector<ld>> c(n + m - 1, vector<ld>(k));
    for (int i = 0; i < k; i++) {
        vector<vector<ld>> dp(n, vector<ld>(m));
        dp[0][0] = 1;
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < m; y++) {
                if (x > 0) {
                    dp[x][y] += dp[x - 1][y] * (1 - p[x - 1][y]);
                }
                if (y > 0) {
                    dp[x][y] += dp[x][y - 1] * p[x][y - 1];
                }
                if (a[x][y] == i + 1) {
                    c[x + y][i] += dp[x][y];
                    dp[x][y] = 0;
                }
            }
        }
    }
    // build ps array for ev of each item, used in next step
    vector<vector<ld>> ps(k, vector<ld>(n + m));
    for (int i = 0; i < k; i++) {
        for (int j = 1; j < n + m; j++) {
            ps[i][j] = ps[i][j - 1] + c[j - 1][i];
        }
    }
    // now that we have the expected loss, we can try every permutation
    // dp[mask] holds the lowest expected loss at time T
    // we can do this with bitmask dp since (same as before) k is small
    vector<pair<ld,int>> dp((1 << k) + 1, make_pair(2e10 + 1, 0));
    dp[0] = make_pair(0, 0);
    for (int mask = 0; mask < (1 << k); mask++) {
        ll curr_t = 0;
        for (int j = 0; j < k; j++) {
            if ((1 << j) & mask) curr_t += t[j];
        }
        for (int i = 0; i < k; i++) {
            if (!((mask >> i) & 1)) {
                int mask_new = mask | (1 << i);
                ld ev = ps[i][min<ll>(curr_t + t[i], n + m - 1)] * v[i];
                if (dp[mask].first + ev < dp[mask_new].first) {
                    dp[mask_new] = make_pair(dp[mask].first + ev, i);
                }
            }
        }
    }
    // then, walk down the mask to get the perm that provided the optimal ev
    vector<int> perm(k);
    ll mask = 0;
    for (int i = 0; i < k; i++) mask += (1 << i);
    for (int i = 0; i < k; i++) {
        perm[k - i - 1] = dp[mask].second;
        mask -= (1 << dp[mask].second);
    }
    for (int i = 0; i < k; i++) cout << perm[i] + 1 << ' ';
}