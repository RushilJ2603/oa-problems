#include <bits/stdc++.h>
using namespace std;

class Cache {
public:
    virtual string get(const string& key) = 0;
    virtual void put(const string& key, int value) = 0;
    virtual void del(const string& key) = 0;
    virtual void clear() = 0;
    virtual ~Cache() {}
};

class LRUCache : public Cache {
    int cap;
    list<pair<string, int>> dll;
    unordered_map<string, list<pair<string, int>>::iterator> mp;
public:
    LRUCache(int capacity) : cap(capacity) {}
    string get(const string& key) override {
        if (mp.find(key) == mp.end()) return "None";
        auto it = mp[key];
        int val = it->second;
        dll.erase(it);
        dll.push_front({key, val});
        mp[key] = dll.begin();
        return to_string(val);
    }
    void put(const string& key, int value) override {
        if (mp.find(key) != mp.end()) {
            dll.erase(mp[key]);
        } else if (dll.size() == cap) {
            mp.erase(dll.back().first);
            dll.pop_back();
        }
        dll.push_front({key, value});
        mp[key] = dll.begin();
    }
    void del(const string& key) override {
        if (mp.find(key) != mp.end()) {
            dll.erase(mp[key]);
            mp.erase(key);
        }
    }
    void clear() override { dll.clear(); mp.clear(); }
};

class LFUCache : public Cache {
    int cap, minFreq;
    unordered_map<string, pair<int, int>> kvf;
    unordered_map<string, list<string>::iterator> kti;
    unordered_map<int, list<string>> ftl;
public:
    LFUCache(int capacity) : cap(capacity), minFreq(0) {}
    string get(const string& key) override {
        if (kvf.find(key) == kvf.end()) return "None";
        int val = kvf[key].first;
        int freq = kvf[key].second;
        ftl[freq].erase(kti[key]);
        if (ftl[freq].empty()) {
            ftl.erase(freq);
            if (minFreq == freq) minFreq++;
        }
        freq++;
        kvf[key].second = freq;
        ftl[freq].push_front(key);
        kti[key] = ftl[freq].begin();
        return to_string(val);
    }
    void put(const string& key, int value) override {
        if (cap == 0) return;
        if (kvf.find(key) != kvf.end()) {
            kvf[key].first = value;
            get(key);
            return;
        }
        if (kvf.size() == cap) {
            string evict = ftl[minFreq].back();
            ftl[minFreq].pop_back();
            if (ftl[minFreq].empty()) ftl.erase(minFreq);
            kvf.erase(evict);
            kti.erase(evict);
        }
        kvf[key] = {value, 1};
        minFreq = 1;
        ftl[1].push_front(key);
        kti[key] = ftl[1].begin();
    }
    void del(const string& key) override {
        if (kvf.find(key) != kvf.end()) {
            int freq = kvf[key].second;
            ftl[freq].erase(kti[key]);
            if (ftl[freq].empty()) ftl.erase(freq);
            kvf.erase(key);
            kti.erase(key);
        }
    }
    void clear() override { kvf.clear(); kti.clear(); ftl.clear(); minFreq = 0; }
};

vector<string> run_cache_operations(int capacity, string policy, vector<string>& operations) {
    Cache* cache;
    if (policy == "LRU") cache = new LRUCache(capacity);
    else cache = new LFUCache(capacity);
    vector<string> res;
    for (const string& op : operations) {
        stringstream ss(op);
        string cmd, key; int val;
        ss >> cmd;
        if (cmd == "put") { ss >> key >> val; cache->put(key, val); }
        else if (cmd == "get") { ss >> key; res.push_back(cache->get(key)); }
        else if (cmd == "delete") { ss >> key; cache->del(key); }
        else if (cmd == "clear") cache->clear();
    }
    delete cache;
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int capacity;
    if (!(cin >> capacity)) return 0;
    string policy; cin >> policy;
    int n; cin >> n;
    cin.ignore();
    vector<string> ops(n);
    for(int i=0; i<n; ++i) getline(cin, ops[i]);
    vector<string> res = run_cache_operations(capacity, policy, ops);
    for(const string& s : res) cout << s << "\n";
    return 0;
}
