# Advanced Dynamic Programming

::: keypoint
Every advanced DP is still fundamentally the same process: define the state, write the recurrence, and memoize. What changes in advanced paradigms is the *shape of the state*. This could be a bitmask representing a set of visited nodes, a boolean `tight` flag in digit DP, or the returns from two child subtrees in tree DP. Viewing advanced DP through this lens demystifies it.
:::

## DP on Trees

Tree DP applies dynamic programming to tree structures, typically by running a post-order Depth-First Search (DFS). In this pattern, each node recursively calls its children, receives their computed DP states, and combines them to form its own state, which it then returns to its parent.

### Maximum Path Sum in a Binary Tree

Given a non-empty binary tree, find the maximum path sum. A path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path must contain at least one node and does not need to go through the root.

**Intuition / approach:**
A brute-force approach might compute the maximum path through every node as a root, which would be $O(n^2)$. Using Tree DP, we can optimize this to $O(n)$. At any node, the maximum path sum *through* this node (acting as the highest point or "arch" of the path) is `node.val + max(0, left_max_path) + max(0, right_max_path)`. We update our global maximum with this value. However, the value this node *returns* to its parent can only include at most one of its children's paths (to remain a valid single path). Thus, it returns `node.val + max(0, max(left_max_path, right_max_path))`.

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    int max_sum;
    
    int dfs(TreeNode* node) {
        if (!node) return 0;
        
        // Compute max path sums from left and right children.
        // Ignore negative paths by taking max with 0.
        int left_sum = max(0, dfs(node->left));
        int right_sum = max(0, dfs(node->right));
        
        // Update the global max with the path acting as an arch through the current node.
        max_sum = max(max_sum, node->val + left_sum + right_sum);
        
        // Return the max path sum extending downwards from this node.
        return node->val + max(left_sum, right_sum);
    }
    
public:
    int maxPathSum(TreeNode* root) {
        max_sum = -1e9; // Safe minimum for negative node values
        dfs(root);
        return max_sum;
    }
};

int main() {
    TreeNode* root = new TreeNode(-10);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    
    Solution sol;
    cout << "Max Path Sum: " << sol.maxPathSum(root) << "\n";
    return 0;
}
```

**Complexity:**
- **Time:** $O(n)$ because each node is visited exactly once.
- **Space:** $O(h)$ where $h$ is the height of the tree, for the recursion stack.

**Practice:** https://leetcode.com/problems/binary-tree-maximum-path-sum/

### House Robber III

The thief has found himself a new place for his thievery again. There is only one entrance to this area, called the "root." Besides the root, each house has one and only one parent house. After a tour, the smart thief realized that all houses in this place form a binary tree. It will automatically contact the police if two directly-linked houses were broken into on the same night. Find the maximum amount of money the thief can rob without alerting the police.

**Intuition / approach:**
For each node, we have two choices: rob it or do not rob it. If we rob it, we cannot rob its children. If we do not rob it, we are free to either rob or not rob its children (taking the maximum of both for each child). The DP state at each node can be represented as a pair of integers: `{max_money_if_not_robbed, max_money_if_robbed}`. 

::: keypoint
Tree DP often requires a node to return multiple pieces of information to its parent. Returning a `pair` or `struct` of states cleanly encapsulates the subproblem results.
:::

```cpp
#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    // Returns {max_not_robbed, max_robbed}
    pair<int, int> dfs(TreeNode* node) {
        if (!node) return {0, 0};
        
        pair<int, int> left = dfs(node->left);
        pair<int, int> right = dfs(node->right);
        
        // If we don't rob this node, we can choose the best option from its children
        int not_robbed = max(left.first, left.second) + max(right.first, right.second);
        
        // If we rob this node, we cannot rob its children
        int robbed = node->val + left.first + right.first;
        
        return {not_robbed, robbed};
    }
    
public:
    int rob(TreeNode* root) {
        pair<int, int> res = dfs(root);
        return max(res.first, res.second);
    }
};

