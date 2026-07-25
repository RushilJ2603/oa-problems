#include <bits/stdc++.h>
using namespace std;

string solve(int n, const string& s, long long k, long long f) {
    vector<array<int, 26>> suffixCnt(n + 1), nxt(n + 1);
    suffixCnt[n].fill(0);
    nxt[n].fill(n);
    for (int j = n - 1; j >= 0; j--) {
        suffixCnt[j] = suffixCnt[j + 1];
        nxt[j] = nxt[j + 1];
        int cj = s[j] - 'a';
        suffixCnt[j][cj]++;
        nxt[j][cj] = j;
    }

    auto maxSum = [&](int j, long long m) -> long long {
        if (m <= 0) return 0;
        long long total = 0;
        for (int c = 25; c >= 0; c--) {
            long long avail = suffixCnt[j][c];
            if (!avail) continue;
            long long take = m < avail ? m : avail;
            total += take * (c + 1);
            m -= take;
            if (m == 0) break;
        }
        return total;
    };

    string out;
    out.reserve(k);
    int lo = 0;
    long long need = f;
    for (long long step = 0; step < k; step++) {
        long long remaining = k - step;
        long long limit = n - remaining;
        for (int c = 0; c < 26; c++) {
            int pos = nxt[lo][c];
            if (pos > limit) continue;
            if (maxSum(pos + 1, remaining - 1) >= need - (c + 1)) {
                out.push_back(char('a' + c));
                need -= (c + 1);
                lo = pos + 1;
                break;
            }
        }
    }
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    string s;
    cin >> s;
    long long k, f;
    cin >> k >> f;
    cout << solve(n, s, k, f) << "\n";
    return 0;
}
