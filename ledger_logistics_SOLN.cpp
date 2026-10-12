#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <climits> 
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>

using namespace std;

#define all(a) (a).begin(), (a).end()
#define REP(i, a, b) for (int i = a; i <= b; i++)
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define dbg(v) cout << "Line(" << __LINE__ << ") -> " << #v << " = " << (v) << endl;
#define nl '\n'
#define cinall(A) for(auto& e : A) cin >> e;
#define setmax(A, B) A = max(A, B)
#define setmin(A, B) A = min(A, B)

typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<vector<int>>> vvvi;
typedef vector<long long> vll;
typedef vector<vector<long long>> vvll;
typedef vector<vector<vector<long long>>> vvvll;
typedef vector<bool> vb; 
typedef vector<string> vs;
typedef vector<vector<string>> vvs;
typedef long long ll;
typedef pair<int, int> pi;
typedef vector<pair<int, int>> vpi; 
typedef map<int, int> mi;


template <typename T> 
void output_vec(const std::vector<T>& vec) {
    for (auto& e : vec) {
        cout << e << " ";
    }
    cout << '\n';
}

template <typename Container, typename F> 
void output_container(const Container& c, F printer) {
    for (auto e : c) {
        printer(e);
        cout << " ";
    }
    cout << nl;
}

template<typename T1, typename T2> 
void output_pair(const pair<T1, T2>& p) {
    cout << "<" << p.f << " " << p.s << ">";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m; 
    vvi a(n, vi(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cin >> a[i][j]; 
    }

    bool ok = true; 
    if (n == 1 || m == 1) {
        for (int i = 1; i < n; i++) {
            ok &= a[i][0] > a[i-1][0]; 
        }
        for (int j = 1; j < m; j++) {
            ok &= a[0][j] > a[0][j-1]; 
        }
    } else {
        ll E1 = 0; 
        ll E2 = 0;
        ll M1 = 0, M2 = 0;
        ll S1 = 0, S2 = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if ((i + j) & 1) {
                    M1 += i + j;
                    S1 += a[i][j];
                } else {
                    M2 += i + j;
                    S2 += a[i][j];
                }
            }
        }
        ok &= (S1 >= M1) && (S2 >= M2);
        E1 = S1 - M1; 
        E2 = S2 - M2; 
    
        if ((n + m - 2) & 1) {
            ok &= (E2 <= 2*E1); 
        } else {
            ok &= (E1 <= 2*E2);
        }
    }
    cout << (ok ? "YES" : "NO") << nl;
}
