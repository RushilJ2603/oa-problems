# Sliding Window and Two Pointers

::: heavy
The **Sliding Window** and **Two Pointers** patterns are the optimal approaches for many contiguous subarray or substring problems. A naive approach usually considers all $O(N^2)$ contiguous subarrays, but a sliding window tracks a valid sequence using two pointers (left and right), bringing the time complexity down to $O(N)$.

Every sliding window problem falls into one of four canonical patterns:
1. **Constant / fixed-size window** — The window size is fixed at exactly $k$. We slide it by simultaneously adding the rightmost element and removing the leftmost element.
2. **Longest / variable window** — We want to maximize the window size. We expand `right` to include elements. While the window becomes invalid, we shrink `left` until it is valid again. We track the maximum window size seen so far.
3. **Shortest / variable window** — We want to minimize the window size. We expand `right` until the window is valid. Then, we aggressively shrink `left` while the window remains valid, tracking the minimum window size.
4. **Counting subarrays** — We want to count the number of subarrays with an *exact* property. This is achieved by computing `atMost(k) - atMost(k - 1)`.
:::

::: keypoint
The **`atMost(k)` trick** converts "exactly $k$" problems into two "at most $k$" sliding window problems. Counting subarrays with *exactly* $k$ elements satisfying a condition is equivalent to:
$(\text{Subarrays with } \le k) - (\text{Subarrays with } \le k-1)$.
For a sliding window where the condition holds, the number of valid subarrays ending at `right` is exactly `right - left + 1`.
:::

## Medium Problems

### Longest Substring Without Repeating Characters
Given a string, find the length of the longest substring without repeating characters.

**Intuition:** This is **Pattern 2 (Longest / variable window)**. We expand the window by moving the `right` pointer. If we see a character we've already included in the window, our window becomes invalid. Instead of moving `left` one step at a time, we can maintain an array or map of the last-seen index for each character. When we encounter a duplicate, we jump the `left` pointer to the right of its last seen position (if that position is within the current window).

```cpp
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> last_seen(256, -1);
        int max_len = 0;
        int left = 0;
        
        for (int right = 0; right < s.length(); ++right) {
            char c = s[right];
            if (last_seen[c] >= left) {
                left = last_seen[c] + 1;
            }
            last_seen[c] = right;
            max_len = max(max_len, right - left + 1);
        }
        
        return max_len;
    }
};
```
**Complexity:** Time $O(N)$ because both pointers traverse the string at most once. Space $O(1)$ since the alphabet size is constant (256 ASCII characters).
**Practice:** https://leetcode.com/problems/longest-substring-without-repeating-characters/

### Max Consecutive Ones III
Given a binary array `nums` and an integer `k`, return the maximum number of consecutive `1`s in the array if you can flip at most `k` `0`s.

**Intuition:** This is **Pattern 2 (Longest / variable window)**. The problem can be rephrased as: find the longest subarray containing at most `k` zeros. We expand `right`, counting zeros. While the zero count exceeds `k`, we increment `left` and decrease the count if `nums[left]` was a zero.

```cpp
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int max_len = 0;
        int zeros = 0;
        int left = 0;
        
        for (int right = 0; right < nums.size(); ++right) {
            if (nums[right] == 0) {
                zeros++;
            }
            while (zeros > k) {
                if (nums[left] == 0) {
                    zeros--;
                }
                left++;
            }
            max_len = max(max_len, right - left + 1);
        }
        
        return max_len;
    }
};
```
**Complexity:** Time $O(N)$ as each element is processed by `right` and `left` at most once. Space $O(1)$.
**Practice:** https://leetcode.com/problems/max-consecutive-ones-iii/

### Fruit Into Baskets
Given an array where elements represent fruit types, find the maximum length of a contiguous subarray with at most 2 distinct elements.

**Intuition:** This is **Pattern 2 (Longest / variable window)**. We are looking for the longest subarray with $\le 2$ distinct integers. We maintain a hash map of frequencies for elements in the window. When the map size exceeds 2, we increment `left` and reduce the frequency of `nums[left]` until a fruit type's frequency becomes 0, at which point we erase it from the map.

