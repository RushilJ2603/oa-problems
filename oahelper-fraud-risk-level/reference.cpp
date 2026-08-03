#include <bits/stdc++.h>
using namespace std;

struct Txn {
    string tid, aid, mid, did, loc, status;
    long long day, amount;
};

struct Row {
    int rank;
    long long score, amount;
    int idx;
    string text;
};

string solve(long long referenceDay,
             vector<tuple<string, string, string, string>>& accounts_raw,
             vector<Txn>& txns,
             vector<tuple<string, string, string>>& merchants_raw,
             vector<tuple<string, string, string, long long>>& devices_raw,
             vector<pair<string, long long>>& locations_raw) {
    unordered_map<string, pair<string, string>> accounts;
    accounts.reserve(accounts_raw.size() * 2 + 8);
    for (auto& a : accounts_raw) {
        accounts[get<0>(a)] = {get<1>(a), get<3>(a)};
    }

    unordered_map<string, string> tiers;
    tiers.reserve(merchants_raw.size() * 2 + 8);
    for (auto& m : merchants_raw) {
        tiers[get<0>(m)] = get<2>(m);
    }

    unordered_map<string, long long> firstUsed;
    firstUsed.reserve(devices_raw.size() * 2 + 8);
    for (auto& d : devices_raw) {
        const string& aid = get<1>(d);
        const string& did = get<2>(d);
        long long day = get<3>(d);
        if (!accounts.count(aid) || day < 1) continue;
        string key = aid + '\x01' + did;
        auto it = firstUsed.find(key);
        if (it == firstUsed.end() || day < it->second) firstUsed[key] = day;
    }

    unordered_map<string, long long> locRisk;
    locRisk.reserve(locations_raw.size() * 2 + 8);
    for (auto& L : locations_raw) locRisk[L.first] = L.second;

    vector<int> cand;
    for (size_t i = 0; i < txns.size(); ++i) {
        const Txn& t = txns[i];
        if (!accounts.count(t.aid)) continue;
        if (!tiers.count(t.mid)) continue;
        if (!locRisk.count(t.loc)) continue;
        if (!(t.day >= 1 && t.day <= referenceDay)) continue;
        if (t.amount <= 0) continue;
        if (t.status != "SUCCESS" && t.status != "FAILED") continue;
        if (t.status != "SUCCESS") continue;
        cand.push_back((int)i);
    }

    unordered_map<string, long long> accSum, accCnt, sameDay;
    for (int i : cand) {
        const Txn& t = txns[i];
        accSum[t.aid] += t.amount;
        accCnt[t.aid] += 1;
        sameDay[t.aid + '\x01' + to_string(t.day)] += 1;
    }

    vector<Row> rows;
    for (int i : cand) {
        const Txn& t = txns[i];
        const auto& acc = accounts[t.aid];
        long long avg = accSum[t.aid] / accCnt[t.aid];

        long long sc = 0;
        if (t.amount > 2 * avg) sc += 4;
        if (sameDay[t.aid + '\x01' + to_string(t.day)] >= 3) sc += 3;

        string key = t.aid + '\x01' + t.did;
        auto it = firstUsed.find(key);
        if (it == firstUsed.end()) sc += 4;
        else if (it->second > t.day) sc += 3;

        const string& tier = tiers[t.mid];
        if (tier == "HIGH") sc += 3;
        else if (tier == "MEDIUM") sc += 1;

        if (locRisk[t.loc] >= 4) sc += 3;
        if (t.loc != acc.second) sc += 2;

        string level;
        int rank;
        if (sc >= 10) { level = "HIGH"; rank = 0; }
        else if (sc >= 6) { level = "MEDIUM"; rank = 1; }
        else continue;

        Row row;
        row.rank = rank;
        row.score = sc;
        row.amount = t.amount;
        row.idx = i;
        row.text = t.tid + "-" + acc.first + "-" + level + "-" + to_string(sc);
        rows.push_back(row);
    }

    if (rows.empty()) return "NA";

    sort(rows.begin(), rows.end(), [](const Row& a, const Row& b) {
        if (a.rank != b.rank) return a.rank < b.rank;
        if (a.score != b.score) return a.score > b.score;
        if (a.amount != b.amount) return a.amount > b.amount;
        return a.idx < b.idx;
    });

    string out;
    for (size_t i = 0; i < rows.size(); ++i) {
        if (i) out.push_back('#');
        out += rows[i].text;
    }
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long referenceDay;
    long long nAcc, nTxn, nMer, nDev, nLoc;
    if (!(cin >> referenceDay)) return 0;
    cin >> nAcc >> nTxn >> nMer >> nDev >> nLoc;

    vector<tuple<string, string, string, string>> accounts_raw(nAcc);
    for (long long i = 0; i < nAcc; ++i) {
        auto& [id, holder, type, home] = accounts_raw[i];
        cin >> id >> holder >> type >> home;
    }

    vector<Txn> txns(nTxn);
    for (long long i = 0; i < nTxn; ++i) {
        Txn& t = txns[i];
        cin >> t.tid >> t.aid >> t.mid >> t.did >> t.loc >> t.day >> t.amount >> t.status;
    }

    vector<tuple<string, string, string>> merchants_raw(nMer);
    for (long long i = 0; i < nMer; ++i) {
        auto& [id, cat, tier] = merchants_raw[i];
        cin >> id >> cat >> tier;
    }

    vector<tuple<string, string, string, long long>> devices_raw(nDev);
    for (long long i = 0; i < nDev; ++i) {
        auto& [act, aid, did, day] = devices_raw[i];
        cin >> act >> aid >> did >> day;
    }

    vector<pair<string, long long>> locations_raw(nLoc);
    for (long long i = 0; i < nLoc; ++i) {
        cin >> locations_raw[i].first >> locations_raw[i].second;
    }

    cout << solve(referenceDay, accounts_raw, txns, merchants_raw, devices_raw, locations_raw) << "\n";
    return 0;
}
