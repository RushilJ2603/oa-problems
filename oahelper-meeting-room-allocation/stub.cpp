#include <bits/stdc++.h>
using namespace std;

long long solve(int n, int r, vector<array<long long, 3>>& meetings) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string raw((istreambuf_iterator<char>(cin)), istreambuf_iterator<char>());
    string normalized;
    normalized.reserve(raw.size());
    for (size_t i = 0; i < raw.size(); ++i) {
        if (raw[i] == '\\' && i + 1 < raw.size() && raw[i + 1] == 'n') {
            normalized.push_back('\n');
            ++i;
        } else {
            normalized.push_back(raw[i]);
        }
    }

    stringstream ss(normalized);
    int n, r;
    if (!(ss >> n >> r)) return 0;
    vector<array<long long, 3>> meetings(n);
    for (int i = 0; i < n; i++) {
        ss >> meetings[i][0] >> meetings[i][1] >> meetings[i][2];
    }
    cout << solve(n, r, meetings) << "\n";
    return 0;
}
