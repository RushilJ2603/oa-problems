# Dynamic Programming

::: heavy
**Dynamic Programming (DP)** is an algorithmic paradigm that solves a given complex problem by breaking it into subproblems and storing the results of these subproblems to avoid computing the same results again. It is applicable when a problem exhibits **overlapping subproblems** (the same subproblem is evaluated multiple times) and **optimal substructure** (an optimal solution can be constructed efficiently from optimal solutions of its subproblems).

The pedagogy of DP follows a four-step ladder, most easily observed in computing the Fibonacci sequence:
1. **Recursion:** Express the problem in terms of itself. Computing the $n$-th Fibonacci number recursively as $F(n) = F(n-1) + F(n-2)$ yields an exponential recursion tree (as illustrated in the Recursion section) where identical subproblems like $F(n-2)$ are recomputed many times. Time complexity is $O(2^{n})$.
2. **Memoization (Top-Down):** Cache the results of recursive calls in an array or hash map. When a subproblem is encountered, return the cached value if it exists. This prunes the recursion tree, reducing the time complexity to $O(n)$ while keeping the spatial overhead of the recursion stack.
3. **Tabulation (Bottom-Up):** Discard the recursion entirely. Determine the base cases and build the solution iteratively from the smallest subproblems up to the desired target. The array serves as a table of solutions.
4. **Space Optimization:** Observe the recurrence relation. If computing the current state only requires a constant number of previous states (e.g., $F(n)$ only requires $F(n-1)$ and $F(n-2)$), the $O(n)$ space table can be reduced to $O(1)$ by maintaining only those few variables.
:::

::: keypoint
To identify a DP problem, look for scenarios asking to "try all choices", find the "minimum/maximum", or count the "number of ways", coupled with a state that repeats during exploration.
:::

::: keypoint
The DP state-design recipe:
1. Express the problem as a function of its indices or parameters, e.g., $f(\text{index}, \dots)$.
2. Write the recurrence relation that connects the current state to its subproblem states.
3. Identify the base cases that terminate the recurrence.
:::

## 1D DP and DP on Grids

### Climbing Stairs
You are climbing a staircase. It takes $n$ steps to reach the top. Each time you can either climb 1 or 2 steps. Determine the total number of distinct ways to reach the top.

**Intuition:**
At any step $i$, you could have arrived from either step $i-1$ (by taking 1 step) or from step $i-2$ (by taking 2 steps). Thus, the number of ways to reach step $i$ is the sum of the ways to reach step $i-1$ and step $i-2$.
- **Recurrence:** $f(i) = f(i-1) + f(i-2)$.
- **Base cases:** $f(1) = 1$, $f(2) = 2$.
This is precisely the Fibonacci sequence shifted. Memoization requires an array of size $n$, and tabulation iterates from 3 to $n$. Since $f(i)$ only needs the two immediate predecessors, we can space-optimize the $O(n)$ array into two integer variables.

```cpp
#include <iostream>

using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;
        
        int prev2 = 1;
        int prev = 2;
        
        for (int i = 3; i <= n; ++i) {
            int curr = prev + prev2;
            prev2 = prev;
            prev = curr;
        }
        
        return prev;
    }
};

int main() {
    Solution sol;
    cout << sol.climbStairs(5) << "\n"; // Expected: 8
    return 0;
}
```
**Complexity:**
- **Time:** $O(n)$ because we iterate from $3$ to $n$.
- **Space:** $O(1)$ as we only maintain two variables.

**Practice:** https://leetcode.com/problems/climbing-stairs/

### Frog Jump (Minimum Energy)
A frog is on the 1st step of an $N$-step stairs. The heights of the stairs are given in an array. The frog can jump 1 or 2 steps at a time. Energy consumed in a jump from $i$ to $j$ is $|h[i] - h[j]|$. Find the minimum energy required to reach the $N$-th step.

**Intuition:**
To reach step $i$ with minimum energy, the frog must have made an optimal jump from either step $i-1$ or step $i-2$. We compute the cost of both choices and take the minimum.
- **Recurrence:** $f(i) = \min(f(i-1) + |h[i] - h[i-1]|, f(i-2) + |h[i] - h[i-2]|)$.
- **Base case:** $f(0) = 0$.
Memoizing the recursion takes $O(n)$ time and $O(n)$ space. Since we only need the minimum energies of the last two steps to compute the current step, tabulation can be space-optimized to use just two variables instead of a full array.

```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumEnergy(vector<int>& height, int n) {
        if (n == 1) return 0;
        
        int prev2 = 0;
        int prev = abs(height[1] - height[0]);
        
        for (int i = 2; i < n; ++i) {
            int jumpOne = prev + abs(height[i] - height[i-1]);
            int jumpTwo = prev2 + abs(height[i] - height[i-2]);
            int curr = min(jumpOne, jumpTwo);
            prev2 = prev;
            prev = curr;
        }
        
        return prev;
    }
};

int main() {
    Solution sol;
    vector<int> heights = {10, 20, 30, 10};
    cout << sol.minimumEnergy(heights, heights.size()) << "\n"; // Expected: 20
    return 0;
}
```
**Complexity:**
- **Time:** $O(n)$ to traverse the array of heights.
- **Space:** $O(1)$ by storing only `prev` and `prev2`.

**Practice:** https://practice.geeksforgeeks.org/problems/geek-jump/1

### Frog Jump with K Distances
A frog can jump up to $K$ steps forward. Find the minimum energy required to reach the $N$-th step.

**Intuition:**
This is a generalization of the previous problem. Instead of checking just $i-1$ and $i-2$, the frog checks all valid steps from $i-1$ back to $i-K$.
- **Recurrence:** $f(i) = \min_{1 \le j \le K} \{f(i-j) + |h[i] - h[i-j]|\}$ for $i-j \ge 0$.
Because $K$ can be large, we cannot reduce the space complexity to $O(1)$ variables easily. We must maintain an array of size $O(n)$ (or at least size $K$) for tabulation.

```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minimizeCost(vector<int>& height, int n, int k) {
        vector<int> dp(n, 0);
        dp[0] = 0;
        
        for (int i = 1; i < n; ++i) {
            int minSteps = INT_MAX;
            for (int j = 1; j <= k; ++j) {
                if (i - j >= 0) {
                    int jump = dp[i-j] + abs(height[i] - height[i-j]);
                    minSteps = min(minSteps, jump);
                }
            }
            dp[i] = minSteps;
        }
        
        return dp[n-1];
    }
};

int main() {
    Solution sol;
    vector<int> heights = {10, 30, 40, 50, 20};
    cout << sol.minimizeCost(heights, heights.size(), 3) << "\n"; // Expected: 30
    return 0;
}
```
**Complexity:**
- **Time:** $O(n \times k)$ since for each of the $n$ steps we iterate back up to $k$ steps.
- **Space:** $O(n)$ to store the DP array (or $O(k)$ if optimized to a rolling buffer).

**Practice:** https://practice.geeksforgeeks.org/problems/minimal-cost/1

### Maximum Sum of Non-Adjacent Elements (House Robber)

::: keypoint
The "pick / not-pick" pattern on a 1D sequence where adjacent elements are constrained.
:::

Given an array of integers, find the maximum sum of a subsequence such that no two elements are adjacent.

**Intuition:**
For any element at index $i$, we have two choices:
1. **Pick it:** We add `arr[i]` to the sum and cannot pick the adjacent element at `i-1`. We move to `i-2`.
2. **Not pick it:** We do not add `arr[i]`, which leaves us free to consider the element at `i-1`.
- **Recurrence:** $f(i) = \max(f(i-1), f(i-2) + \text{arr}[i])$.
- **Base cases:** $f(0) = \text{arr}[0]$. $f(1) = \max(\text{arr}[0], \text{arr}[1])$.
Since state $i$ only depends on $i-1$ and $i-2$, memoization or a full tabulation array can be space-optimized to use just two variables.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        
        int prev2 = nums[0];
        int prev = max(nums[0], nums[1]);
        
        for (int i = 2; i < n; ++i) {
            int pick = nums[i] + prev2;
            int notPick = prev;
            int curr = max(pick, notPick);
            prev2 = prev;
            prev = curr;
        }
        
        return prev;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {2, 7, 9, 3, 1};
    cout << sol.rob(nums) << "\n"; // Expected: 12
    return 0;
}
```
**Complexity:**
- **Time:** $O(n)$ for a single pass through the array.
- **Space:** $O(1)$ using constant extra space.

**Practice:** https://leetcode.com/problems/house-robber/

### House Robber II
You are given an array representing houses in a circle. House 1 and House $n$ are adjacent. Find the maximum amount you can rob without alerting the police (robbing two adjacent houses).

**Intuition:**
Because the array is circular, we cannot rob both the first house and the last house simultaneously. The optimal solution must therefore either:
1. Exclude the first house (consider houses from $1$ to $n-1$).
2. Exclude the last house (consider houses from $0$ to $n-2$).
The answer is the maximum of these two linear "House Robber" problems.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    int robLinear(vector<int>& nums, int start, int end) {
        int prev2 = 0;
        int prev = 0;
        
        for (int i = start; i <= end; ++i) {
            int curr = max(prev, prev2 + nums[i]);
            prev2 = prev;
            prev = curr;
        }
        
        return prev;
    }
    
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        
        // Exclude last house vs Exclude first house
        return max(robLinear(nums, 0, n - 2), robLinear(nums, 1, n - 1));
    }
};

int main() {
    Solution sol;
    vector<int> nums = {2, 3, 2};
    cout << sol.rob(nums) << "\n"; // Expected: 3
    return 0;
}
```
**Complexity:**
- **Time:** $O(n)$ because we solve two linear $O(n)$ problems.
- **Space:** $O(1)$ since each linear pass uses constant extra space.

**Practice:** https://leetcode.com/problems/house-robber-ii/

### Ninja's Training
A ninja has $N$ days of training. Each day, they can perform one of three tasks (0, 1, or 2), earning different points. The ninja cannot perform the same task on two consecutive days. Find the maximum total points achievable.

**Intuition:**
At any day $i$, the optimal choice depends heavily on which task was chosen on day $i-1$. Therefore, the DP state must track both the current day and the task performed on the previous day.
- **Recurrence:** $f(\text{day}, \text{last}) = \max_{t \ne \text{last}} \{ f(\text{day}-1, t) + \text{points}[\text{day}][t] \}$.
For tabulation, the state `dp[day][last]` represents the maximum merit on `day` given that `last` task was not allowed. A 2D array of size $N \times 4$ is sufficient (where task 3 represents "no previous constraint" for day 0). Because the current day relies exclusively on the immediate previous day, we can space-optimize to a 1D array of size 4.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximumPoints(vector<vector<int>>& points, int n) {
        // prev[last_task] stores max points up to the previous day
        vector<int> prev(4, 0);
        
        // Base case for day 0
        prev[0] = max(points[0][1], points[0][2]);
        prev[1] = max(points[0][0], points[0][2]);
        prev[2] = max(points[0][0], points[0][1]);
        prev[3] = max({points[0][0], points[0][1], points[0][2]});
        
        // Iterate for remaining days
        for (int day = 1; day < n; ++day) {
            vector<int> temp(4, 0);
            for (int last = 0; last < 4; ++last) {
                temp[last] = 0;
                for (int task = 0; task < 3; ++task) {
                    if (task != last) {
                        temp[last] = max(temp[last], points[day][task] + prev[task]);
                    }
                }
            }
            prev = temp;
        }
        
        return prev[3];
    }
};

int main() {
    Solution sol;
    vector<vector<int>> points = {{1, 2, 5}, {3, 1, 1}, {3, 3, 3}};
    cout << sol.maximumPoints(points, points.size()) << "\n"; // Expected: 11
    return 0;
}
```
**Complexity:**
- **Time:** $O(n \times 4 \times 3) = O(n)$ to process each day.
- **Space:** $O(1)$ since we only use two arrays of size 4.

**Practice:** https://practice.geeksforgeeks.org/problems/geek-training/1

### Grid Unique Paths
Given an $m \times n$ grid, determine the number of possible unique paths from the top-left corner to the bottom-right corner, moving only down or right.

**Intuition:**
To reach cell $(i, j)$, you must have moved down from $(i-1, j)$ or right from $(i, j-1)$. The total number of paths to $(i, j)$ is the sum of paths to those two incoming cells.
- **Recurrence:** $f(i, j) = f(i-1, j) + f(i, j-1)$.
- **Base cases:** $f(0, 0) = 1$. Boundaries out of bounds contribute 0.
A standard 2D tabulation table `dp[m][n]` processes row by row. Since computing the current row only requires the current row itself (for the left cell) and the immediate previous row (for the top cell), we can space-optimize to a 1D array representing the previous row.

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> prev(n, 1);
        
        for (int i = 1; i < m; ++i) {
            vector<int> curr(n, 1);
            for (int j = 1; j < n; ++j) {
                // curr[j-1] is left, prev[j] is top
                curr[j] = curr[j-1] + prev[j];
            }
            prev = curr;
        }
        
        return prev[n-1];
    }
};

int main() {
    Solution sol;
    cout << sol.uniquePaths(3, 7) << "\n"; // Expected: 28
    return 0;
}
```
**Complexity:**
- **Time:** $O(m \times n)$ to process the grid.
- **Space:** $O(n)$ to store a single row of the grid.

**Practice:** https://leetcode.com/problems/unique-paths/

### Grid Unique Paths II
Similar to the previous problem, but the grid contains obstacles (represented by $1$, open space by $0$). Find the number of unique paths from top-left to bottom-right.

**Intuition:**
The logic is identical to Grid Unique Paths, except we cannot move through obstacles. If a cell contains an obstacle, the number of paths to reach it is strictly $0$.
- **Recurrence:** If $\text{grid}[i][j] == 1$, $f(i, j) = 0$. Else, $f(i, j) = f(i-1, j) + f(i, j-1)$.
As before, we optimize space by retaining only the previous row in a 1D array.

