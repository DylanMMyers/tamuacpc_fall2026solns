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


void solve() {
    int n;
    cin >> n;

    // {S, X, Y, original index}
    vector<array<int, 4>> customers(n);

    for (int i = 0; i < n; i++) {
        int S, X, Y;
        cin >> S >> X >> Y;
        customers[i] = {S, X, Y, i};
    }

    sort(customers.begin(), customers.end(), [](auto const& l, auto const& r){ return l[1] < r[1]; });

    // {S, remaining time, id}
    priority_queue<array<int, 3>> pq;

    vector<int> finishTimes(n);

    int currTime = 0;

    for (auto [S, X, Y, id] : customers) {

        while (!pq.empty() && currTime < X) {
            auto [ps, remaining, pid] = pq.top();
            pq.pop();

            int available = X - currTime;

            if (remaining <= available) {
                currTime += remaining;
                finishTimes[pid] = currTime;
            }
            else {
                remaining -= available;
                currTime = X;

                pq.push({ps, remaining, pid});
            }
        }

        currTime = max(currTime, X);

        pq.push({S, Y, id});
    }

    while (!pq.empty()) {
        auto [S, remaining, id] = pq.top();
        pq.pop();

        currTime += remaining;
        finishTimes[id] = currTime;
    }

    for (int i = 0; i < n; i++) {
        cout << finishTimes[i] << "\n";
    }
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