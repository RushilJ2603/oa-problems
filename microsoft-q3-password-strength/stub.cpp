#include <bits/stdc++.h>
using namespace std;

// Return true if the password is weak, false if strong.
bool isWeak(const string &pw, const vector<string> &commons) {
    // WRITE YOUR CODE HERE
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    if (!getline(cin, line)) return 0;
    int n = stoi(line);
    vector<string> pw(n);
    for (int i = 0; i < n; i++) getline(cin, pw[i]);
    int c = 0;
    if (getline(cin, line)) c = stoi(line);
    vector<string> commons(c);
    for (int i = 0; i < c; i++) getline(cin, commons[i]);
    for (int i = 0; i < n; i++)
        cout << (isWeak(pw[i], commons) ? "weak" : "strong") << "\n";
    return 0;
}