```cpp
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        unordered_map<int, int> count;
        int max_fruits = 0;
        int left = 0;
        
        for (int right = 0; right < fruits.size(); ++right) {
            count[fruits[right]]++;
            while (count.size() > 2) {
                count[fruits[left]]--;
                if (count[fruits[left]] == 0) {
                    count.erase(fruits[left]);
                }
                left++;
            }
            max_fruits = max(max_fruits, right - left + 1);
        }
        
        return max_fruits;
    }
};
```
**Complexity:** Time $O(N)$ amortized. The inner while loop runs at most $N$ times globally. Space $O(1)$ since the map stores at most 3 distinct elements.
**Practice:** https://leetcode.com/problems/fruit-into-baskets/

### Longest Repeating Character Replacement
Given a string `s` and an integer `k`, you can replace any character at most `k` times. Return the length of the longest substring containing the same letter.

**Intuition:** This is **Pattern 2 (Longest / variable window)**. For any window, the number of characters we need to replace is the window size minus the frequency of the most common character in the window. Thus, we want: `(window_length) - max_frequency <= k`. We expand `right`, updating frequencies and the global `max_frequency`. If the replacement count exceeds `k`, we shrink the window. Notably, we don't need to decrement `max_frequency` when shrinking, because only a higher `max_frequency` could ever give us a strictly longer valid window later.

```cpp
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> count(26, 0);
        int max_freq = 0;
        int max_len = 0;
        int left = 0;
        
        for (int right = 0; right < s.length(); ++right) {
            count[s[right] - 'A']++;
            max_freq = max(max_freq, count[s[right] - 'A']);
            
            if ((right - left + 1) - max_freq > k) {
                count[s[left] - 'A']--;
                left++;
            }
            max_len = max(max_len, right - left + 1);
        }
        
        return max_len;
    }
};
```
**Complexity:** Time $O(N)$ using the observation that `max_freq` does not need strict downgrading. Space $O(1)$ for the alphabet array.
**Practice:** https://leetcode.com/problems/longest-repeating-character-replacement/

### Binary Subarrays With Sum
Given a binary array `nums` and an integer `goal`, return the number of non-empty subarrays with a sum `goal`.

**Intuition:** This is **Pattern 4 (Counting subarrays)** using the `atMost` trick. Finding exactly `goal` sum is equal to finding `atMost(goal) - atMost(goal - 1)`. In the `atMost(k)` helper, we keep a running sum. When the sum exceeds `k`, we shrink the window. The number of valid subarrays ending at `right` is exactly `right - left + 1`.

```cpp
#include <vector>

using namespace std;

class Solution {
private:
    int atMost(const vector<int>& nums, int goal) {
        if (goal < 0) return 0;
        int count = 0;
        int current_sum = 0;
        int left = 0;
        
        for (int right = 0; right < nums.size(); ++right) {
            current_sum += nums[right];
            while (current_sum > goal) {
                current_sum -= nums[left];
                left++;
            }
            count += (right - left + 1);
        }
        return count;
    }

public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        return atMost(nums, goal) - atMost(nums, goal - 1);
    }
};
```
**Complexity:** Time $O(N)$ as `atMost` processes each element a constant number of times. Space $O(1)$.
**Practice:** https://leetcode.com/problems/binary-subarrays-with-sum/

### Count Number of Nice Subarrays
Given an array of integers `nums` and an integer `k`, a continuous subarray is called "nice" if there are `k` odd numbers on it. Return the number of nice subarrays.

**Intuition:** This is **Pattern 4 (Counting subarrays)**. We can map odd numbers to `1` and even numbers to `0`. Then, the problem perfectly reduces to finding subarrays with a sum exactly equal to `k`. We reuse the `atMost(k) - atMost(k - 1)` trick.

```cpp
#include <vector>

using namespace std;

class Solution {
private:
    int atMost(const vector<int>& nums, int k) {
        if (k < 0) return 0;
        int count = 0;
        int odd_count = 0;
        int left = 0;
        
        for (int right = 0; right < nums.size(); ++right) {
            if (nums[right] % 2 != 0) odd_count++;
            
            while (odd_count > k) {
                if (nums[left] % 2 != 0) odd_count--;
                left++;
            }
            count += (right - left + 1);
        }
        return count;
    }

public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        return atMost(nums, k) - atMost(nums, k - 1);
    }
};
```
**Complexity:** Time $O(N)$ for two passes of the sliding window. Space $O(1)$.
**Practice:** https://leetcode.com/problems/count-number-of-nice-subarrays/

