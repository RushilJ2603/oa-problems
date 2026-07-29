#include <bits/stdc++.h>
using namespace std;

// Greedy with a max-heap: drive forward, and remember the fuel of every station passed. Whenever the
// tank can't reach the next needed point, "retroactively" take the largest passed refuel (one stop).
// Each stop we make is the best fuel available so far, so the number of stops is minimal.
int solve(long long target, long long startFuel, vector<pair<long long,long long>> st) {
    sort(st.begin(), st.end());
    priority_queue<long long> pq;
    long long fuel = startFuel;
    int stops = 0, i = 0, n = (int)st.size();
    while (fuel < target) {
        while (i < n && st[i].first <= fuel) { pq.push(st[i].second); i++; }
        if (pq.empty()) return -1;           // stuck: nothing left to refuel with
        fuel += pq.top(); pq.pop();
        stops++;
    }
    return stops;
}

int main() {
    long long target, startFuel;
    if (scanf("%lld %lld", &target, &startFuel) != 2) return 0;
    int n;
    if (scanf("%d", &n) != 1) n = 0;
    vector<pair<long long,long long>> st(n);
    for (auto &p : st) scanf("%lld %lld", &p.first, &p.second);
    printf("%d\n", solve(target, startFuel, st));
    return 0;
}
