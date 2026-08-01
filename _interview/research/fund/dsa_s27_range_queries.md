# Range Queries & Advanced Data Structures

::: keypoint
A recurring trade-off in range queries is precomputing a structure once so that each of many queries can be answered in $O(\log n)$ (or $O(1)$) instead of the naive $O(n)$ time. The decision guide is:
- **Immutable array + associative query** → prefix sums
- **Immutable array + idempotent query (min/max/gcd)** → sparse table
- **Point update + prefix/range sum** → Fenwick Tree (Binary Indexed Tree)
- **Range update + range query** → Segment Tree (with lazy propagation)
:::

## Prefix Sums & Difference Arrays

### Range Sum Query — Immutable
Given an integer array `nums`, handle multiple queries of the form: calculate the sum of the elements of `nums` between indices `left` and `right` inclusive where `left <= right`.

**Intuition:**
A naive approach would iterate from `left` to `right` for each query, taking $O(n)$ time per query. If the array never changes (immutable), we can precompute the sum of elements from index $0$ to $i$ for all $i$. The sum of any range $[L, R]$ is simply the prefix sum up to $R$ minus the prefix sum up to $L-1$.

**C++ solution:**
```cpp
#include <iostream>
#include <vector>

using namespace std;

class NumArray {
    vector<int> prefix;
public:
    NumArray(vector<int>& nums) {
        int n = nums.size();
        prefix.assign(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
    }
    
    int sumRange(int left, int right) {
        return prefix[right + 1] - prefix[left];
    }
};

int main() {
    vector<int> nums = {-2, 0, 3, -5, 2, -1};
    NumArray* obj = new NumArray(nums);
    cout << obj->sumRange(0, 2) << "\n"; // Output: 1
    cout << obj->sumRange(2, 5) << "\n"; // Output: -1
    cout << obj->sumRange(0, 5) << "\n"; // Output: -3
    delete obj;
    return 0;
}
```

**Complexity:** Time $O(n)$ to build, $O(1)$ per query. Space $O(n)$ for the prefix array.
**Practice:** https://leetcode.com/problems/range-sum-query-immutable/

### Range Sum Query 2D — Immutable
Given a 2D matrix `matrix`, handle multiple queries of the form: calculate the sum of the elements of `matrix` inside the rectangle defined by its upper left corner `(row1, col1)` and lower right corner `(row2, col2)`.

**Intuition:**
Extending prefix sums to 2D, `prefix[i][j]` stores the sum of all elements in the submatrix from `(0, 0)` to `(i-1, j-1)`. To query a rectangle from `(r1, c1)` to `(r2, c2)`, we take the sum up to `(r2, c2)`, subtract the rectangles extending too far right and down, and add back the doubly-subtracted top-left overlap.

**C++ solution:**
```cpp
#include <iostream>
#include <vector>

using namespace std;

class NumMatrix {
    vector<vector<int>> prefix;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return;
        int m = matrix.size();
        int n = matrix[0].size();
        prefix.assign(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                prefix[i + 1][j + 1] = matrix[i][j] + prefix[i][j + 1] + 
                                       prefix[i + 1][j] - prefix[i][j];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return prefix[row2 + 1][col2 + 1] - prefix[row1][col2 + 1] - 
               prefix[row2 + 1][col1] + prefix[row1][col1];
    }
};

int main() {
    vector<vector<int>> matrix = {
        {3, 0, 1, 4, 2},
        {5, 6, 3, 2, 1},
        {1, 2, 0, 1, 5},
        {4, 1, 0, 1, 7},
        {1, 0, 3, 0, 5}
    };
    NumMatrix* obj = new NumMatrix(matrix);
    cout << obj->sumRegion(2, 1, 4, 3) << "\n"; // Output: 8
    cout << obj->sumRegion(1, 1, 2, 2) << "\n"; // Output: 11
    cout << obj->sumRegion(1, 2, 2, 4) << "\n"; // Output: 12
    delete obj;
    return 0;
}
```

**Complexity:** Time $O(m \times n)$ to build, $O(1)$ per query. Space $O(m \times n)$ for the prefix matrix.
**Practice:** https://leetcode.com/problems/range-sum-query-2d-immutable/

