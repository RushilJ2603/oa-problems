// Cisco Q1 — Drone Delivery with Battery Swap Stations.
// The harness (struct + parse_input + format_output + main) is fixed. Fill in solve().
#include <iostream>
#include <vector>
#include <utility>

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
    // Single integer: the minimum number of moves, or -1 if infeasible.
    cout << result << "\n";
}

static int solve(const InputData &D) {
    // TODO: minimum moves from (sr,sc) to (er,ec).
    //   state = (row, col, battery-left, vouchers-left)
    //   move  -> 1 step, costs 1 battery (needs battery >= 1)
    //   swap on a kiosk with a voucher -> 0 steps, refills battery to B
    // 0-1 BFS (deque) or Dijkstra. Return -1 if the customer is unreachable.
    (void)D;
    return -1;
}

int main() {
    InputData D;
    if (!parse_input(D)) return 0;
    format_output(solve(D));
    return 0;
}