```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        
        if (obstacleGrid[0][0] == 1 || obstacleGrid[m-1][n-1] == 1) {
            return 0;
        }
        
        vector<int> prev(n, 0);
        
        for (int i = 0; i < m; ++i) {
            vector<int> curr(n, 0);
            for (int j = 0; j < n; ++j) {
                if (obstacleGrid[i][j] == 1) {
                    curr[j] = 0;
                } else if (i == 0 && j == 0) {
                    curr[j] = 1;
                } else {
                    int up = (i > 0) ? prev[j] : 0;
                    int left = (j > 0) ? curr[j-1] : 0;
                    curr[j] = up + left;
                }
            }
            prev = curr;
        }
        
        return prev[n-1];
    }
};

int main() {
    Solution sol;
    vector<vector<int>> grid = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    cout << sol.uniquePathsWithObstacles(grid) << "\n"; // Expected: 2
    return 0;
}
```
**Complexity:**
- **Time:** $O(m \times n)$ to traverse the grid cells.
- **Space:** $O(n)$ by keeping a 1D DP array for the previous row.

**Practice:** https://leetcode.com/problems/unique-paths-ii/

### Minimum Path Sum in a Grid
Given an $m \times n$ grid filled with non-negative numbers, find a path from top-left to bottom-right that minimizes the sum of all numbers along its path. You can only move down or right.

**Intuition:**
At any cell $(i, j)$, you must pick the cheaper of the two paths arriving from above $(i-1, j)$ and from the left $(i, j-1)$, and then add the current cell's value.
- **Recurrence:** $f(i, j) = \min(f(i-1, j), f(i, j-1)) + \text{grid}[i][j]$.
- **Base case:** $f(0, 0) = \text{grid}[0][0]$.
Out-of-bounds cells evaluate to infinity so they are ignored by the $\min$ function. A full 2D table can again be collapsed to a 1D array representing the previous row.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        vector<int> prev(n, 0);
        
        for (int i = 0; i < m; ++i) {
            vector<int> curr(n, 0);
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0) {
                    curr[j] = grid[i][j];
                } else {
                    int up = grid[i][j];
                    if (i > 0) up += prev[j];
                    else up += 1e9;
                    
                    int left = grid[i][j];
                    if (j > 0) left += curr[j-1];
                    else left += 1e9;
                    
                    curr[j] = min(up, left);
                }
            }
            prev = curr;
        }
        
        return prev[n-1];
    }
};

int main() {
    Solution sol;
    vector<vector<int>> grid = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    cout << sol.minPathSum(grid) << "\n"; // Expected: 7
    return 0;
}
```
**Complexity:**
- **Time:** $O(m \times n)$ to process the whole grid.
- **Space:** $O(n)$ keeping a 1D array.

**Practice:** https://leetcode.com/problems/minimum-path-sum/

### Minimum Path Sum in a Triangle
Given a triangle array, return the minimum path sum from top to bottom. For each step, you may move to an adjacent number on the row below: from index $i$ to index $i$ or $i+1$.

**Intuition:**
Because a top-down approach branches outward, fixing a bottom-up traversal is structurally cleaner. From any node $(i, j)$, you look downward to $(i+1, j)$ and $(i+1, j+1)$ and take the minimum path sum extending from those nodes.
- **Recurrence (Bottom-Up):** $f(i, j) = \min(f(i+1, j), f(i+1, j+1)) + \text{triangle}[i][j]$.
- **Base cases:** The bottom row is simply the elements themselves: $f(n-1, j) = \text{triangle}[n-1][j]$.
Space optimization works here as well. Processing backwards from the bottom row means we only need to keep the $O(n)$ elements of the row directly below us.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        // Start with the last row
        vector<int> front = triangle[n-1];
        
        for (int i = n - 2; i >= 0; --i) {
            vector<int> curr(i + 1, 0);
            for (int j = 0; j <= i; ++j) {
                curr[j] = min(front[j], front[j+1]) + triangle[i][j];
            }
            front = curr;
        }
        
        return front[0];
    }
};

int main() {
    Solution sol;
    vector<vector<int>> triangle = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    cout << sol.minimumTotal(triangle) << "\n"; // Expected: 11
    return 0;
}
```
**Complexity:**
- **Time:** $O(n^2)$ where $n$ is the number of rows, as there are $O(n^2)$ elements in the triangle.
- **Space:** $O(n)$ space used by a 1D array of size up to $n$.

**Practice:** https://leetcode.com/problems/triangle/

### Minimum / Maximum Falling Path Sum
Given an $n \times n$ array of integers `matrix`, return the minimum sum of any falling path through the matrix. You start anywhere on the first row and can move down, down-left, or down-right.

**Intuition:**
We want the minimum path reaching any cell on the final row. Let $f(i, j)$ be the minimum falling path sum to reach cell $(i, j)$. You can arrive at $(i, j)$ from the cell directly above, the cell diagonally top-left, or the cell diagonally top-right.
- **Recurrence:** $f(i, j) = \min(f(i-1, j-1), f(i-1, j), f(i-1, j+1)) + \text{matrix}[i][j]$.
- **Base case:** The top row defaults to `matrix[0][j]`.
After calculating $f(n-1, j)$ for all $j$, the global minimum is the smallest element in the last row. Optimization stores just the previous row in a 1D array.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<int> prev = matrix[0];
        
        for (int i = 1; i < n; ++i) {
            vector<int> curr(n, 0);
            for (int j = 0; j < n; ++j) {
                int up = prev[j];
                int leftDiag = (j > 0) ? prev[j-1] : 1e9;
                int rightDiag = (j < n - 1) ? prev[j+1] : 1e9;
                
                curr[j] = matrix[i][j] + min({up, leftDiag, rightDiag});
            }
            prev = curr;
        }
        
        int minSum = 1e9;
        for (int j = 0; j < n; ++j) {
            minSum = min(minSum, prev[j]);
        }
        return minSum;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> matrix = {{2, 1, 3}, {6, 5, 4}, {7, 8, 9}};
    cout << sol.minFallingPathSum(matrix) << "\n"; // Expected: 13
    return 0;
}
```
**Complexity:**
- **Time:** $O(n^2)$ for an $n \times n$ matrix computation.
- **Space:** $O(n)$ because we maintain the 1D rolling array.

**Practice:** https://leetcode.com/problems/minimum-falling-path-sum/

### Cherry Pickup II

::: heavy
When a problem features multiple actors moving concurrently in a shared state space, they must be bundled into a single unified DP state. Trying to run one actor first and the second actor later fails to capture optimal overlapping decisions.
:::

You have a grid `grid` representing a field of cherries. Robot #1 starts at top-left `(0, 0)` and Robot #2 starts at top-right `(0, cols - 1)`. Both robots move down one row at a time. Each can move down-left, directly down, or down-right. They collect cherries in their paths, but if they land on the same cell, the cherry is collected only once. Find the maximum cherries collected by both robots combined.

**Intuition:**
Since the robots move simultaneously downwards, they are always on the same row `i`. We track the column of Robot 1 (`j1`) and Robot 2 (`j2`).
- **State:** $f(i, j_1, j_2)$ represents the max cherries from row $i$ to the bottom given Robot 1 is at $j_1$ and Robot 2 is at $j_2$.
- **Transition:** There are 3 choices for Robot 1 and 3 choices for Robot 2, generating $3 \times 3 = 9$ transitions. We take the maximum of these 9 choices on the subsequent row $f(i+1, j_1', j_2')$.
- **Base case:** On the last row $n-1$, if $j_1 = j_2$, return $\text{grid}[n-1][j_1]$. Otherwise, return $\text{grid}[n-1][j_1] + \text{grid}[n-1][j_2]$.
To optimize space from a 3D table to a 2D table, observe that row $i$ only needs row $i+1$. We maintain a 2D array representing `dp[j1][j2]`.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        
        // dp[j1][j2] stores max cherries for current row
        vector<vector<int>> front(m, vector<int>(m, 0));
        
        // Base case: last row
        for (int j1 = 0; j1 < m; ++j1) {
            for (int j2 = 0; j2 < m; ++j2) {
                if (j1 == j2) front[j1][j2] = grid[n-1][j1];
                else front[j1][j2] = grid[n-1][j1] + grid[n-1][j2];
            }
        }
        
        // Iterate bottom-up from second-to-last row
        for (int i = n - 2; i >= 0; --i) {
            vector<vector<int>> curr(m, vector<int>(m, 0));
            for (int j1 = 0; j1 < m; ++j1) {
                for (int j2 = 0; j2 < m; ++j2) {
                    int maxCherries = -1e9;
                    
                    // 9 possible combinations of movements
                    for (int d1 = -1; d1 <= 1; ++d1) {
                        for (int d2 = -1; d2 <= 1; ++d2) {
                            int nj1 = j1 + d1;
                            int nj2 = j2 + d2;
                            int ans = 0;
                            
                            if (j1 == j2) ans = grid[i][j1];
                            else ans = grid[i][j1] + grid[i][j2];
                            
                            if (nj1 >= 0 && nj1 < m && nj2 >= 0 && nj2 < m) {
                                ans += front[nj1][nj2];
                            } else {
                                ans += -1e9;
                            }
                            
                            maxCherries = max(maxCherries, ans);
                        }
                    }
                    curr[j1][j2] = maxCherries;
                }
            }
            front = curr;
        }
        
        return front[0][m-1];
    }
};

int main() {
    Solution sol;
    vector<vector<int>> grid = {
        {3, 1, 1},
        {2, 5, 1},
        {1, 5, 5},
        {2, 1, 1}
    };
    cout << sol.cherryPickup(grid) << "\n"; // Expected: 24
    return 0;
}
```
**Complexity:**
- **Time:** $O(n \times m \times m \times 9) = O(n \cdot m^2)$, considering the 9 internal transitions per state pair on each row.
- **Space:** $O(m^2)$ to preserve the previous row state matrix.

**Practice:** https://leetcode.com/problems/cherry-pickup-ii/

## DP on Subsequences & Knapsack

### Subset Sum Equal to Target
Given an array of non-negative integers and a target sum `k`, determine if there is a subset of the given array whose elements sum to `k`.

**Intuition:**
We can try all possible subsets by making a take or not-take decision for each element. Our state requires knowing which element we are considering and how much target sum is left to form, so we define $f(\text{index}, \text{target})$.
The recurrence is:
- **Not Take:** We don't include the current element, so we check $f(\text{index} - 1, \text{target})$.
- **Take:** We include the current element (only if its value is $\le \text{target}$), checking $f(\text{index} - 1, \text{target} - \text{arr}[\text{index}])$.
The answer is the logical OR of these two possibilities.

We can memoize this recursion in a 2D table `dp[N][k + 1]`. To convert to bottom-up tabulation, we iterate from index $1$ to $N - 1$ and fill the table iteratively from our base cases (target 0 is always true). Finally, because the current row `curr` relies exclusively on the previous row `prev`, we can space-optimize this to use two 1D arrays, avoiding $O(n \times k)$ memory.

::: keypoint
For subsequence and knapsack problems, the DP state almost always requires an `index` parameter (to track the current element) and a secondary parameter (like `target`, `weight`, or `sum`) to represent the remaining constraint.
:::

```cpp
#include <iostream>
#include <vector>

using namespace std;

bool subsetSumToK(int n, int k, vector<int>& arr) {
    // Space optimized bottom-up DP
    vector<bool> prev(k + 1, false);
    
    // Base case: A target of 0 can always be achieved with an empty subset
    prev[0] = true;
    
    // Base case: For the first element, we can achieve target arr[0] if it's within bounds
    if (arr[0] <= k) {
        prev[arr[0]] = true;
    }
    
    for (int ind = 1; ind < n; ind++) {
        vector<bool> curr(k + 1, false);
        curr[0] = true; // Target 0 is always possible
        for (int target = 1; target <= k; target++) {
            bool notTake = prev[target];
            bool take = false;
            if (arr[ind] <= target) {
                take = prev[target - arr[ind]];
            }
            curr[target] = take | notTake;
        }
        prev = curr;
    }
    
    return prev[k];
}

int main() {
    vector<int> arr = {1, 2, 3, 4};
    int k = 4;
    cout << (subsetSumToK(4, k, arr) ? "True" : "False") << "\n";
    return 0;
}
```

**Complexity:** Time $O(n \times k)$, Space $O(k)$ for the single 1D array tracking the previous row.
**Practice:** https://www.geeksforgeeks.org/problems/subset-sum-problem-1611555638/1

### Partition Equal Subset Sum
Given an integer array, determine if it can be partitioned into two subsets such that the sum of elements in both subsets is equal.

**Intuition:**
If the total sum of the entire array is odd, it is mathematically impossible to divide it into two equal integer halves. If the total sum is even, the problem strictly reduces to checking whether there exists a single subset whose sum is exactly `total_sum / 2`. If one such subset exists, the remaining elements automatically sum to the other half. We can reuse the exact DP logic from Subset Sum Equal to Target.

```cpp
#include <iostream>
#include <vector>

using namespace std;

bool canPartition(vector<int>& nums) {
    int totalSum = 0;
    for (int num : nums) totalSum += num;
    
    if (totalSum % 2 != 0) return false;
    
    int target = totalSum / 2;
    int n = nums.size();
    
    vector<bool> prev(target + 1, false);
    prev[0] = true;
    
    if (nums[0] <= target) prev[nums[0]] = true;
    
    for (int ind = 1; ind < n; ind++) {
        vector<bool> curr(target + 1, false);
        curr[0] = true;
        for (int t = 1; t <= target; t++) {
            bool notTake = prev[t];
            bool take = false;
            if (nums[ind] <= t) take = prev[t - nums[ind]];
            curr[t] = take | notTake;
        }
        prev = curr;
    }
    return prev[target];
}

int main() {
    vector<int> nums = {1, 5, 11, 5};
    cout << (canPartition(nums) ? "True" : "False") << "\n";
    return 0;
}
```

