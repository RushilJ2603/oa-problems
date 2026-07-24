#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; if(!(cin>>n)) return 0;
    vector<long long> p(n), r(n);
    for(auto&x:p) cin>>x;
    for(auto&x:r) cin>>x;
    // For each i: min increment so it overlaps at least one other sensor (others at original range).
    // Sorting by position lets us check only neighbors, but O(n^2) is simplest and correct; we do the
    // efficient sorted version so large n is fine.
    vector<int> idx(n); iota(idx.begin(),idx.end(),0);
    sort(idx.begin(),idx.end(),[&](int a,int b){return p[a]<p[b];});
    vector<long long> d(n);
    // The best neighbor for i minimises (|p_i-p_j| - r_j). Over j>i (to the right, sorted) the term
    // (p_j - r_j) should be minimal; over j<i (left) the term (p_j + r_j) should be maximal. We do a
    // sweep keeping the best (p_j - r_j) to the right and (p_j + r_j) to the left.
    // Compute need_i = min_j (|p_i - p_j| - r_j) - r_i, then d_i = max(0, need_i).
    vector<long long> bestNeed(n, LLONG_MAX);
    // pass with j to the LEFT of i (p_j <= p_i): |p_i-p_j| = p_i - p_j; term = p_i - p_j - r_j = p_i - (p_j + r_j)
    long long maxLeft = LLONG_MIN;   // max (p_j + r_j) among processed
    for(int k=0;k<n;k++){
        int i=idx[k];
        if(maxLeft!=LLONG_MIN) bestNeed[i]=min(bestNeed[i], p[i] - maxLeft - r[i]);
        maxLeft=max(maxLeft, p[i]+r[i]);
    }
    // pass with j to the RIGHT of i (p_j >= p_i): |p_i-p_j| = p_j - p_i; term = p_j - p_i - r_j = (p_j - r_j) - p_i
    long long minRight = LLONG_MAX;  // min (p_j - r_j) among processed (to the right)
    for(int k=n-1;k>=0;k--){
        int i=idx[k];
        if(minRight!=LLONG_MAX) bestNeed[i]=min(bestNeed[i], minRight - p[i] - r[i]);
        minRight=min(minRight, p[i]-r[i]);
    }
    string out;
    for(int i=0;i<n;i++){ long long v=max(0LL, bestNeed[i]); out+=to_string(v); out+=(i+1<n?' ':'\n'); }
    cout<<out;
    return 0;
}
