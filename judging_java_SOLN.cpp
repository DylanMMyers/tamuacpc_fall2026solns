#include <iostream>
#include <cstdlib>
#include <vector>
#include <numeric>

using namespace std;

vector<vector<int>> beat_list(1025);

bool first_wins(int i, int j){
    cout << "? " << i << " " << j << endl;

    int a;
    cin >> a;
    if (a == -1) exit(0);

    if (a == 1) {
        beat_list[i].push_back(j);
    } else {
        beat_list[j].push_back(i);
    }

    return a == 1;
}

int main() {
    int n;
    cin >> n;

    vector<int> coffee_remaining(n);
    iota(coffee_remaining.begin(), coffee_remaining.end(), 1);
    vector<int> temp;
    
    // find the best via a tournament bracket
    while (coffee_remaining.size() > 1){
        for (int i = 0; i < coffee_remaining.size(); i+=2){
            if (first_wins(coffee_remaining[i], coffee_remaining[i+1])) {
                temp.push_back(coffee_remaining[i]);
            } else {
                temp.push_back(coffee_remaining[i+1]);
            }
        }
        coffee_remaining = temp;
        temp.clear();
    }

    // find the second best via search of the best's competitors
    int best = coffee_remaining[0];
    vector<int> &candidates = beat_list[best];
    
    int ans = candidates[0];
    for (int i = 1; i < candidates.size(); i++) {
        if (!first_wins(ans, candidates[i])) {
            ans = candidates[i];
        }
    }
    cout << "! " << ans;
    cout << endl;
}