**Complexity:** Time $O(n \times S/2)$, Space $O(S/2)$ where $S$ is the total sum of the array.
**Practice:** https://leetcode.com/problems/partition-equal-subset-sum/

### Partition a Set into Two Subsets with Minimum Absolute Difference
Given an array of $n$ integers, partition it into two subsets such that the absolute difference between their sums is minimized. Return this minimum absolute difference.

**Intuition:**
Let the sums of the two subsets be $S_1$ and $S_2$. We know $S_1 + S_2 = \text{total\_sum}$, which means $S_2 = \text{total\_sum} - S_1$. We want to minimize $|S_1 - S_2|$, which is equivalent to minimizing $|\text{total\_sum} - 2S_1|$. 
To find all valid values for $S_1$, we can run the Subset Sum DP tabulation for a target of `total_sum`. After completely filling out the DP table, the last row indicates every possible subset sum that can be formed using the array. We iterate $S_1$ from $0$ up to $\text{total\_sum} / 2$, check if the sum $S_1$ is possible, and track the minimum difference.

```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int minDifference(vector<int>& arr) {
    int n = arr.size();
    int totalSum = 0;
    for (int num : arr) totalSum += num;
    
    vector<bool> prev(totalSum + 1, false);
    prev[0] = true;
    
    if (arr[0] <= totalSum) prev[arr[0]] = true;
    
    for (int ind = 1; ind < n; ind++) {
        vector<bool> curr(totalSum + 1, false);
        curr[0] = true;
        for (int t = 1; t <= totalSum; t++) {
            bool notTake = prev[t];
            bool take = false;
            if (arr[ind] <= t) take = prev[t - arr[ind]];
            curr[t] = take | notTake;
        }
        prev = curr;
    }
    
    int mini = 1e9;
    for (int s1 = 0; s1 <= totalSum / 2; s1++) {
        if (prev[s1]) {
            int s2 = totalSum - s1;
            mini = min(mini, abs(s1 - s2));
        }
    }
    return mini;
}

int main() {
    vector<int> arr = {3, 9, 7, 3};
    cout << minDifference(arr) << "\n";
    return 0;
}
```

**Complexity:** Time $O(n \times S)$, Space $O(S)$ where $S$ is the total sum of the array elements.
**Practice:** https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/

### Count Subsets with Sum K
Given an array of integers and a sum `K`, find the number of subsets that add up to `K`.

**Intuition:**
Instead of a boolean state representing *if* a sum is possible, our state $f(\text{index}, \text{target})$ represents the *count* of ways to form the target sum.
The recurrence becomes addition: $f(\text{index}, \text{target}) = f(\text{index} - 1, \text{target}) + f(\text{index} - 1, \text{target} - \text{arr}[\text{index}])$.
A trap here is zero handling. If elements can be zero, we must process them because picking or not picking a zero changes the subset but not the sum (adding $2^k$ subsets if there are $k$ zeroes). The base cases at index 0 must account for this: if the array has a zero at index 0 and target is 0, there are two ways (take it or leave it). If we convert this to tabulated DP, space optimization to a 1D array is identical to previous patterns.

```cpp
#include <iostream>
#include <vector>

using namespace std;

int findWays(vector<int>& num, int tar) {
    int n = num.size();
    vector<int> prev(tar + 1, 0);
    
    // Careful base case to handle 0s
    if (num[0] == 0) prev[0] = 2; // Two ways: take 0 or not take 0
    else prev[0] = 1; // One way: not take
    
    if (num[0] != 0 && num[0] <= tar) prev[num[0]] = 1;
    
    for (int ind = 1; ind < n; ind++) {
        vector<int> curr(tar + 1, 0);
        for (int t = 0; t <= tar; t++) {
            int notTake = prev[t];
            int take = 0;
            if (num[ind] <= t) take = prev[t - num[ind]];
            curr[t] = notTake + take;
        }
        prev = curr;
    }
    return prev[tar];
}

int main() {
    vector<int> num = {1, 2, 2, 3};
    int tar = 3;
    cout << findWays(num, tar) << "\n"; // Expected: 3
    return 0;
}
```

**Complexity:** Time $O(n \times K)$, Space $O(K)$ using one 1D array.
**Practice:** https://www.geeksforgeeks.org/problems/perfect-sum-problem5633/1

### Count Partitions with a Given Difference
Given an array and a difference `D`, count the number of partitions into two subsets $S_1$ and $S_2$ such that $S_1 \ge S_2$ and $S_1 - S_2 = D$.

**Intuition:**
We have two linear equations:
$S_1 - S_2 = D$
$S_1 + S_2 = \text{total\_sum}$
Adding both equations yields $2S_1 = \text{total\_sum} + D$, reducing to $S_1 = (\text{total\_sum} + D) / 2$.
Thus, finding the number of partitions with difference `D` is exactly the same problem as counting the number of subsets with sum $(\text{total\_sum} + D) / 2$. If $\text{total\_sum} + D$ is odd or negative, it's impossible. We then run the subset count DP logic.

```cpp
#include <iostream>
#include <vector>

using namespace std;

int countPartitions(int n, int d, vector<int>& arr) {
    int totalSum = 0;
    for (int x : arr) totalSum += x;
    
    // Check constraints: sum must be non-negative and even
    if (totalSum - d < 0 || (totalSum + d) % 2 != 0) return 0;
    
    int tar = (totalSum + d) / 2;
    vector<int> prev(tar + 1, 0);
    
    if (arr[0] == 0) prev[0] = 2; 
    else prev[0] = 1;
    
    if (arr[0] != 0 && arr[0] <= tar) prev[arr[0]] = 1;
    
    for (int ind = 1; ind < n; ind++) {
        vector<int> curr(tar + 1, 0);
        for (int t = 0; t <= tar; t++) {
            int notTake = prev[t];
            int take = 0;
            if (arr[ind] <= t) take = prev[t - arr[ind]];
            curr[t] = notTake + take;
        }
        prev = curr;
    }
    return prev[tar];
}

int main() {
    vector<int> arr = {5, 2, 6, 4};
    int d = 3;
    cout << countPartitions(arr.size(), d, arr) << "\n";
    return 0;
}
```

**Complexity:** Time $O(n \times S)$, Space $O(S)$ where $S = (\text{total\_sum} + D) / 2$.
**Practice:** https://www.geeksforgeeks.org/problems/partitions-with-given-difference/1

### 0/1 Knapsack
Given $N$ items with specific weights and values, and a knapsack with maximum capacity $W$, find the maximum total value we can put in the knapsack. Each item can be picked at most once.

**Intuition:**
We define the state $f(\text{index}, \text{remaining\_weight})$ as the maximum value achievable from items $0$ to $\text{index}$ with a capacity of $\text{remaining\_weight}$.
Recurrence:
- **Not Take:** We skip the item and earn $0$ value, leaving $f(\text{index} - 1, \text{remaining\_weight})$.
- **Take:** If the item fits, we earn its value and consume its weight, giving $\text{value}[\text{index}] + f(\text{index} - 1, \text{remaining\_weight} - \text{weight}[\text{index}])$.
We take the maximum of these two paths. We map this to a 2D table, but because the current state depends exclusively on the previous row, we can space-optimize.

::: keypoint
When space-optimizing a DP where the current row relies on strictly smaller columns of the *previous* row (like 0/1 Knapsack), iterate the inner loop **backwards** (from $W$ down to $0$) to use a single 1D array. Traversing forward would overwrite values still needed for later computations in the same row.
:::

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int knapsack(vector<int>& weight, vector<int>& value, int n, int W) {
    // Single 1D array space optimization
    vector<int> prev(W + 1, 0);
    
    // Base case: using the 0-th item
    for (int w = weight[0]; w <= W; w++) {
        prev[w] = value[0];
    }
    
    for (int ind = 1; ind < n; ind++) {
        // Traverse backwards to safely use only 1 row
        for (int w = W; w >= 0; w--) {
            int notTake = 0 + prev[w];
            int take = -1e9;
            if (weight[ind] <= w) {
                take = value[ind] + prev[w - weight[ind]];
            }
            prev[w] = max(take, notTake);
        }
    }
    return prev[W];
}

int main() {
    vector<int> weight = {1, 2, 4, 5};
    vector<int> value = {5, 4, 8, 6};
    int W = 5;
    cout << knapsack(weight, value, 4, W) << "\n"; // Expected: 13
    return 0;
}
```

**Complexity:** Time $O(N \times W)$, Space $O(W)$ tracking only one row.
**Practice:** https://www.geeksforgeeks.org/problems/0-1-knapsack-problem0945/1

### Minimum Coins
Given an array of coin denominations and a target value $V$, find the minimum number of coins needed to make $V$. You have an infinite supply of each coin.

**Intuition:**
This introduces unbounded DP. Because we can pick the same coin multiple times, the state $f(\text{index}, \text{target})$ represents the minimum coins needed using denominations up to $\text{index}$.
The recurrence shifts slightly:
- **Not Take:** We discard the coin entirely: $f(\text{index} - 1, \text{target})$.
- **Take:** We pick the coin, add 1 to the count, but **we stay at the same index** so we could pick it again: $1 + f(\text{index}, \text{target} - \text{coins}[\text{index}])$.
Because we need $f(\text{index}, \text{target} - \text{coins}[\text{index}])$, our current computation depends on values from the *current* row. This allows space-optimizing with a single 1D array moving left-to-right.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int minCoins(vector<int>& coins, int V) {
    int n = coins.size();
    vector<int> dp(V + 1, 1e9);
    
    // Base case for ind = 0: only possible if V is divisible by the first coin
    for (int t = 0; t <= V; t++) {
        if (t % coins[0] == 0) dp[t] = t / coins[0];
    }
    
    for (int ind = 1; ind < n; ind++) {
        for (int t = 0; t <= V; t++) {
            int notTake = dp[t];
            int take = 1e9;
            if (coins[ind] <= t) {
                take = 1 + dp[t - coins[ind]];
            }
            dp[t] = min(take, notTake);
        }
    }
    
    int ans = dp[V];
    return ans >= 1e9 ? -1 : ans;
}

int main() {
    vector<int> coins = {1, 2, 5};
    int V = 11;
    cout << minCoins(coins, V) << "\n"; // Expected: 3 (5+5+1)
    return 0;
}
```

**Complexity:** Time $O(N \times V)$, Space $O(V)$ tracking a single 1D array.
**Practice:** https://leetcode.com/problems/coin-change/

### Target Sum
You are given an integer array `nums` and an integer `target`. You want to build an expression out of `nums` by adding one of the symbols `+` and `-` before each integer in `nums` and then concatenate all the integers. Find the number of different expressions that evaluate to `target`.

**Intuition:**
Assigning `+` or `-` to elements effectively partitions the array into a positive subset $S_1$ and a negative subset $S_2$. We know $S_1 - S_2 = \text{target}$. 
Like earlier partition problems, substituting $S_2 = \text{total\_sum} - S_1$ yields $S_1 = (\text{total\_sum} + \text{target}) / 2$. This reduces identically to counting subsets with sum equal to $(\text{total\_sum} + \text{target}) / 2$. 

```cpp
#include <iostream>
#include <vector>

using namespace std;

int findTargetSumWays(vector<int>& nums, int target) {
    int totalSum = 0;
    for (int num : nums) totalSum += num;
    
    if (totalSum - target < 0 || (totalSum + target) % 2 != 0) return 0;
    
    int s1 = (totalSum + target) / 2;
    int n = nums.size();
    
    vector<int> prev(s1 + 1, 0);
    
    if (nums[0] == 0) prev[0] = 2;
    else prev[0] = 1;
    
    if (nums[0] != 0 && nums[0] <= s1) prev[nums[0]] = 1;
    
    for (int ind = 1; ind < n; ind++) {
        vector<int> curr(s1 + 1, 0);
        for (int t = 0; t <= s1; t++) {
            int notTake = prev[t];
            int take = 0;
            if (nums[ind] <= t) take = prev[t - nums[ind]];
            curr[t] = take + notTake;
        }
        prev = curr;
    }
    return prev[s1];
}

int main() {
    vector<int> nums = {1, 1, 1, 1, 1};
    int target = 3;
    cout << findTargetSumWays(nums, target) << "\n"; // Expected: 5
    return 0;
}
```

**Complexity:** Time $O(n \times S)$, Space $O(S)$ where $S = (\text{total\_sum} + \text{target}) / 2$.
**Practice:** https://leetcode.com/problems/target-sum/

### Coin Change II
You are given an integer array `coins` representing coins of different denominations and an integer `amount`. Return the number of combinations that make up that amount. Assume an infinite supply of coins.

**Intuition:**
We combine the count logic from subset sums with the unbounded logic from Minimum Coins. The recurrence changes from taking the minimum to summing the combinations.
- **Not Take:** $f(\text{index} - 1, \text{amount})$
- **Take:** $f(\text{index}, \text{amount} - \text{coins}[\text{index}])$ (We stay at the current index to reuse the coin)
Because the "Take" transition looks at the current row's previously computed values, a 1D space optimization updates the array strictly left to right.

