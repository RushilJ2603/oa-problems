#include <bits/stdc++.h>
using namespace std;

long long getValidConfigurations(int n, vector<int>& coordinationThreshold) {
    sort(coordinationThreshold.begin(), coordinationThreshold.end());
    long long validConfigs = 0;
    
    if (coordinationThreshold[0] > 0) {
        validConfigs++;
    }
    for (int k = 1; k < n; k++) {
        if (coordinationThreshold[k - 1] < k && coordinationThreshold[k] > k) {
            validConfigs++;
        }
    }
    if (coordinationThreshold[n - 1] < n) {
        validConfigs++;
    }
    return validConfigs;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << getValidConfigurations(n, a) << "\n";
    return 0;
}
