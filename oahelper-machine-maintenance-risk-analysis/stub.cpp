#include <bits/stdc++.h>
using namespace std;

string solve(
    long long ref,
    vector<string>& id,
    vector<string>& name,
    vector<string>& type,
    unordered_map<string, pair<long long, long long>>& prof,
    const vector<tuple<string, string, long long, long long, long long>>& sensors,
    const vector<tuple<string, string, long long, string>>& logs,
    const vector<tuple<string, string, long long, string>>& faults
) {
    // WRITE YOUR CODE HERE
    return "NA";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long ref;
    if (!(cin >> ref)) return 0;
    long long nM, nP, nS, nL, nF;
    cin >> nM >> nP >> nS >> nL >> nF;
    vector<string> id(nM), name(nM), type(nM);
    for (long long i = 0; i < nM; i++) cin >> id[i] >> name[i] >> type[i];
    unordered_map<string, pair<long long, long long>> prof;
    for (long long i = 0; i < nP; i++) {
        string t; long long a, b; cin >> t >> a >> b;
        prof[t] = {a, b};
    }
    vector<tuple<string, string, long long, long long, long long>> sensors;
    sensors.reserve(nS);
    for (long long i = 0; i < nS; i++) {
        string rid, mid; long long day, tp, vbn;
        cin >> rid >> mid >> day >> tp >> vbn;
        sensors.emplace_back(rid, mid, day, tp, vbn);
    }
    vector<tuple<string, string, long long, string>> logs;
    logs.reserve(nL);
    for (long long i = 0; i < nL; i++) {
        string lid, mid, mt; long long day;
        cin >> lid >> mid >> day >> mt;
        logs.emplace_back(lid, mid, day, mt);
    }
    vector<tuple<string, string, long long, string>> faults;
    faults.reserve(nF);
    for (long long i = 0; i < nF; i++) {
        string fid, mid, sv; long long day;
        cin >> fid >> mid >> day >> sv;
        faults.emplace_back(fid, mid, day, sv);
    }
    cout << solve(ref, id, name, type, prof, sensors, logs, faults) << "\n";
    return 0;
}
