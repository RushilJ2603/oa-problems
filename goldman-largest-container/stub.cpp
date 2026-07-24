#include <bits/stdc++.h>
using namespace std;

// Return the lexicographically largest arrangement reachable by the (reusable) swaps.
vector<long long> largestContainer(vector<long long>& container,
                                   vector<long long>& firstPos,
                                   vector<long long>& secondPos,
                                   vector<long long>& slide) {
    // WRITE YOUR CODE HERE
    return container;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> container(n);
    for (auto& x : container) cin >> x;
    int m;
    cin >> m;
    vector<long long> firstPos(m), secondPos(m), slide(m);
    for (auto& x : firstPos) cin >> x;
    for (auto& x : secondPos) cin >> x;
    for (auto& x : slide) cin >> x;
    vector<long long> res = largestContainer(container, firstPos, secondPos, slide);
    for (size_t i = 0; i < res.size(); ++i) cout << res[i] << " \n"[i + 1 == res.size()];
    return 0;
}
