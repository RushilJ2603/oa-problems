#include <bits/stdc++.h>
using namespace std;

// The grid is infinite, but activity spreads by at most one cell per cycle, so after T cycles
// nothing outside a T-cell margin around the starting slice can be active. Allocate exactly that
// margin and the finite array is EXACT, not an approximation: a cube outside it is provably
// inactive, so treating out-of-range neighbours as inactive is correct rather than a truncation.
//
//   x, y : R + 2T  and  C + 2T   (the slice, padded by T on each side)
//   z    : 2T + 1                (the slice sits at z = T; that plane is the original one)
long long conwayCubes(int T, const vector<string> &slice) {
    const int R = (int)slice.size();
    const int C = R ? (int)slice[0].size() : 0;
    const int X = R + 2 * T, Y = C + 2 * T, Z = 2 * T + 1;
    vector<vector<vector<unsigned char>>> cur(
        Z, vector<vector<unsigned char>>(X, vector<unsigned char>(Y, 0)));

    int x = T;
    for (const string &row : slice) {
        int y = T;
        for (char ch : row) {
            if (ch == '#') cur[T][x][y] = 1;
            y++;
        }
        x++;
    }

    for (int t = 0; t < T; t++) {
        // A separate destination buffer is what makes the update SIMULTANEOUS: every decision below
        // reads `cur`, which no write in this cycle can touch.
        vector<vector<vector<unsigned char>>> nxt(
            Z, vector<vector<unsigned char>>(X, vector<unsigned char>(Y, 0)));
        for (int z = 0; z < Z; z++) {
            for (int i = 0; i < X; i++) {
                for (int j = 0; j < Y; j++) {
                    int cnt = 0;
                    for (int dz = -1; dz <= 1; dz++) {
                        int nz = z + dz;
                        if (nz < 0 || nz >= Z) continue;
                        for (int dx = -1; dx <= 1; dx++) {
                            int nx = i + dx;
                            if (nx < 0 || nx >= X) continue;
                            for (int dy = -1; dy <= 1; dy++) {
                                if (dz == 0 && dx == 0 && dy == 0) continue;  // not its own neighbour
                                int ny = j + dy;
                                if (ny < 0 || ny >= Y) continue;
                                cnt += cur[nz][nx][ny];
                            }
                        }
                    }
                    if (cur[z][i][j])
                        nxt[z][i][j] = (cnt == 2 || cnt == 3) ? 1 : 0;
                    else
                        nxt[z][i][j] = (cnt == 3) ? 1 : 0;
                }
            }
        }
        cur.swap(nxt);
    }

    long long active = 0;
    for (int z = 0; z < Z; z++)
        for (int i = 0; i < X; i++)
            for (int j = 0; j < Y; j++)
                active += cur[z][i][j];
    return active;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int R, T;
    if (!(cin >> R >> T)) return 0;
    vector<string> slice;
    for (int i = 0; i < R; i++) {
        string row;
        cin >> row;
        slice.push_back(row);
    }
    cout << conwayCubes(T, slice) << "\n";
    return 0;
}
