#include <bits/stdc++.h>
using namespace std;

string makeLargest(const string& s) {
    if ((int)s.size() <= 2) return s;
    vector<string> parts;
    int balance = 0, start = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        balance += (s[i] == '1' ? 1 : -1);
        if (balance == 0) {
            string inner = s.substr(start + 1, i - start - 1);
            parts.push_back("1" + makeLargest(inner) + "0");
            start = i + 1;
        }
    }
    sort(parts.begin(), parts.end(), greater<string>());
    string result;
    for (const string& p : parts) result += p;
    return result;
}

string solve(string s) {
    return makeLargest(s);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    if (!(cin >> s)) return 0;
    cout << solve(s) << "\n";
    return 0;
}
