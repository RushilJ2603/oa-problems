#include <bits/stdc++.h>
using namespace std;

vector<string> run_cache_operations(int capacity, string policy, vector<string>& operations) {
    // WRITE YOUR CODE HERE
    return {};
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int capacity;
    if (!(cin >> capacity)) return 0;
    string policy; cin >> policy;
    int n; cin >> n;
    cin.ignore();
    vector<string> ops(n);
    for(int i=0; i<n; ++i) {
        getline(cin, ops[i]);
    }
    vector<string> res = run_cache_operations(capacity, policy, ops);
    for(const string& s : res) cout << s << "\n";
    return 0;
}
