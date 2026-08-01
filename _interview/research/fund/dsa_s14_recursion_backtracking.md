# Recursion & Backtracking

::: heavy
**Recursion** is a method of solving a problem where the solution depends on solutions to smaller instances of the same problem. Every recursive algorithm requires a **base case** to terminate and a **recursive case** that breaks the problem down. As functions call themselves, execution pauses and is pushed onto the **call stack**, waiting for the child call to return. 

To visualize and trace recursive executions, we use a **recursion tree**. Each node represents a function call, and its children represent the subsequent recursive calls made from that state. In combinatorial problems, two dominant templates emerge for exploring the tree:
1. **Pick / Not-Pick (Take / Not-Take):** Typically used over an array or string. At each index, branch twice: one path includes the current element, and the other excludes it.
2. **For-Each Choice:** Used when multiple options are available at a state. Iterate through all valid choices, apply a choice, recurse, and then undo the choice (this is the skeleton of backtracking).
:::

::: keypoint
The core of backtracking is the **undo step** (`mutate $\rightarrow$ recurse $\rightarrow$ un-mutate`). Instead of creating expensive copies of the state (like paths or boards) for every recursive call, we pass a single shared state buffer by reference. We push a choice onto the buffer, recurse, and pop it off immediately after the call returns, leaving the buffer clean for the next choice.
:::

::: trap
Always verify your base cases. Missing, incorrect, or unreachable base cases will cause the recursion to continue indefinitely, leading to a stack overflow error as the call stack exhausts available memory.
:::

## Recursion Fundamentals & the Subsequence Pattern

### Recursive Implementation of `atoi`
The `atoi` function converts a string to an integer, handling leading whitespace, an optional sign, and discarding trailing non-numeric characters.

**Intuition:** 
We can parse the string sequentially. The base case is when we reach the end of the string or encounter a non-digit character. The recursive case multiplies the accumulated result by 10 and adds the current digit. To handle sign and overflow natively across recursion, we can pass an index and a sign, but typically `atoi` is solved iteratively. A recursive approach mimics the iterative parsing: process one character, then recurse for the rest.

```cpp
#include <string>
#include <climits>

class Solution {
    int recursiveAtoi(const std::string& s, int i, int sign, long result) {
        if (i == s.length() || s[i] < '0' || s[i] > '9') {
            return sign * result;
        }
        
        result = result * 10 + (s[i] - '0');
        
        if (sign == 1 && result > INT_MAX) return INT_MAX;
        if (sign == -1 && result > (long)INT_MAX + 1) return INT_MIN;
        
        return recursiveAtoi(s, i + 1, sign, result);
    }
    
public:
    int myAtoi(std::string s) {
        int i = 0;
        int n = s.length();
        int sign = 1;
        
        while (i < n && s[i] == ' ') i++;
        if (i < n && (s[i] == '+' || s[i] == '-')) {
            sign = (s[i] == '-') ? -1 : 1;
            i++;
        }
        
        return recursiveAtoi(s, i, sign, 0);
    }
};
```

**Complexity:** Time is $O(n)$ where $n$ is the length of the string, exploring each character once. Space is $O(n)$ for the recursion stack depth.
**Practice:** https://leetcode.com/problems/string-to-integer-atoi/

### `pow(x, n)` — fast exponentiation by recursion

::: keypoint
Instead of multiplying `x` by itself `n` times ($O(n)$), we can use binary exponentiation: $x^n = (x^{n/2})^2$ if $n$ is even, and $x \cdot (x^{n/2})^2$ if $n$ is odd. This cuts the problem size in half at each step.
:::

**Intuition:**
Brute force is a loop running $n$ times. To optimize, if we know $x^{n/2}$, we can square it to get $x^n$. This logarithmic reduction requires handling negative powers (by reciprocating $x$) and potential integer overflow on `n`.

```cpp
class Solution {
    double fastPow(double x, long long n) {
        if (n == 0) return 1.0;
        
        double half = fastPow(x, n / 2);
        if (n % 2 == 0) {
            return half * half;
        } else {
            return half * half * x;
        }
    }
public:
    double myPow(double x, int n) {
        long long num = n;
        if (num < 0) {
            x = 1 / x;
            num = -num;
        }
        return fastPow(x, num);
    }
};
```

**Complexity:** Time is $O(\log n)$ because the exponent is halved each call. Space is $O(\log n)$ for the recursion depth.
**Practice:** https://leetcode.com/problems/powx-n/

### Count Good Numbers
A digit string is "good" if the digits at even indices are even (`0, 2, 4, 6, 8`) and digits at odd indices are prime (`2, 3, 5, 7`). Count the total good numbers of length $n$, modulo $10^9 + 7$.

**Intuition:**
There are 5 even digits and 4 prime digits. For a string of length $n$, there are $\lceil n/2 \rceil$ even indices and $\lfloor n/2 \rfloor$ odd indices. Thus, the answer is $5^{\lceil n/2 \rceil} \times 4^{\lfloor n/2 \rfloor}$. We can compute this using fast exponentiation.

