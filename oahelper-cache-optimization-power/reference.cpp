#include <iostream>
#include <vector>

using namespace std;

static const long long MOD = 1000000007LL;

long long solve(int n, const vector<long long>& power) {
    vector<int> left(n), right(n), st;
    st.reserve(n);

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && power[st.back()] >= power[i]) st.pop_back();
        left[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }

    st.clear();
    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && power[st.back()] > power[i]) st.pop_back();
        right[i] = st.empty() ? n : st.back();
        st.push_back(i);
    }

    vector<long long> prefix(n + 1, 0), prefixPrefix(n + 2, 0);
    for (int i = 0; i < n; ++i) {
        prefix[i + 1] = (prefix[i] + power[i]) % MOD;
    }
    for (int i = 0; i <= n; ++i) {
        prefixPrefix[i + 1] = (prefixPrefix[i] + prefix[i]) % MOD;
    }

    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        int L = left[i];
        int R = right[i];

        long long leftCount = i - L;
        long long rightCount = R - i;

        long long sumRight = (prefixPrefix[R + 1] - prefixPrefix[i + 1] + MOD) % MOD;
        long long sumLeft = (prefixPrefix[i + 1] - prefixPrefix[L + 1] + MOD) % MOD;

        long long total = (leftCount % MOD) * sumRight % MOD;
        total = (total - (rightCount % MOD) * sumLeft % MOD + MOD) % MOD;

        ans = (ans + (power[i] % MOD) * total) % MOD;
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<long long> power(n);
    for (int i = 0; i < n; ++i) cin >> power[i];

    cout << solve(n, power) << "\n";
    return 0;
}
