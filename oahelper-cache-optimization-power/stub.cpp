#include <iostream>
#include <vector>

using namespace std;

long long solve(int n, const vector<long long>& power) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> power(n);
    for (int i = 0; i < n; i++) {
        cin >> power[i];
    }
    cout << solve(n, power) << "\n";
    return 0;
}