int main() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(3);
    root->right->right = new TreeNode(1);
    
    Solution sol;
    cout << "Max Robbed: " << sol.rob(root) << "\n";
    return 0;
}
```

**Complexity:**
- **Time:** $O(n)$ to visit every node once.
- **Space:** $O(h)$ for the recursion stack.

**Practice:** https://leetcode.com/problems/house-robber-iii/

### Binary Tree Cameras

Given a binary tree, we install cameras on the nodes of the tree. Each camera at a node can monitor its parent, itself, and its immediate children. Calculate the minimum number of cameras needed to monitor all nodes of the tree.

::: heavy
This problem introduces a state machine into Tree DP. A greedy-DP approach works best by evaluating the status of a node relative to its children.
:::

**Intuition / approach:**
We want to place cameras bottom-up. A leaf node should generally not have a camera (it is more optimal to place a camera on its parent). We can classify each node into one of three states:
0. Has a camera
1. Is covered (by a camera on a child)
2. Needs to be covered

During post-order traversal, a node decides its state based on its children:
- If any child needs cover (state 2), we MUST place a camera here (returns 0).
- If any child has a camera (state 0), we are covered (returns 1).
- If both children are covered (state 1), we are not covered and need our parent to place a camera (returns 2).

```cpp
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    int cameras = 0;
    
    // Returns: 0 = Has Camera, 1 = Covered, 2 = Needs Cover
    int dfs(TreeNode* node) {
        if (!node) return 1; // Null nodes are implicitly covered
        
        int left = dfs(node->left);
        int right = dfs(node->right);
        
        // If any child needs cover, place a camera here
        if (left == 2 || right == 2) {
            cameras++;
            return 0;
        }
        
        // If any child has a camera, this node is covered
        if (left == 0 || right == 0) {
            return 1;
        }
        
        // Both children are covered, this node now needs cover from its parent
        return 2;
    }
    
public:
    int minCameraCover(TreeNode* root) {
        // If the root itself needs cover, place one last camera
        if (dfs(root) == 2) {
            cameras++;
        }
        return cameras;
    }
};

int main() {
    TreeNode* root = new TreeNode(0);
    root->left = new TreeNode(0);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(0);
    
    Solution sol;
    cout << "Min Cameras: " << sol.minCameraCover(root) << "\n";
    return 0;
}
```

**Complexity:**
- **Time:** $O(n)$ to process each node.
- **Space:** $O(h)$ for the recursion stack.

**Practice:** https://leetcode.com/problems/binary-tree-cameras/

### Diameter of a Tree via DP

Find the length of the longest path between any two nodes in a tree. The length of a path between two nodes is represented by the number of edges between them.

**Intuition / approach:**
The diameter of a tree is simply the maximum over all nodes of `height(left_child) + height(right_child)`. Just like in maximum path sum, our DFS function will return the height of the current subtree (`1 + max(left_height, right_height)`), but as a side-effect, we update a global max diameter with `left_height + right_height`.

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    int max_diameter = 0;
    
    int dfs(TreeNode* node) {
        if (!node) return 0;
        
        int left_height = dfs(node->left);
        int right_height = dfs(node->right);
        
        // Update diameter: path going through the current node
        max_diameter = max(max_diameter, left_height + right_height);
        
        // Return height of the tree rooted at this node
        return 1 + max(left_height, right_height);
    }
    
public:
    int diameterOfBinaryTree(TreeNode* root) {
        dfs(root);
        return max_diameter;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    
    Solution sol;
    cout << "Diameter: " << sol.diameterOfBinaryTree(root) << "\n";
    return 0;
}
```

**Complexity:**
- **Time:** $O(n)$.
- **Space:** $O(h)$.

**Practice:** https://leetcode.com/problems/diameter-of-binary-tree/

## Bitmask DP

In Bitmask DP, the DP state incorporates a subset of items, encoded compactly into the bits of an integer. The $i$-th bit of the integer `mask` is `1` if the $i$-th item is in the subset, and `0` otherwise. This allows memoization over all possible subsets ($2^n$ combinations). Bitmask DP is typically viable only when $n \le 20$. 

Standard iterations over all masks look like `for (int mask = 0; mask < (1<<n); ++mask)`. To enumerate all submasks of a given `mask`, the standard idiom is `for (int s = mask; s; s = (s - 1) & mask)`.

### Travelling Salesman Problem

Given a list of cities and the distances between each pair of cities, what is the shortest possible route that visits each city exactly once and returns to the origin city?

::: heavy
The state requires knowing two things: the set of cities visited so far (the `mask`), and the *current city* we are at (`u`). Only with both can we accurately compute the distance to the next unvisited city.
:::

