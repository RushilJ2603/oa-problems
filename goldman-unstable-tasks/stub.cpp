#include <bits/stdc++.h>
using namespace std;

// Count tasks whose limit sequence (ordered by increasing timestamp) both rises and falls.
int countUnstable(vector<string>& task, vector<long long>& timestamp, vector<long long>& limit) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<string> task(n);
    for (auto& s : task) cin >> s;
    vector<long long> timestamp(n), limit(n);
    for (auto& x : timestamp) cin >> x;
    for (auto& x : limit) cin >> x;
    cout << countUnstable(task, timestamp, limit) << "\n";
    return 0;
}
