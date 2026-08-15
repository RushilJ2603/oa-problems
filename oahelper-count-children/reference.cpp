#include <bits/stdc++.h>
using namespace std;

string addBig(string a, string b) {
    string res = "";
    int i = a.length() - 1;
    int j = b.length() - 1;
    int carry = 0;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        res += to_string(sum % 10);
        carry = sum / 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

string countChildren(long long n, long long i) {
    if (n < 1 || i < 1 || i > n) return "0";
    long long k = n - i + 1;
    if (k == 1) return "1";
    if (k == 2) return "1";
    string prev = "1";
    string curr = "1";
    for (int j = 3; j <= k; ++j) {
        string next = addBig(prev, curr);
        prev = curr;
        curr = next;
    }
    return curr;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, i;
    if (cin >> n >> i) {
        cout << countChildren(n, i) << "\n";
    }
    return 0;
}
