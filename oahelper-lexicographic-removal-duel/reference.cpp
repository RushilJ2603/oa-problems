#include <bits/stdc++.h>
using namespace std;

char solve(const string& s) {
    int n = (int)s.size();
    if (n <= 1) return s[0];
    vector<int> prv(n), nxt(n);
    vector<char> alive(n, 1);
    for (int i = 0; i < n; i++) {
        prv[i] = i - 1;
        nxt[i] = (i + 1 < n) ? i + 1 : -1;
    }
    int head = 0, tail = n - 1;
    priority_queue<int, vector<int>, greater<int>> hD, hA;
    for (int i = 0; i + 1 < n; i++) {
        if (s[i] > s[i + 1]) hD.push(i);
        else if (s[i] < s[i + 1]) hA.push(i);
    }
    for (int turn = 0; turn < n - 1; turn++) {
        bool mini = (turn % 2 == 0);
        auto& h = mini ? hD : hA;
        int target = -1;
        while (!h.empty()) {
            int i = h.top(); h.pop();
            int j = nxt[i];
            bool ok = alive[i] && j != -1 && (mini ? (s[i] > s[j]) : (s[i] < s[j]));
            if (ok) { target = i; break; }
        }
        if (target == -1) target = tail;
        int i = target;
        alive[i] = 0;
        int p = prv[i], q = nxt[i];
        if (p != -1) nxt[p] = q; else head = q;
        if (q != -1) prv[q] = p; else tail = p;
        if (p != -1 && q != -1) {
            if (s[p] > s[q]) hD.push(p);
            else if (s[p] < s[q]) hA.push(p);
        }
    }
    return s[head];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    if (!(cin >> s)) return 0;
    cout << solve(s) << "\n";
    return 0;
}