```cpp
class Solution {
    long long power(long long x, long long n, int mod) {
        if (n == 0) return 1;
        long long half = power(x, n / 2, mod);
        long long res = (half * half) % mod;
        if (n % 2 != 0) res = (res * x) % mod;
        return res;
    }
public:
    int countGoodNumbers(long long n) {
        int mod = 1e9 + 7;
        long long evenPositions = (n + 1) / 2;
        long long oddPositions = n / 2;
        
        long long evenWays = power(5, evenPositions, mod);
        long long oddWays = power(4, oddPositions, mod);
        
        return (evenWays * oddWays) % mod;
    }
};
```

**Complexity:** Time is $O(\log n)$ for the modular exponentiation. Space is $O(\log n)$ for the recursion stack.
**Practice:** https://leetcode.com/problems/count-good-numbers/

### Sort a Stack Using Recursion
Sort a stack such that the greatest elements are at the top, using only recursion (no explicit loops or additional data structures).

**Intuition:**
The problem enforces a pure recursive mindset. We can empty the stack by recursively popping the top element until it is empty. Then, as the recursive calls return, we insert each held element back into the stack in its sorted position. Inserting in sorted order is itself a recursive process: if the element is greater than the stack's top, just push it; otherwise, pop the top, recursively insert, and push the top back.

```cpp
#include <stack>

class Solution {
    void insertSorted(std::stack<int>& st, int val) {
        if (st.empty() || st.top() <= val) {
            st.push(val);
            return;
        }
        int temp = st.top();
        st.pop();
        insertSorted(st, val);
        st.push(temp);
    }
public:
    void sortStack(std::stack<int>& st) {
        if (st.empty()) return;
        
        int temp = st.top();
        st.pop();
        
        sortStack(st);
        insertSorted(st, temp);
    }
};
```

**Complexity:** Time is $O(n^2)$ because in the worst case (reverse sorted), every element requires $O(n)$ recursive calls to be inserted. Space is $O(n)$ for the call stack.
**Practice:** https://www.geeksforgeeks.org/sort-a-stack-using-recursion/

### Reverse a Stack Using Recursion
Reverse a stack using only standard stack operations and recursion.

**Intuition:**
Similar to sorting a stack, we first recursively pop all elements to reach the bottom. On the way back up the call stack, we need to place the held element at the *bottom* of the stack. Placing an element at the bottom requires a helper recursive function that pops everything, inserts the target element, and puts everything back.

```cpp
#include <stack>

class Solution {
    void insertAtBottom(std::stack<int>& st, int val) {
        if (st.empty()) {
            st.push(val);
            return;
        }
        int temp = st.top();
        st.pop();
        insertAtBottom(st, val);
        st.push(temp);
    }
public:
    void reverseStack(std::stack<int>& st) {
        if (st.empty()) return;
        
        int temp = st.top();
        st.pop();
        
        reverseStack(st);
        insertAtBottom(st, temp);
    }
};
```

**Complexity:** Time is $O(n^2)$ as each `insertAtBottom` takes $O(n)$ time. Space is $O(n)$ due to the call stack depth.
**Practice:** https://www.geeksforgeeks.org/reverse-a-stack-using-recursion/

### Generate All Binary Strings (no consecutive 1s)
Given an integer $n$, generate all binary strings of length $n$ such that there are no consecutive `1`s.

**Intuition:**
We build the strings character by character. At any position, we can always append a `0`. We can only append a `1` if the previous character was not `1`. This is a classic backtracking tree where decisions depend on the last appended state. We pass the current string and the last character added.

```cpp
#include <vector>
#include <string>

class Solution {
    void generate(int n, std::string current, std::vector<std::string>& res) {
        if (current.length() == n) {
            res.push_back(current);
            return;
        }
        
        // We can always append '0'
        generate(n, current + "0", res);
        
        // We can append '1' only if the last character isn't '1'
        if (current.empty() || current.back() != '1') {
            generate(n, current + "1", res);
        }
    }
public:
    std::vector<std::string> generateBinaryStrings(int n) {
        std::vector<std::string> res;
        generate(n, "", res);
        return res;
    }
};
```

**Complexity:** Time is $O(2^n)$ in the worst case, but heavily pruned by the constraint (it tightly bounds to Fibonacci numbers $O(\phi^n)$). Space is $O(n)$ for the depth of the recursion stack.
**Practice:** https://www.geeksforgeeks.org/generate-all-binary-strings-without-consecutive-1s/

### Generate Parentheses (all valid combinations)

::: keypoint
Valid parenthesis combinations can be generated by maintaining counts of `open` and `close` brackets used. You can always place an open bracket if you haven't exhausted `n`. You can place a close bracket only if `close < open`.
:::

**Intuition:**
We have $n$ pairs of parentheses. A combination is valid if at any point, the number of `)` does not exceed the number of `(`. We backtrack by keeping track of the current string, and the remaining counts of open and close brackets. If we have open brackets available, we try placing one. If we have more close brackets available than open brackets, we try placing a close bracket.

```cpp
#include <vector>
#include <string>

class Solution {
    void backtrack(std::vector<std::string>& res, std::string& current, int open, int close, int n) {
        if (current.length() == 2 * n) {
            res.push_back(current);
            return;
        }
        
        if (open < n) {
            current.push_back('(');
            backtrack(res, current, open + 1, close, n);
            current.pop_back(); // Undo
        }
        if (close < open) {
            current.push_back(')');
            backtrack(res, current, open, close + 1, n);
            current.pop_back(); // Undo
        }
    }
public:
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> res;
        std::string current;
        backtrack(res, current, 0, 0, n);
        return res;
    }
};
```

