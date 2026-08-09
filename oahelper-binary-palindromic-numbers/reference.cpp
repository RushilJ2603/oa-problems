#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Binary palindromes are sparse: one of length L is fixed by its first ceil(L/2) bits, and the
// leading bit must be 1, so there are only 2^(ceil(L/2)-1) of them per length — under 200k below
// 2^33 in total. Build them all once, sort, then every query is a binary search for the neighbours.
static vector<ll> buildPalindromes(ll limit) {
    vector<ll> out;
    for (int len = 1; len <= 34; len++) {
        int half = (len + 1) / 2;
        // top bit of the half is the number's leading bit and must be 1
        for (ll h = (1LL << (half - 1)); h < (1LL << half); h++) {
            ll v = h;
            // mirror: append len-half more bits, reflecting the half
            for (int i = len - half - 1; i >= 0; i--) {
                v = (v << 1) | ((h >> (half - 1 - i)) & 1LL);
            }
            if (v <= limit) out.push_back(v);
        }
    }
    sort(out.begin(), out.end());
    out.erase(unique(out.begin(), out.end()), out.end());
    return out;
}

ll minOpsToPalindrome(ll n, const vector<ll> &pal) {
    // nearest palindrome on either side
    vector<ll>::const_iterator it = lower_bound(pal.begin(), pal.end(), n);
    ll best = LLONG_MAX;
    if (it != pal.end()) best = min(best, *it - n);
    if (it != pal.begin()) best = min(best, n - *(it - 1));
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // headroom above the 2*10^9 ceiling so the palindrome ABOVE the largest query still exists
    vector<ll> pal = buildPalindromes(1LL << 34);
    int t;
    if (!(cin >> t)) return 0;
    string out;
    while (t--) {
        ll n;
        cin >> n;
        out += to_string(minOpsToPalindrome(n, pal));
        out += '\n';
    }
    cout << out;
    return 0;
}
