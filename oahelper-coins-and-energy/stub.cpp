#include <bits/stdc++.h>
using namespace std;

int getRich(long long initialEnergy, vector<int>& energy, vector<int>& coins) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    long long initialEnergy;
    if (!(cin >> initialEnergy)) return 0;
    int n; cin >> n;
    vector<int> energy(n);
    for (int i = 0; i < n; i++) cin >> energy[i];
    int m; cin >> m;
    vector<int> coins(m);
    for (int i = 0; i < m; i++) cin >> coins[i];
    cout << getRich(initialEnergy, energy, coins) << "\n";
    return 0;
}
