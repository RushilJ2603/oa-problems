#include <bits/stdc++.h>
using namespace std;

long long solve(vector<int>& supplierStock, long long orders) {
    // Binary search the highest sale price P such that we can sell >= orders
    // units at prices >= P. Then take all sales above P, plus leftover at P.
    long long low = 0, high = 0;
    for (int s : supplierStock) high = max(high, (long long)s);

    long long P = 0;
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        long long count = 0;
        for (int s : supplierStock) {
            if (s >= mid) count += (s - mid + 1);
        }
        if (count >= orders) {
            P = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    long long total = 0;
    long long sold = 0;
    for (int s : supplierStock) {
        if (s >= P + 1) {
            long long k = s;
            long long m = P + 1;
            long long items = k - m + 1;
            sold += items;
            total += (k + m) * items / 2;
        }
    }
    total += (orders - sold) * P;
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> stock(n);
    for (int i = 0; i < n; ++i) cin >> stock[i];
    long long orders;
    cin >> orders;
    cout << solve(stock, orders) << "\n";
    return 0;
}