### Number of Substrings Containing All Three Characters
Given a string `s` consisting only of characters 'a', 'b', and 'c'. Return the number of substrings containing at least one occurrence of all these characters.

**Intuition:** While this can be done via sliding window, an optimal O(N) strategy counts valid substrings directly using a last-seen map. As we traverse the string, if we have seen all three characters at least once, any substring starting from index `0` up to `min(last_seen['a'], last_seen['b'], last_seen['c'])` and ending at the current `right` pointer is valid.

```cpp
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numberOfSubstrings(string s) {
        vector<int> last_seen(3, -1);
        int count = 0;
        
        for (int right = 0; right < s.length(); ++right) {
            last_seen[s[right] - 'a'] = right;
            if (last_seen[0] != -1 && last_seen[1] != -1 && last_seen[2] != -1) {
                count += 1 + min({last_seen[0], last_seen[1], last_seen[2]});
            }
        }
        
        return count;
    }
};
```
**Complexity:** Time $O(N)$. We do exactly one pass. Space $O(1)$ for storing three indices.
**Practice:** https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/

### Maximum Points You Can Obtain from Cards
Given an array `cardPoints` and an integer `k`, you can pick `k` cards from either the beginning or the end. Return the maximum score.

**Intuition:** This is **Pattern 1 (Constant / fixed-size window)** on the complement. Instead of picking `k` cards from the ends, we are leaving behind a contiguous subarray of exactly `n - k` cards in the middle. We want to minimize the sum of this leftover subarray to maximize the sum of the picked cards. We compute the sum of the first `n - k` elements, then slide the window one element at a time.

```cpp
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        int window_size = n - k;
        
        int current_window_sum = 0;
        for (int i = 0; i < window_size; ++i) {
            current_window_sum += cardPoints[i];
        }
        
        int min_window_sum = current_window_sum;
        for (int i = window_size; i < n; ++i) {
            current_window_sum += cardPoints[i] - cardPoints[i - window_size];
            min_window_sum = min(min_window_sum, current_window_sum);
        }
        
        int total_sum = accumulate(cardPoints.begin(), cardPoints.end(), 0);
        return total_sum - min_window_sum;
    }
};
```
**Complexity:** Time $O(N)$ to iterate through the array once. Space $O(1)$.
**Practice:** https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/

## Hard Problems

### Longest Substring with At Most K Distinct Characters
Given a string `s` and an integer `k`, return the length of the longest substring that contains at most `k` distinct characters.

**Intuition:** This is **Pattern 2 (Longest / variable window)** and identical in structure to "Fruit Into Baskets" (where $k=2$). We use an array or map to count character frequencies. When the number of distinct characters exceeds `k`, we advance `left` and decrease frequencies, removing the character entirely if its count hits 0.

```cpp
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        unordered_map<char, int> count;
        int max_len = 0;
        int left = 0;
        
        for (int right = 0; right < s.length(); ++right) {
            count[s[right]]++;
            while (count.size() > k) {
                count[s[left]]--;
                if (count[s[left]] == 0) {
                    count.erase(s[left]);
                }
                left++;
            }
            max_len = max(max_len, right - left + 1);
        }
        
        return max_len;
    }
};
```
**Complexity:** Time $O(N)$ amortized, as each character enters and leaves the map at most once. Space $O(\min(N, \text{alphabet size}))$.
**Practice:** https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/

### Subarrays with K Different Integers
Given an integer array `nums` and an integer `k`, return the number of good subarrays, where a good subarray has exactly `k` different integers.

**Intuition:** This is **Pattern 4 (Counting subarrays)**. We calculate subarrays with `atMost(k)` distinct integers minus subarrays with `atMost(k - 1)` distinct integers. We track frequencies in a map; if the map size exceeds `k`, we shrink the window.