::: keypoint
Note the **difference-array trick** for $O(1)$ range updates on an initially empty array followed by a single query phase. To add $v$ to all elements in $[L, R]$, simply add $v$ to `diff[L]` and subtract $v$ from `diff[R+1]`. After all updates, the prefix sum of the `diff` array yields the final values.
:::

## Sparse Table

::: heavy
A **Sparse Table** precomputes answers for every power-of-two length. A range minimum over an arbitrary length $L$ can be found by querying two overlapping blocks of the largest power of two $2^k \le L$. Because `min` is an **idempotent** operation (the overlap doesn't change the answer), this computes the result in $O(1)$ time. Note that sparse tables do NOT support updates.
:::

### Range Minimum Query with a sparse table
Given an immutable array, answer queries for the minimum element in the range `[L, R]`.

**Intuition:**
A naive approach takes $O(n)$ per query. A segment tree takes $O(\log n)$. A sparse table achieves $O(1)$ query time by exploiting the idempotent nature of `min`. We build a table `st[i][j]` that stores the minimum of the range starting at index `i` of length $2^j$. The range $[i, i+2^j-1]$ is the union of $[i, i+2^{j-1}-1]$ and $[i+2^{j-1}, i+2^j-1]$. To answer a query for $[L, R]$, let $k = \lfloor\log_2(R - L + 1)\rfloor$. The answer is $\min(\text{st}[L][k], \text{st}[R - 2^k + 1][k])$.

**C++ solution:**
```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class SparseTable {
    vector<vector<int>> st;
    vector<int> log2_val;
public:
    SparseTable(const vector<int>& arr) {
        int n = arr.size();
        int max_log = log2(n) + 1;
        
        st.assign(n, vector<int>(max_log));
        log2_val.assign(n + 1, 0);
        
        for (int i = 2; i <= n; i++) {
            log2_val[i] = log2_val[i / 2] + 1;
        }
        
        for (int i = 0; i < n; i++) {
            st[i][0] = arr[i];
        }
        
        for (int j = 1; j < max_log; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    
    int queryMin(int L, int R) {
        int k = log2_val[R - L + 1];
        return min(st[L][k], st[R - (1 << k) + 1][k]);
    }
};

int main() {
    vector<int> arr = {7, 2, 3, 0, 5, 10, 3, 12, 18};
    SparseTable st(arr);
    
    cout << st.queryMin(0, 4) << "\n"; // Output: 0
    cout << st.queryMin(4, 7) << "\n"; // Output: 3
    cout << st.queryMin(7, 8) << "\n"; // Output: 12
    return 0;
}
```

::: keypoint
A sparse table builds in $O(n \log n)$ time and queries in $O(1)$ time. It is strictly superior to segment trees for immutable RMQ when query volume is massive.
:::

**Complexity:** Time $O(n \log n)$ to build, $O(1)$ per query. Space $O(n \log n)$ for the table.
**Practice:** https://www.geeksforgeeks.org/sparse-table/

## Fenwick Tree / Binary Indexed Tree

::: heavy
A **Binary Indexed Tree (BIT)** or Fenwick Tree answers point updates and prefix sums in $O(\log n)$ time using the low-bit trick: `i & (-i)` isolates the lowest set bit of $i$.
In a 1-indexed BIT array, the element at index $i$ stores the sum of a range of elements ending at $i$ with length equal to its lowest set bit.
Example: For $i = 12$ (`1100` in binary), the lowest set bit is $4$ (`0100`). Thus, `bit[12]` covers the sum of $4$ elements ending at $12$ (indices $9, 10, 11, 12$).
- **Update $i$:** Add value to `bit[i]`, then jump to the next interval that contains this element by adding the lowest set bit (`i += i & (-i)`).
- **Prefix Sum $i$:** Add `bit[i]` to the total, then jump to the preceding disjoint interval by subtracting the lowest set bit (`i -= i & (-i)`).
:::

### Point-update / Prefix-sum with a BIT
Given an array `nums`, support queries for the sum in range $[L, R]$ and point updates (changing `nums[i]` to a new value).

**Intuition:**
Prefix sums give $O(1)$ queries but $O(n)$ updates. A plain array gives $O(1)$ updates but $O(n)$ queries. A BIT balances both to $O(\log n)$. A range sum $[L, R]$ is simply the prefix sum up to $R$ minus the prefix sum up to $L-1$.

**C++ solution:**
```cpp
#include <iostream>
#include <vector>

using namespace std;

class FenwickTree {
    vector<int> bit;
    int n;
public:
    FenwickTree(int n) {
        this->n = n;
        bit.assign(n + 1, 0); // 1-indexed
    }
    
    // Add val to element at index i (1-indexed)
    void add(int i, int val) {
        while (i <= n) {
            bit[i] += val;
            i += i & (-i); // Move to parent
        }
    }
    
    // Prefix sum from 1 to i
    int query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += bit[i];
            i -= i & (-i); // Move to preceding interval
        }
        return sum;
    }
    
    // Range sum from L to R (1-indexed)
    int queryRange(int L, int R) {
        return query(R) - query(L - 1);
    }
};

int main() {
    int n = 5;
    FenwickTree ft(n);
    vector<int> arr = {1, 2, 3, 4, 5};
    // Build tree
    for (int i = 0; i < n; i++) {
        ft.add(i + 1, arr[i]);
    }
    
    cout << ft.queryRange(1, 3) << "\n"; // Output: 6
    // Point update: add 5 to index 2 (was 2, now 7)
    ft.add(2, 5); 
    cout << ft.queryRange(1, 3) << "\n"; // Output: 11
    return 0;
}
```

::: keypoint
A BIT requires only an array of size $n+1$, making it exceptionally space-efficient with very small constant factors compared to a Segment Tree.
:::

**Complexity:** Time $O(n \log n)$ to build via point updates (or $O(n)$ with a linear build algorithm), $O(\log n)$ per query/update. Space $O(n)$.
**Practice:** https://leetcode.com/problems/range-sum-query-mutable/

### Count of Smaller Numbers After Self
Given an integer array `nums`, return an integer array `counts` where `counts[i]` is the number of smaller elements to the right of `nums[i]`.

**Intuition:**
Iterate from right to left. We need to know how many previously seen elements are strictly less than the current element. We can treat the possible array values as indices in a BIT. When we see a value, we query the BIT for the sum in the range $[0, value-1]$ to count the smaller numbers, and then add $1$ to the BIT at index `value`.

::: trap
The values in `nums` might be negative or extremely large (e.g., $10^4$ or $10^9$). You cannot use them directly as BIT indices. You must **coordinate compress** them: map the smallest unique value to 1, the next to 2, etc., so they fit in a dense array of size $\le n$.
:::

**C++ solution:**
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class FenwickTree {
    vector<int> bit;
    int n;
public:
    FenwickTree(int n) : n(n), bit(n + 1, 0) {}
    
    void add(int i, int val) {
        while (i <= n) {
            bit[i] += val;
            i += i & (-i);
        }
    }
    
    int query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += bit[i];
            i -= i & (-i);
        }
        return sum;
    }
};

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return {};
        
        // Coordinate Compression
        vector<int> sorted_nums = nums;
        sort(sorted_nums.begin(), sorted_nums.end());
        sorted_nums.erase(unique(sorted_nums.begin(), sorted_nums.end()), sorted_nums.end());
        
        unordered_map<int, int> rank;
        for (int i = 0; i < sorted_nums.size(); ++i) {
            rank[sorted_nums[i]] = i + 1; // 1-indexed for BIT
        }
        
        FenwickTree ft(sorted_nums.size());
        vector<int> result(n);
        
        // Process from right to left
        for (int i = n - 1; i >= 0; --i) {
            int r = rank[nums[i]];
            result[i] = ft.query(r - 1);
            ft.add(r, 1);
        }
        
        return result;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {5, 2, 6, 1};
    vector<int> result = sol.countSmaller(nums);
    
    for (int count : result) {
        cout << count << " "; // Output: 2 1 1 0
    }
    cout << "\n";
    return 0;
}
```

**Complexity:** Time $O(n \log n)$ due to sorting and BIT operations. Space $O(n)$ for the BIT and maps.
**Practice:** https://leetcode.com/problems/count-of-smaller-numbers-after-self/

## Segment Tree

A **Segment Tree** answers range queries and point updates recursively in $O(\log n)$ time. It is a full binary tree where each node represents an interval. The root represents the whole array $[0, n-1]$. Each internal node splits its interval in half, handing $[L, mid]$ to its left child and $[mid+1, R]$ to its right child. Leaves represent single elements. It is commonly implemented using an array-backed tree of size $4n$.

### Range Sum Query — Mutable
Answer range sum queries and point updates.

**Intuition:**
We build the tree recursively. To update an index, we traverse down to the leaf representing that index, update it, and recalculate parent values on the way back up. To query a range $[L, R]$, we traverse the tree. If a node's interval is fully within $[L, R]$, we return its value immediately. If it's completely outside, we return a neutral value (like $0$ for sum). Otherwise, we recursively query both children and combine their results.

**C++ solution:**
```cpp
#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {
    vector<int> tree;
    int n;
    
    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = start + (end - start) / 2;
        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
    
    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = start + (end - start) / 2;
        if (start <= idx && idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
    
    int query(int node, int start, int end, int L, int R) {
        if (R < start || end < L) return 0; // Completely outside
        if (L <= start && end <= R) return tree[node]; // Completely inside
        
        int mid = start + (end - start) / 2;
        int p1 = query(2 * node, start, mid, L, R);
        int p2 = query(2 * node + 1, mid + 1, end, L, R);
        return p1 + p2;
    }
    
public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.assign(4 * n, 0);
        if (n > 0) build(arr, 1, 0, n - 1); // 1-indexed for tree nodes
    }
    
    void update(int idx, int val) {
        update(1, 0, n - 1, idx, val);
    }
    
    int query(int L, int R) {
        return query(1, 0, n - 1, L, R);
    }
};

