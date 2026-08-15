#include <bits/stdc++.h>
using namespace std;

vector<int> solve(int n, vector<long long>& priorities) {
    vector<int> starvation(n, 0);
    vector<long long> minValues;
    vector<int> minIndices;
    for (int i = n - 1; i >= 0; i--) {
        int left = 0;
        int right = (int)minValues.size() - 1;
        int answerPos = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (minValues[mid] < priorities[i]) {
                answerPos = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        if (answerPos != -1) {
            starvation[i] = minIndices[answerPos] - i;
        }
        if (minValues.empty() || priorities[i] < minValues.back()) {
            minValues.push_back(priorities[i]);
            minIndices.push_back(i);
        }
    }
    return starvation;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> priorities(n);
    for (int i = 0; i < n; i++) cin >> priorities[i];
    vector<int> ans = solve(n, priorities);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
    return 0;
}