**Intuition / approach:**
A pure brute-force approach generates all permutations of cities ($O(n!)$). Using DP, we define the state as `dp[mask][u]`, which represents the minimum cost to visit all remaining unvisited cities and return to the start, given that we have currently visited the cities in `mask` and are currently at city `u`. 

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int tsp(const vector<vector<int>>& dist) {
        int n = dist.size();
        const int INF = 1e9;
        // dp[mask][u]
        vector<vector<int>> dp(1 << n, vector<int>(n, INF));
        
        // Base case: if we have visited all nodes and are at node u,
        // the cost is the distance from u back to the start node (node 0).
        for (int i = 0; i < n; i++) {
            dp[(1 << n) - 1][i] = dist[i][0];
        }
        
        // Iterate backwards from the full mask to the empty mask
        for (int mask = (1 << n) - 2; mask >= 1; mask--) {
            for (int u = 0; u < n; u++) {
                // If node u is in the current mask
                if (mask & (1 << u)) {
                    for (int v = 0; v < n; v++) {
                        // If node v is NOT in the current mask
                        if (!(mask & (1 << v))) {
                            dp[mask][u] = min(dp[mask][u], dist[u][v] + dp[mask | (1 << v)][v]);
                        }
                    }
                }
            }
        }
        
        // We start at node 0, with only node 0 visited
        return dp[1][0];
    }
};

int main() {
    vector<vector<int>> dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    
    Solution sol;
    cout << "Shortest TSP tour cost: " << sol.tsp(dist) << "\n";
    return 0;
}
```

**Complexity:**
- **Time:** $O(n^2 2^n)$ because there are $n 2^n$ states and calculating each takes $O(n)$.
- **Space:** $O(n 2^n)$ to store the DP table.

**Practice:** https://www.geeksforgeeks.org/travelling-salesman-problem-set-1/

### Assignment Problem

There are $N$ people and $N$ tasks. Given a matrix `cost` where `cost[i][j]` is the cost of assigning the $j$-th task to the $i$-th person, find the minimum total cost to assign exactly one task to each person.

::: keypoint
We do not need to explicitly store *which* person we are currently assigning in the DP state. The number of set bits in the `mask` of assigned tasks implicitly tells us exactly how many people have been assigned tasks so far.
:::

**Intuition / approach:**
Let `dp[mask]` be the minimum cost to assign tasks to the first `k` people, where `mask` represents the subset of tasks that have already been assigned. The value `k` is simply the number of set bits in `mask`, achievable via `__builtin_popcount(mask)`. We iterate through all unassigned tasks and assign one to person `k`.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minCostAssignment(const vector<vector<int>>& cost) {
        int n = cost.size();
        vector<int> dp(1 << n, 1e9);
        dp[0] = 0; // 0 cost to assign 0 tasks to 0 people
        
        for (int mask = 0; mask < (1 << n); mask++) {
            int k = __builtin_popcount(mask); // Which person we are assigning to
            if (k == n) continue;
            
            for (int j = 0; j < n; j++) {
                // If task j is not assigned yet
                if (!(mask & (1 << j))) {
                    dp[mask | (1 << j)] = min(dp[mask | (1 << j)], dp[mask] + cost[k][j]);
                }
            }
        }
        
        return dp[(1 << n) - 1];
    }
};

int main() {
    vector<vector<int>> cost = {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4}
    };
    
    Solution sol;
    cout << "Minimum Assignment Cost: " << sol.minCostAssignment(cost) << "\n";
    return 0;
}
```

**Complexity:**
- **Time:** $O(n 2^n)$ because we do $O(n)$ work for each of the $2^n$ masks.
- **Space:** $O(2^n)$ for the DP table.

**Practice:** https://www.geeksforgeeks.org/job-assignment-problem-using-branch-and-bound/

### Number of Ways to Wear Different Hats

There are `n` people and 40 types of hats. Each person has a list of preferred hats. Find the number of ways that the `n` people can wear different hats.

**Intuition / approach:**
Because $n \le 10$ and hats $\le 40$, it is vastly more efficient to use a bitmask over the *people* rather than the hats. We iterate over the hats from 1 to 40. For each hat, we can either skip it, or assign it to any person who wants it and currently does not have a hat (checked via the `mask`). The state is `dp[hat_index][mask]`.

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int numberWays(vector<vector<int>>& hats) {
        int n = hats.size();
        const int MOD = 1e9 + 7;
        
        // hat_to_people[i] stores list of people who like hat i
        vector<vector<int>> hat_to_people(41);
        for (int i = 0; i < n; i++) {
            for (int h : hats[i]) {
                hat_to_people[h].push_back(i);
            }
        }
        
        // dp[mask] = number of ways to assign hats such that people in 'mask' have hats.
        // We optimize space by only keeping the previous hat's DP array.
        vector<int> dp(1 << n, 0);
        dp[0] = 1;
        
        for (int h = 1; h <= 40; h++) {
            vector<int> next_dp = dp; // Skip this hat
            for (int mask = 0; mask < (1 << n); mask++) {
                if (dp[mask] == 0) continue;
                // Try to assign hat h to someone who likes it
                for (int p : hat_to_people[h]) {
                    if (!(mask & (1 << p))) { // If person p doesn't have a hat yet
                        next_dp[mask | (1 << p)] = (next_dp[mask | (1 << p)] + dp[mask]) % MOD;
                    }
                }
            }
            dp = next_dp;
        }
        
        return dp[(1 << n) - 1];
    }
};

