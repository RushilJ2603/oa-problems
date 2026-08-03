#include <bits/stdc++.h>
using namespace std;

struct Row {
    int levelRank;
    long long score;
    long long dsm;
    int idx;
    string name;
};

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
    long long nM = (long long)id.size();
    unordered_map<string, int> index;
    for (long long i = 0; i < nM; i++) index[id[i]] = (int)i;

    vector<long long> cnt(nM, 0), sumT(nM, 0), sumV(nM, 0), tb(nM, 0), vb(nM, 0), hf(nM, 0), lastM(nM, -1);
    unordered_map<string, pair<long long, long long>> tAgg;

    for (auto& rec : sensors) {
        string mid = get<1>(rec);
        long long day = get<2>(rec), tp = get<3>(rec), vbn = get<4>(rec);
        auto it = index.find(mid);
        if (it == index.end()) continue;
        if (day < 1 || day > ref) continue;
        if (tp < 0 || vbn < 0) continue;
        int k = it->second;
        cnt[k]++; sumT[k] += tp; sumV[k] += vbn;
        auto pr = prof[type[k]];
        if (tp > pr.first) tb[k]++;
        if (vbn > pr.second) vb[k]++;
        auto& ag = tAgg[type[k]];
        ag.first += tp; ag.second += 1;
    }
    for (auto& rec : logs) {
        string mid = get<1>(rec), mt = get<3>(rec);
        long long day = get<2>(rec);
        auto it = index.find(mid);
        if (it == index.end()) continue;
        if (mt != "PREVENTIVE" && mt != "CORRECTIVE") continue;
        if (day < 1 || day > ref) continue;
        lastM[it->second] = max(lastM[it->second], day);
    }
    for (auto& rec : faults) {
        string mid = get<1>(rec), sv = get<3>(rec);
        long long day = get<2>(rec);
        auto it = index.find(mid);
        if (it == index.end()) continue;
        if (sv != "LOW" && sv != "MEDIUM" && sv != "HIGH") continue;
        if (day < 1 || day > ref) continue;
        if (sv == "HIGH") hf[it->second]++;
    }

    vector<Row> rows;
    for (long long i = 0; i < nM; i++) {
        auto pr = prof[type[i]];
        long long c = cnt[i];
        long long avgT = c ? sumT[i] / c : 0;
        long long avgV = c ? sumV[i] / c : 0;
        bool noMaint = (lastM[i] < 0);
        long long dsm = noMaint ? ref + 1 : ref - lastM[i];
        long long mtAvg = 0;
        auto ait = tAgg.find(type[i]);
        if (ait != tAgg.end() && ait->second.second > 0)
            mtAvg = ait->second.first / ait->second.second;
        long long s = 0;
        if (dsm >= 90) s += 4;
        if (noMaint) s += 3;
        if (tb[i] >= 2) s += 3;
        if (vb[i] >= 2) s += 3;
        if (hf[i] >= 1) s += 3;
        if (c > 0 && avgT > mtAvg) s += 2;
        if (c > 0 && avgV > pr.second) s += 2;
        if (s >= 6) rows.push_back({s >= 10 ? 0 : 1, s, dsm, (int)i, name[i]});
    }
    sort(rows.begin(), rows.end(), [](const Row& a, const Row& b) {
        if (a.levelRank != b.levelRank) return a.levelRank < b.levelRank;
        if (a.score != b.score) return a.score > b.score;
        if (a.dsm != b.dsm) return a.dsm > b.dsm;
        return a.idx < b.idx;
    });
    if (rows.empty()) return "NA";
    string out;
    for (size_t i = 0; i < rows.size(); i++) {
        if (i) out += '#';
        out += rows[i].name;
        out += '-';
        out += (rows[i].levelRank == 0 ? "HIGH" : "MEDIUM");
        out += '-';
        out += to_string(rows[i].score);
        out += '-';
        out += to_string(rows[i].dsm);
    }
    return out;
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