**Complexity:** Time is $O(4^n / \sqrt{n})$ which is the $n$-th Catalan number, reflecting the number of valid sequences. Space is $O(n)$ for the recursion depth and string buffer.
**Practice:** https://leetcode.com/problems/generate-parentheses/

### Print All Subsequences / Power Set (pick / not-pick)

::: keypoint
The "Pick / Not-Pick" template is the backbone for subset and subsequence problems. At every index in an array, we branch into two universes: one where we include `arr[i]` in our current subsequence, and one where we skip it.
:::

**Intuition:**
A subsequence is derived by deleting some or no elements without changing the order. To generate all, we traverse the array. At each element, we first try taking it (push to buffer, recurse, pop), then we try not taking it (recurse directly). Once the index reaches the array's end, the buffer holds one valid subsequence.

```cpp
#include <vector>

class Solution {
    void backtrack(int index, const std::vector<int>& nums, std::vector<int>& current, std::vector<std::vector<int>>& res) {
        if (index == nums.size()) {
            res.push_back(current);
            return;
        }
        
        // Choice 1: Pick the current element
        current.push_back(nums[index]);
        backtrack(index + 1, nums, current, res);
        current.pop_back(); // Undo
        
        // Choice 2: Do not pick the current element
        backtrack(index + 1, nums, current, res);
    }
public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
        std::vector<std::vector<int>> res;
        std::vector<int> current;
        backtrack(0, nums, current, res);
        return res;
    }
};
```

**Complexity:** Time is $O(2^n \cdot n)$ since there are $2^n$ subsequences and we spend $O(n)$ copying each to the result array. Space is $O(n)$ for the recursion stack and the state buffer.
**Practice:** https://leetcode.com/problems/subsets/

### Learn All Patterns of Subsequences — print-all, print-one, count

When dealing with subsequence conditions (e.g., subsequences with a specific sum), we can tweak the base structure to achieve three different goals:
1. **Print All:** Standard backtracking; accumulate results in a list.
2. **Print One:** Change the return type to boolean. If a recursive call returns `true`, immediately return `true` without exploring further branches.
3. **Count:** Change the return type to integer. Return 1 when the base condition is met, 0 otherwise, and sum the results of the recursive calls.

![Recursion patterns: print-all / print-one / count, and the subsequence take/not-take choice.](../assets/ss_021.png)

```cpp
#include <iostream>
#include <vector>

// Shared state, made concrete here so the three skeletons compile and run.
// In a real problem `arr`, `n`, and the predicate come from the input.
std::vector<int> arr = {1, 2, 1};
int n = (int)arr.size();
std::vector<std::vector<int>> res;
bool conditionMet() { return true; } // replace with the real test, e.g. running sum == target

// 1. Print-All Pattern — collect every qualifying subsequence
void printAll(int index, std::vector<int>& path) {
    if (index == n) {
        if (conditionMet()) res.push_back(path);
        return;
    }
    path.push_back(arr[index]);
    printAll(index + 1, path); // Pick
    path.pop_back();
    printAll(index + 1, path); // Not pick
}

// 2. Print-One Pattern — return true up the stack to stop at the first hit
bool printOne(int index, std::vector<int>& path) {
    if (index == n) {
        return conditionMet();
    }
    path.push_back(arr[index]);
    if (printOne(index + 1, path)) return true; // Pick
    path.pop_back();
    if (printOne(index + 1, path)) return true; // Not pick
    return false;
}

// 3. Count Pattern — return 1/0 at the base case and sum the branches
int countSubseq(int index, int sum) {
    if (index == n) {
        return conditionMet() ? 1 : 0;
    }
    int l = countSubseq(index + 1, sum + arr[index]); // Pick
    int r = countSubseq(index + 1, sum);              // Not pick
    return l + r;
}

int main() {
    std::vector<int> path;
    printAll(0, path);
    std::cout << res.size() << " subsequences collected\n";
    std::cout << (printOne(0, path) ? "found\n" : "none\n");
    std::cout << countSubseq(0, 0) << " subsequences counted\n";
    return 0;
}
```

### Count Subsequences with Sum K
Find the number of subsequences of an array that sum to a target value $K$.

**Intuition:**
We apply the **Count** pattern. At each element, we can either include it in our sum or exclude it. The total count from the current state is the sum of counts from both choices. If we reach the end of the array, we check if the accumulated sum equals $K$. (Note: for arrays with positive numbers, we can prune if `sum > K`).

```cpp
#include <vector>

class Solution {
    int countSubsequences(int index, int currentSum, const std::vector<int>& nums, int target) {
        // Assuming elements are non-negative, optional pruning:
        // if (currentSum > target) return 0;
        
        if (index == nums.size()) {
            return currentSum == target ? 1 : 0;
        }
        
        // Pick
        int pick = countSubsequences(index + 1, currentSum + nums[index], nums, target);
        // Not pick
        int notPick = countSubsequences(index + 1, currentSum, nums, target);
        
        return pick + notPick;
    }
public:
    int perfectSum(std::vector<int>& nums, int target) {
        return countSubsequences(0, 0, nums, target);
    }
};
```

