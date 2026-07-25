#include <bits/stdc++.h>
using namespace std;

struct Meeting {
    long long s, e, p;
    int id;
};

struct ByEnd {
    long long e, p;
    int id;
    bool operator<(const ByEnd& o) const {
        if (e != o.e) return e < o.e;
        if (p != o.p) return p < o.p;
        return id < o.id;
    }
};

struct ByPrio {
    long long p, e;
    int id;
    bool operator<(const ByPrio& o) const {
        if (p != o.p) return p < o.p;
        if (e != o.e) return e < o.e;
        return id < o.id;
    }
};

long long solve(int n, int r, vector<Meeting> meetings) {
    sort(meetings.begin(), meetings.end(), [](const Meeting& a, const Meeting& b) {
        if (a.s != b.s) return a.s < b.s;
        if (a.p != b.p) return a.p > b.p;
        return a.id < b.id;
    });

    set<ByEnd> by_end;
    set<ByPrio> by_prio;
    long long total = 0;

    for (const auto& m : meetings) {
        while (!by_end.empty() && by_end.begin()->e <= m.s) {
            auto it = by_end.begin();
            by_prio.erase(ByPrio{it->p, it->e, it->id});
            by_end.erase(it);
        }

        if ((int)by_end.size() < r) {
            by_end.insert({m.e, m.p, m.id});
            by_prio.insert({m.p, m.e, m.id});
            total += m.p;
        } else if (!by_prio.empty() && m.p > by_prio.begin()->p) {
            auto lo = *by_prio.begin();
            total = total - lo.p + m.p;
            by_prio.erase(by_prio.begin());
            by_end.erase(ByEnd{lo.e, lo.p, lo.id});
            by_end.insert({m.e, m.p, m.id});
            by_prio.insert({m.p, m.e, m.id});
        }
    }
    return total;
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
    int n, r;
    if (!(ss >> n >> r)) return 0;
    vector<Meeting> meetings(n);
    for (int i = 0; i < n; i++) {
        ss >> meetings[i].s >> meetings[i].e >> meetings[i].p;
        meetings[i].id = i;
    }
    cout << solve(n, r, meetings) << "\n";
    return 0;
}
