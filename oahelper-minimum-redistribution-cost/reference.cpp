#include <bits/stdc++.h>
using namespace std;

long long calculateMinimumRedistributionCost(vector<int>& products) {
    int n = (int)products.size();
    if (n <= 1) return 0;
    long long total = 0;
    for (int x : products) total += x;
    long long avg = total / n;
    auto get_cost = [&](bool reverse_dir) {
        long long current_prefix = 0;
        long long sum_prefix = 0;
        long long min_prefix = 0;
        for (int step = 0; step < n; ++step) {
            int i = reverse_dir ? (n - 1 - step) : step;
            current_prefix += (products[i] - avg);
            sum_prefix += current_prefix;
            if (step == 0 || current_prefix < min_prefix) min_prefix = current_prefix;
        }
        return sum_prefix - (long long)n * min_prefix;
    };
    return min(get_cost(false), get_cost(true));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> products(n);
    for (int i = 0; i < n; i++) cin >> products[i];
    cout << calculateMinimumRedistributionCost(products) << "\n";
    return 0;
}
