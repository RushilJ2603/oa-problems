#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

struct CustomBitset {
    unsigned long long words[16];

    CustomBitset() {
        memset(words, 0, sizeof(words));
    }

    void set(int pos) {
        if (pos >= 0 && pos < 1024) {
            words[pos >> 6] |= (1ULL << (pos & 63));
        }
    }

    void add(const CustomBitset& other) {
        for (int i = 0; i < 16; ++i) {
            words[i] |= other.words[i];
        }
    }
};

struct FenwickTree {
    CustomBitset tree[1025];

    void update(int idx, const CustomBitset& val) {
        for (; idx < 1025; idx += idx & -idx) {
            tree[idx].add(val);
        }
    }

    CustomBitset query(int idx) {
        CustomBitset res;
        for (; idx > 0; idx -= idx & -idx) {
            res.add(tree[idx]);
        }
        return res;
    }
};

vector<int> getDistinctScoreValues(int n, vector<int>& arr) {
    FenwickTree ft;
    
    for (int x : arr) {
        CustomBitset union_scores;
        if (x > 0) {
            union_scores = ft.query(x);
        }
        
        CustomBitset new_scores;
        new_scores.set(x);
        
        for (int i = 0; i < 16; ++i) {
            unsigned long long w = union_scores.words[i];
            while (w) {
                int bit = __builtin_ctzll(w);
                int s = (i << 6) | bit;
                new_scores.set(s | x);
                w &= (w - 1);
            }
        }
        
        ft.update(x + 1, new_scores);
    }
    
    CustomBitset all_scores = ft.query(1024);
    
    vector<int> result;
    result.push_back(0);
    
    for (int i = 0; i < 16; ++i) {
        unsigned long long w = all_scores.words[i];
        while (w) {
            int bit = __builtin_ctzll(w);
            int val = (i << 6) | bit;
            result.push_back(val);
            w &= (w - 1);
        }
    }
    
    sort(result.begin(), result.end());
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    vector<int> res = getDistinctScoreValues(n, arr);
    for (size_t i = 0; i < res.size(); ++i) {
        cout << res[i] << "\n";
    }
    return 0;
}
