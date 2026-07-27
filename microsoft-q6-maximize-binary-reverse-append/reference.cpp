#include <bits/stdc++.h>
using namespace std;

// The "reverse R, then append c" procedure applies a FIXED position-permutation pi to the
// chosen input permutation (independent of the characters). Because pi is a bijection, every
// arrangement of the multiset is an achievable final string, so the maximum final string is
// simply the multiset sorted descending: ones then zeros. The required INPUT permutation is
// the unique preimage: place target[j] at input position pi[j].
//
// pi is built in O(n) with the classic deque trick: "reverse then append at the end" is the
// same as toggling a direction flag and pushing to the front when reversed.
string solveOne(const string &s) {
    int n = (int)s.size();
    int ones = (int)count(s.begin(), s.end(), '1');
    deque<int> dq;
    bool rev = false;
    for (int i = 0; i < n; i++) {
        rev = !rev;
        if (rev) dq.push_front(i);
        else dq.push_back(i);
    }
    vector<int> pi(dq.begin(), dq.end());
    if (rev) reverse(pi.begin(), pi.end());
    string target(n, '0');
    for (int i = 0; i < ones; i++) target[i] = '1';
    string p(n, '0');
    for (int j = 0; j < n; j++) p[pi[j]] = target[j];
    return p;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    string out;
    while (T--) {
        string s;
        cin >> s;
        out += solveOne(s);
        out += '\n';
    }
    cout << out;
    return 0;
}
