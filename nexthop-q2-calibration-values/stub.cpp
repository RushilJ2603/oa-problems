#include <bits/stdc++.h>
using namespace std;

long long calibrationValue(const string &s) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    long long total = 0;
    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        total += calibrationValue(s);
    }
    cout << total << "\n";
    return 0;
}