**Complexity:** Time is $O(2^n)$ because we explore two branches per element. Space is $O(n)$ for the recursion depth.
**Practice:** https://www.geeksforgeeks.org/problems/perfect-sum-problem5633/1

### Check if There Exists a Subsequence with Sum K
Determine if any subsequence of an array sums exactly to $K$.

**Intuition:**
We apply the **Print One** pattern. Instead of exhaustive search, we return `true` as soon as we find a valid subsequence. This short-circuits the evaluation, drastically reducing runtime in successful cases.

```cpp
#include <vector>

class Solution {
    bool checkSubsequence(int index, int currentSum, const std::vector<int>& nums, int target) {
        if (index == nums.size()) {
            return currentSum == target;
        }
        
        // Pick
        if (checkSubsequence(index + 1, currentSum + nums[index], nums, target)) {
            return true;
        }
        
        // Not pick
        if (checkSubsequence(index + 1, currentSum, nums, target)) {
            return true;
        }
        
        return false;
    }
public:
    bool isSubsetSum(std::vector<int>& nums, int target) {
        return checkSubsequence(0, 0, nums, target);
    }
};
```

**Complexity:** Time is $O(2^n)$ worst-case, but early termination improves average time. Space is $O(n)$ for recursion depth.
**Practice:** https://www.geeksforgeeks.org/problems/subset-sum-problem-1611555638/1

### Combination Sum (unlimited reuse)

::: keypoint
When an element can be reused an unlimited number of times, the "Pick" branch should NOT advance the index (`index + 1`), but rather stay on the same `index` to allow picking the same element again. The "Not-Pick" branch advances the index as usual.
:::

**Intuition:**
Given an array of distinct integers and a target sum, find all unique combinations that sum to target. We use the take/not-take template. If we take `candidates[i]`, we recurse with the same index `i` because we can reuse it. If we don't take it, we recurse with `i + 1`. We prune the tree if the sum exceeds the target.

```cpp
#include <vector>

class Solution {
    void backtrack(int index, int currentSum, std::vector<int>& current, 
                   const std::vector<int>& candidates, int target, 
                   std::vector<std::vector<int>>& res) {
        if (index == candidates.size()) {
            if (currentSum == target) {
                res.push_back(current);
            }
            return;
        }
        
        // Optimization: pruning if elements are positive
        if (currentSum > target) return;
        
        // Pick (stay at the same index for unlimited reuse)
        if (currentSum + candidates[index] <= target) {
            current.push_back(candidates[index]);
            backtrack(index, currentSum + candidates[index], current, candidates, target, res);
            current.pop_back();
        }
        
        // Not Pick (move to the next index)
        backtrack(index + 1, currentSum, current, candidates, target, res);
    }
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
        std::vector<std::vector<int>> res;
        std::vector<int> current;
        backtrack(0, 0, current, candidates, target, res);
        return res;
    }
};
```

**Complexity:** Time is exponentially bounded $O(2^t)$, where $t$ is $target / \min(candidates)$, as the tree depth can be up to $t$. Space is $O(t)$ for the recursion stack and buffer.
**Practice:** https://leetcode.com/problems/combination-sum/

### Combination Sum II (each used once, skip duplicates)

::: trap
If you use the standard pick/not-pick template on an array with duplicates and just put results into a `std::set` to ensure uniqueness, you will TLE (Time Limit Exceeded). You must sort the array and skip duplicates at the tree-branching level using the **For-Each Choice** template.
:::

**Intuition:**
We need to find combinations summing to the target, but each element in the input can only be used once, and the result must not contain duplicate combinations. By sorting the array, identical elements become adjacent. At any recursive state, we loop over possible next elements. If `candidates[i] == candidates[i-1]`, skipping it prevents generating duplicate subsets originating from the same depth level.

```cpp
#include <vector>
#include <algorithm>

class Solution {
    void backtrack(int start, int target, std::vector<int>& current, 
                   const std::vector<int>& candidates, std::vector<std::vector<int>>& res) {
        if (target == 0) {
            res.push_back(current);
            return;
        }
        
        for (int i = start; i < candidates.size(); i++) {
            // Skip duplicates at the same tree depth
            if (i > start && candidates[i] == candidates[i - 1]) continue;
            
            // Prune: if current element exceeds target, further elements will too (since sorted)
            if (candidates[i] > target) break;
            
            current.push_back(candidates[i]);
            // Move to i + 1 because each element is used at most once
            backtrack(i + 1, target - candidates[i], current, candidates, res);
            current.pop_back();
        }
    }
public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {
        std::sort(candidates.begin(), candidates.end());
        std::vector<std::vector<int>> res;
        std::vector<int> current;
        backtrack(0, target, current, candidates, res);
        return res;
    }
};
```

**Complexity:** Time is $O(2^n \cdot n)$ in the worst case (e.g., all identical elements), bounded by combinations of size up to $n$. Space is $O(n)$ for the recursion stack depth.
**Practice:** https://leetcode.com/problems/combination-sum-ii/

## Backtracking — Harder Problems

### Subset Sum I

Given a list of integers, return the sums of all possible subsets in increasing order. A subset sum is the sum of any combination of elements from the array.

