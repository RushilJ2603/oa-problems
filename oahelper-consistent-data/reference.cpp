#include <iostream>

using namespace std;

int solve(int n) {
    long long e0 = 0;
    long long e1 = 0;
    long long mod = 1e9 + 7;
    for (int i = 1; i <= n; i++) {
        if (i % 2 != 0) {
            e0 = (e0 + e1 + 1) % mod;
        } else {
            e1 = (e1 + e0 + 1) % mod;
        }
    }
    return (int)((e0 + e1) % mod);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if (cin >> n) {
        cout << solve(n) << "\n";
    }
    return 0;
}
