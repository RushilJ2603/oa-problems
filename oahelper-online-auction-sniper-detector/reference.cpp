#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> solve(int N, long long W, int K,
                            vector<long long>& t, vector<int>& u) {
    unordered_map<int, int> cnt;
    cnt.reserve(N * 2);
    set<int> qualifying;
    int left = 0;
    vector<pair<int,int>> res;
    res.reserve(N);
    for (int i = 0; i < N; i++) {
        int c = ++cnt[u[i]];
        if (c == K) qualifying.insert(u[i]);
        long long lo = t[i] - W;
        while (t[left] < lo) {
            int uu = u[left];
            int nc = --cnt[uu];
            if (nc == K - 1) qualifying.erase(uu);
            left++;
        }
        int flag = (cnt[u[i]] >= K) ? 1 : 0;
        int smallest = qualifying.empty() ? -1 : *qualifying.begin();
        res.push_back({flag, smallest});
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, K;
    long long W;
    if (!(cin >> N >> W >> K)) return 0;
    vector<long long> t(N);
    vector<int> u(N);
    for (int i = 0; i < N; i++) cin >> t[i] >> u[i];
    auto res = solve(N, W, K, t, u);
    for (auto &p : res) cout << p.first << " " << p.second << "\n";
    return 0;
}
