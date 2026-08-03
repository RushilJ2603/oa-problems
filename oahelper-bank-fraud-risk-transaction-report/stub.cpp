#include <bits/stdc++.h>
using namespace std;

string solve(
    long long referenceDay,
    vector<tuple<string,string,string,string>>& accounts,
    vector<tuple<string,string,string,string,string,long long,long long,string>>& txns,
    vector<tuple<string,string,string>>& merchants,
    vector<tuple<string,string,string,long long>>& devices,
    vector<pair<string,long long>>& locations
) {
    // WRITE YOUR CODE HERE
    return "NA";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long referenceDay;
    if (!(cin >> referenceDay)) return 0;
    long long nAcc, nTxn, nMer, nDev, nLoc;
    cin >> nAcc >> nTxn >> nMer >> nDev >> nLoc;
    vector<tuple<string,string,string,string>> accounts(nAcc);
    for (auto& a : accounts) {
        string id, h, ty, hl; cin >> id >> h >> ty >> hl;
        a = {id, h, ty, hl};
    }
    vector<tuple<string,string,string,string,string,long long,long long,string>> txns(nTxn);
    for (auto& t : txns) {
        string tid, aid, mid, did, loc, st; long long day, amt;
        cin >> tid >> aid >> mid >> did >> loc >> day >> amt >> st;
        t = {tid, aid, mid, did, loc, day, amt, st};
    }
    vector<tuple<string,string,string>> merchants(nMer);
    for (auto& m : merchants) {
        string id, c, r; cin >> id >> c >> r; m = {id, c, r};
    }
    vector<tuple<string,string,string,long long>> devices(nDev);
    for (auto& d : devices) {
        string act, aid, did; long long fud;
        cin >> act >> aid >> did >> fud; d = {act, aid, did, fud};
    }
    vector<pair<string,long long>> locations(nLoc);
    for (auto& l : locations) {
        string loc; long long rs; cin >> loc >> rs; l = {loc, rs};
    }
    cout << solve(referenceDay, accounts, txns, merchants, devices, locations) << "\n";
    return 0;
}
