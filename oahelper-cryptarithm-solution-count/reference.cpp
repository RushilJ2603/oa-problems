#include <bits/stdc++.h>
using namespace std;

static string A, B, C;
static int L;
static int assignVal[26];
static bool usedDigit[10];
static bool isLead[26];
static long long total;

static void rec(int col, int carry);

static void placeC(int col, int carry, int sum) {
    int dig = sum % 10, car = sum / 10;
    if (col >= (int)C.size()) return;
    int c = C[col] - 'A';
    if (assignVal[c] >= 0) {
        if (assignVal[c] == dig) rec(col + 1, car);
        return;
    }
    if (usedDigit[dig]) return;
    if (dig == 0 && isLead[c]) return;
    assignVal[c] = dig; usedDigit[dig] = true;
    rec(col + 1, car);
    assignVal[c] = -1; usedDigit[dig] = false;
}

static void placeB(int col, int carry, int av) {
    if (col >= (int)B.size()) { placeC(col, carry, av + carry); return; }
    int b = B[col] - 'A';
    if (assignVal[b] >= 0) { placeC(col, carry, av + assignVal[b] + carry); return; }
    for (int d = 0; d < 10; d++) {
        if (usedDigit[d]) continue;
        if (d == 0 && isLead[b]) continue;
        assignVal[b] = d; usedDigit[d] = true;
        placeC(col, carry, av + d + carry);
        assignVal[b] = -1; usedDigit[d] = false;
    }
}

static void rec(int col, int carry) {
    if (col == L) { if (carry == 0) total++; return; }
    if (col >= (int)A.size()) { placeB(col, carry, 0); return; }
    int a = A[col] - 'A';
    if (assignVal[a] >= 0) { placeB(col, carry, assignVal[a]); return; }
    for (int d = 0; d < 10; d++) {
        if (usedDigit[d]) continue;
        if (d == 0 && isLead[a]) continue;
        assignVal[a] = d; usedDigit[d] = true;
        placeB(col, carry, d);
        assignVal[a] = -1; usedDigit[d] = false;
    }
}

long long solve(string w1, string w2, string w3) {
    set<char> letters;
    for (char ch : w1) letters.insert(ch);
    for (char ch : w2) letters.insert(ch);
    for (char ch : w3) letters.insert(ch);
    if (letters.size() > 10) return 0;

    for (int i = 0; i < 26; i++) { assignVal[i] = -1; isLead[i] = false; }
    for (int i = 0; i < 10; i++) usedDigit[i] = false;
    if (w1.size() > 1) isLead[w1[0] - 'A'] = true;
    if (w2.size() > 1) isLead[w2[0] - 'A'] = true;
    if (w3.size() > 1) isLead[w3[0] - 'A'] = true;

    A = w1; reverse(A.begin(), A.end());
    B = w2; reverse(B.begin(), B.end());
    C = w3; reverse(C.begin(), C.end());
    L = max({(int)A.size(), (int)B.size(), (int)C.size()});

    total = 0;
    rec(0, 0);
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string w1, w2, w3;
    if (!(cin >> w1 >> w2 >> w3)) return 0;
    cout << solve(w1, w2, w3) << "\n";
    return 0;
}
