#include <iostream>
#include <vector>

using namespace std;

vector<int> getDistinctScoreValues(int n, vector<int>& arr) {
    // WRITE YOUR CODE HERE
    return {};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    vector<int> res = getDistinctScoreValues(n, arr);
    for (size_t i = 0; i < res.size(); ++i) {
        cout << res[i] << "\n";
    }
    return 0;
}
