#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; if (!(cin >> n)) return 0;
    long long a = 1, b = 1;        // ways to reach step 0 and step 1
    for (int i = 2; i <= n; ++i) { long long c = a + b; a = b; b = c; }
    cout << b << "\n";
    return 0;
}