**Intuition / approach:**
Since we need all possible subset sums, this is a classic "pick/not-pick" (take/not-take) recursion pattern. For each element, we have two choices: include it in the current subset sum, or exclude it. We maintain a running sum as we traverse the array. When we reach the end of the array (base case), we add the running sum to our result list. Finally, we sort the result list before returning.

**C++ solution:**
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    void solve(int index, int currentSum, const vector<int>& arr, vector<int>& ans) {
        if (index == arr.size()) {
            ans.push_back(currentSum);
            return;
        }
        
        // Pick the current element
        solve(index + 1, currentSum + arr[index], arr, ans);
        
        // Not-pick the current element
        solve(index + 1, currentSum, arr, ans);
    }
    
public:
    vector<int> subsetSums(vector<int>& arr, int n) {
        vector<int> ans;
        solve(0, 0, arr, ans);
        sort(ans.begin(), ans.end());
        return ans;
    }
};
```

**Complexity:**
- Time: $O(2^n + 2^n \log(2^n))$ where $n$ is the size of the array. The branching factor is 2 and the depth is $n$, generating $2^n$ subsets. Sorting the $2^n$ sums takes $O(2^n \log(2^n))$.
- Space: $O(2^n)$ to store the result array of subset sums, plus $O(n)$ for the recursion stack depth.

**Practice:** https://practice.geeksforgeeks.org/problems/subset-sums2234/1

### Subset Sum II

Given an integer array `nums` that may contain duplicates, return all possible unique subsets (the power set). The solution set must not contain duplicate subsets, but the order does not matter.

**Intuition / approach:**
Because the input can contain duplicates, using a standard take/not-take approach blindly will generate duplicate subsets (e.g., taking the first '2' vs taking the second '2' when input is `[1, 2, 2]`). To avoid this, we use the "for each choice" template over a sorted array. At any recursion step (building a subset of a certain length), we iterate through all possible *next* elements. If an element is the same as the previous element in the loop (and it's not the first element we are considering at this depth), we skip it. This ensures we only branch on unique elements at each position of the subset.

**C++ solution:**
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    void findSubsets(int index, vector<int>& nums, vector<int>& current, vector<vector<int>>& ans) {
        ans.push_back(current);
        
        for (int i = index; i < nums.size(); ++i) {
            // Skip duplicates to prevent duplicate subsets
            if (i > index && nums[i] == nums[i - 1]) continue;
            
            current.push_back(nums[i]);
            findSubsets(i + 1, nums, current, ans);
            current.pop_back(); // Undo choice (backtrack)
        }
    }
    
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> current;
        sort(nums.begin(), nums.end()); // Crucial for duplicate skipping
        findSubsets(0, nums, current, ans);
        return ans;
    }
};
```

**Complexity:**
- Time: $O(2^n \cdot n)$. Branching factor is roughly 2, generating at most $2^n$ unique subsets. Each subset takes $O(n)$ time to copy into the answer list. Sorting takes $O(n \log n)$ which is dominated by the subset generation.
- Space: $O(2^n \cdot n)$ to store all subset lists, plus $O(n)$ for the auxiliary recursion stack and the `current` state buffer.

**Practice:** https://leetcode.com/problems/subsets-ii/

### Combination Sum III

Find all valid combinations of $k$ numbers that sum up to $n$ such that only numbers from 1 to 9 are used and each number is used at most once.

**Intuition / approach:**
This is a bounded combination problem. The candidate space is fixed from 1 to 9. We need exactly $k$ elements, and their sum must be exactly $n$. We can use a recursive function that keeps track of the current number we are considering (from 1 to 9), the remaining `k` elements to pick, and the remaining `target` sum. If `k == 0` and `target == 0`, we've found a valid combination. We optimize by breaking early if `target < 0`.

**C++ solution:**
```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    void solve(int start, int k, int n, vector<int>& current, vector<vector<int>>& ans) {
        if (k == 0 && n == 0) {
            ans.push_back(current);
            return;
        }
        
        // Base cases for pruning
        if (k == 0 || n < 0) return;
        
        for (int i = start; i <= 9; ++i) {
            current.push_back(i);
            solve(i + 1, k - 1, n - i, current, ans);
            current.pop_back(); // Backtrack
        }
    }
    
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> ans;
        vector<int> current;
        solve(1, k, n, current, ans);
        return ans;
    }
};
```

**Complexity:**
- Time: $O(C(9, k) \cdot k)$. The branching factor decreases as we pick numbers. There are at most $\binom{9}{k}$ valid combinations, and copying each takes $O(k)$ time. Since the candidate space is strictly 9, this is a fast constant-bounded execution $O(1)$.
- Space: $O(k)$ for the recursion stack and the `current` path buffer. The result space requires $O(\text{valid combinations} \cdot k)$.

**Practice:** https://leetcode.com/problems/combination-sum-iii/

### Letter Combinations of a Phone Number

Given a string containing digits from `2-9` inclusive, return all possible letter combinations that the number could represent. A mapping of digits to letters (just like on the telephone buttons) is given.

**Intuition / approach:**
Each digit maps to a set of 3 or 4 letters. This forms a natural tree structure where the $i$-th level of the tree corresponds to the $i$-th digit in the input string. At each digit, we branch out for every character it maps to. We append the character to our current string, recurse to the next digit, and then backtrack by removing the character. 

