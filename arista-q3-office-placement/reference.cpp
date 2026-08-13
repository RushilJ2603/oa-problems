#include <bits/stdc++.h>
using namespace std;

int minimaxDistance(int h, int w, int n) {
    const int cells = h * w;
    // Manhattan distance between every pair of plots. The grid is tiny, so this is cheaper than
    // recomputing coordinates inside the search.
    vector<vector<int>> dist(cells, vector<int>(cells));
    for (int a = 0; a < cells; a++) {
        for (int b = 0; b < cells; b++) {
            dist[a][b] = abs(a / w - b / w) + abs(a % w - b % w);
        }
    }

    int best = INT_MAX;
    vector<int> chosen;
    chosen.reserve(n);

    // Every way to put n offices on distinct plots. C(27,5) = 80730 at the very largest, so the
    // search space is the point of the problem: there is nothing to be clever about.
    function<void(int)> place = [&](int from) {
        if ((int)chosen.size() == n) {
            int worst = 0;
            for (int c = 0; c < cells; c++) {
                int near = INT_MAX;
                for (int o : chosen) near = min(near, dist[c][o]);
                worst = max(worst, near);
            }
            best = min(best, worst);
            return;
        }
        // Leave enough plots to finish the placement.
        for (int c = from; c <= cells - (n - (int)chosen.size()); c++) {
            chosen.push_back(c);
            place(c + 1);
            chosen.pop_back();
        }
    };
    place(0);
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int h, w, n;
    if (!(cin >> h >> w >> n)) return 0;
    cout << minimaxDistance(h, w, n) << "\n";
    return 0;
}
