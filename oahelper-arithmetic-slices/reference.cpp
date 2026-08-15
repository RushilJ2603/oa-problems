#include <iostream>
#include <vector>
#include <string>

using namespace std;

int solve(int n, const vector<int>& latencies) {
    if (n < 3) return 0;
    int currentStreak = 0;
    int totalCount = 0;
    for (int i = 2; i < n; ++i) {
        if ((long long)latencies[i] - latencies[i - 1] == (long long)latencies[i - 1] - latencies[i - 2]) {
            currentStreak++;
            totalCount += currentStreak;
        } else {
            currentStreak = 0;
        }
    }
    return totalCount;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    if (getline(cin, line)) {
        if (line.size() >= 2 && line.front() == '[' && line.back() == ']') {
            line = line.substr(1, line.size() - 2);
        }
        vector<int> nums;
        string current = "";
        for (char c : line) {
            if (c == ',') {
                if (!current.empty()) {
                    nums.push_back(stoi(current));
                    current = "";
                }
            } else if (c != ' ' && c != '\r' && c != '\n') {
                current += c;
            }
        }
        if (!current.empty()) nums.push_back(stoi(current));
        cout << solve(nums.size(), nums) << "\n";
    }
    return 0;
}