**C++ solution:**
```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    const vector<string> mapping = {
        "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
    };

    void backtrack(int index, const string& digits, string& current, vector<string>& ans) {
        if (index == digits.length()) {
            ans.push_back(current);
            return;
        }
        
        int digit = digits[index] - '0';
        const string& letters = mapping[digit];
        
        for (char c : letters) {
            current.push_back(c);
            backtrack(index + 1, digits, current, ans);
            current.pop_back();
        }
    }
    
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        
        vector<string> ans;
        string current = "";
        backtrack(0, digits, current, ans);
        return ans;
    }
};
```

**Complexity:**
- Time: $O(4^n \cdot n)$ where $n$ is the length of digits. The branching factor is at most 4 (for digits 7 and 9), with depth $n$. Appending the generated string of length $n$ to the answer takes $O(n)$.
- Space: $O(n)$ for the recursion stack and the mutable `current` string, excluding the space required for the output array.

**Practice:** https://leetcode.com/problems/letter-combinations-of-a-phone-number/

### Palindrome Partitioning

Given a string `s`, partition `s` such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of `s`.

![Recursion tree for palindrome partitioning.](../assets/ss_048.png)

::: keypoint
The key realization in partitioning problems is that the "choice" is where to place the next cut. At index `i`, we iterate through all possible endpoints `j` (from `i` to `n-1`). If the substring `s[i...j]` is a palindrome, we make a cut, add the substring to our current partition list, and recurse starting from `j + 1`.
:::

**Intuition / approach:**
We want to break the string into chunks, validating that each chunk is a palindrome. Starting from the front of the string, we test prefixes of increasing length. Once we find a palindrome prefix, we split it off, and recursively solve the rest of the string. After exploring that path, we backtrack by removing the prefix and continue looking for longer palindrome prefixes.

**C++ solution:**
```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    bool isPalindrome(const string& s, int start, int end) {
        while (start < end) {
            if (s[start++] != s[end--]) return false;
        }
        return true;
    }

    void solve(int index, const string& s, vector<string>& current, vector<vector<string>>& ans) {
        if (index == s.length()) {
            ans.push_back(current);
            return;
        }
        
        for (int i = index; i < s.length(); ++i) {
            // If the prefix s[index...i] is a palindrome, branch out
            if (isPalindrome(s, index, i)) {
                current.push_back(s.substr(index, i - index + 1));
                solve(i + 1, s, current, ans);
                current.pop_back(); // Undo choice
            }
        }
    }
    
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans;
        vector<string> current;
        solve(0, s, current, ans);
        return ans;
    }
};
```

**Complexity:**
- Time: $O(2^n \cdot n)$ where $n$ is the length of string `s`. The branching factor is up to $n$ in the worst case (e.g., "aaaaa"), mapping to the $2^{n-1}$ possible ways to insert cuts between $n$ characters. Checking palindromes and substring extraction takes $O(n)$ time at each valid state.
- Space: $O(n)$ for the depth of the recursion tree and the `current` path state buffer.

**Practice:** https://leetcode.com/problems/palindrome-partitioning/

### Word Search

Given an `m x n` grid of characters `board` and a string `word`, return `true` if `word` exists in the grid. The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.

**Intuition / approach:**
We scan the grid for any cell that matches the first letter of our target `word`. When we find a match, we launch a Depth-First Search (DFS) backtracking routine to explore all valid paths. To prevent reusing cells, we must track our visited path. We can do this efficiently without an extra `visited` array by temporarily mutating the cell on the board (e.g., to `'#'`) before recursing, and reverting it back after (the classic backtracking undo step).

**C++ solution:**
```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    bool backtrack(int r, int c, int index, vector<vector<char>>& board, const string& word) {
        if (index == word.length()) return true;
        
        if (r < 0 || r >= board.size() || c < 0 || c >= board[0].size() || board[r][c] != word[index]) {
            return false;
        }
        
        char temp = board[r][c];
        board[r][c] = '#'; // Mark as visited
        
        // Explore all 4 directions
        bool found = backtrack(r + 1, c, index + 1, board, word) ||
                     backtrack(r - 1, c, index + 1, board, word) ||
                     backtrack(r, c + 1, index + 1, board, word) ||
                     backtrack(r, c - 1, index + 1, board, word);
                     
        board[r][c] = temp; // Backtrack (un-mark)
        return found;
    }
    
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == word[0] && backtrack(i, j, 0, board, word)) {
                    return true;
                }
            }
        }
        return false;
    }
};
```

