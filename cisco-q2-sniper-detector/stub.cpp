// Cisco Q2 — Online Auction Sniper Detector.
// The harness (struct + parse_input + format_output + main) is fixed. Fill in solve().
#include <cstdio>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <set>

using namespace std;
typedef long long ll;

struct InputData {
    int N;                        // number of bids
    ll  W;                        // window length (seconds)
    int K;                        // sniping threshold (bids per user)
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
    // One line per bid: "<flag> <smallest_sniper>"
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
    // TODO: for each bid i, return (flag, smallest_sniper).
    //   window for bid i is [t_i - W, t_i]; a past bid at t' counts iff t_i - t' <= W.
    //   flag    = 1 if bid i's user has >= K bids in that window, else 0.
    //   smallest_sniper = smallest user id with >= K bids in the window, or -1.
    // Slide a window over the (already time-sorted) bids; keep a per-user count (hash map, since
    // ids reach 1e9) and an ordered set of users currently at >= K so the smallest is set.begin().
    return vector<pair<int, ll>>(D.N, make_pair(0, (ll)-1));
}

int main() {
    InputData D;
    if (!parse_input(D)) return 0;
    format_output(solve(D));
    return 0;
}
