#include <bits/stdc++.h>
using namespace std;

long long solve(const string& color) {
    long long zeros = 0;
    long long seconds = 0;
    for (char c : color) {
        if (c == '0') {
            ++zeros;
        } else if (zeros > 0) {
            seconds = max(seconds + 1, zeros);
        }
    }
    return seconds;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string color;
    if (!(cin >> color)) return 0;
    cout << solve(color) << "\n";
    return 0;
}
