#include <bits/stdc++.h>
using namespace std;

struct Row {
    int rank;
    long long score;
    long long amt;
    int order;
    string tid, holder, level;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long referenceDay;
    if (!(cin >> referenceDay)) return 0;
    long long nAcc, nTxn, nMer, nDev, nLoc;
    cin >> nAcc >> nTxn >> nMer >> nDev >> nLoc;

    unordered_map<string, string> home, holder;
    home.reserve(nAcc * 2 + 4);
    holder.reserve(nAcc * 2 + 4);
    for (long long i = 0; i < nAcc; ++i) {
        string a, h, ty, hl;
        cin >> a >> h >> ty >> hl;
        home[a] = hl;
        holder[a] = h;
    }

    struct T { string tid, aid, mid, did, loc, status; long long day, amt; int order; };
    vector<T> txns((size_t)nTxn);
    for (long long i = 0; i < nTxn; ++i) {
        T &t = txns[(size_t)i];
        cin >> t.tid >> t.aid >> t.mid >> t.did >> t.loc >> t.day >> t.amt >> t.status;
        t.order = (int)i;
    }

    unordered_map<string, string> tier;
    tier.reserve(nMer * 2 + 4);
    for (long long i = 0; i < nMer; ++i) {
        string m, c, r;
        cin >> m >> c >> r;
        tier[m] = r;
    }

    unordered_map<string, long long> firstUsed;   // key = accountId + '\x01' + deviceId
    firstUsed.reserve(nDev * 2 + 4);
    for (long long i = 0; i < nDev; ++i) {
        string act, aid, did; long long fud;
        cin >> act >> aid >> did >> fud;
        if (!home.count(aid) || fud < 1) continue;
        string key = aid + '\x01' + did;
        auto it = firstUsed.find(key);
        if (it == firstUsed.end() || fud < it->second) firstUsed[key] = fud;
    }

    unordered_map<string, long long> risk;
    risk.reserve(nLoc * 2 + 4);
    for (long long i = 0; i < nLoc; ++i) {
        string l; long long rs;
        cin >> l >> rs;
        risk[l] = rs;
    }

    vector<int> ok;
    ok.reserve(txns.size());
    for (size_t i = 0; i < txns.size(); ++i) {
        const T &t = txns[i];
        if (!home.count(t.aid)) continue;
        if (!tier.count(t.mid)) continue;
        if (!risk.count(t.loc)) continue;
        if (!(t.day >= 1 && t.day <= referenceDay)) continue;
        if (t.amt <= 0) continue;
        if (t.status != "SUCCESS" && t.status != "FAILED") continue;
        if (t.status != "SUCCESS") continue;
        ok.push_back((int)i);
    }

    unordered_map<string, long long> tot, cnt;
    unordered_map<string, long long> dayCnt;   // key = accountId + '\x01' + day
    for (int idx : ok) {
        const T &t = txns[(size_t)idx];
        tot[t.aid] += t.amt;
        cnt[t.aid] += 1;
        dayCnt[t.aid + '\x01' + to_string(t.day)] += 1;
    }

    vector<Row> rows;
    for (int idx : ok) {
        const T &t = txns[(size_t)idx];
        long long avg = tot[t.aid] / cnt[t.aid];
        long long score = 0;
        if (t.amt > 2 * avg) score += 4;
        if (dayCnt[t.aid + '\x01' + to_string(t.day)] >= 3) score += 3;
        auto it = firstUsed.find(t.aid + '\x01' + t.did);
        if (it == firstUsed.end()) score += 4;
        else if (it->second > t.day) score += 3;
        const string &rt = tier[t.mid];
        if (rt == "HIGH") score += 3;
        else if (rt == "MEDIUM") score += 1;
        if (risk[t.loc] >= 4) score += 3;
        if (t.loc != home[t.aid]) score += 2;

        Row r;
        if (score >= 10) { r.level = "HIGH"; r.rank = 0; }
        else if (score >= 6) { r.level = "MEDIUM"; r.rank = 1; }
        else continue;
        r.score = score; r.amt = t.amt; r.order = t.order;
        r.tid = t.tid; r.holder = holder[t.aid];
        rows.push_back(r);
    }

    if (rows.empty()) { cout << "NA\n"; return 0; }
    sort(rows.begin(), rows.end(), [](const Row &a, const Row &b) {
        if (a.rank != b.rank) return a.rank < b.rank;
        if (a.score != b.score) return a.score > b.score;
        if (a.amt != b.amt) return a.amt > b.amt;
        return a.order < b.order;
    });
    string out;
    for (size_t i = 0; i < rows.size(); ++i) {
        if (i) out += '#';
        out += rows[i].tid + '-' + rows[i].holder + '-' + rows[i].level + '-' + to_string(rows[i].score);
    }
    out += '\n';
    cout << out;
    return 0;
}