**Complexity:**
- Time: $O(m \cdot n \cdot 3^L)$ where $m, n$ are grid dimensions and $L$ is the length of `word`. In the worst case, we start a search at all $m \times n$ cells. During the DFS, the branching factor is 3 (we don't go back where we came from) up to a depth of $L$.
- Space: $O(L)$ for the recursion stack depth. No extra visited grid was allocated.

**Practice:** https://leetcode.com/problems/word-search/

### N-Queens

The $n$-queens puzzle is the problem of placing $n$ queens on an $n \times n$ chessboard such that no two queens attack each other. Return all distinct solutions.

::: heavy
N-Queens is the quintessential backtracking constraint-satisfaction problem. The naive way checks every cell for safety in $O(N)$ time. The optimal way trades space for time: we maintain sets (usually arrays acting as hash sets) of which columns, main diagonals, and anti-diagonals are already under attack. This reduces the safety check to $O(1)$.
:::

**Intuition / approach:**
We place queens row by row. Since each row can only have one queen, the row index serves as our recursion depth. For a given row, we iterate through every column `col`. To quickly check if placing a queen at `(row, col)` is safe, we consult three state arrays:
- `cols[col]`: is there a queen in this column?
- `diag1[row + col]`: is there a queen on the minor diagonal (bottom-left to top-right)? Every cell on this diagonal shares the same sum of `row + col`.
- `diag2[row - col + n - 1]`: is there a queen on the major diagonal (top-left to bottom-right)? Every cell here shares a constant difference `row - col`.

If safe, we place the queen, mark the three arrays, recurse to the next row, and finally backtrack by removing the queen and un-marking the arrays.

**C++ solution:**
```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    void solve(int row, int n, vector<string>& board, vector<vector<string>>& ans, 
               vector<bool>& cols, vector<bool>& diag1, vector<bool>& diag2) {
        if (row == n) {
            ans.push_back(board);
            return;
        }
        
        for (int col = 0; col < n; ++col) {
            if (cols[col] || diag1[row + col] || diag2[row - col + n - 1]) continue;
            
            // Place queen
            board[row][col] = 'Q';
            cols[col] = diag1[row + col] = diag2[row - col + n - 1] = true;
            
            solve(row + 1, n, board, ans, cols, diag1, diag2);
            
            // Undo choice
            board[row][col] = '.';
            cols[col] = diag1[row + col] = diag2[row - col + n - 1] = false;
        }
    }
    
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<string> board(n, string(n, '.'));
        vector<bool> cols(n, false), diag1(2 * n - 1, false), diag2(2 * n - 1, false);
        
        solve(0, n, board, ans, cols, diag1, diag2);
        return ans;
    }
};
```

**Complexity:**
- Time: $O(N!)$ strictly bounded, as the branching factor starts at $N$ and drops. Finding the valid placements takes $O(N!)$, and we spend $O(N^2)$ to copy the board configuration into the answer.
- Space: $O(N)$ for the state tracking arrays (`cols`, `diag1`, `diag2`), the recursion stack depth of $N$, and the $N \times N$ `board` buffer.

**Practice:** https://leetcode.com/problems/n-queens/

### Rat in a Maze

Consider a rat placed at `(0, 0)` in a square matrix `m` of order `n` and has to reach the destination at `(n-1, n-1)`. Find all possible lexicographically sorted paths. $0$ represents blocked cell, $1$ is open. Valid moves are 'D' (Down), 'L' (Left), 'R' (Right), 'U' (Up).

**Intuition / approach:**
We explore the grid starting at `(0,0)`, recursively trying the four directions. To ensure the paths are produced in lexicographic order, we must explore the branches in alphabetical order of the moves: D, L, R, U. We mark cells as visited to prevent cycles, and un-mark them on the way back (backtracking). If we reach `(n-1, n-1)`, we append the path string.

**C++ solution:**
```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    void solve(int r, int c, vector<vector<int>>& m, int n, string path, vector<string>& ans, vector<vector<bool>>& vis) {
        if (r == n - 1 && c == n - 1) {
            ans.push_back(path);
            return;
        }
        
        // Lexicographical order: D, L, R, U
        int dr[] = {1, 0, 0, -1};
        int dc[] = {0, -1, 1, 0};
        char dir[] = {'D', 'L', 'R', 'U'};
        
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < n && nc >= 0 && nc < n && !vis[nr][nc] && m[nr][nc] == 1) {
                vis[nr][nc] = true;
                solve(nr, nc, m, n, path + dir[i], ans, vis);
                vis[nr][nc] = false; // backtrack
            }
        }
    }
    
public:
    vector<string> findPath(vector<vector<int>>& m, int n) {
        if (m[0][0] == 0 || m[n - 1][n - 1] == 0) return {};
        
        vector<string> ans;
        vector<vector<bool>> vis(n, vector<bool>(n, false));
        vis[0][0] = true;
        solve(0, 0, m, n, "", ans, vis);
        return ans;
    }
};
```

**Complexity:**
- Time: $O(4^{(m \cdot n)})$. In the absolute worst case, the branching factor is up to 3 at each step (since we don't go backwards) out of a maximum depth of $m \times n$. However, valid paths are significantly fewer. 
- Space: $O(m \cdot n)$ auxiliary space for the `vis` matrix and maximum recursion stack depth.

**Practice:** https://practice.geeksforgeeks.org/problems/rat-in-a-maze-problem/1

### Word Break

Given a string `s` and a dictionary of strings `wordDict`, return `true` if `s` can be segmented into a space-separated sequence of one or more dictionary words.

**Intuition / approach:**
We can try partitioning the string just like in Palindrome Partitioning. For each prefix, we check if it is in the dictionary. If it is, we recursively ask if the *suffix* can be broken down. Since multiple paths might lead to examining the exact same suffix, the pure backtracking approach results in repeated work (exponential time). We optimize this heavily by introducing **memoization**: we store whether a specific starting index can successfully be broken down.

**C++ solution:**
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
private:
    bool solve(int index, const string& s, const unordered_set<string>& dict, vector<int>& memo) {
        if (index == s.length()) return true;
        if (memo[index] != -1) return memo[index] == 1;
        
        for (int i = index; i < s.length(); ++i) {
            string word = s.substr(index, i - index + 1);
            if (dict.count(word)) {
                if (solve(i + 1, s, dict, memo)) {
                    return memo[index] = 1;
                }
            }
        }
        
        return memo[index] = 0;
    }
    
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        vector<int> memo(s.length(), -1);
        return solve(0, s, dict, memo);
    }
};
```

**Complexity:**
- Time: $O(n^3)$ where $n$ is the length of `s`. The state space (depth) is $O(n)$. At each state, there is a loop taking $O(n)$ steps, and string extraction `substr` takes $O(n)$ time. The memoization prevents redundant subtree evaluations. 
- Space: $O(n)$ for the recursion depth and the `memo` array space.

**Practice:** https://leetcode.com/problems/word-break/

### M-Coloring Problem

Given an undirected graph and an integer `M`, determine if the graph can be colored with at most `M` colors such that no two adjacent vertices of the graph are colored with the same color.

**Intuition / approach:**
We process one node at a time (from `0` to `N-1`). For a given node, we test all colors from `1` to `M`. For each color, we check if it is safe to apply (none of the node's neighbors currently have this color). If it's safe, we color the node and recursively attempt to color the next node. If the recursive call returns `true`, we propagate the success. If it fails, we remove the color (backtrack) and try the next color.

**C++ solution:**
```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    bool isSafe(int node, const vector<int>& color, const vector<vector<int>>& graph, int n, int col) {
        for (int i = 0; i < n; ++i) {
            // If connected and has the same color
            if (i != node && graph[node][i] == 1 && color[i] == col) {
                return false;
            }
        }
        return true;
    }

    bool solve(int node, const vector<vector<int>>& graph, vector<int>& color, int m, int n) {
        if (node == n) return true; // All nodes colored successfully
        
        for (int i = 1; i <= m; ++i) {
            if (isSafe(node, color, graph, n, i)) {
                color[node] = i; // Assign color
                
                if (solve(node + 1, graph, color, m, n)) {
                    return true;
                }
                
                color[node] = 0; // Backtrack
            }
        }
        return false;
    }
    