int main() {
    vector<int> nums = {1, 3, 5};
    SegmentTree st(nums);
    cout << st.query(0, 2) << "\n"; // Output: 9
    st.update(1, 2); // nums becomes {1, 2, 5}
    cout << st.query(0, 2) << "\n"; // Output: 8
    return 0;
}
```

::: keypoint
A Segment Tree is highly versatile. By simply changing the operation (`+`, `min`, `max`, `gcd`) in the `build`, `update`, and `query` methods, and choosing the right neutral element (e.g., $0$ for sum, $\infty$ for min), you can adapt it to a wide variety of queries.
:::

**Complexity:** Time $O(n)$ to build, $O(\log n)$ per query/update. Space $O(n)$ (specifically $4n$).
**Practice:** https://leetcode.com/problems/range-sum-query-mutable/

### Range Minimum / Range Max query with a segment tree
Answer range minimum queries and point updates.

**Intuition:**
We swap the `+` operator for `min`, and use $\infty$ instead of $0$ for intervals that fall completely outside the query range.

**C++ solution:**
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

class MinSegmentTree {
    vector<int> tree;
    int n;
    
    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = start + (end - start) / 2;
        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }
    
    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = start + (end - start) / 2;
        if (start <= idx && idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }
    
    int query(int node, int start, int end, int L, int R) {
        if (R < start || end < L) return INF; // Completely outside
        if (L <= start && end <= R) return tree[node]; // Completely inside
        
        int mid = start + (end - start) / 2;
        int p1 = query(2 * node, start, mid, L, R);
        int p2 = query(2 * node + 1, mid + 1, end, L, R);
        return min(p1, p2);
    }
    
public:
    MinSegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.assign(4 * n, 0);
        if (n > 0) build(arr, 1, 0, n - 1);
    }
    
    void update(int idx, int val) {
        update(1, 0, n - 1, idx, val);
    }
    
    int query(int L, int R) {
        return query(1, 0, n - 1, L, R);
    }
};

int main() {
    vector<int> nums = {5, 2, 7, 3, 1};
    MinSegmentTree st(nums);
    cout << st.query(0, 2) << "\n"; // Output: 2
    cout << st.query(2, 4) << "\n"; // Output: 1
    st.update(4, 8); // nums becomes {5, 2, 7, 3, 8}
    cout << st.query(2, 4) << "\n"; // Output: 3
    return 0;
}
```

