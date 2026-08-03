#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

long long solve(int Xp, int Yp, const vector<pair<int, int>>& trees,
                vector<Point> building) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int Xp, Yp, N;
    if (!(cin >> Xp >> Yp >> N)) return 0;
    vector<pair<int, int>> trees(N);
    for (int i = 0; i < N; ++i) cin >> trees[i].first >> trees[i].second;
    int K;
    cin >> K;
    vector<Point> building(K);
    for (int i = 0; i < K; ++i) cin >> building[i].x >> building[i].y;
    cout << solve(Xp, Yp, trees, building) << "\n";
    return 0;
}
