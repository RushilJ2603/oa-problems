#include <bits/stdc++.h>
using namespace std;

long long solve(int n, vector<long long>& arr, int k) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; 
    if(!(cin >> n)) return 0; 
    vector<long long> arr(n); 
    for(auto& x : arr) cin >> x;
    int k; 
    cin >> k;
    cout << solve(n, arr, k) << "\n"; 
    return 0; 
}
