#include <bits/stdc++.h>
using namespace std;

long long minTransformCost(const vector<long long> &machineCount,
                           const vector<long long> &finalMachineCount,
                           long long shiftingCost) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> machineCount(n), finalMachineCount(3);
    for (int i = 0; i < n; i++) cin >> machineCount[i];
    for (int i = 0; i < 3; i++) cin >> finalMachineCount[i];
    long long shiftingCost;
    cin >> shiftingCost;
    cout << minTransformCost(machineCount, finalMachineCount, shiftingCost) << "\n";
    return 0;
}
