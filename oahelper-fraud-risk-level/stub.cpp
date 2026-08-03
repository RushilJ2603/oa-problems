#include <bits/stdc++.h>
using namespace std;

struct Txn {
    string tid, aid, mid, did, loc, status;
    long long day, amount;
};

string solve(long long referenceDay,
             vector<tuple<string, string, string, string>>& accounts_raw,
             vector<Txn>& txns,
             vector<tuple<string, string, string>>& merchants_raw,
             vector<tuple<string, string, string, long long>>& devices_raw,
             vector<pair<string, long long>>& locations_raw) {
    // WRITE YOUR CODE HERE
    return "NA";
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
