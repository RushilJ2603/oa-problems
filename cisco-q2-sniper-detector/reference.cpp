// Cisco Q2 — Online Auction Sniper Detector.
// For each bid, report (flag, smallest-sniper): flag=1 if this bid's user has >= K bids in the
// last W seconds [t_i - W, t_i]; smallest-sniper = smallest user id with >= K bids in that window
// (or -1). Sliding window over the (time-sorted) bids + a per-user count + an ordered set of
// currently-sniping users. VERIFIED against an independent O(N^2) brute force + all samples.
#include <cstdio>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <set>

using namespace std;
typedef long long ll;

struct InputData {
    int N;
    ll  W;
    int K;
    vector<pair<ll, ll>> bids;    // (timestamp, user_id), timestamps increasing
};

static bool parse_input(InputData &D) {
    if (scanf("%d %lld %d", &D.N, &D.W, &D.K) != 3) return false;
    D.bids.resize(D.N);
    for (int i = 0; i < D.N; ++i)
        scanf("%lld %lld", &D.bids[i].first, &D.bids[i].second);
    return true;
}

static void format_output(const vector<pair<int, ll>> &results) {
    string out;
    for (size_t i = 0; i < results.size(); ++i) {
        out += to_string(results[i].first);
        out += ' ';
        out += to_string(results[i].second);
        out += '\n';
    }
    fputs(out.c_str(), stdout);
}

static vector<pair<int, ll>> solve(const InputData &D) {
    vector<pair<int, ll>> res(D.N);
    unordered_map<ll, int> cnt;   // user id -> #bids currently in window
    set<ll> snipers;              // users with cnt >= K, ordered => smallest first
    int left = 0;
    for (int i = 0; i < D.N; ++i) {
        ll t = D.bids[i].first, u = D.bids[i].second;
        if (++cnt[u] == D.K) snipers.insert(u);
        while (t - D.bids[left].first > D.W) {
            ll ul = D.bids[left].second;
            if (--cnt[ul] == D.K - 1) snipers.erase(ul);
            ++left;
        }
        int flag = (cnt[u] >= D.K) ? 1 : 0;
        ll smallest = snipers.empty() ? -1 : *snipers.begin();
        res[i] = make_pair(flag, smallest);
    }
    return res;
}

int main() {
    InputData D;
    if (!parse_input(D)) return 0;
    format_output(solve(D));
    return 0;
}