int main() {
    vector<vector<int>> hats = {{3, 4}, {4, 5}, {5}};
    Solution sol;
    cout << "Number of ways: " << sol.numberWays(hats) << "\n";
    return 0;
}
```

**Complexity:**
- **Time:** $O(H \cdot 2^n)$ where $H$ is the number of hats (40).
- **Space:** $O(2^n)$ for the optimized 1D DP table.

**Practice:** https://leetcode.com/problems/number-of-ways-to-wear-different-hats-to-each-other/

## Digit DP

Digit DP is used to count the number of integers in a range $[L, R]$ that satisfy a specific property relating to their decimal digits. The standard trick is to compute $f(R) - f(L - 1)$, where $f(X)$ counts valid numbers in the range $[0, X]$. 

::: heavy
The core of Digit DP is the `tight` flag. When constructing a number digit by digit from left to right, if `tight == true`, the digits we can choose are constrained by the original number $X$. If `tight == false`, we have already chosen a smaller digit at an earlier position, so we are free to pick any digit from `0` to `9`.
:::

### Count numbers with a given digit-sum

Find the count of positive integers less than or equal to $N$ whose digits sum to exactly $S$.

**Intuition / approach:**
We construct the number digit by digit from the most significant to the least significant. Our DP state needs to track:
1. `pos`: the current digit position we are placing.
2. `sum`: the running sum of the digits placed so far.
3. `tight`: a boolean indicating if our choices are restricted by the upper bound $N$.

We memoize the results using `dp[pos][sum][tight]`.

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

class Solution {
    vector<vector<vector<long long>>> memo;
    string numStr;
    int targetSum;
    
    long long solve(int pos, int sum, int tight) {
        if (sum > targetSum) return 0;
        if (pos == numStr.length()) return sum == targetSum ? 1 : 0;
        
        if (memo[pos][sum][tight] != -1) {
            return memo[pos][sum][tight];
        }
        
        long long ans = 0;
        int limit = tight ? (numStr[pos] - '0') : 9;
        
        for (int d = 0; d <= limit; d++) {
            ans += solve(pos + 1, sum + d, tight && (d == limit));
        }
        
        return memo[pos][sum][tight] = ans;
    }
    
public:
    long long countNumbersWithSum(int n, int s) {
        numStr = to_string(n);
        targetSum = s;
        memo.assign(20, vector<vector<long long>>(200, vector<long long>(2, -1)));
        
        // We include 0 in the count if targetSum is 0, which is fine, 
        // but problem asks for positive integers. If s > 0, 0 is excluded naturally.
        return solve(0, 0, 1);
    }
};

int main() {
    int N = 1000;
    int S = 5;
    Solution sol;
    cout << "Count of numbers <= " << N << " with sum " << S << ": " << sol.countNumbersWithSum(N, S) << "\n";
    return 0;
}
```

**Complexity:**
- **Time:** $O(L \cdot S \cdot 2 \cdot 10)$, where $L$ is the number of digits in $N$, and $S$ is the target sum. This simplifies to $O(L \cdot S)$.
- **Space:** $O(L \cdot S)$ for the memoization table.

**Practice:** https://www.geeksforgeeks.org/count-of-numbers-between-l-and-r-having-a-given-digit-sum/

### Numbers With Repeated Digits

Given a positive integer `n`, return the number of positive integers less than or equal to `n` that have at least one repeated digit.