```cpp
#include <iostream>
#include <vector>

using namespace std;

int change(int amount, vector<int>& coins) {
    int n = coins.size();
    vector<int> dp(amount + 1, 0);
    
    // Base case: if amount is divisible by first coin, there is 1 combination
    for (int t = 0; t <= amount; t++) {
        if (t % coins[0] == 0) dp[t] = 1;
    }
    
    for (int ind = 1; ind < n; ind++) {
        for (int t = 0; t <= amount; t++) {
            int notTake = dp[t];
            int take = 0;
            if (coins[ind] <= t) take = dp[t - coins[ind]];
            dp[t] = take + notTake;
        }
    }
    return dp[amount];
}

int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 5;
    cout << change(amount, coins) << "\n"; // Expected: 4
    return 0;
}
```

**Complexity:** Time $O(N \times A)$, Space $O(A)$ where $A$ is the target amount.
**Practice:** https://leetcode.com/problems/coin-change-ii/

### Unbounded Knapsack
Given weights and values of $N$ items, put these items in a knapsack of capacity $W$ to maximize total value. We have an infinite supply of each item.

**Intuition:**
This mirrors 0/1 Knapsack, but unbounded. If we take an item, we stay at the same index so we can pick it again.
- **Not Take:** $f(\text{index} - 1, \text{weight})$
- **Take:** $\text{value}[\text{index}] + f(\text{index}, \text{weight} - \text{weight}[\text{index}])$
By taking the maximum of these choices, we tabulate. We can crush the 2D DP array down to a single 1D array. Since we need data from the current index computation, we traverse left-to-right (opposite of 0/1 Knapsack).

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int unboundedKnapsack(int n, int W, vector<int>& value, vector<int>& weight) {
    vector<int> dp(W + 1, 0);
    
    // Base case
    for (int w = 0; w <= W; w++) {
        dp[w] = (w / weight[0]) * value[0];
    }
    
    for (int ind = 1; ind < n; ind++) {
        // Left to right traversal for unbounded items
        for (int w = 0; w <= W; w++) {
            int notTake = 0 + dp[w]; // Refers to the previous row's value implicitly
            int take = -1e9;
            if (weight[ind] <= w) {
                take = value[ind] + dp[w - weight[ind]]; // Refers to current row's value
            }
            dp[w] = max(take, notTake);
        }
    }
    return dp[W];
}

int main() {
    vector<int> weight = {2, 4, 6};
    vector<int> value = {5, 11, 13};
    int W = 10;
    cout << unboundedKnapsack(3, W, value, weight) << "\n"; // Expected: 27
    return 0;
}
```

**Complexity:** Time $O(N \times W)$, Space $O(W)$.
**Practice:** https://www.geeksforgeeks.org/problems/knapsack-with-duplicate-items4201/1

### The 1D Array Dual-Identity — why traversal direction decides 0/1 vs. Unbounded

Both knapsack variants collapse to a single 1D array of size $W+1$, and the *only* difference between them is the direction of the inner loop. This is the most commonly memorised-without-understanding rule in dynamic programming, and it is worth deriving properly, because once you see it you can never again write the wrong direction.

::: definition
**The dual-identity of a 1D DP cell.** When you crush a 2D table `dp[index][w]` into one array `dp[w]`, each cell carries **two different meanings depending on when you look at it** during the current row's sweep:

- **Before** you overwrite `dp[w]` in this iteration, it still holds row $index-1$'s value — *"yesterday's"* value.
- **After** you overwrite it, it holds row $index$'s value — *"today's"* value.

The recurrence needs `dp[w - weight[index]]`. Whether that read lands on yesterday's or today's value is decided entirely by whether the sweep has already passed position `w - weight[index]`. That is what the loop direction controls, and it is the whole mechanism.
:::

::: keypoint
**The Golden Rule of 1D knapsack DP:**

| Variant | Items usable | Inner loop | Which value it reads | Why |
|---|---|---|---|---|
| **0/1 Knapsack** | once each | `for (w = W; w >= weight[i]; --w)` | *yesterday's* | Going right-to-left, `w - weight[i]` is to the **left** of `w` and has not been touched yet this row, so it still holds row $i-1$ — the item is not reused |
| **Unbounded** | infinitely | `for (w = weight[i]; w <= W; ++w)` | *today's* | Going left-to-right, `w - weight[i]` was **already updated** this row, so it may already include item $i$ — which is exactly the chaining that lets it be picked again |

Read it as one sentence: **"0/1 goes backward to preserve the past; Unbounded goes forward to chain the present."**
:::

The failure mode is symmetric and silent, which is what makes it worth internalising:

::: trap
Write a 0/1 knapsack with a **left-to-right** loop and it silently becomes Unbounded — each item gets picked as many times as it fits, and the answer comes out **too large**. Write Unbounded **right-to-left** and it silently becomes 0/1 — each item is used at most once, and the answer comes out **too small**.

Neither version crashes. Neither produces a warning. Both are perfectly valid programs that solve *the other problem*. On small hand-checked examples where each item happens to be worth taking only once, the two agree — so the bug survives your sample test and dies on the hidden ones.

Run both sweeps over the Unbounded Knapsack example above (`weight = {2,4,6}`, `value = {5,11,13}`, $W = 10$) and the difference is immediate:

```
forward  sweep -> 27      (unbounded: five copies of the weight-2 item)
backward sweep -> 24      (0/1: the weight-4 and weight-6 items, once each)
```

One loop direction, one character of difference, and a wrong answer with no diagnostic.
:::

Concretely, with a single coin of weight 3 and a 1D array over amounts, running **forward**:

```
dp[3] is updated using dp[0]        -> dp[3] now accounts for one coin
dp[6] is updated using dp[3]        -> dp[3] ALREADY has one coin, so dp[6] gets two
dp[9] is updated using dp[6]        -> three coins...
```

The updates cascade within the row, and that cascade *is* "infinite supply". Running **backward**, `dp[6]` is computed before `dp[3]` is touched, so it reads a `dp[3]` that predates this coin entirely, and no chaining can occur.

::: interview
A clean way to state this if asked: the 2D recurrence for 0/1 knapsack reads strictly from the **previous row** (`dp[i-1][...]`), so a 1D collapse must preserve the previous row at every point it still needs to read — hence backward. Unbounded knapsack's recurrence reads from the **current row** (`dp[i][w - wt]`), so the 1D collapse must expose already-updated values — hence forward. The direction is not a trick; it is a direct consequence of which row the recurrence names.
:::

### Rod Cutting
Given a rod of length $N$ and an array of prices for different lengths `prices[]`, find the maximum value obtainable by cutting up the rod and selling the pieces.

**Intuition:**
This is identically Unbounded Knapsack wrapped in a physical metaphor. The rod pieces are "items" with lengths (weights) $1$ to $N$, and their values are given by the `prices` array. The total knapsack capacity is the full rod length $N$. We optimize directly to a 1D DP array.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int cutRod(vector<int>& price, int n) {
    vector<int> dp(n + 1, 0);
    
    // Base case: using lengths of 1 (index 0 implies length 1)
    for (int length = 0; length <= n; length++) {
        dp[length] = length * price[0];
    }
    
    for (int ind = 1; ind < n; ind++) {
        for (int length = 0; length <= n; length++) {
            int notTake = dp[length];
            int take = -1e9;
            int rodLength = ind + 1; // 0-indexed implies length ind + 1
            if (rodLength <= length) {
                take = price[ind] + dp[length - rodLength];
            }
            dp[length] = max(take, notTake);
        }
    }
    return dp[n];
}

int main() {
    vector<int> price = {1, 5, 8, 9, 10, 17, 17, 20};
    int n = 8;
    cout << cutRod(price, n) << "\n"; // Expected: 22 (pieces of length 2 and 6)
    return 0;
}
```

**Complexity:** Time $O(n^2)$, Space $O(n)$.
**Practice:** https://www.geeksforgeeks.org/problems/rod-cutting0840/1

## DP on Strings

### Longest Common Subsequence
Given two strings `text1` and `text2`, return the length of their longest common subsequence. A subsequence is generated by deleting some characters without changing the relative order of the remaining ones.

::: keypoint
The foundation of DP on strings is expressing the state as comparing prefixes: let `f(i, j)` be the answer for the prefix `s1[0..i]` and `s2[0..j]`. The transitions depend entirely on whether the characters at the current indices match (`s1[i] == s2[j]`) or do not match.
:::

To build the intuition, we start from the ends of the strings. Let the strings have lengths $n$ and $m$. We evaluate the characters at indices $i$ and $j$.
- **Match:** If `text1[i] == text2[j]`, this character must be part of the longest common subsequence. The length increases by 1, and we recurse on the remaining prefixes: `1 + f(i-1, j-1)`.
- **Mismatch:** If `text1[i] != text2[j]`, they cannot both be in the common subsequence. We must try ignoring the character from `text1` (recursing on `f(i-1, j)`) and ignoring the character from `text2` (recursing on `f(i, j-1)`), taking the maximum of these two choices.

The base case occurs when either index goes out of bounds ($i < 0$ or $j < 0$), in which case the common subsequence length is 0.

By shifting our indices to be 1-based (where $i=0$ represents an empty prefix), we avoid negative indices. We can write a top-down memoized solution, which easily translates to a bottom-up 2D tabulation where `dp[i][j]` depends on `dp[i-1][j-1]`, `dp[i-1][j]`, and `dp[i][j-1]`. Since the current row $i$ only depends on the previous row $i-1$, we can space-optimize this to use two 1D arrays: `prev` and `curr`.

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.size();
        int m = text2.size();
        vector<int> prev(m + 1, 0), curr(m + 1, 0);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    curr[j] = 1 + prev[j - 1];
                } else {
                    curr[j] = max(prev[j], curr[j - 1]);
                }
            }
            prev = curr;
        }
        return prev[m];
    }
};

int main() {
    Solution sol;
    cout << sol.longestCommonSubsequence("abcde", "ace") << "\n";
    return 0;
}
```
**Complexity:** Time $O(n \times m)$ to fill the DP table. Space $O(\min(n, m))$ using space optimization, as we only need to store the previous row of the shorter string.
**Practice:** https://leetcode.com/problems/longest-common-subsequence/

### Print the Longest Common Subsequence
Given two strings `text1` and `text2`, print any one of their longest common subsequences.

Finding the length is not enough; we must reconstruct the actual string. This requires backtracking through the 2D DP table we built for the LCS length. We start at the bottom-right cell `dp[n][m]` and work our way back to `dp[0][0]`.

At any cell `(i, j)`:
1. If `text1[i-1] == text2[j-1]`, this character contributed to the LCS length (it came from `dp[i-1][j-1] + 1`). We include this character in our result and move diagonally to `(i-1, j-1)`.
2. If they do not match, the value `dp[i][j]` came from either `dp[i-1][j]` or `dp[i][j-1]`. We step in the direction of the strictly larger value. If they are equal, either direction works.

Since we trace backwards from the end of the strings, the characters are extracted in reverse order. We must reverse the constructed string before returning it.

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string printLCS(string text1, string text2) {
        int n = text1.size();
        int m = text2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Build the 2D DP table
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        // Backtrack to find the string
        string lcs = "";
        int i = n, j = m;
        while (i > 0 && j > 0) {
            if (text1[i - 1] == text2[j - 1]) {
                lcs += text1[i - 1];
                i--;
                j--;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                i--;
            } else {
                j--;
            }
        }

        reverse(lcs.begin(), lcs.end());
        return lcs;
    }
};

int main() {
    Solution sol;
    cout << sol.printLCS("abcde", "ace") << "\n";
    return 0;
}
```
**Complexity:** Time $O(n \times m)$ to build the table and $O(n + m)$ to backtrack. Space $O(n \times m)$ because we must store the entire 2D table for backtracking.
**Practice:** https://www.geeksforgeeks.org/printing-longest-common-subsequence/

### Longest Common Substring
Given two strings `text1` and `text2`, find the length of their longest common substring. Unlike a subsequence, a substring must be contiguous.

For substrings, we still compare prefixes, but the state definition shifts slightly: let `dp[i][j]` be the length of the longest common suffix of `text1[0..i-1]` and `text2[0..j-1]`.
If `text1[i-1] == text2[j-1]`, the common suffix grows, so `dp[i][j] = 1 + dp[i-1][j-1]`.
If they do not match, the contiguous sequence is broken, and `dp[i][j]` strictly drops to 0.

The longest common substring overall could end at any index, so we track the maximum value found anywhere in the table. Like LCS, we only need the previous row `i-1` to compute the current row `i`, so we can space-optimize it to a 1D array.

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestCommonSubstring(string text1, string text2) {
        int n = text1.size();
        int m = text2.size();
        vector<int> prev(m + 1, 0), curr(m + 1, 0);
        int maxLen = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    curr[j] = 1 + prev[j - 1];
                    maxLen = max(maxLen, curr[j]);
                } else {
                    curr[j] = 0;
                }
            }
            prev = curr;
        }
        return maxLen;
    }
};

int main() {
    Solution sol;
    cout << sol.longestCommonSubstring("abcdxyz", "xyzabcd") << "\n";
    return 0;
}
```
**Complexity:** Time $O(n \times m)$ to evaluate all pairs. Space $O(m)$ using a 1D optimization.
**Practice:** https://www.geeksforgeeks.org/longest-common-substring-dp-29/

### Longest Palindromic Subsequence
Given a string `s`, find the length of its longest palindromic subsequence.

A palindrome reads the same forwards and backwards. If we reverse the string `s` to create `t`, the longest palindromic subsequence of `s` is simply the longest common subsequence (LCS) of `s` and `t`. This conceptually converts a new problem directly into an instance of LCS.

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        string t = s;
        reverse(t.begin(), t.end());
        int n = s.size();
        
        vector<int> prev(n + 1, 0), curr(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1]) {
                    curr[j] = 1 + prev[j - 1];
                } else {
                    curr[j] = max(prev[j], curr[j - 1]);
                }
            }
            prev = curr;
        }
        return prev[n];
    }
};

int main() {
    Solution sol;
    cout << sol.longestPalindromeSubseq("bbbab") << "\n";
    return 0;
}
```
**Complexity:** Time $O(n^2)$ since both strings have length $n$, executing the standard LCS algorithm. Space $O(n)$ with space optimization.
**Practice:** https://leetcode.com/problems/longest-palindromic-subsequence/

