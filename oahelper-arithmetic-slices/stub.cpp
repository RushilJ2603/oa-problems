#include <iostream>
#include <vector>
#include <string>

using namespace std;

int solve(int n, const vector<int>& latencies) {
    // WRITE YOUR CODE HERE
    return 0;
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
