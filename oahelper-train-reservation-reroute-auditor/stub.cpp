#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Event {
    int type;  // 0 = BOOK, 1 = QUERY
    int l, r;
    ll p;
};

vector<ll> solve(int M, int N, ll T, const vector<Event>& events) {
    // WRITE YOUR CODE HERE
    return {};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string raw((istreambuf_iterator<char>(cin)), istreambuf_iterator<char>());
    string normalized;
    normalized.reserve(raw.size());
    for (size_t i = 0; i < raw.size(); ++i) {
        if (raw[i] == '\\' && i + 1 < raw.size() && raw[i + 1] == 'n') {
            normalized.push_back('\n');
            ++i;
        } else {
            normalized.push_back(raw[i]);
        }
    }

    stringstream ss(normalized);
    int M, N;
    ll T;
    if (!(ss >> M >> N >> T)) return 0;

    vector<Event> events;
    events.reserve(N);
    for (int i = 0; i < N; ++i) {
        string op;
        ss >> op;
        if (op == "BOOK") {
            int l, r;
            ll p;
            ss >> l >> r >> p;
            events.push_back({0, l, r, p});
        } else {
            int l, r;
            ss >> l >> r;
            events.push_back({1, l, r, 0});
        }
    }

    vector<ll> ans = solve(M, N, T, events);
    for (ll x : ans) cout << x << '\n';
    return 0;
}