```cpp
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
private:
    int atMost(const vector<int>& nums, int k) {
        if (k == 0) return 0;
        unordered_map<int, int> count;
        int total = 0;
        int left = 0;
        
        for (int right = 0; right < nums.size(); ++right) {
            count[nums[right]]++;
            while (count.size() > k) {
                count[nums[left]]--;
                if (count[nums[left]] == 0) {
                    count.erase(nums[left]);
                }
                left++;
            }
            total += (right - left + 1);
        }
        return total;
    }

public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return atMost(nums, k) - atMost(nums, k - 1);
    }
};
```
**Complexity:** Time $O(N)$ as the `atMost` helper parses the array with a sliding window. Space $O(K)$ for the map.
**Practice:** https://leetcode.com/problems/subarrays-with-k-different-integers/

### Minimum Window Substring
Given two strings `s` and `t`, return the minimum window substring of `s` such that every character in `t` (including duplicates) is included in the window.

**Intuition:** This is **Pattern 3 (Shortest / variable window)**. We first populate a frequency map of the characters we need from `t`. As we expand `right`, if we see a needed character, we decrement its need-count; if it becomes $\ge 0$, we've satisfied one required character (`formed` counter increases). When `formed` equals the length of `t`, our window is valid. We then shrink `left` aggressively to minimize the window, breaking when shrinking makes the window invalid again.

::: keypoint
For "Shortest" window problems, we only update the answer **while the window is valid**, which happens inside the `while` loop shrinking `left`.
:::

```cpp
#include <string>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> need(128, 0);
        for (char c : t) need[c]++;
        
        int required = t.length();
        int min_len = INT_MAX, start_idx = 0;
        int left = 0, formed = 0;
        
        for (int right = 0; right < s.length(); ++right) {
            if (need[s[right]] > 0) formed++;
            need[s[right]]--;
            
            while (formed == required) {
                if (right - left + 1 < min_len) {
                    min_len = right - left + 1;
                    start_idx = left;
                }
                
                need[s[left]]++;
                if (need[s[left]] > 0) formed--;
                left++;
            }
        }
        
        return min_len == INT_MAX ? "" : s.substr(start_idx, min_len);
    }
};
```
**Complexity:** Time $O(N)$ since both pointers traverse `s` at most once. Space $O(1)$ for the fixed-size array.
**Practice:** https://leetcode.com/problems/minimum-window-substring/

### Minimum Window Subsequence
Given strings `s1` and `s2`, return the minimum contiguous substring part of `s1`, so that `s2` is a subsequence of the part.

**Intuition:** This is a **two-pointer forward/back scan** (not a standard window because we need a subsequence, so order matters). We advance `right` in `s1` and a pointer in `s2`. Once `s2` is fully matched, we know the current `right` is the end of a valid window. To find the optimal `left`, we scan *backwards* from `right` to match `s2` in reverse. This finds the shortest window ending at `right`. We then resume our forward search from `left + 1`.

```cpp
#include <string>

using namespace std;

class Solution {
public:
    string minWindow(string s1, string s2) {
        int m = s1.length(), n = s2.length();
        int min_len = m + 1, start = -1;
        int right = 0, ptr2 = 0;
        
        while (right < m) {
            if (s1[right] == s2[ptr2]) {
                ptr2++;
            }
            if (ptr2 == n) {
                // Found a valid window, now shrink it by matching backwards
                int left = right;
                ptr2--;
                while (ptr2 >= 0) {
                    if (s1[left] == s2[ptr2]) {
                        ptr2--;
                    }
                    if (ptr2 >= 0) left--;
                }
                
                if (right - left + 1 < min_len) {
                    min_len = right - left + 1;
                    start = left;
                }
                
                // Restart search from left + 1
                right = left;
                ptr2 = 0;
            }
            right++;
        }
        
        return start == -1 ? "" : s1.substr(start, min_len);
    }
};
```
**Complexity:** Time $O(N \times M)$ worst case, though generally faster. Finding a match takes $O(N)$, and backtracking takes $O(N)$ total across all matches. Space $O(1)$.
**Practice:** https://leetcode.com/problems/minimum-window-subsequence/

## Close

::: interview
To recognize a sliding window problem on sight, look for keywords like "contiguous subarray" or "substring", paired with an optimization (e.g., "longest", "shortest", "maximum") or a requirement to "count". The crux of solving it is explicitly defining the condition that makes a window **invalid** (the shrink condition). If you are asked to find "exactly $K$" of something, immediately reach for the `atMost(K) - atMost(K - 1)` trick!
:::
