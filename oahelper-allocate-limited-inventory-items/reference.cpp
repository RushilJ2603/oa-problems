#include <bits/stdc++.h>
using namespace std;

struct Req {
    int id;
    long long qty;
    long long ts;
    int ord;
};

vector<int> solve(vector<vector<long long>>& requests, long long totalInventory) {
    map<long long, vector<Req>, greater<long long>> byBid;
    set<int> allIds;
    for (size_t i = 0; i < requests.size(); ++i) {
        long long cid = requests[i][0];
        long long qty = requests[i][1];
        long long bid = requests[i][2];
        long long ts = requests[i][3];
        byBid[bid].push_back({(int)cid, qty, ts, (int)i});
        allIds.insert((int)cid);
    }
    set<int> got;
    long long inv = totalInventory;
    for (auto& [bid, reqs] : byBid) {
        if (inv <= 0) break;
        auto active = reqs;
        sort(active.begin(), active.end(), [](const Req& a, const Req& b) {
            if (a.ts != b.ts) return a.ts < b.ts;
            return a.ord < b.ord;
        });
        while (inv > 0 && !active.empty()) {
            long long k = (long long)active.size();
            if (inv < k) {
                for (long long i = 0; i < inv; ++i) got.insert(active[(size_t)i].id);
                inv = 0;
                break;
            }
            long long roundsByInv = inv / k;
            long long minQty = LLONG_MAX;
            for (auto& r : active) minQty = min(minQty, r.qty);
            long long rounds = min(roundsByInv, minQty);
            inv -= rounds * k;
            vector<Req> next;
            for (auto& r : active) {
                r.qty -= rounds;
                got.insert(r.id);
                if (r.qty > 0) next.push_back(r);
            }
            active.swap(next);
        }
    }
    vector<int> ans;
    for (int id : allIds)
        if (!got.count(id)) ans.push_back(id);
    sort(ans.begin(), ans.end());
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    int cols;
    cin >> cols;
    vector<vector<long long>> requests(n, vector<long long>(cols));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < cols; ++j)
            cin >> requests[i][j];
    long long totalInventory;
    cin >> totalInventory;
    vector<int> res = solve(requests, totalInventory);
    for (size_t i = 0; i < res.size(); ++i) {
        if (i) cout << ' ';
        cout << res[i];
    }
    cout << "\n";
    return 0;
}