**Complexity:** Time $O(n)$ to build, $O(\log n)$ per query/update. Space $O(n)$.
**Practice:** https://www.geeksforgeeks.org/segment-tree-set-1-range-minimum-query/

## Lazy Propagation

::: heavy
If we need to perform **range updates** (e.g., "add $V$ to all elements in $[L, R]$"), a standard segment tree would require $O(n \log n)$ time to update each leaf individually.
**Lazy Propagation** solves this by deferring updates with a secondary `lazy[]` array. When we want to update a range that fully covers a segment tree node, we update that node's value immediately and store the pending update in `lazy[node]` for its children. We do not traverse to the children yet. Later, if we need to visit those children for a subsequent query or update, we "push" the pending lazy value down to them. This restores $O(\log n)$ time for both range queries and range updates.
:::

### Range Update + Range Sum with lazy propagation
Add value `v` to all elements in range `[L, R]`, and query the sum in range `[L, R]`.

**Intuition:**
We maintain `tree[]` (the sum) and `lazy[]` (pending additions). Before visiting a node's children, we call a `push` function to apply any pending `lazy` value to the children and add it to the children's `lazy` state. When a node completely covers our target range, we apply the update directly to the node (for a sum tree, adding $v \times \text{number of elements in range}$) and mark it lazy, then halt recursion.

