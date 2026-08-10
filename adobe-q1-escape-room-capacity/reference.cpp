#include <bits/stdc++.h>
using namespace std;

// Nothing changes the occupancy except a show starting or a show ending, so the whole timeline
// collapses to those <= 2N instants. Record each show as a pair of DELTAS
//
//     +attendees at start_time      -attendees at end_time
//
// and sweep the instants in order, keeping a running sum. Because both deltas for a given instant
// live in the same map entry, the departures and arrivals at time t are applied together before the
// sum is inspected — which is exactly the "[start, end)" rule: a show ending at t has already
// released the room to a show starting at t. A show with start == end contributes +a and -a to the
// same key and cancels, which is also what the rule says.
//
// The running sum reaches 10^5 * 10^9 = 10^14, so it must be 64-bit.
bool canSchedule(long long capacity, const vector<array<long long, 3>> &shows) {
    map<long long, long long> delta;
    for (const auto &s : shows) {
        delta[s[0]] += s[2];
        delta[s[1]] -= s[2];
    }
    long long inside = 0;
    for (const auto &kv : delta) {
        inside += kv.second;
        if (inside > capacity) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long capacity;
    int n;
    if (!(cin >> capacity)) return 0;
    cin >> n;
    vector<array<long long, 3>> shows(n);
    for (int i = 0; i < n; i++) cin >> shows[i][0] >> shows[i][1] >> shows[i][2];
    cout << (canSchedule(capacity, shows) ? "True" : "False") << "\n";
    return 0;
}