### Minimum Insertions to Make a String Palindrome
Given a string `s`, find the minimum number of character insertions required to make it a palindrome.

To minimize insertions, we should leverage the existing palindromic structure of the string. The characters that already form a palindrome do not need pairs inserted for them. Therefore, we should find the Longest Palindromic Subsequence (LPS).

The characters in `s` that do not belong to the LPS must be paired with new inserted characters to form a full palindrome. The number of insertions is precisely the length of the string minus the length of its LPS.

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minInsertions(string s) {
        string t = s;
        reverse(t.begin(), t.end());
        int n = s.size();
        
        vector<int> prev(n + 1, 0), curr(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (s[i - 1] == t[j - 1]) {
                    curr[j] = 1 + prev[j - 1];
                } else {
                    curr[j] = max(prev[j], curr[j - 1]);
                }
            }
            prev = curr;
        }
        
        int lpsLength = prev[n];
        return n - lpsLength;
    }
};

int main() {
    Solution sol;
    cout << sol.minInsertions("mbadm") << "\n";
    return 0;
}
```
**Complexity:** Time $O(n^2)$ to compute the LPS via LCS. Space $O(n)$ utilizing a space-optimized 1D array.
**Practice:** https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/

### Minimum Insertions/Deletions to Convert String A to B
Given two strings `word1` and `word2`, find the minimum number of insertions and deletions required to convert `word1` to `word2`.

We want to perform the minimum operations, meaning we should retain as many characters as possible from the original string. The maximum characters we can leave untouched is exactly the Longest Common Subsequence (LCS) of both strings.

Every character in `word1` that is not part of the LCS must be deleted. Every character in `word2` that is not part of the LCS must be inserted.
- Deletions = `word1.length() - LCS`
- Insertions = `word2.length() - LCS`
- Total operations = `word1.length() + word2.length() - 2 * LCS`

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        vector<int> prev(m + 1, 0), curr(m + 1, 0);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    curr[j] = 1 + prev[j - 1];
                } else {
                    curr[j] = max(prev[j], curr[j - 1]);
                }
            }
            prev = curr;
        }
        
        int lcs = prev[m];
        return (n - lcs) + (m - lcs);
    }
};

int main() {
    Solution sol;
    cout << sol.minDistance("sea", "eat") << "\n";
    return 0;
}
```
**Complexity:** Time $O(n \times m)$ to compute the LCS. Space $O(\min(n, m))$ for space optimization.
**Practice:** https://leetcode.com/problems/delete-operation-for-two-strings/

### Shortest Common Supersequence
Given two strings `str1` and `str2`, return the shortest string that has both `str1` and `str2` as subsequences.

The shortest common supersequence must contain all characters of `str1` and `str2`, but we avoid writing duplicate characters for their Longest Common Subsequence (LCS). The length of this supersequence is exactly `len(str1) + len(str2) - LCS`.

To construct the string, we first build the standard LCS 2D DP table. We then backtrack from `(n, m)`:
- If characters match (`str1[i-1] == str2[j-1]`), include this character once, and move diagonally to `(i-1, j-1)`.
- If they do not match, we look at `dp[i-1][j]` and `dp[i][j-1]`. We move in the direction of the larger value, but we MUST include the character of the string whose index we are decrementing. This ensures the characters not in the LCS are retained.
- When one string is exhausted (an index reaches 0), we append all remaining characters of the other string.
- Finally, reverse the result.

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        string ans = "";
        int i = n, j = m;
        while (i > 0 && j > 0) {
            if (str1[i - 1] == str2[j - 1]) {
                ans += str1[i - 1];
                i--;
                j--;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                ans += str1[i - 1];
                i--;
            } else {
                ans += str2[j - 1];
                j--;
            }
        }

        while (i > 0) {
            ans += str1[i - 1];
            i--;
        }
        while (j > 0) {
            ans += str2[j - 1];
            j--;
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
};

int main() {
    Solution sol;
    cout << sol.shortestCommonSupersequence("abac", "cab") << "\n";
    return 0;
}
```
**Complexity:** Time $O(n \times m)$ to populate the DP table and trace back. Space $O(n \times m)$ since tracing requires the entire table structure.
**Practice:** https://leetcode.com/problems/shortest-common-supersequence/

### Distinct Subsequences
Given strings `s` and `t`, return the number of distinct subsequences of `s` which equal `t`.

Let `f(i, j)` count the ways to form the prefix `t[0..j]` using a subsequence of the prefix `s[0..i]`.
When comparing characters from the ends:
- If `s[i] == t[j]`, we have two options: we can either use `s[i]` to match `t[j]` (ways: `f(i-1, j-1)`), or we can choose not to use `s[i]` and look for another match in the rest of `s` (ways: `f(i-1, j)`). The total ways is their sum.
- If `s[i] != t[j]`, we cannot use `s[i]` to match, so we must ignore it: `f(i-1, j)`.

The base case is when `t` is exhausted (`j < 0`): we have found 1 valid subsequence (the empty string). If `s` is exhausted but `t` is not, there are 0 ways.

Using bottom-up tabulation, the table dimensions are `(n+1) \times (m+1)`. We can space-optimize this to a 1D array. Since computing `curr[j]` relies on `prev[j-1]` and `prev[j]`, if we compute the 1D array from right to left (from $m$ down to 1), we can overwrite the same array without losing the `j-1` value from the previous row.

```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int numDistinct(string s, string t) {
        int n = s.size();
        int m = t.size();
        
        // Use double or unsigned long long to avoid intermediate integer overflow
        vector<unsigned long long> dp(m + 1, 0);
        dp[0] = 1; // Empty string t is formed 1 way

        for (int i = 1; i <= n; i++) {
            for (int j = m; j >= 1; j--) {
                if (s[i - 1] == t[j - 1]) {
                    dp[j] = dp[j - 1] + dp[j];
                }
            }
        }
        return dp[m];
    }
};

int main() {
    Solution sol;
    cout << sol.numDistinct("rabbbit", "rabbit") << "\n";
    return 0;
}
```
**Complexity:** Time $O(n \times m)$ to fill the DP state. Space $O(m)$ utilizing the 1D single-array space optimization.
**Practice:** https://leetcode.com/problems/distinct-subsequences/

### Edit Distance

::: heavy
Edit Distance defines the core framework for complex string transformations. We are given three operations (insert, delete, replace), and the problem forces us to handle indices dynamically across them.
:::

Given two strings `word1` and `word2`, return the minimum number of operations to convert `word1` to `word2`. 

Let `f(i, j)` be the minimum operations to convert the prefix `word1[0..i]` to `word2[0..j]`.
We evaluate characters from the right:
- **Match:** If `word1[i] == word2[j]`, no operation is needed. The cost is exactly `f(i-1, j-1)`.
- **Mismatch:** If they differ, we can do one of three operations. Each operation conceptually adds 1 to the cost and modifies the problem state:
  1. **Insert:** We insert `word2[j]` at the end of `word1`. The indices shift such that `word2[j]` is matched, but `word1[i]` is still waiting to be matched: `1 + f(i, j-1)`.
  2. **Delete:** We delete `word1[i]`. We move to `word1[i-1]` but keep trying to match `word2[j]`: `1 + f(i-1, j)`.
  3. **Replace:** We replace `word1[i]` with `word2[j]`. Both are now matched: `1 + f(i-1, j-1)`.
We take the minimum of these three choices.

Base cases:
If `word1` is exhausted ($i < 0$), we must insert the remaining $j+1$ characters of `word2`.
If `word2` is exhausted ($j < 0$), we must delete the remaining $i+1$ characters of `word1`.

In tabulation, we shift to 1-based indexing. We can space optimize this to two 1D arrays since we only ever read from the current and previous rows.

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        
        vector<int> prev(m + 1, 0), curr(m + 1, 0);
        
        // Base case: word1 exhausted (requires j insertions)
        for (int j = 0; j <= m; j++) {
            prev[j] = j;
        }

        for (int i = 1; i <= n; i++) {
            // Base case: word2 exhausted (requires i deletions)
            curr[0] = i; 
            for (int j = 1; j <= m; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    curr[j] = prev[j - 1];
                } else {
                    curr[j] = 1 + min({curr[j - 1], prev[j], prev[j - 1]});
                }
            }
            prev = curr;
        }
        
        return prev[m];
    }
};

int main() {
    Solution sol;
    cout << sol.minDistance("horse", "ros") << "\n";
    return 0;
}
```
**Complexity:** Time $O(n \times m)$ to process states. Space $O(m)$ via two 1D arrays optimization.
**Practice:** https://leetcode.com/problems/edit-distance/

### Wildcard Matching

::: heavy
Pattern matching with wildcard asterisks introduces a branching transition state: an asterisk can match zero characters or it can "consume" multiple characters, requiring careful state delegation to handle unbounded matches.
:::

Given a string `s` and a pattern `p` (where `?` matches any single character and `*` matches any sequence of characters including empty), determine if `s` matches `p`.

Let `f(i, j)` return whether `s[0..i]` matches `p[0..j]`.
When comparing characters:
- If `s[i] == p[j]` or `p[j] == '?'`, they match. We move both pointers left: `f(i-1, j-1)`.
- If `p[j] == '*'`, it can either:
  1. Match zero characters in `s` (we ignore the `*` and move `j` left): `f(i, j-1)`.
  2. Match one or more characters in `s` (we consume `s[i]` and keep the `*` active to potentially match more): `f(i-1, j)`.
  We take the logical OR of these two outcomes.
- If they do not match and `p[j]` is a regular character, return `false`.

Base cases:
- Both exhausted ($i < 0$ and $j < 0$): `true`.
- Pattern exhausted, string remains ($j < 0$, $i \ge 0$): `false`.
- String exhausted, pattern remains ($i < 0$, $j \ge 0$): `true` only if every remaining character in the pattern is `*`.

Using bottom-up tabulation with 1-based indexing, we can optimize space to use two 1D arrays.

```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();
        
        vector<bool> prev(m + 1, false), curr(m + 1, false);
        
        // Base case: both exhausted
        prev[0] = true; 
        
        // Base case: string exhausted, pattern remains
        for (int j = 1; j <= m; j++) {
            if (p[j - 1] == '*') {
                prev[j] = prev[j - 1];
            } else {
                prev[j] = false;
            }
        }

        for (int i = 1; i <= n; i++) {
            curr[0] = false; // Pattern exhausted, string remains
            for (int j = 1; j <= m; j++) {
                if (s[i - 1] == p[j - 1] || p[j - 1] == '?') {
                    curr[j] = prev[j - 1];
                } else if (p[j - 1] == '*') {
                    curr[j] = curr[j - 1] || prev[j];
                } else {
                    curr[j] = false;
                }
            }
            prev = curr;
        }
        
        return prev[m];
    }
};

int main() {
    Solution sol;
    cout << boolalpha << sol.isMatch("cb", "?a") << "\n"; // Output: false
    cout << boolalpha << sol.isMatch("adceb", "*a*b") << "\n"; // Output: true
    return 0;
}
```
**Complexity:** Time $O(n \times m)$ examining all state transitions. Space $O(m)$ using a space optimization of two 1D arrays.
**Practice:** https://leetcode.com/problems/wildcard-matching/

## DP on Stocks & Longest Increasing Subsequence

### 1. Best Time to Buy and Sell Stock (single transaction)
You are given an array `prices` where `prices[i]` is the price of a given stock on the $i$-th day. You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock. Return the maximum profit you can achieve.

**Intuition / approach:**
A brute force approach would check all possible pairs of days $(i, j)$ with $i < j$, which takes $O(n^{2})$ time. To improve this, we can make a single pass through the array. For any given day $i$ where we might sell the stock, the best day to have bought it would be the day with the minimum price seen so far (from day $0$ to day $i-1$). Thus, we can maintain the minimum price seen so far and track the maximum profit we can achieve by selling on the current day. This is a form of dynamic programming with space optimization inherently built-in.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        int minPrice = prices[0];
        int maxProfit = 0;
        
        for (int i = 1; i < prices.size(); i++) {
            int profit = prices[i] - minPrice;
            maxProfit = max(maxProfit, profit);
            minPrice = min(minPrice, prices[i]);
        }
        
        return maxProfit;
    }
};

int main() {
    Solution sol;
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << "Max Profit: " << sol.maxProfit(prices) << "\n";
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(n)$, where $n$ is the number of days, since we make a single pass.
- **Space Complexity:** $O(1)$, since we only use a few variables to track the minimum price and maximum profit.

**Practice:** https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

### 2. Buy and Sell Stock II (unlimited)
You are given an integer array `prices` where `prices[i]` is the price of a given stock on the $i$-th day. On each day, you may decide to buy and/or sell the stock. You can only hold at most one share of the stock at any time. However, you can buy it then immediately sell it on the same day. Find and return the maximum profit you can achieve.

**Intuition / approach:**
We can either be holding a stock or not holding a stock on any given day. This gives us a state: $f(\text{index}, \text{buy})$, where $\text{buy}$ is a boolean indicating if we are allowed to buy (1) or if we must sell (0). 
The recurrence relation is:
- If we can buy: `profit = max(-prices[i] + f(i+1, 0), 0 + f(i+1, 1))`
- If we can sell: `profit = max(prices[i] + f(i+1, 1), 0 + f(i+1, 0))`
We can memoize this, then convert to a bottom-up table, and finally optimize to $O(1)$ space since day $i$ only depends on day $i+1$. Alternatively, a greedy approach of simply adding all positive price differences between consecutive days also works, but the DP template is crucial for harder variations.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        // Space optimized DP
        int aheadNotBuy = 0, aheadBuy = 0;
        int currNotBuy = 0, currBuy = 0;
        
        for (int i = n - 1; i >= 0; i--) {
            currBuy = max(-prices[i] + aheadNotBuy, 0 + aheadBuy);
            currNotBuy = max(prices[i] + aheadBuy, 0 + aheadNotBuy);
            
            aheadBuy = currBuy;
            aheadNotBuy = currNotBuy;
        }
        
        return aheadBuy;
    }
};

