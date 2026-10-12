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
using ld = long double;

#define pqueue priority_queue
#define int long long

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define read(x) for(int i=0;i<x.size();i++)cin >> x[i];


const int mod = (int)(1e9+7);

vector<vector<ll>> matMult(vector<vector<ll>> mat1, vector<vector<ll>> mat2){ // multiply two matricies together
    int R1 = mat1.size(), C1 = mat1[0].size();
    int R2 = mat2.size(), C2 = mat2[0].size();
 
    vector<vector<ll>> res(R1, vector<ll>(C2, 0));
 
    for (int i = 0; i < R1; i++) {
        for (int j = 0; j < C2; j++) {
            res[i][j] = 0;
            for (int k = 0; k < R2; k++) {
                res[i][j] = (res[i][j] + mat1[i][k] * mat2[k][j] % mod) % mod;
            }
        }
    }
    return res;
}
 
vector<vector<ll>> matPower(vector<vector<ll>> A, ll b){ //A to the b power
    vector<vector<ll>> res = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}; // 3x3 identity matrix
 
    while(b){
        if(b&1)res = matMult(res, A);
        A = matMult(A, A);
        b >>= 1;
    }
    return res;
}
 


signed main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); 

    //ll is long long

    ll N, A, B;
    cin >> N >> A >> B;

    if(N <= 3){
        if(N <= 2)cout << 1 << endl;
        else cout << ((A + B) % mod) << endl;
        return 0;
    }

    vector<vector<ll>> initial = {{(A+B)%mod}, {1}, {1}};
    vector<vector<ll>> next = {{0, A, B}, {1, 0, 0}, {0, 1, 0}};
    vector<vector<ll>> res = matMult(matPower(next, N-3), initial);

    cout << res[0][0] << endl;

    return 0;
}