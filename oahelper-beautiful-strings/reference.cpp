#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

struct Poly {
    vector<int> c;
    Poly(int sz = 0) { if (sz > 0) c.assign(sz, 0); }
    static Poly constant(int v) {
        Poly p(1);
        p.c[0] = v;
        return p;
    }
    static Poly x() {
        Poly p(2);
        p.c[0] = 0;
        p.c[1] = 1;
        return p;
    }
};

int K_lim;

Poly add(const Poly& a, const Poly& b) {
    int sz = max((int)a.c.size(), (int)b.c.size());
    Poly res(sz);
    for (int i = 0; i < sz; i++) {
        long long v = 0;
        if (i < (int)a.c.size()) v += a.c[i];
        if (i < (int)b.c.size()) v += b.c[i];
        res.c[i] = (int)(v % MOD);
    }
    if ((int)res.c.size() > K_lim + 1) res.c.resize(K_lim + 1);
    return res;
}

Poly mul(const Poly& a, const Poly& b) {
    if (a.c.empty() || b.c.empty()) return Poly(0);
    int n = (int)a.c.size(), m = (int)b.c.size();
    int rs = min(n + m - 1, K_lim + 1);
    Poly res(rs);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m && i + j < rs; j++) {
            res.c[i + j] = (int)((res.c[i + j] + (long long)a.c[i] * b.c[j]) % MOD);
        }
    }
    return res;
}

struct Mat {
    Poly m[2][2];
    static Mat id() {
        Mat r;
        r.m[0][0] = Poly::constant(1);
        r.m[1][1] = Poly::constant(1);
        return r;
    }
};

Mat mat_mul(const Mat& A, const Mat& B) {
    Mat C;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            Poly s(0);
            for (int k = 0; k < 2; k++) s = add(s, mul(A.m[i][k], B.m[k][j]));
            C.m[i][j] = s;
        }
    }
    return C;
}

Mat mat_pow(Mat A, long long p) {
    Mat r = Mat::id();
    while (p > 0) {
        if (p & 1) r = mat_mul(r, A);
        A = mat_mul(A, A);
        p >>= 1;
    }
    return r;
}

long long solve(long long N, int K) {
    K_lim = K;
    if (N == 1) return K == 0 ? 26 : 0;
    Mat T;
    T.m[0][0] = Poly::constant(0);
    T.m[0][1] = Poly::constant(5);
    T.m[1][0] = Poly::constant(21);
    T.m[1][1] = add(Poly::constant(20), Poly::x());
    T = mat_pow(T, N - 1);
    Poly v = Poly::constant(5), c = Poly::constant(21);
    Poly Rv = add(mul(T.m[0][0], v), mul(T.m[0][1], c));
    Poly Rc = add(mul(T.m[1][0], v), mul(T.m[1][1], c));
    Poly Tot = add(Rv, Rc);
    if (K < (int)Tot.c.size()) return Tot.c[K];
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long N;
    int K;
    if (!(cin >> N >> K)) return 0;
    cout << solve(N, K) << "\n";
    return 0;
}
