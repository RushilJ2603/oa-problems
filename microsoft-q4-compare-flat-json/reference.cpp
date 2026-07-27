#include <bits/stdc++.h>
using namespace std;

// Extract every double-quoted token in order. Since keys/values never contain a '"',
// quotes strictly delimit them, so the tokens are key,value,key,value,... regardless of
// any ':' ',' '{' '}' that appear inside values.
vector<string> tokens(const string &s) {
    vector<string> t;
    int i = 0, n = (int)s.size();
    while (i < n) {
        if (s[i] == '"') {
            int j = i + 1;
            string cur;
            while (j < n && s[j] != '"') cur += s[j++];
            t.push_back(cur);
            i = j + 1;
        } else {
            i++;
        }
    }
    return t;
}

map<string,string> parse(const string &s) {
    vector<string> t = tokens(s);
    map<string,string> m;
    for (size_t i = 0; i + 1 < t.size(); i += 2) m[t[i]] = t[i + 1];
    return m;
}

int main() {
    string a, b;
    getline(cin, a);
    getline(cin, b);
    map<string,string> ma = parse(a), mb = parse(b);
    vector<string> res;
    for (auto &kv : ma) {
        auto it = mb.find(kv.first);
        if (it != mb.end() && it->second != kv.second) res.push_back(kv.first);
    }
    sort(res.begin(), res.end());
    string out;
    for (auto &k : res) { out += k; out += '\n'; }
    fputs(out.c_str(), stdout);
    return 0;
}
