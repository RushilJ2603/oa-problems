#include <bits/stdc++.h>
using namespace std;

int solve(int rows, int cols, vector<vector<int>>& grid,
          int sr, int sc, int er, int ec, int B,
          vector<pair<int,int>>& stations, int K) {
    if (sr == er && sc == ec) return 0;

    vector<vector<char>> isKiosk(rows, vector<char>(cols, 0));
    for (auto& st : stations) isKiosk[st.first][st.second] = 1;

    int Bp1 = B + 1, Kp1 = K + 1;
    long long total = 1LL * rows * cols * Bp1 * Kp1;
    vector<int> dist((size_t)total, INT_MAX);

    auto idx = [&](int r, int c, int b, int k) -> long long {
        return (((long long)r * cols + c) * Bp1 + b) * Kp1 + k;
    };

    deque<long long> dq;
    long long startIdx = idx(sr, sc, B, 0);
    dist[(size_t)startIdx] = 0;
    dq.push_back(startIdx);

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    while (!dq.empty()) {
        long long cur = dq.front();
        dq.pop_front();
        int k = (int)(cur % Kp1);
        long long tmp = cur / Kp1;
        int b = (int)(tmp % Bp1);
        tmp /= Bp1;
        int c = (int)(tmp % cols);
        int r = (int)(tmp / cols);
        int d = dist[(size_t)cur];

        if (b > 0) {
            for (int dir = 0; dir < 4; dir++) {
                int nr = r + dr[dir], nc = c + dc[dir];
                if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
                if (grid[nr][nc] == 1) continue;
                long long nidx = idx(nr, nc, b - 1, k);
                if (dist[(size_t)nidx] > d + 1) {
                    dist[(size_t)nidx] = d + 1;
                    dq.push_back(nidx);
                }
            }
        }

        if (isKiosk[r][c] && k < K && b < B) {
            long long nidx = idx(r, c, B, k + 1);
            if (dist[(size_t)nidx] > d) {
                dist[(size_t)nidx] = d;
                dq.push_front(nidx);
            }
        }
    }

    int best = INT_MAX;
    for (int b = 0; b <= B; b++)
        for (int k = 0; k <= K; k++)
            best = min(best, dist[(size_t)idx(er, ec, b, k)]);
    return best == INT_MAX ? -1 : best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int rows, cols;
    if (!(cin >> rows >> cols)) return 0;
    vector<vector<int>> grid(rows, vector<int>(cols));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            cin >> grid[i][j];
    int sr, sc, er, ec, B, M, K;
    cin >> sr >> sc >> er >> ec >> B >> M;
    vector<pair<int,int>> stations(M);
    for (int i = 0; i < M; i++)
        cin >> stations[i].first >> stations[i].second;
    cin >> K;
    cout << solve(rows, cols, grid, sr, sc, er, ec, B, stations, K) << "\n";
    return 0;
}
