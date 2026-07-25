#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<tuple<int,int,long long>>& meetings) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<tuple<int,int,long long>> meetings(n);
    for (int i = 0; i < n; i++) {
        int s, e;
        long long p;
        cin >> s >> e >> p;
        meetings[i] = {s, e, p};
    }
    cout << solve(n, meetings) << "\n";
    return 0;
}
