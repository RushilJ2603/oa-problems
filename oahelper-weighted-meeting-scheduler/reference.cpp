#include <bits/stdc++.h>
using namespace std;

struct Meeting {
    int start, end;
    long long payment;
};

long long solve(int n, vector<Meeting>& meetings) {
    sort(meetings.begin(), meetings.end(), [](const Meeting& a, const Meeting& b) {
        return a.end < b.end;
    });

    vector<int> ends(n);
    for (int i = 0; i < n; ++i) ends[i] = meetings[i].end;

    vector<long long> dp(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int count = upper_bound(ends.begin(), ends.end(), meetings[i - 1].start) - ends.begin();
        dp[i] = max(dp[i - 1], meetings[i - 1].payment + dp[count]);
    }
    return dp[n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    if (!(cin >> N)) return 0;
    vector<Meeting> meetings(N);
    for (int i = 0; i < N; ++i)
        cin >> meetings[i].start >> meetings[i].end >> meetings[i].payment;
    cout << solve(N, meetings) << "\n";
    return 0;
}