int main() {
    Solution sol;
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << "Max Profit: " << sol.maxProfit(prices) << "\n";
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(n)$, as we iterate through the array once.
- **Space Complexity:** $O(1)$, because we only need variables for the current and ahead states.

**Practice:** https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/

### 3. Buy and Sell Stock III (at most two)
You are given an array `prices` where `prices[i]` is the price of a given stock on the $i$-th day. Find the maximum profit you can achieve. You may complete at most two transactions. Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

**Intuition / approach:**
Now we have an additional constraint: at most two transactions. We add this to our state. The state becomes $f(\text{index}, \text{buy}, \text{cap})$, where $\text{cap}$ is the number of remaining transactions we can complete (0, 1, or 2). A transaction is counted as completed when we sell.
The recurrence is:
- If we can buy: `max(-prices[i] + f(i+1, 0, cap), 0 + f(i+1, 1, cap))`
- If we can sell: `max(prices[i] + f(i+1, 1, cap-1), 0 + f(i+1, 0, cap))`
Base cases: If $\text{cap} == 0$ or $\text{index} == n$, the profit is 0. We can build a 3D DP table and then space optimize it to a 2D array since day $i$ only depends on day $i+1$.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        // ahead[buy][cap]
        vector<vector<int>> ahead(2, vector<int>(3, 0));
        vector<vector<int>> curr(2, vector<int>(3, 0));
        
        for (int i = n - 1; i >= 0; i--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int cap = 1; cap <= 2; cap++) {
                    if (buy == 1) {
                        curr[buy][cap] = max(-prices[i] + ahead[0][cap], 0 + ahead[1][cap]);
                    } else {
                        curr[buy][cap] = max(prices[i] + ahead[1][cap - 1], 0 + ahead[0][cap]);
                    }
                }
            }
            ahead = curr;
        }
        
        return ahead[1][2];
    }
};

int main() {
    Solution sol;
    vector<int> prices = {3, 3, 5, 0, 0, 3, 1, 4};
    cout << "Max Profit: " << sol.maxProfit(prices) << "\n";
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(n \times 2 \times 3) = O(n)$, iterating through the states.
- **Space Complexity:** $O(2 \times 3) = O(1)$, as we only keep two tables of size $2 \times 3$.

**Practice:** https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/

### 4. Buy and Sell Stock IV (at most k)

::: keypoint
When a parameter like `k` is introduced, it just replaces the hardcoded `2` in the previous problem's DP state. The 3D DP $f(\text{index}, \text{buy}, \text{cap})$ naturally generalizes to handle any $k$.
:::

You are given an integer array `prices` and an integer `k`. Find the maximum profit you can achieve. You may complete at most `k` transactions.

**Intuition / approach:**
The logic is identical to Buy and Sell Stock III, but our capacity is `k` instead of 2. Our state is $f(\text{index}, \text{buy}, \text{cap})$. The recurrence remains the same. If $k$ is extremely large (e.g., $k \ge n/2$), we could theoretically make as many transactions as we want, reducing the problem to Buy and Sell Stock II, though standard $O(n \cdot k)$ DP typically passes anyway unless $k$ and $n$ are both large.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;
        
        // ahead[buy][cap]
        vector<vector<int>> ahead(2, vector<int>(k + 1, 0));
        vector<vector<int>> curr(2, vector<int>(k + 1, 0));
        
        for (int i = n - 1; i >= 0; i--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int cap = 1; cap <= k; cap++) {
                    if (buy == 1) {
                        curr[buy][cap] = max(-prices[i] + ahead[0][cap], 0 + ahead[1][cap]);
                    } else {
                        curr[buy][cap] = max(prices[i] + ahead[1][cap - 1], 0 + ahead[0][cap]);
                    }
                }
            }
            ahead = curr;
        }
        
        return ahead[1][k];
    }
};

int main() {
    Solution sol;
    vector<int> prices = {3, 2, 6, 5, 0, 3};
    int k = 2;
    cout << "Max Profit: " << sol.maxProfit(k, prices) << "\n";
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(n \cdot k)$, where $n$ is the number of days and $k$ is the max transactions.
- **Space Complexity:** $O(k)$, tracking the previous and current day arrays for states.

**Practice:** https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/

### 5. Buy and Sell With Cooldown
You are given an array `prices` where `prices[i]` is the price of a given stock on the $i$-th day. Find the maximum profit you can achieve with unlimited transactions, with the restriction that after you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).

**Intuition / approach:**
We drop the capacity parameter `cap` because transactions are unlimited, similar to Buy and Sell Stock II. The state is just $f(\text{index}, \text{buy})$. The twist is the recurrence: when we sell a stock on day $i$, we cannot buy on day $i+1$. We must transition to day $i+2$ in the "buy" state.
- If we buy: `max(-prices[i] + f(i+1, 0), 0 + f(i+1, 1))`
- If we sell: `max(prices[i] + f(i+2, 1), 0 + f(i+1, 0))`
To space optimize, since day $i$ depends on day $i+1$ and day $i+2$, we only need to keep track of the DP values from the last two days.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        
        int ahead2Buy = 0, ahead2NotBuy = 0; // f(i+2)
        int aheadBuy = 0, aheadNotBuy = 0;   // f(i+1)
        int currBuy = 0, currNotBuy = 0;     // f(i)
        
        for (int i = n - 1; i >= 0; i--) {
            currBuy = max(-prices[i] + aheadNotBuy, 0 + aheadBuy);
            currNotBuy = max(prices[i] + ahead2Buy, 0 + aheadNotBuy);
            
            ahead2Buy = aheadBuy;
            ahead2NotBuy = aheadNotBuy;
            
            aheadBuy = currBuy;
            aheadNotBuy = currNotBuy;
        }
        
        return aheadBuy;
    }
};

int main() {
    Solution sol;
    vector<int> prices = {1, 2, 3, 0, 2};
    cout << "Max Profit: " << sol.maxProfit(prices) << "\n";
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(n)$, since we iterate once through the prices array.
- **Space Complexity:** $O(1)$, using only a few variables.

**Practice:** https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/

### 6. Buy and Sell With Transaction Fee
You are given an array `prices` where `prices[i]` is the price of a given stock on the $i$-th day, and an integer `fee` representing a transaction fee. Find the maximum profit you can achieve with unlimited transactions, but you must pay the transaction fee for each transaction.

**Intuition / approach:**
The state remains $f(\text{index}, \text{buy})$ like in problem II. A transaction fee is incurred whenever a transaction completes. We can subtract the `fee` when we sell (or when we buy). The recurrence if we deduct on sell is:
- If we can buy: `max(-prices[i] + f(i+1, 0), 0 + f(i+1, 1))`
- If we can sell: `max(prices[i] - fee + f(i+1, 1), 0 + f(i+1, 0))`
This simplifies down to exactly problem II but with `- fee` attached to the selling branch.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        int aheadNotBuy = 0, aheadBuy = 0;
        int currNotBuy = 0, currBuy = 0;
        
        for (int i = n - 1; i >= 0; i--) {
            currBuy = max(-prices[i] + aheadNotBuy, 0 + aheadBuy);
            currNotBuy = max(prices[i] - fee + aheadBuy, 0 + aheadNotBuy);
            
            aheadBuy = currBuy;
            aheadNotBuy = currNotBuy;
        }
        
        return aheadBuy;
    }
};

int main() {
    Solution sol;
    vector<int> prices = {1, 3, 2, 8, 4, 9};
    int fee = 2;
    cout << "Max Profit: " << sol.maxProfit(prices, fee) << "\n";
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(n)$, for iterating through the array.
- **Space Complexity:** $O(1)$, for only maintaining states of the adjacent day.

**Practice:** https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/

### 7. Longest Increasing Subsequence (DP)

::: keypoint
The LIS pattern requires iterating over all previous elements to build upon existing subsequences. The state $f(\text{index}, \text{prev\_index})$ dictates trying all valid extensions.
:::

Given an integer array `nums`, return the length of the longest strictly increasing subsequence.

**Intuition / approach:**
The standard take/not-take pattern asks: do we include the current element? It depends on the element we picked *last*. Thus, the state is $f(\text{index}, \text{prev\_index})$. 
- We can skip `nums[index]`: $0 + f(\text{index} + 1, \text{prev\_index})$
- We can take `nums[index]` only if $\text{prev\_index} == -1$ or `nums[index] > nums[prev_index]`: $1 + f(\text{index} + 1, \text{index})$
We shift $\text{prev\_index}$ by $+1$ in the memoization table to handle the $-1$ state, giving us a $O(n^{2})$ space and time DP. An alternative 1D DP tabulation maintains an array `dp` where `dp[i]` is the length of the LIS ending precisely at index $i$.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        // dp[i] stores the length of LIS ending at index i
        vector<int> dp(n, 1);
        int maxi = 1;
        
        for (int i = 0; i < n; i++) {
            for (int prev = 0; prev < i; prev++) {
                if (nums[prev] < nums[i]) {
                    dp[i] = max(dp[i], 1 + dp[prev]);
                }
            }
            maxi = max(maxi, dp[i]);
        }
        
        return maxi;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "LIS Length: " << sol.lengthOfLIS(nums) << "\n";
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(n^{2})$, because for each of the $n$ elements, we potentially look back at all previous elements.
- **Space Complexity:** $O(n)$, to store the `dp` array.

**Practice:** https://leetcode.com/problems/longest-increasing-subsequence/

### 8. Print the Longest Increasing Subsequence
Given an integer array `nums`, find and print the actual elements of the longest strictly increasing subsequence.

**Intuition / approach:**
To recover the actual sequence, we use the 1D DP approach from the previous problem but add a `hash` (or `parent`) array. Every time we update `dp[i] = 1 + dp[prev]`, we also set `hash[i] = prev` to remember that the LIS ending at $i$ was extended from `prev`. After finding the maximum `dp` value, we start from the index of that maximum and trace back through the `hash` array, collecting the elements, and finally reversing them.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> printLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1);
        vector<int> hash(n);
        
        int maxi = 1;
        int lastIndex = 0;
        
        for (int i = 0; i < n; i++) {
            hash[i] = i; // initially, it points to itself
            for (int prev = 0; prev < i; prev++) {
                if (nums[prev] < nums[i] && 1 + dp[prev] > dp[i]) {
                    dp[i] = 1 + dp[prev];
                    hash[i] = prev;
                }
            }
            if (dp[i] > maxi) {
                maxi = dp[i];
                lastIndex = i;
            }
        }
        
        vector<int> lis;
        lis.push_back(nums[lastIndex]);
        while (hash[lastIndex] != lastIndex) {
            lastIndex = hash[lastIndex];
            lis.push_back(nums[lastIndex]);
        }
        
        reverse(lis.begin(), lis.end());
        return lis;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    vector<int> lis = sol.printLIS(nums);
    cout << "LIS: ";
    for (int x : lis) cout << x << " ";
    cout << "\n";
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(n^{2})$, to populate the `dp` and `hash` arrays.
- **Space Complexity:** $O(n)$, for the `dp`, `hash`, and output arrays.

**Practice:** https://leetcode.com/problems/longest-increasing-subsequence/

### 9. Longest Increasing Subsequence using Binary Search ($O(n\log n)$)

::: keypoint
Instead of $O(n^{2})$ DP, maintaining an active list of the smallest ending elements for sequences of various lengths yields an $O(n \log n)$ solution using binary search (`lower_bound`).
:::

Given an integer array `nums`, return the length of the longest strictly increasing subsequence in optimal $O(n \log n)$ time.

**Intuition / approach:**
We can maintain a `temp` array that stores the smallest tail element of all increasing subsequences of length `k`. When we process `nums[i]`, if it is greater than the last element in `temp`, it extends the longest subsequence found so far, so we append it. Otherwise, we find the first element in `temp` that is $\ge \text{nums}[i]$ using binary search and replace it. This keeps the potential elements for extending sequences as small as possible. The length of `temp` at the end is the length of the LIS (though `temp` itself is not necessarily the valid LIS).

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> temp;
        temp.push_back(nums[0]);
        
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > temp.back()) {
                temp.push_back(nums[i]);
            } else {
                auto it = lower_bound(temp.begin(), temp.end(), nums[i]);
                *it = nums[i];
            }
        }
        
        return temp.size();
    }
};

