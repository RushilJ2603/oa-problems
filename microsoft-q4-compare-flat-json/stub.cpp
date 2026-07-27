#include <bits/stdc++.h>
using namespace std;

// Return the keys present in BOTH objects with different values, sorted ascending.
vector<string> diffKeys(const string &json1, const string &json2) {
    // WRITE YOUR CODE HERE
    return {};
}

int main() {
    string a, b;
    getline(cin, a);
    getline(cin, b);
    for (const string &k : diffKeys(a, b)) cout << k << "\n";
    return 0;
}
