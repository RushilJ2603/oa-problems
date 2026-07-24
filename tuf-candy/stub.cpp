#include <bits/stdc++.h>
using namespace std;

// Return the minimum total candies satisfying the neighbour rating rule.
long long minCandies(vector<long long>& ratings) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    vector<long long> ratings(n); for(auto& x: ratings) cin>>x;
    cout << minCandies(ratings) << "\n";
    return 0;
}
