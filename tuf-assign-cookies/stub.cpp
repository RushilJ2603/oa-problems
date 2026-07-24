#include <bits/stdc++.h>
using namespace std;

// Return the maximum number of students that can each be given a cookie
// (cookie j may go to student i iff cookie[j] >= student[i]).
int maxAssigned(vector<long long>& student, vector<long long>& cookie) {
    // WRITE YOUR CODE HERE
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> student(n);
    for (auto& x : student) cin >> x;
    int m;
    cin >> m;
    vector<long long> cookie(m);
    for (auto& x : cookie) cin >> x;
    cout << maxAssigned(student, cookie) << "\n";
    return 0;
}
