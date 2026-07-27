#include <bits/stdc++.h>
using namespace std;

bool isWeak(const string &pw, const vector<string> &commons) {
    if ((int)pw.size() < 6) return true;
    bool allDigit = true, allUpper = true, allLower = true;
    for (char c : pw) {
        if (!(c >= '0' && c <= '9')) allDigit = false;
        if (!(c >= 'A' && c <= 'Z')) allUpper = false;
        if (!(c >= 'a' && c <= 'z')) allLower = false;
    }
    if (allDigit || allUpper || allLower) return true;
    for (const string &w : commons)
        if (pw.find(w) != string::npos) return true;
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

    string out;
    for (int i = 0; i < n; i++)
        out += isWeak(pw[i], commons) ? "weak\n" : "strong\n";
    fputs(out.c_str(), stdout);
    return 0;
}