int main() {
    Solution sol;
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "LIS Length: " << sol.lengthOfLIS(nums) << "\n";
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(n \log n)$, as we perform a binary search (`lower_bound`) for each of the $n$ elements.
- **Space Complexity:** $O(n)$, to store the `temp` array.

**Practice:** https://leetcode.com/problems/longest-increasing-subsequence/

### 10. Largest Divisible Subset
Given a set of distinct positive integers `nums`, return the largest subset `answer` such that every pair `(answer[i], answer[j])` of elements in this subset satisfies: `answer[i] % answer[j] == 0` or `answer[j] % answer[i] == 0`.

**Intuition / approach:**
If we sort the array, the divisibility condition becomes simpler: we only need to check if a new element `nums[i]` is divisible by the largest element in our current subset `nums[j]`. If $nums[i] \pmod{nums[j]} == 0$, and $nums[j]$ is a multiple of everything before it, then by transitivity, $nums[i]$ is also a multiple of everything before it.
This transforms the problem into a variation of Longest Increasing Subsequence. We just change the condition `nums[j] < nums[i]` to `nums[i] % nums[j] == 0`. We also need to print the sequence, so we use the `hash` trace-back technique.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return {};
        
        sort(nums.begin(), nums.end());
        vector<int> dp(n, 1), hash(n);
        int maxi = 1, lastIndex = 0;
        
        for (int i = 0; i < n; i++) {
            hash[i] = i;
            for (int prev = 0; prev < i; prev++) {
                if (nums[i] % nums[prev] == 0 && 1 + dp[prev] > dp[i]) {
                    dp[i] = 1 + dp[prev];
                    hash[i] = prev;
                }
            }
            if (dp[i] > maxi) {
                maxi = dp[i];
                lastIndex = i;
            }
        }
        
        vector<int> res;
        res.push_back(nums[lastIndex]);
        while (hash[lastIndex] != lastIndex) {
            lastIndex = hash[lastIndex];
            res.push_back(nums[lastIndex]);
        }
        
        reverse(res.begin(), res.end());
        return res;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 2, 4, 8};
    vector<int> subset = sol.largestDivisibleSubset(nums);
    cout << "Subset: ";
    for (int x : subset) cout << x << " ";
    cout << "\n";
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(n^{2})$, dominated by the nested DP loops after an $O(n \log n)$ sort.
- **Space Complexity:** $O(n)$, for the `dp` and `hash` arrays.

**Practice:** https://leetcode.com/problems/largest-divisible-subset/

### 11. Longest String Chain
Given an array of words, a word chain is a sequence of words `[word_1, word_2, ..., word_k]` such that `word_1` is a predecessor of `word_2`, etc. Word A is a predecessor of word B if inserting exactly one letter anywhere in word A makes it equal to word B. Return the length of the longest possible word chain.

**Intuition / approach:**
This is another LIS variant. If we sort the array by string length, we can build chains progressively. Instead of comparing numeric values, we compare strings using a helper function `isPredecessor(s1, s2)` which checks if `s1` can be formed by deleting exactly one character from `s2`. The DP logic is identical to LIS: `dp[i] = max(dp[i], 1 + dp[prev])` if valid.

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
    bool isPredecessor(const string& s1, const string& s2) {
        if (s1.size() + 1 != s2.size()) return false;
        int i = 0, j = 0;
        while (j < s2.size()) {
            if (i < s1.size() && s1[i] == s2[j]) {
                i++; j++;
            } else {
                j++;
            }
        }
        return i == s1.size();
    }
    
    static bool comp(const string& val1, const string& val2) {
        return val1.size() < val2.size();
    }

public:
    int longestStrChain(vector<string>& words) {
        sort(words.begin(), words.end(), comp);
        int n = words.size();
        vector<int> dp(n, 1);
        int maxi = 1;
        
        for (int i = 0; i < n; i++) {
            for (int prev = 0; prev < i; prev++) {
                if (isPredecessor(words[prev], words[i]) && 1 + dp[prev] > dp[i]) {
                    dp[i] = 1 + dp[prev];
                }
            }
            maxi = max(maxi, dp[i]);
        }
        
        return maxi;
    }
};

int main() {
    Solution sol;
    vector<string> words = {"a", "b", "ba", "bca", "bda", "bdca"};
    cout << "Longest Chain: " << sol.longestStrChain(words) << "\n";
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(n^{2} \cdot \ell + n \log n)$, where $n$ is the number of words and $\ell$ is the maximum length of a word. Sorting takes $O(n \log n \cdot \ell)$, and the nested loops call the $O(\ell)$ predecessor check.
- **Space Complexity:** $O(n)$, for the `dp` array.

**Practice:** https://leetcode.com/problems/longest-string-chain/

### 12. Longest Bitonic Subsequence
Given an array of positive integers, return the length of the longest bitonic subsequence. A subsequence is bitonic if it first strictly increases, then strictly decreases. (It can also be purely increasing or purely decreasing).

**Intuition / approach:**
A bitonic sequence centered at index $i$ is made up of the Longest Increasing Subsequence ending at $i$ and the Longest Decreasing Subsequence starting at $i$. We can compute the standard LIS from left to right into an array `dp1`. Then we compute the LIS from right to left (which is effectively the longest decreasing subsequence) into an array `dp2`. The length of the longest bitonic subsequence peaking at $i$ is `dp1[i] + dp2[i] - 1` (subtract 1 because `nums[i]` is counted twice). The answer is the maximum over all valid $i$. Some strict definitions require it to both increase and decrease (meaning length $\ge 3$ with a clear peak), but Leetcode's variant allows just increasing or decreasing, while GeeksForGeeks enforces finding a proper peak or similar rules. We will implement the general standard approach.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int LongestBitonicSequence(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        
        vector<int> dp1(n, 1);
        for (int i = 0; i < n; i++) {
            for (int prev = 0; prev < i; prev++) {
                if (nums[prev] < nums[i] && 1 + dp1[prev] > dp1[i]) {
                    dp1[i] = 1 + dp1[prev];
                }
            }
        }
        
        vector<int> dp2(n, 1);
        for (int i = n - 1; i >= 0; i--) {
            for (int prev = n - 1; prev > i; prev--) {
                if (nums[prev] < nums[i] && 1 + dp2[prev] > dp2[i]) {
                    dp2[i] = 1 + dp2[prev];
                }
            }
        }
        
        int maxi = 0;
        for (int i = 0; i < n; i++) {
            // Under strict bitonic rules, some platforms demand dp1[i] > 1 and dp2[i] > 1.
            maxi = max(maxi, dp1[i] + dp2[i] - 1);
        }
        
        return maxi;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 11, 2, 10, 4, 5, 2, 1};
    cout << "Longest Bitonic Subsequence: " << sol.LongestBitonicSequence(nums) << "\n";
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(n^{2})$, calculating `dp1` and `dp2` each takes $O(n^{2})$.
- **Space Complexity:** $O(n)$, storing the two DP arrays.

**Practice:** https://www.geeksforgeeks.org/problems/longest-bitonic-subsequence0824/1

### 13. Number of Longest Increasing Subsequences
Given an integer array `nums`, return the number of longest increasing subsequences. Notice that the sequence has to be strictly increasing.

**Intuition / approach:**
We need to track two things at each index $i$: `dp[i]` (the length of the LIS ending at $i$) and `cnt[i]` (the number of ways to form an LIS of length `dp[i]` ending at $i$). 
When inspecting a previous element `nums[prev] < nums[i]`:
- If `1 + dp[prev] > dp[i]`, we found a strictly longer sequence. We update `dp[i] = 1 + dp[prev]` and reset `cnt[i] = cnt[prev]`.
- If `1 + dp[prev] == dp[i]`, we found *another* way to form an LIS of the same max length. We add the counts: `cnt[i] += cnt[prev]`.
Finally, we sum `cnt[i]` for all $i$ where `dp[i]` equals the maximum LIS length overall.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        
        vector<int> dp(n, 1);
        vector<int> cnt(n, 1);
        int maxi = 1;
        
        for (int i = 0; i < n; i++) {
            for (int prev = 0; prev < i; prev++) {
                if (nums[prev] < nums[i]) {
                    if (1 + dp[prev] > dp[i]) {
                        dp[i] = 1 + dp[prev];
                        cnt[i] = cnt[prev];
                    } else if (1 + dp[prev] == dp[i]) {
                        cnt[i] += cnt[prev];
                    }
                }
            }
            maxi = max(maxi, dp[i]);
        }
        
        int totalWays = 0;
        for (int i = 0; i < n; i++) {
            if (dp[i] == maxi) {
                totalWays += cnt[i];
            }
        }
        
        return totalWays;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 3, 5, 4, 7};
    cout << "Number of LIS: " << sol.findNumberOfLIS(nums) << "\n";
    return 0;
}
```

**Complexity:**
- **Time Complexity:** $O(n^{2})$, nested loops to process all elements.
- **Space Complexity:** $O(n)$, for the `dp` and `cnt` arrays.

**Practice:** https://leetcode.com/problems/number-of-longest-increasing-subsequence/

## Partition DP (MCM) & DP on Squares

::: keypoint
The **Partition DP / Matrix Chain Multiplication (MCM)** pattern is used when the problem requires dividing an array or string into segments or evaluating an expression in different orders. The core idea is to express the state as a range $[i, j]$ and try every possible partition point $k$ between $i$ and $j$, recursively solve the two halves, and combine their results to find the optimal solution for the range.
:::

### Matrix Chain Multiplication (memoized)

Given an array `arr` where the dimensions of the $i$-th matrix are `arr[i-1]` $\times$ `arr[i]`, find the minimum number of scalar multiplications needed to multiply the chain of matrices.

::: heavy
The number of multiplications for two matrices of dimensions $A \times B$ and $B \times C$ is $A \times B \times C$. The cost of multiplying a chain of matrices depends entirely on the order in which we parenthesize them. We cannot use a simple 1D state because we need to know the cost of multiplying a *subchain* of matrices. Thus, we need a 2D state $f(i, j)$ representing the minimum multiplications to multiply matrices from index $i$ to $j$.
:::

**Intuition / Approach**:
- We express the state as $f(i, j)$, the minimum cost to multiply the matrices from $i$ to $j$.
- If $i = j$, there is only one matrix, so zero multiplications are needed. Cost is 0.
- Otherwise, we can partition the chain at any point $k$ such that $i \le k < j$. The subchains are $(i \dots k)$ and $(k+1 \dots j)$.
- The cost for a chosen $k$ is the cost of the left subchain + cost of the right subchain + cost to multiply the two resulting matrices. The dimensions of the left resulting matrix are `arr[i-1]` $\times$ `arr[k]` and the right resulting matrix are `arr[k]` $\times$ `arr[j]`. The multiplication cost is `arr[i-1] * arr[k] * arr[j]`.
- We try all $k$ from $i$ to $j-1$ and take the minimum cost. We memoize the results of $f(i, j)$ in a 2D table.

```cpp
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
    int f(int i, int j, vector<int>& arr, vector<vector<int>>& dp) {
        if (i == j) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        
        int minCost = INT_MAX;
        for (int k = i; k < j; ++k) {
            int cost = f(i, k, arr, dp) + f(k + 1, j, arr, dp) 
                     + arr[i - 1] * arr[k] * arr[j];
            minCost = min(minCost, cost);
        }
        return dp[i][j] = minCost;
    }

public:
    int matrixMultiplication(int N, vector<int>& arr) {
        // Matrices are from index 1 to N-1
        vector<vector<int>> dp(N, vector<int>(N, -1));
        return f(1, N - 1, arr, dp);
    }
};

int main() {
    Solution sol;
    vector<int> arr = {40, 20, 30, 10, 30};
    cout << sol.matrixMultiplication(arr.size(), arr) << endl; // Output: 26000
    return 0;
}
```

**Complexity**: 
- **Time:** $O(n^{3})$. There are $O(n^{2})$ states, and for each state, we loop $O(n)$ times to find the optimal partition $k$.
- **Space:** $O(n^{2})$ for the DP table and $O(n)$ for the recursion stack, giving $O(n^{2})$ auxiliary space.

**Practice:** https://www.geeksforgeeks.org/problems/matrix-chain-multiplication0303/1

### Matrix Chain Multiplication (bottom-up)

We convert the memoized MCM solution into tabulation.

**Intuition / Approach**:
- The state $f(i, j)$ depends on $f(i, k)$ and $f(k+1, j)$. This means a larger interval $[i, j]$ depends on smaller sub-intervals.
- To compute bottom-up, we iterate the length of the chain from 2 to $N-1$. Alternatively, we can mimic the recursion by iterating $i$ from $N-1$ down to 1, and $j$ from $i+1$ to $N-1$.
- The base case is when $i = j$, the cost is 0, which we can initialize in a 2D vector.
- The inner loop iterates $k$ from $i$ to $j-1$ to compute the minimum cost.

```cpp
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    int matrixMultiplication(int N, vector<int>& arr) {
        vector<vector<int>> dp(N, vector<int>(N, 0));
        
        // Base case is implicitly 0 when i == j
        
        for (int i = N - 1; i >= 1; --i) {
            for (int j = i + 1; j < N; ++j) {
                int minCost = INT_MAX;
                for (int k = i; k < j; ++k) {
                    int cost = dp[i][k] + dp[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                    minCost = min(minCost, cost);
                }
                dp[i][j] = minCost;
            }
        }
        return dp[1][N - 1];
    }
};

int main() {
    Solution sol;
    vector<int> arr = {40, 20, 30, 10, 30};
    cout << sol.matrixMultiplication(arr.size(), arr) << endl; // Output: 26000
    return 0;
}
```

**Complexity**: 
- **Time:** $O(n^{3})$. Three nested loops: $i$, $j$, and $k$.
- **Space:** $O(n^{2})$ for the 2D DP table. Space optimization is not possible because we need values from various lengths and indices.

**Practice:** https://www.geeksforgeeks.org/problems/matrix-chain-multiplication0303/1

### Minimum Cost to Cut a Stick

Given a wooden stick of length `n` and an array `cuts` indicating the positions where you must make cuts. The cost of a cut is the length of the stick segment being cut. Return the minimum total cost of the cuts.

**Intuition / Approach**:
- A naive approach would be to make any cut and then independently solve for the resulting segments. However, the segments depend on the boundaries. 
- To make the subproblems independent, we sort the `cuts` array and add $0$ at the beginning and $n$ at the end. This allows us to define a stick segment using the indices of the `cuts` array.
- State $f(i, j)$ represents the minimum cost to cut the stick defined by `cuts[i-1]` and `cuts[j+1]`. The possible cuts to make are the elements in `cuts` from index $i$ to $j$.
- If we make a cut at `cuts[k]` (where $i \le k \le j$), the cost of this cut is `cuts[j+1] - cuts[i-1]`.
- The problem is split into $f(i, k-1)$ and $f(k+1, j)$.
- We try all possible cuts $k$ and take the minimum.

```cpp
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
    int f(int i, int j, vector<int>& cuts, vector<vector<int>>& dp) {
        if (i > j) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        
        int minCost = INT_MAX;
        for (int k = i; k <= j; ++k) {
            int cost = cuts[j + 1] - cuts[i - 1] 
                     + f(i, k - 1, cuts, dp) + f(k + 1, j, cuts, dp);
            minCost = min(minCost, cost);
        }
        return dp[i][j] = minCost;
    }

