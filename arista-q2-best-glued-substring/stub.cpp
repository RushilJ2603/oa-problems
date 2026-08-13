#include <bits/stdc++.h>
using namespace std;

string bestGluedSubstring(const string &s, const string &p, const string &q) {
    // WRITE YOUR CODE HERE
    return s.substr(0, 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, p, q;
    if (!(cin >> s)) return 0;
    cin >> p >> q;
    cout << bestGluedSubstring(s, p, q) << "\n";
    return 0;
}
