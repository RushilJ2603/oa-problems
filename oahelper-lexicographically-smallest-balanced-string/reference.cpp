#include <bits/stdc++.h>
using namespace std;

string solve(int n, int k, string s) {
    if (n % k != 0) return "-1";

    vector<int> freq(26, 0);
    for (char c : s) freq[c - 'a']++;

    bool balanced = true;
    int current_req = 0;
    for (int i = 0; i < 26; ++i) {
        int rem = freq[i] % k;
        if (rem != 0) balanced = false;
        current_req += (k - rem) % k;
    }
    if (balanced) return s;

    for (int L = n - 1; L >= 0; --L) {
        int char_out = s[L] - 'a';
        int old_rem_out = freq[char_out] % k;
        current_req -= (k - old_rem_out) % k;
        freq[char_out]--;
        int new_rem_out = freq[char_out] % k;
        current_req += (k - new_rem_out) % k;

        for (int c = s[L] - 'a' + 1; c < 26; ++c) {
            int old_rem_in = freq[c] % k;
            int old_req_c = (k - old_rem_in) % k;
            freq[c]++;
            int new_rem_in = freq[c] % k;
            int new_req_c = (k - new_rem_in) % k;
            int req = current_req - old_req_c + new_req_c;

            if (req <= n - 1 - L) {
                string ans = s.substr(0, L);
                ans += (char)('a' + c);
                int rem_a = n - 1 - L - req;
                vector<int> req_count(26, 0);
                for (int i = 0; i < 26; ++i) {
                    req_count[i] = (k - freq[i] % k) % k;
                }
                req_count[0] += rem_a;
                for (int i = 0; i < 26; ++i) {
                    ans.append(req_count[i], (char)('a' + i));
                }
                return ans;
            }
            freq[c]--;
        }
    }
    return "-1";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    if (!(cin >> n >> k)) return 0;
    string s;
    cin >> s;
    cout << solve(n, k, s) << "\n";
    return 0;
}
