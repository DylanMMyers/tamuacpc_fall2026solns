#include <iostream>

using std::cin, std::cout;

int main() {
    int T; cin >> T;
    while (T--) {
        int p; cin >> p;

        int m = 9999;
        for (int x_part = 0; x_part < 100; x_part++) {
            int a = x_part / 10 % 10;
            int b = x_part % 10;

            int xs[3] = {
                a * 1000 + b * 100 + 67,
                a * 1000 + 670 + b,
                6700 + a * 10 + b
            };

            for (int x : xs) {
                bool has_67 = false;
                int px = p + x;
                while (px > 0) {
                    if (px % 100 == 67) {
                        has_67 = true;
                        break;
                    }
                    px /= 10;
                }
                if (has_67) {
                    m = std::min(m, x);
                }
            }
        }

        cout << m << "\n";
    }
}