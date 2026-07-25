#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
static const ll MOD = 1000000007LL;

pair<ll, ll> solve_one(int n, const vector<ll>& a, const vector<ll>& b, const vector<ll>& c) {
    ll total = 0;
    for (int i = 0; i < n; i++) total += a[i];

    ll lo = 1, hi = total / n, m = 1;
    while (lo <= hi) {
        ll mid = lo + (hi - lo) / 2;
        ll need = 0;
        bool over = false;
        for (int i = 0; i < n; i++) {
            need += (mid > b[i] ? mid : b[i]);
            if (need > total) {
                over = true;
                break;
            }
        }
        if (!over) {
            m = mid;
            lo = mid + 1;
        } else
            hi = mid - 1;
    }

    ll slack = total;
    vector<pair<ll, ll>> donors;
    donors.reserve(n);
    for (int i = 0; i < n; i++) {
        ll low = (m > b[i] ? m : b[i]);
        slack -= low;
        if (a[i] > low) donors.push_back({c[i], a[i] - low});
    }
    sort(donors.begin(), donors.end(),
         [](const pair<ll, ll>& x, const pair<ll, ll>& y) { return x.first > y.first; });

    ll cost = 0;
    for (auto& pr : donors) {
        ll keep;
        if (slack >= pr.second) {
            slack -= pr.second;
            keep = 0;
        } else {
            keep = pr.second - slack;
            slack = 0;
        }
        if (keep) cost = (cost + (pr.first % MOD) * (keep % MOD)) % MOD;
    }
    return {m, cost % MOD};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    string out;
    while (T--) {
        int n;
        cin >> n;
        vector<ll> a(n), b(n), c(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];
        for (int i = 0; i < n; i++) cin >> c[i];
        auto [m, cost] = solve_one(n, a, b, c);
        out += to_string(m);
        out += ' ';
        out += to_string(cost);
        out += '\n';
    }
    cout << out;
    return 0;
}