public:
    bool graphColoring(vector<vector<int>>& graph, int m, int n) {
        vector<int> color(n, 0);
        return solve(0, graph, color, m, n);
    }
};
```

**Complexity:**
- Time: $O(M^N)$. In the worst case, branching factor is $M$ (colors) and recursion depth is $N$ (nodes). Checking safety adds an $O(N)$ factor at each step, making worst-case $O(N \cdot M^N)$.
- Space: $O(N)$ for the `color` array tracking state and the recursion stack depth.

**Practice:** https://practice.geeksforgeeks.org/problems/m-coloring-problem-1587115620/1

### Sudoku Solver

Write a program to solve a Sudoku puzzle by filling the empty cells. Empty cells are indicated by the character `'.'`.

::: heavy
Sudoku pushes backtracking to its limit. The search space is immense, but the tight rules aggressively prune invalid branches. The algorithm scans for the first empty cell, attempts digits 1-9, and recurses. If no digit works, it means an earlier placement was incorrect, triggering a chain of backtracking undo operations.
:::

**Intuition / approach:**
We traverse the $9 \times 9$ board looking for an empty cell. When we find one, we try placing digits '1' through '9'. We check validity: the digit must not exist in the current row, column, or $3 \times 3$ sub-grid. If safe, we place it and recurse. Note that the recursion returns a `bool`. If the recursion returns `true`, the board is solved and we immediately bubble up the success. If it returns `false`, we erase the digit (`'.'`) and try the next one. 

**C++ solution:**
```cpp
#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    bool isValid(vector<vector<char>>& board, int row, int col, char c) {
        for (int i = 0; i < 9; ++i) {
            if (board[i][col] == c) return false; // Check column
            if (board[row][i] == c) return false; // Check row
            // Check 3x3 box
            if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c) return false;
        }
        return true;
    }

    bool solve(vector<vector<char>>& board) {
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                if (board[i][j] == '.') {
                    for (char c = '1'; c <= '9'; ++c) {
                        if (isValid(board, i, j, c)) {
                            board[i][j] = c;
                            
                            if (solve(board)) return true;
                            
                            board[i][j] = '.'; // Backtrack
                        }
                    }
                    return false; // No valid number found, trigger backtrack
                }
            }
        }
        return true; // Completely filled
    }
    
public:
    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }
};
```

**Complexity:**
- Time: $O(9^{(n^2)})$ bounded theoretically, but significantly faster in practice. The branching factor is at most 9, and depth is the number of empty cells (at most 81). The rigid constraints aggressively cut branches.
- Space: $O(1)$ auxiliary space excluding the recursion stack, which goes up to $O(81)$ deep.

**Practice:** https://leetcode.com/problems/sudoku-solver/

::: interview
What interviewers probe here: recognizing backtracking problems (generate all X / does an X exist / count X over a combinatorial space) and the pick/not-pick vs for-each-choice templates.
:::
