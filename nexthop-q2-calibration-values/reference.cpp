#include <bits/stdc++.h>
using namespace std;

static const char *WORDS[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

// Scan LEFT TO RIGHT and ask, at every index independently, "does a digit START here?" — a digit
// character, or one of the nine words matching at this exact position. The index then advances by
// ONE, never by the length of the word that matched, which is what makes overlaps like the shared
// 't' in "eightwo" or the shared 'e' in "oneight" both count.
long long calibrationValue(const string &s) {
    int first = -1, last = -1;
    for (size_t i = 0; i < s.size(); i++) {
        int d = -1;
        if (s[i] >= '0' && s[i] <= '9') {
            d = s[i] - '0';
        } else {
            for (int w = 0; w < 9; w++) {
                size_t len = strlen(WORDS[w]);
                if (i + len <= s.size() && s.compare(i, len, WORDS[w]) == 0) {
                    d = w + 1;
                    break;
                }
            }
        }
        if (d >= 0) {
            if (first < 0) first = d;
            last = d;
        }
    }
    if (first < 0) return 0;   // guaranteed not to happen by the constraints
    return 10LL * first + last;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    long long total = 0;
    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        total += calibrationValue(s);
    }
    cout << total << "\n";
    return 0;
}
