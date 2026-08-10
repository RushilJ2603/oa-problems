#include <bits/stdc++.h>
using namespace std;

bool canSchedule(long long capacity, const vector<array<long long, 3>> &shows) {
    // WRITE YOUR CODE HERE
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long capacity;
    int n;
    if (!(cin >> capacity)) return 0;
    cin >> n;
    vector<array<long long, 3>> shows(n);   // {start_time, end_time, attendees}
    for (int i = 0; i < n; i++) cin >> shows[i][0] >> shows[i][1] >> shows[i][2];
    cout << (canSchedule(capacity, shows) ? "True" : "False") << "\n";
    return 0;
}