**Intuition / approach:**
It is easier to count the total numbers with NO repeated digits (all unique digits), and subtract this count from $N$. To count numbers with unique digits using Digit DP, we track a `mask` of digits used so far. The DP state needs `pos`, `mask`, `tight`, and an additional boolean `isLeadingZero` to handle the fact that leading zeros do not count towards digit uniqueness.

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
    vector<vector<vector<vector<int>>>> memo;
    string s;

    int solve(int pos, int mask, int tight, int isLeadingZero) {
        if (pos == s.length()) {
            return isLeadingZero ? 0 : 1; // 1 valid number if it's not entirely zeros
        }
        
        if (memo[pos][mask][tight][isLeadingZero] != -1) {
            return memo[pos][mask][tight][isLeadingZero];
        }
        
        int ans = 0;
        int limit = tight ? (s[pos] - '0') : 9;
        
        for (int d = 0; d <= limit; d++) {
            // If d is already used, we can't use it again (unless it's a leading zero)
            if ((mask & (1 << d)) && (!isLeadingZero || d != 0)) {
                continue;
            }
            
            int nextMask = mask;
            if (!isLeadingZero || d != 0) {
                nextMask |= (1 << d);
            }
            
            int nextTight = tight && (d == limit);
            int nextLeadingZero = isLeadingZero && (d == 0);
            
            ans += solve(pos + 1, nextMask, nextTight, nextLeadingZero);
        }
        
        return memo[pos][mask][tight][isLeadingZero] = ans;
    }

public:
    int numDupDigitsAtMostN(int n) {
        s = to_string(n);
        memo.assign(10, vector<vector<vector<int>>>(1024, vector<vector<int>>(2, vector<int>(2, -1))));
        int uniqueCount = solve(0, 0, 1, 1);
        return n - uniqueCount;
    }
};

int main() {
    int N = 1000;
    Solution sol;
    cout << "Numbers with repeated digits <= " << N << ": " << sol.numDupDigitsAtMostN(N) << "\n";
    return 0;
}
```

**Complexity:**
- **Time:** $O(L \cdot 2^{10} \cdot 2 \cdot 2 \cdot 10) = O(L)$, where $L$ is the number of digits in $N$.
- **Space:** $O(L \cdot 2^{10})$ for the memoization table.

**Practice:** https://leetcode.com/problems/numbers-with-repeated-digits/

## Interval DP

Interval DP solves problems by solving smaller contiguous subarrays (intervals) and combining them. The state is usually `dp[left][right]`. Iteration is almost always by `length` of the interval, from $2$ to $n$.

### Optimal Cost to Evaluate (Burst Balloons)

You are given `n` balloons, indexed from 0 to `n - 1`. Each balloon is painted with a number on it. You are asked to burst all the balloons. If you burst the $i$-th balloon, you will get `nums[i - 1] * nums[i] * nums[i + 1]` coins. Find the maximum coins you can collect.

**Intuition / approach:**
If we think about the *first* balloon to burst, it divides the array into two parts, but they are now adjacent, meaning they depend on each other. Instead, we think about the *last* balloon to burst. If balloon `k` is the last to burst in the interval `(left, right)`, the subproblems `(left, k)` and `(k, right)` are completely independent because `k` shields them from each other until it is burst. 

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        // Pad the array with 1s at boundaries
        vector<int> A(n + 2, 1);
        for (int i = 0; i < n; i++) A[i + 1] = nums[i];
        
        int m = A.size();
        // dp[i][j] is the max coins for bursting balloons strictly between i and j
        vector<vector<int>> dp(m, vector<int>(m, 0));
        
        for (int len = 2; len < m; len++) {
            for (int left = 0; left < m - len; left++) {
                int right = left + len;
                for (int k = left + 1; k < right; k++) {
                    dp[left][right] = max(dp[left][right],
                        dp[left][k] + dp[k][right] + A[left] * A[k] * A[right]);
                }
            }
        }
        
        return dp[0][m - 1];
    }
};

int main() {
    vector<int> nums = {3, 1, 5, 8};
    Solution sol;
    cout << "Max coins: " << sol.maxCoins(nums) << "\n";
    return 0;
}
```

**Complexity:**
- **Time:** $O(n^3)$ because there are $n^2$ intervals and computing each takes $O(n)$ time iterating over `k`.
- **Space:** $O(n^2)$ for the DP table.

**Practice:** https://leetcode.com/problems/burst-balloons/

## Close

::: interview
When do you use these? Bitmask DP appears when $n \le 20$ and the problem involves permutations, subsets, or assignments. Digit DP is the exclusive tool for "count numbers in a range with property P". Tree DP is necessary whenever you need to aggregate information over a rooted tree (often asking for paths or subset selections). Interval DP is the answer when you are collapsing adjacent elements and the order of operations matters. These are the DP flavours that separate medium from hard OA rounds.
:::
