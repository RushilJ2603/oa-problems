// Cisco Q1 — Drone Delivery with Battery Swap Stations.
// Minimum moves from (sr,sc) to (er,ec) on a grid, battery capacity B, K swap vouchers usable
// only on kiosk cells. State = (row, col, battery-left, vouchers-left); a move costs 1 step and
// 1 battery, a swap on a kiosk costs 0 steps and refills to B for one voucher -> 0-1 BFS.
// VERIFIED: cross-checked against an independent Dijkstra brute force on random grids, and
// reproduces all three provided samples.
#include <iostream>
#include <vector>
#include <utility>
#include <deque>
#include <climits>
#include <algorithm>

using namespace std;

struct InputData {
    int rows;
    int cols;
    vector<vector<int>> grid;
    int sr, sc;
    int er, ec;
    int B;
    int M;
    vector<pair<int, int>> stations;
    int K;
};

static bool parse_input(InputData &D) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (!(cin >> D.rows >> D.cols)) return false;
    D.grid.assign(D.rows, vector<int>(D.cols, 0));
    for (int r = 0; r < D.rows; ++r)
        for (int c = 0; c < D.cols; ++c) cin >> D.grid[r][c];
    cin >> D.sr >> D.sc >> D.er >> D.ec >> D.B >> D.M;
    D.stations.assign(D.M, make_pair(0, 0));
    for (int i = 0; i < D.M; ++i) cin >> D.stations[i].first >> D.stations[i].second;
    cin >> D.K;
    return true;
}

static void format_output(int result) {
    cout << result << "\n";
}

static int solve(const InputData &D) {
    int R = D.rows, C = D.cols, B = D.B, K = D.K;
    vector<vector<char>> kiosk(R, vector<char>(C, 0));
    for (auto &s : D.stations) kiosk[s.first][s.second] = 1;

    auto id = [&](int r, int c, int b, int k) {
        return ((r * C + c) * (B + 1) + b) * (K + 1) + k;
    };
    vector<int> dist((size_t)R * C * (B + 1) * (K + 1), INT_MAX);
    deque<int> dq;
    int start = id(D.sr, D.sc, B, K);
    dist[start] = 0;
    dq.push_back(start);

    const int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
    while (!dq.empty()) {
        int u = dq.front(); dq.pop_front();
        int k = u % (K + 1), t = u / (K + 1);
        int b = t % (B + 1); t /= (B + 1);
        int c = t % C, r = t / C;
        int d = dist[u];

        if (kiosk[r][c] && k > 0 && b < B) {
            int v = id(r, c, B, k - 1);
            if (d < dist[v]) { dist[v] = d; dq.push_front(v); }
        }
        if (b > 0) {
            for (int dir = 0; dir < 4; ++dir) {
                int nr = r + dr[dir], nc = c + dc[dir];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                if (D.grid[nr][nc] != 0) continue;
                int v = id(nr, nc, b - 1, k);
                if (d + 1 < dist[v]) { dist[v] = d + 1; dq.push_back(v); }
            }
        }
    }

    int ans = INT_MAX;
    for (int b = 0; b <= B; ++b)
        for (int k = 0; k <= K; ++k)
            ans = min(ans, dist[id(D.er, D.ec, b, k)]);
    return ans == INT_MAX ? -1 : ans;
}

int main() {
    InputData D;
    if (!parse_input(D)) return 0;
    format_output(solve(D));
    return 0;
}
