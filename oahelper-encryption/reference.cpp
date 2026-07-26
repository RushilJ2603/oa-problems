#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

long long solve(string S) {
    int n = (int)S.size();
    vector<char> C(S.begin(), S.end());
    sort(C.begin(), C.end());
    vector<long long> p2(n + 1, 1);
    for (int i = 1; i <= n; i++) p2[i] = (p2[i - 1] * 2) % MOD;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int j = i;
        while (j + 1 < n && (int)C[j + 1] - (int)C[i] <= 17) j++;
        // subsequences that include C[i] as their leftmost (smallest-index in sorted) char
        ans = (ans + p2[j - i]) % MOD;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string S;
    if (!(cin >> S)) return 0;
    cout << solve(S) << "\n";
    return 0;
}
