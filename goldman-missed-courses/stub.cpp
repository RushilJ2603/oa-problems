#include <bits/stdc++.h>
using namespace std;

// Distinct values of (i % numCourses) for i in [firstDay, lastDay].
long long missedCourses(long long numCourses, long long firstDay, long long lastDay) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long nc, fd, ld;
    if (!(cin >> nc >> fd >> ld)) return 0;
    cout << missedCourses(nc, fd, ld) << "\n";
    return 0;
}
