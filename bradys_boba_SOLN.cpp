#include <iostream>
#include <vector>

using std::cin, std::cout, std::vector;

int main() {
    int D, P; cin >> D >> P;
    vector<int> d_counts(2001, 0);
    vector<int> p_counts(2001, 0);

    for (int i = 0; i < D; i++) {
        int d; cin >> d;
        d_counts[d] += 1;
    }
    for (int i = 0; i < P; i++) {
        int p; cin >> p;
        p_counts[p] += 1;
    }

    int total = D * P;

    for (int i = 0; i < 2001; i++) {
        total -= d_counts[i] * p_counts[i];
    }

    cout << total << "\n";
}