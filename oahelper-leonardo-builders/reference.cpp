#include <bits/stdc++.h>
using namespace std;

const int MAX_DIM = 505;

struct Point {
    long long x, y;
};

long long my_gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

vector<Point> normalize(vector<Point> pts) {
    if (pts.empty()) return pts;
    long long min_x = pts[0].x, min_y = pts[0].y;
    for (const auto& p : pts) {
        if (p.x < min_x) min_x = p.x;
        if (p.y < min_y) min_y = p.y;
    }
    for (auto& p : pts) {
        p.x -= min_x;
        p.y -= min_y;
    }
    return pts;
}

pair<pair<int, int>, vector<bitset<MAX_DIM>>> rasterize(const vector<Point>& poly) {
    long long max_x = 0, max_y = 0;
    for (const auto& p : poly) {
        if (p.x > max_x) max_x = p.x;
        if (p.y > max_y) max_y = p.y;
    }

    int w = (int)max_x;
    int h = (int)max_y;
    int grid_w = w + 3;
    int grid_h = h + 3;
    vector<vector<int>> temp_grid(grid_h, vector<int>(grid_w, 0));

    int k = (int)poly.size();
    for (int i = 0; i < k; ++i) {
        Point p1 = poly[i];
        Point p2 = poly[(i + 1) % k];
        long long x1 = p1.x + 1;
        long long y1 = p1.y + 1;
        long long x2 = p2.x + 1;
        long long y2 = p2.y + 1;
        long long dx = x2 - x1;
        long long dy = y2 - y1;
        long long g = my_gcd(abs(dx), abs(dy));
        for (long long j = 0; j <= g; ++j) {
            temp_grid[y1 + j * dy / g][x1 + j * dx / g] = 1;
        }
    }

    vector<pair<int, int>> q;
    q.push_back({0, 0});
    temp_grid[0][0] = 2;
    size_t head = 0;
    while (head < q.size()) {
        pair<int, int> cur = q[head++];
        int dxs[] = {0, 0, 1, -1};
        int dys[] = {1, -1, 0, 0};
        for (int d = 0; d < 4; ++d) {
            int nx = cur.first + dxs[d];
            int ny = cur.second + dys[d];
            if (nx >= 0 && nx < grid_w && ny >= 0 && ny < grid_h) {
                if (temp_grid[ny][nx] == 0) {
                    temp_grid[ny][nx] = 2;
                    q.push_back({nx, ny});
                }
            }
        }
    }

    vector<bitset<MAX_DIM>> shape_bits(h + 1);
    for (int y = 0; y <= h; ++y) {
        for (int x = 0; x <= w; ++x) {
            if (temp_grid[y + 1][x + 1] != 2) {
                shape_bits[y].set(x);
            }
        }
    }
    return {{w, h}, shape_bits};
}

vector<Point> rotate90(const vector<Point>& poly) {
    vector<Point> new_poly;
    new_poly.reserve(poly.size());
    for (const auto& p : poly) {
        new_poly.push_back({-p.y, p.x});
    }
    return normalize(new_poly);
}

long long solve(int Xp, int Yp, const vector<pair<int, int>>& trees,
                vector<Point> building) {
    vector<bitset<MAX_DIM>> land_trees(Yp + 1);
    for (auto [x, y] : trees) {
        if (x >= 0 && x <= Xp && y >= 0 && y <= Yp) {
            land_trees[y].set(x);
        }
    }

    vector<Point> current = normalize(building);
    long long total_ways = 0;
    set<string> seen_masks;

    for (int rot = 0; rot < 4; ++rot) {
        auto res = rasterize(current);
        int w = res.first.first;
        int h = res.first.second;
        const auto& mask = res.second;

        string sig;
        for (int y = 0; y <= h; ++y) {
            for (int x = 0; x <= w; ++x) {
                sig += (mask[y].test(x) ? '1' : '0');
            }
            sig += ';';
        }

        if (!seen_masks.count(sig)) {
            seen_masks.insert(sig);
            if (w <= Xp && h <= Yp) {
                for (int dy = 0; dy <= Yp - h; ++dy) {
                    for (int dx = 0; dx <= Xp - w; ++dx) {
                        bool collision = false;
                        for (int r = 0; r <= h; ++r) {
                            if ((land_trees[dy + r] & (mask[r] << dx)).any()) {
                                collision = true;
                                break;
                            }
                        }
                        if (!collision) total_ways++;
                    }
                }
            }
        }
        current = rotate90(current);
    }
    return total_ways;
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