**C++ solution:**
```cpp
#include <iostream>
#include <vector>

using namespace std;

class LazySegmentTree {
    vector<long long> tree, lazy;
    int n;
    
    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            int mid = start + (end - start) / 2;
            // Apply lazy value to left child
            tree[2 * node] += lazy[node] * (mid - start + 1);
            lazy[2 * node] += lazy[node];
            
            // Apply lazy value to right child
            tree[2 * node + 1] += lazy[node] * (end - mid);
            lazy[2 * node + 1] += lazy[node];
            
            lazy[node] = 0; // Clear current node's lazy value
        }
    }
    
    void updateRange(int node, int start, int end, int L, int R, long long val) {
        if (L <= start && end <= R) {
            // Completely inside
            tree[node] += val * (end - start + 1);
            lazy[node] += val;
            return;
        }
        
        push(node, start, end);
        
        int mid = start + (end - start) / 2;
        if (L <= mid) {
            updateRange(2 * node, start, mid, L, R, val);
        }
        if (R > mid) {
            updateRange(2 * node + 1, mid + 1, end, L, R, val);
        }
        
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
    
    long long queryRange(int node, int start, int end, int L, int R) {
        if (R < start || end < L) return 0;
        if (L <= start && end <= R) return tree[node];
        
        push(node, start, end);
        
        int mid = start + (end - start) / 2;
        long long p1 = queryRange(2 * node, start, mid, L, R);
        long long p2 = queryRange(2 * node + 1, mid + 1, end, L, R);
        return p1 + p2;
    }
    
public:
    LazySegmentTree(int n) {
        this->n = n;
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }
    
    void update(int L, int R, long long val) {
        updateRange(1, 0, n - 1, L, R, val);
    }
    
    long long query(int L, int R) {
        return queryRange(1, 0, n - 1, L, R);
    }
};

int main() {
    int n = 5;
    LazySegmentTree st(n);
    // Array is implicitly {0, 0, 0, 0, 0}
    
    st.update(0, 2, 5); // Add 5 to indices [0, 2] -> {5, 5, 5, 0, 0}
    cout << st.query(1, 3) << "\n"; // Output: 10 (5 + 5 + 0)
    
    st.update(2, 4, 2); // Add 2 to indices [2, 4] -> {5, 5, 7, 2, 2}
    cout << st.query(1, 3) << "\n"; // Output: 14 (5 + 7 + 2)
    
    return 0;
}
```

**Complexity:** Time $O(\log n)$ per range query or range update. Space $O(n)$.
**Practice:** https://leetcode.com/problems/range-module/

::: interview
In an interview, pick the lightest tool that answers the queries requested:
- Reach for **prefix sums** before a BIT before a segment tree.
- Use a **segment tree with lazy propagation** only when you truly need BOTH arbitrary range updates AND arbitrary range queries.
- Note that many "hard" OA problems are simply a standard structure (like a BIT) hiding behind a verbose story. Always map the operations requested (e.g., "count inversions") to the data structures available.
:::
