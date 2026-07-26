#include <bits/stdc++.h>
using namespace std;

// Add one to a decimal number given as a digit string, propagating carry from the least significant
// (rightmost) digit. A leading '9...9' produces one extra leading '1'.
string addOne(string s) {
    int i = (int)s.size() - 1;
    while (i >= 0) {
        if (s[i] == '9') {
            s[i] = '0';
            i--;
        } else {
            s[i] = s[i] + 1;
            return s;
        }
    }
    return "1" + s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    if (!(cin >> s)) return 0;
    cout << addOne(s) << "\n";
    return 0;
}
