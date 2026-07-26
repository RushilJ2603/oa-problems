#include <bits/stdc++.h>
using namespace std;

bool checkThreshold(int N, long long K, const vector<long long>& A, long long D) {
    vector<int> dq(N);
    int head = 0, tail = 0;
    long long segments = 0;
    for (int j = 0; j < N; ++j) {
        while (tail > head && A[dq[tail - 1]] <= A[j]) {
            --tail;
        }
        dq[tail++] = j;
        while (tail > head && A[dq[head]] - A[j] >= D) {
            ++head;
            ++segments;
        }
    }
    return segments >= K;
}

long long solve(int N, long long K, vector<long long>& A) {
    long long low = 0, high = 1000000000, ans = 0;
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        if (checkThreshold(N, K, A, mid)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    long long K;
    if (!(cin >> N >> K)) return 0;
    vector<long long> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    cout << solve(N, K, A) << "\n";
    return 0;
}