public:
    int minCost(int n, vector<int>& cuts) {
        int c = cuts.size();
        cuts.push_back(n);
        cuts.insert(cuts.begin(), 0);
        sort(cuts.begin(), cuts.end());
        
        vector<vector<int>> dp(c + 1, vector<int>(c + 1, -1));
        return f(1, c, cuts, dp);
    }
};

int main() {
    Solution sol;
    vector<int> cuts = {1, 3, 4, 5};
    cout << sol.minCost(7, cuts) << endl; // Output: 16
    return 0;
}
```

**Complexity**: 
- **Time:** $O(c \log c + c^{3})$, where $c$ is the number of cuts. Sorting takes $O(c \log c)$, and there are $c^{2}$ states in DP with an inner loop of $O(c)$.
- **Space:** $O(c^{2})$ for the DP table and $O(c)$ for the recursion stack.

**Practice:** https://leetcode.com/problems/minimum-cost-to-cut-a-stick/

### Burst Balloons

Given `n` balloons indexed `0` to `n-1`, each with a number of coins on it. Bursting balloon `i` gives `nums[i-1] * nums[i] * nums[i+1]` coins. If `i-1` or `i+1` goes out of bounds, treat it as a balloon with a `1`. Return the maximum coins you can collect by bursting balloons wisely.

::: heavy
A forward approach (picking which balloon to burst *first*) creates dependent subproblems: bursting a balloon makes its left and right neighbors adjacent, which means the subproblems cannot be solved independently.
Instead, we think in reverse: pick which balloon to burst **last** in a range $[i, j]$. If $k$ is the last balloon to burst, then all other balloons in $[i, j]$ have already been burst. Thus, balloon $k$'s adjacent neighbors when it bursts are precisely the elements just outside the range, i.e., at indices $i-1$ and $j+1$. The subproblems $[i, k-1]$ and $[k+1, j]$ are now completely independent!
:::

**Intuition / Approach**:
- Pad the `nums` array with a `1` at both ends to handle edge cases.
- Let $f(i, j)$ be the maximum coins obtained by bursting balloons in the range $[i, j]$.
- We iterate through every balloon $k$ in $[i, j]$ and assume it is the **last** balloon to burst in this range.
- The coins obtained from bursting $k$ last is `nums[i-1] * nums[k] * nums[j+1]`.
- We add the maximum coins from completely bursting the left range $f(i, k-1)$ and the right range $f(k+1, j)$.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    int f(int i, int j, vector<int>& nums, vector<vector<int>>& dp) {
        if (i > j) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        
        int maxCoins = 0;
        for (int k = i; k <= j; ++k) {
            int coins = nums[i - 1] * nums[k] * nums[j + 1]
                      + f(i, k - 1, nums, dp) + f(k + 1, j, nums, dp);
            maxCoins = max(maxCoins, coins);
        }
        return dp[i][j] = maxCoins;
    }

public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
        return f(1, n, nums, dp);
    }
};

int main() {
    Solution sol;
    vector<int> nums = {3, 1, 5, 8};
    cout << sol.maxCoins(nums) << endl; // Output: 167
    return 0;
}
```

**Complexity**: 
- **Time:** $O(n^{3})$. Number of states is $O(n^{2})$ and trying every element as the last balloon takes $O(n)$.
- **Space:** $O(n^{2})$ for the DP table and $O(n)$ recursion depth.

**Practice:** https://leetcode.com/problems/burst-balloons/

### Evaluate Boolean Expression to True

Given a string representing a boolean expression with `T`, `F`, and operators `&`, `|`, `^`. Find the number of ways to parenthesize the expression such that it evaluates to True.

**Intuition / Approach**:
- The expression consists of alternating operands (`T/F`) and operators (`&/|/^`).
- We want to partition the expression at every operator. For a chosen operator at index $k$, it splits the expression into a left sub-expression and a right sub-expression.
- The outcome of the full expression depends on the boolean values of both left and right parts. Thus, for any range $[i, j]$, we need to compute **two** values: the number of ways it evaluates to True, and the number of ways it evaluates to False.
- Let $f(i, j, \text{isTrue})$ be the number of ways to evaluate the expression from $i$ to $j$ to the target boolean `isTrue`.
- For each operator $k$ between $i$ and $j$, we compute the true/false counts for the left part $[i, k-1]$ and right part $[k+1, j]$. Depending on the operator `&`, `|`, `^`, we combine these counts using combinatorics.

```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
    int MOD = 1003;
    
    int f(int i, int j, int isTrue, string& exp, vector<vector<vector<int>>>& dp) {
        if (i > j) return 0;
        if (i == j) {
            if (isTrue == 1) return exp[i] == 'T';
            else return exp[i] == 'F';
        }
        if (dp[i][j][isTrue] != -1) return dp[i][j][isTrue];
        
        long long ways = 0;
        // Operators are at i+1, i+3, ..., j-1
        for (int k = i + 1; k <= j - 1; k += 2) {
            long long lT = f(i, k - 1, 1, exp, dp);
            long long lF = f(i, k - 1, 0, exp, dp);
            long long rT = f(k + 1, j, 1, exp, dp);
            long long rF = f(k + 1, j, 0, exp, dp);
            
            if (exp[k] == '&') {
                if (isTrue) ways = (ways + (lT * rT) % MOD) % MOD;
                else ways = (ways + (lT * rF) % MOD + (lF * rT) % MOD + (lF * rF) % MOD) % MOD;
            } else if (exp[k] == '|') {
                if (isTrue) ways = (ways + (lT * rT) % MOD + (lT * rF) % MOD + (lF * rT) % MOD) % MOD;
                else ways = (ways + (lF * rF) % MOD) % MOD;
            } else if (exp[k] == '^') {
                if (isTrue) ways = (ways + (lT * rF) % MOD + (lF * rT) % MOD) % MOD;
                else ways = (ways + (lT * rT) % MOD + (lF * rF) % MOD) % MOD;
            }
        }
        return dp[i][j][isTrue] = ways;
    }

public:
    int countWays(int n, string exp) {
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, -1)));
        return f(0, n - 1, 1, exp, dp);
    }
};

int main() {
    Solution sol;
    cout << sol.countWays(7, "T|T&F^T") << endl; // Output: 4
    return 0;
}
```

**Complexity**: 
- **Time:** $O(n^{3})$. There are $O(n^{2})$ states (ignoring the constant factor of 2), and for each state, we iterate over the intermediate operators taking $O(n)$ time.
- **Space:** $O(n^{2})$ for the 3D DP table and $O(n)$ recursion stack.

**Practice:** https://www.geeksforgeeks.org/problems/boolean-parenthesization5610/1

### Palindrome Partitioning II

Given a string `s`, partition it such that every substring is a palindrome. Find the minimum cuts needed.

**Intuition / Approach**:
- This is a variation of the MCM pattern known as the **Front Partition** pattern. Since we just need to cut the string into valid parts, we can iterate over the starting index $i$ and find a valid ending index $j$.
- If `s[i...j]` is a palindrome, we can make a cut after $j$. The remaining problem is to partition the string from $j+1$ to the end. Thus, a 1D state $f(i)$ suffices.
- Let $f(i)$ be the minimum cuts to partition the suffix `s[i...N-1]`.
- We iterate $j$ from $i$ to $N-1$. If the substring `s[i...j]` is a palindrome, we recursively solve for $f(j+1)$ and add 1 (for the cut). We take the minimum across all valid $j$.
- The base case is when $i = N$, which means the string is empty and requires 0 cuts. However, a string of length $n$ that is fully a palindrome needs 0 cuts, but our logic will make 1 cut at the end. We return `f(0) - 1` at the end to correct for the implicit cut at the very end of the string.

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
    bool isPalindrome(int i, int j, string& s) {
        while (i < j) {
            if (s[i] != s[j]) return false;
            i++; j--;
        }
        return true;
    }

    int f(int i, int n, string& s, vector<int>& dp) {
        if (i == n) return 0;
        if (dp[i] != -1) return dp[i];
        
        int minCuts = 1e9;
        for (int j = i; j < n; ++j) {
            if (isPalindrome(i, j, s)) {
                int cuts = 1 + f(j + 1, n, s, dp);
                minCuts = min(minCuts, cuts);
            }
        }
        return dp[i] = minCuts;
    }

public:
    int minCut(string s) {
        int n = s.size();
        vector<int> dp(n, -1);
        return f(0, n, s, dp) - 1;
    }
};

int main() {
    Solution sol;
    cout << sol.minCut("aab") << endl; // Output: 1
    return 0;
}
```

**Complexity**: 
- **Time:** $O(n^{3})$ worst-case for the memoized approach if we re-check palindromes every time in $O(n)$. With a precomputed boolean 2D table for palindromes, it is optimized to $O(n^{2})$.
- **Space:** $O(n)$ for the 1D DP array.

**Practice:** https://leetcode.com/problems/palindrome-partitioning-ii/

### Partition Array for Maximum Sum

Given an integer array `arr`, partition it into contiguous subarrays of length at most `k`. After partitioning, each subarray has their values changed to become the maximum value of that subarray. Return the largest sum of the given array.

**Intuition / Approach**:
- This is another **Front Partition** problem. We need to process the array from left to right. Let $f(i)$ be the maximum sum obtainable from the suffix starting at index $i$.
- From index $i$, we can form a subarray of length $1, 2, \dots, k$. We iterate a pointer $j$ from $i$ to $\min(n-1, i+k-1)$.
- As we expand the window `arr[i...j]`, we track the maximum element seen so far.
- If we place a partition after $j$, the subarray length is `len = j - i + 1`. The sum for this chunk becomes `len * maxElement`. The remaining array is recursively solved via $f(j+1)$.
- We try all valid lengths and take the maximum total sum.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    int f(int i, vector<int>& arr, int k, vector<int>& dp) {
        int n = arr.size();
        if (i == n) return 0;
        if (dp[i] != -1) return dp[i];
        
        int len = 0;
        int maxElement = -1;
        int maxSum = -1;
        
        for (int j = i; j < min(n, i + k); ++j) {
            len++;
            maxElement = max(maxElement, arr[j]);
            int sum = len * maxElement + f(j + 1, arr, k, dp);
            maxSum = max(maxSum, sum);
        }
        
        return dp[i] = maxSum;
    }

public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        vector<int> dp(arr.size(), -1);
        return f(0, arr, k, dp);
    }
};

int main() {
    Solution sol;
    vector<int> arr = {1, 15, 7, 9, 2, 5, 10};
    cout << sol.maxSumAfterPartitioning(arr, 3) << endl; // Output: 84
    return 0;
}
```

**Complexity**: 
- **Time:** $O(n \times k)$. There are $O(n)$ states and we try at most $k$ choices from each state.
- **Space:** $O(n)$ for the 1D DP table and recursion stack.

**Practice:** https://leetcode.com/problems/partition-array-for-maximum-sum/

### Count Square Submatrices with All Ones

Given a $m \times n$ matrix of ones and zeros, return how many square submatrices have all ones.

**Intuition / Approach**:
- This falls under the **DP on Grids / Squares** category.
- A square is determined by its bottom-right corner. Let `dp[i][j]` be the side length of the **maximum square** whose bottom-right corner is at $(i, j)$. 
- Interestingly, if the maximum square ending at $(i, j)$ has size $S$, it implies there are exactly $S$ valid squares ending at this cell (of sizes $1 \times 1, 2 \times 2, \dots, S \times S$).
- To compute `dp[i][j]`: if `matrix[i][j]` is 1, it can extend squares ending at its top, left, and top-left. The size of the new square is limited by the smallest of these three adjacent squares. So, `dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]})`.
- We sum all values in the DP table to get the total number of squares.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int totalSquares = 0;
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 1) {
                    if (i == 0 || j == 0) {
                        dp[i][j] = 1;
                    } else {
                        dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
                    }
                    totalSquares += dp[i][j];
                }
            }
        }
        
        return totalSquares;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> matrix = {
        {0, 1, 1, 1},
        {1, 1, 1, 1},
        {0, 1, 1, 1}
    };
    cout << sol.countSquares(matrix) << endl; // Output: 15
    return 0;
}
```

**Complexity**: 
- **Time:** $O(m \times n)$ since we process every cell of the grid exactly once.
- **Space:** $O(m \times n)$ for the DP table. This can be space-optimized to $O(n)$ by keeping only the current and previous rows.

**Practice:** https://leetcode.com/problems/count-square-submatrices-with-all-ones/

::: interview
Dynamic Programming is one of the most common and feared topics in interviews. Interviewers are looking for you to recognize DP patterns quickly:
1. Identify if it requires "try all ways" and has overlapping subproblems / repeated states.
2. Recall the common templates: take / not-take for subsequences, 0/1 Knapsack, LCS for string matching grids, and Partition/MCM for division problems.
3. **Always state the recurrence before coding.** Formulate it as a mathematical function $f(i, j) = \dots$ and explain it to the interviewer. This shows structured thinking.
4. If you start with a 2D table, always observe if the current row only depends on the previous row. If so, know how to verbally explain or code space-optimizing it to two 1D arrays or a single 1D array.
:::
