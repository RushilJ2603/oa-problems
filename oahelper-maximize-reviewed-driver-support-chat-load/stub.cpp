#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<long long>& chatLoad, int k, vector<int>& reviewMinutes) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> chatLoad(n);
    for (auto& x : chatLoad) cin >> x;
    int k;
    cin >> k;
    vector<int> reviewMinutes(k);
    for (auto& x : reviewMinutes) cin >> x;
    cout << solve(n, chatLoad, k, reviewMinutes) << "\n";
    return 0;
}
