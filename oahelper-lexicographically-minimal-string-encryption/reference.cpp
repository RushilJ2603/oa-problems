#include <bits/stdc++.h>
using namespace std;

string solve(const string& originalString) {
    int n = (int)originalString.size();
    if (n == 0) return "";
    vector<char> suffixMin(n + 1);
    suffixMin[n] = char(127);
    for (int i = n - 1; i >= 0; --i)
        suffixMin[i] = min(originalString[i], suffixMin[i + 1]);
    string temporary;
    string encrypted;
    encrypted.reserve(n);
    for (int i = 0; i < n; ++i) {
        temporary.push_back(originalString[i]);
        while (!temporary.empty() && temporary.back() <= suffixMin[i + 1]) {
            encrypted.push_back(temporary.back());
            temporary.pop_back();
        }
    }
    return encrypted;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    if (!(cin >> s)) return 0;
    cout << solve(s) << "\n";
    return 0;
}
