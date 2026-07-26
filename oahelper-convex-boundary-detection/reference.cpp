#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
    bool operator<(const Point& o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
    bool operator==(const Point& o) const { return x == o.x && y == o.y; }
};

static long long cross(const Point& o, const Point& a, const Point& b) {
    return 1LL * (a.x - o.x) * (b.y - o.y) - 1LL * (a.y - o.y) * (b.x - o.x);
}

vector<Point> solve(int n, vector<Point> pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    int m = (int)pts.size();
    if (m <= 1) return pts;

    vector<Point> lower, upper;
    for (const auto& p : pts) {
        while (lower.size() >= 2 &&
               cross(lower[lower.size() - 2], lower[lower.size() - 1], p) < 0)
            lower.pop_back();
        lower.push_back(p);
    }
    for (int i = m - 1; i >= 0; --i) {
        const auto& p = pts[i];
        while (upper.size() >= 2 &&
               cross(upper[upper.size() - 2], upper[upper.size() - 1], p) < 0)
            upper.pop_back();
        upper.push_back(p);
    }

    vector<Point> hull;
    hull.reserve(lower.size() + upper.size());
    for (const auto& p : lower) hull.push_back(p);
    for (const auto& p : upper) hull.push_back(p);
    sort(hull.begin(), hull.end());
    hull.erase(unique(hull.begin(), hull.end()), hull.end());
    return hull;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<Point> pts(n);
    for (int i = 0; i < n; i++) cin >> pts[i].x >> pts[i].y;
    auto ans = solve(n, pts);
    for (size_t i = 0; i < ans.size(); i++) {
        cout << ans[i].x << ' ' << ans[i].y;
        if (i + 1 < ans.size()) cout << '\n';
    }
    return 0;
}
