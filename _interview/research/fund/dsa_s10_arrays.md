# Arrays

Array traversal is the foundation of many algorithms. Beyond simple iteration, a few core techniques appear repeatedly. The **two-pointer** technique involves using two indices to process pairs of elements or track distinct bounds within a single array, often reducing time complexity from $O(n^2)$ to $O(n)$.

::: definition
A **prefix-sum** array stores the sum of all elements up to a given index. If `prefix[i] = A[0] + ... + A[i]`, then the sum of any subarray `A[L...R]` can be computed in $O(1)$ time as `prefix[R] - prefix[L-1]`.
:::

```cpp
#include <vector>

std::vector<int> buildPrefixSum(const std::vector<int>& arr) {
    if (arr.empty()) return {};
    std::vector<int> prefix(arr.size());
    prefix[0] = arr[0];
    for (size_t i = 1; i < arr.size(); ++i) {
        prefix[i] = prefix[i - 1] + arr[i];
    }
    return prefix;
}
```

::: keypoint
Prefix sums are the universal tool for answering static subarray queries efficiently. Whenever a problem asks for subarray sums or XORs, prefix arrays are the primary candidate.
:::

::: definition
A **difference-array** is the inverse of a prefix-sum array, used to perform multiple range addition updates in $O(1)$ time. If `D[i] = A[i] - A[i-1]`, adding a value $V$ to range `[L, R]` simply requires `D[L] += V` and `D[R+1] -= V`. The final array is reconstructed by taking the prefix sums of `D`.
:::

```cpp
#include <vector>

void rangeAdd(std::vector<int>& diff, int L, int R, int val) {
    diff[L] += val;
    if (R + 1 < diff.size()) {
        diff[R + 1] -= val;
    }
}
```

## Basic Array Problems

### Largest Element
Given an array, find the maximum element present in it.

**Intuition:**
The brute force approach is sorting the array and returning the last element ($O(n \log n)$). A better and optimal approach is to maintain a maximum variable and perform a single pass ($O(n)$) through the array, updating the variable whenever a larger element is found.

```cpp
#include <vector>
#include <algorithm>
#include <limits>

int largestElement(const std::vector<int>& arr) {
    if (arr.empty()) return std::numeric_limits<int>::min();
    int max_val = arr[0];
    for (int num : arr) {
        max_val = std::max(max_val, num);
    }
    return max_val;
}
```

**Complexity:**
- Time: $O(n)$, where $n$ is the size of the array, for a single traversal.
- Space: $O(1)$, as only a single variable is used.

**Practice:** https://www.geeksforgeeks.org/problems/largest-element-in-array/1

### Second Largest Element
Given an array of integers, find the second largest element. Return -1 if it does not exist.

**Intuition:**
A brute force method sorts the array ($O(n \log n)$) and scans from the end for the first distinct smaller element. A better approach uses two passes ($O(n)$): one to find the largest, and another to find the largest element strictly smaller than the maximum. The optimal approach does this in a single pass ($O(n)$) without sorting, keeping track of both the largest and second-largest elements simultaneously.

```cpp
#include <vector>

int secondLargestElement(const std::vector<int>& arr) {
    int largest = -1;
    int second_largest = -1;
    
    for (int num : arr) {
        if (num > largest) {
            second_largest = largest;
            largest = num;
        } else if (num > second_largest && num != largest) {
            second_largest = num;
        }
    }
    return second_largest;
}
```

**Complexity:**
- Time: $O(n)$, visiting each element exactly once.
- Space: $O(1)$, storing only two integer variables.

**Practice:** https://www.geeksforgeeks.org/problems/second-largest3735/1

### Check if the Array is Sorted
Check if the array is sorted in non-decreasing order. Some common variants also check if the array is sorted and rotated.

**Intuition:**
To verify if an array is sorted in non-decreasing order, compare each element with the next. If any `arr[i] > arr[i+1]`, it is not sorted. To check if it is sorted and possibly rotated (as often asked on LeetCode), we count the number of "drops" where `arr[i] > arr[(i + 1) % n]`. If the drop count is 0 or 1, the array is sorted and rotated.

```cpp
#include <vector>

bool checkSorted(const std::vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) return true;
    int drops = 0;
    
    for (int i = 0; i < n; ++i) {
        if (arr[i] > arr[(i + 1) % n]) {
            drops++;
        }
    }
    return drops <= 1;
}
```

**Complexity:**
- Time: $O(n)$, single pass to check adjacent elements.
- Space: $O(1)$, no auxiliary arrays used.

**Practice:** https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/

### Remove Duplicates from Sorted Array
Given a sorted integer array, remove the duplicates in-place such that each unique element appears only once. The relative order should be kept. Return the number of unique elements.

**Intuition:**
A brute force approach inserts elements into a `std::set` to filter duplicates ($O(n \log n)$), then copies them back. Because the array is already sorted, duplicates are adjacent. The optimal approach uses the **two-pointer** technique: one pointer `i` tracks the position of the last unique element, and a fast pointer `j` scans the array. When `arr[j]` differs from `arr[i]`, we increment `i` and write `arr[j]` to `arr[i]`.

```cpp
#include <vector>

int removeDuplicates(std::vector<int>& arr) {
    if (arr.empty()) return 0;
    
    int i = 0;
    for (int j = 1; j < arr.size(); ++j) {
        if (arr[i] != arr[j]) {
            i++;
            arr[i] = arr[j];
        }
    }
    return i + 1;
}
```

**Complexity:**
- Time: $O(n)$, traversing the array with the `j` pointer once.
- Space: $O(1)$, modifying the array in-place.

**Practice:** https://leetcode.com/problems/remove-duplicates-from-sorted-array/

### Left Rotate Array by One
Given an array, rotate its elements to the left by one position. The first element becomes the last element.

**Intuition:**
To shift everything left by one, save the first element in a temporary variable, shift elements from index 1 to $n-1$ one position to the left, and finally place the saved element at the last index.

```cpp
#include <vector>

void rotateLeftOne(std::vector<int>& arr) {
    if (arr.empty()) return;
    
    int temp = arr[0];
    for (size_t i = 1; i < arr.size(); ++i) {
        arr[i - 1] = arr[i];
    }
    arr.back() = temp;
}
```

**Complexity:**
- Time: $O(n)$, shifting each element exactly once.
- Space: $O(1)$, using only one temporary variable.

**Practice:** https://leetcode.com/problems/rotate-array/

### Left Rotate Array by K Places
Given an array, rotate its elements to the left by $k$ places.

**Intuition:**
A brute force approach shifts the array by one position $k$ times ($O(n \cdot k)$). A better approach stores the first $k$ elements in a temporary array, shifts the rest left, and copies the temporary elements to the end ($O(n)$ time, $O(k)$ space). The optimal **reversal algorithm** avoids extra space: reversing the first $k$ elements, then the remaining $n-k$ elements, and finally reversing the entire array places all elements in their correctly rotated positions.

::: keypoint
The reversal algorithm for array rotation (`reverse(0, k-1)`, `reverse(k, n-1)`, `reverse(0, n-1)`) achieves $O(n)$ time and $O(1)$ space, avoiding any temporary buffers.
:::

```cpp
#include <vector>
#include <algorithm>

void rotateLeft(std::vector<int>& arr, int k) {
    int n = arr.size();
    if (n == 0) return;
    k = k % n;
    
    std::reverse(arr.begin(), arr.begin() + k);
    std::reverse(arr.begin() + k, arr.end());
    std::reverse(arr.begin(), arr.end());
}
```

**Complexity:**
- Time: $O(n)$, each element is reversed at most twice.
- Space: $O(1)$, swapping is done in-place.

**Practice:** https://leetcode.com/problems/rotate-array/

### Move Zeros to End
Given an integer array, move all `0`s to the end while maintaining the relative order of the non-zero elements.

**Intuition:**
A brute force method copies non-zero elements into a new array, fills the rest with zeros, and copies back ($O(n)$ time, $O(n)$ space). The optimal approach applies the **two-pointer** technique in-place: a pointer `j` tracks the position of the first zero. When a non-zero element is found by pointer `i`, we swap it with the zero at `j` and increment `j`.

```cpp
#include <vector>
#include <utility>

void moveZeroes(std::vector<int>& arr) {
    int j = -1;
    int n = arr.size();
    
    for (int i = 0; i < n; ++i) {
        if (arr[i] == 0) {
            j = i;
            break;
        }
    }
    
    if (j == -1) return;
    
    for (int i = j + 1; i < n; ++i) {
        if (arr[i] != 0) {
            std::swap(arr[i], arr[j]);
            j++;
        }
    }
}
```

**Complexity:**
- Time: $O(n)$, passing over the array at most twice.
- Space: $O(1)$, modifying the array in-place.

**Practice:** https://leetcode.com/problems/move-zeroes/

### Linear Search
Find if a given target element exists in an array.

**Intuition:**
Iterate through the array from the first element to the last. If the current element matches the target, return its index. If the loop completes without a match, return -1.

```cpp
#include <vector>

int linearSearch(const std::vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}
```

**Complexity:**
- Time: $O(n)$, checking each element at most once.
- Space: $O(1)$, no extra memory is allocated.

**Practice:** https://www.geeksforgeeks.org/problems/who-will-win-1587115621/1

### Union of Two Sorted Arrays
Given two sorted arrays, return a new sorted array containing their union (all unique elements present in either array).

**Intuition:**
A brute force approach inserts all elements from both arrays into a `std::set` ($O((m+n) \log(m+n))$) and builds the result. Since both arrays are already sorted, the optimal approach uses a **two-pointer merge**. We place pointers `i` and `j` at the start of each array. We compare the elements, append the smaller one (if it's not a duplicate of the last inserted element), and advance the corresponding pointer.

```cpp
#include <vector>

std::vector<int> findUnion(const std::vector<int>& arr1, const std::vector<int>& arr2) {
    int n = arr1.size();
    int m = arr2.size();
    int i = 0, j = 0;
    std::vector<int> union_arr;
    
    while (i < n && j < m) {
        if (arr1[i] <= arr2[j]) {
            if (union_arr.empty() || union_arr.back() != arr1[i]) {
                union_arr.push_back(arr1[i]);
            }
            i++;
        } else {
            if (union_arr.empty() || union_arr.back() != arr2[j]) {
                union_arr.push_back(arr2[j]);
            }
            j++;
        }
    }
    
    while (i < n) {
        if (union_arr.empty() || union_arr.back() != arr1[i]) {
            union_arr.push_back(arr1[i]);
        }
        i++;
    }
    
    while (j < m) {
        if (union_arr.empty() || union_arr.back() != arr2[j]) {
            union_arr.push_back(arr2[j]);
        }
        j++;
    }
    
    return union_arr;
}
```

**Complexity:**
- Time: $O(m + n)$, as both arrays are traversed at most once.
- Space: $O(m + n)$, for storing the result array containing the union.

**Practice:** https://www.geeksforgeeks.org/problems/union-of-two-sorted-arrays-1587115621/1

### Find the Missing Number
Given an array containing $n$ distinct numbers in the range $[0, n]$, return the only number in the range that is missing from the array.

**Intuition:**
A brute force method searches for each number from $0$ to $n$ linearly ($O(n^2)$). A better approach uses a hash set or frequency array ($O(n)$ space). The optimal approaches use either mathematics or bit manipulation in $O(1)$ space. We can sum all numbers in the array and subtract it from the expected sum $\frac{n(n+1)}{2}$. Alternatively, taking the XOR of all array elements and all numbers from $0$ to $n$ isolates the missing number, because $x \oplus x = 0$.

```cpp
#include <vector>

int missingNumber(const std::vector<int>& nums) {
    int n = nums.size();
    int xor1 = 0, xor2 = 0;
    
    for (int i = 0; i < n; ++i) {
        xor1 ^= nums[i];
        xor2 ^= (i + 1);
    }
    
    return xor1 ^ xor2;
}
```

**Complexity:**
- Time: $O(n)$, single pass to compute the XORs.
- Space: $O(1)$, only maintaining two integer variables.

**Practice:** https://leetcode.com/problems/missing-number/

### Maximum Consecutive Ones
Given a binary array, return the maximum number of consecutive `1`s in the array.

**Intuition:**
Iterate through the array, keeping a running count of `1`s. Whenever a `0` is encountered, reset the count. Update the maximum count at each `1`.

```cpp
#include <vector>
#include <algorithm>

int findMaxConsecutiveOnes(const std::vector<int>& nums) {
    int max_count = 0;
    int current_count = 0;
    
    for (int num : nums) {
        if (num == 1) {
            current_count++;
            max_count = std::max(max_count, current_count);
        } else {
            current_count = 0;
        }
    }
    return max_count;
}
```

**Complexity:**
- Time: $O(n)$, checking each array element exactly once.
- Space: $O(1)$, only tracking counts.

**Practice:** https://leetcode.com/problems/max-consecutive-ones/

### Find the Number that Appears Once
Given a non-empty array of integers where every element appears twice except for one, find that single one.

**Intuition:**
A brute force approach checks each number against the rest ($O(n^2)$). A better approach builds a frequency map using a hash table ($O(n)$ time, $O(n)$ space). The optimal solution leverages the XOR bitwise operator: XORing a number with itself yields 0, and XORing with 0 yields the number itself. Thus, XORing all elements together cancels out the paired numbers, leaving only the single number.

```cpp
#include <vector>

int singleNumber(const std::vector<int>& nums) {
    int ans = 0;
    for (int num : nums) {
        ans ^= num;
    }
    return ans;
}
```

**Complexity:**
- Time: $O(n)$, computing the XOR over the array.
- Space: $O(1)$, storing a single variable.

**Practice:** https://leetcode.com/problems/single-number/

### Longest Subarray with Sum K (positives)
Given an array containing only positive integers and a target sum $K$, find the length of the longest subarray whose elements sum to $K$.

**Intuition:**
A brute force checks all subarrays ($O(n^2)$). Since all numbers are positive, the running sum is strictly non-decreasing as the window expands. The optimal approach uses a **sliding window** (two pointers). We expand the right pointer to increase the sum. If the sum exceeds $K$, we shrink from the left until the sum is $\le K$. Whenever the sum exactly equals $K$, we update our maximum length.

```cpp
#include <vector>
#include <algorithm>

int longestSubarrayWithSumK(const std::vector<int>& arr, long long k) {
    int left = 0, right = 0;
    long long sum = arr[0];
    int max_len = 0;
    int n = arr.size();
    
    while (right < n) {
        while (left <= right && sum > k) {
            sum -= arr[left];
            left++;
        }
        
        if (sum == k) {
            max_len = std::max(max_len, right - left + 1);
        }
        
        right++;
        if (right < n) {
            sum += arr[right];
        }
    }
    
    return max_len;
}
```

**Complexity:**
- Time: $O(n)$, as both `left` and `right` traverse the array at most once.
- Space: $O(1)$, using a few tracking variables.

**Practice:** https://www.geeksforgeeks.org/problems/longest-sub-array-with-sum-k0809/1

### Longest Subarray with Sum K (positives + negatives)
Given an array containing positive, negative, and zero integers, find the length of the longest subarray that sums to $K$.

**Intuition:**
The sliding window technique fails here because adding negative numbers can decrease the sum, destroying the monotonic property. We must rely on **prefix sums**. If the prefix sum up to index `i` is $S$, and we seek a subarray ending at `i` with sum $K$, we need to check if there is an earlier prefix sum equal to $S - K$. We store the *first* occurrence of each prefix sum in a hash map to maximize the subarray length.

::: keypoint
When array elements can be negative, sliding window fails. Always pivot to prefix sums combined with a hash map to find earlier states in $O(1)$ time.
:::

```cpp
#include <vector>
#include <unordered_map>
#include <algorithm>

int lenOfLongSubarr(const std::vector<int>& arr, int k) {
    std::unordered_map<long long, int> prefix_map;
    long long sum = 0;
    int max_len = 0;
    
    for (int i = 0; i < arr.size(); ++i) {
        sum += arr[i];
        
        if (sum == k) {
            max_len = std::max(max_len, i + 1);
        }
        
        long long rem = sum - k;
        if (prefix_map.find(rem) != prefix_map.end()) {
            int len = i - prefix_map[rem];
            max_len = std::max(max_len, len);
        }
        
        if (prefix_map.find(sum) == prefix_map.end()) {
            prefix_map[sum] = i;
        }
    }
    
    return max_len;
}
```

**Complexity:**
- Time: $O(n)$ on average, assuming $O(1)$ unordered map insertions and lookups.
- Space: $O(n)$, as the hash map can store up to $n$ distinct prefix sums.

**Practice:** https://www.geeksforgeeks.org/problems/longest-sub-array-with-sum-k0809/1

## Medium Array Problems

### Two Sum
Given an array of integers and a target sum, return the indices of the two numbers that add up to the target. If only checking for existence (or if returning values instead of indices), a two-pointer approach is possible.

**Intuition / approach:**
- **Brute force:** Check all pairs $(i, j)$ with $i < j$ to see if `nums[i] + nums[j] == target`. This takes $O(n^2)$ time.
- **Better (Hashmap):** Iterate through the array while maintaining a hashmap of the elements seen so far and their indices. For each element, check if `target - nums[i]` exists in the hashmap. If it does, we found the pair. This improves the time to $O(n)$ but uses $O(n)$ space.
- **Optimal (Two-pointer on sorted array):** If the array is already sorted (or if we only need to return the numbers rather than their original indices), we can place pointers at the start and end of the array. If the sum is less than the target, move the left pointer right. If the sum is greater, move the right pointer left. This takes $O(n \log n)$ time to sort and $O(n)$ time to find the pair, using $O(1)$ space. For returning the original indices, the hashmap approach is the optimal one.

```cpp
#include <vector>
#include <unordered_map>

using namespace std;

// Hashmap approach (Optimal for returning indices)
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> seen;
    for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        if (seen.find(complement) != seen.end()) {
            return {seen[complement], i};
        }
        seen[nums[i]] = i;
    }
    return {};
}
```

**Complexity:**
- **Time:** $O(n)$ — Single pass through the array, average $O(1)$ lookup and insertion in unordered_map.
- **Space:** $O(n)$ — Hashmap stores up to $n$ elements in the worst case.

**Practice:** https://leetcode.com/problems/two-sum/

### Sort an Array of 0s, 1s and 2s
Given an array consisting only of 0s, 1s, and 2s, sort it in-place without using library sort functions.

**Intuition / approach:**
- **Brute force:** Use a standard sorting algorithm like Merge Sort or Quick Sort. Time complexity $O(n \log n)$.
- **Better:** Count the number of 0s, 1s, and 2s in a first pass. In a second pass, overwrite the array with the counted number of 0s, then 1s, then 2s. This takes $O(n)$ time but requires two passes.
- **Optimal (Dutch National Flag Algorithm):** Use three pointers: `low`, `mid`, and `high`. The goal is to maintain the invariant:
  - `[0, low - 1]` contains 0s
  - `[low, mid - 1]` contains 1s
  - `[mid, high]` is unsorted
  - `[high + 1, n - 1]` contains 2s
  We iterate `mid` from 0 to `high`. If `nums[mid]` is 0, we swap it with `nums[low]`, incrementing both. If it's 1, we just increment `mid`. If it's 2, we swap it with `nums[high]` and decrement `high`.

```cpp
#include <vector>
#include <algorithm>

using namespace std;

void sortColors(vector<int>& nums) {
    int low = 0, mid = 0, high = nums.size() - 1;
    while (mid <= high) {
        if (nums[mid] == 0) {
            swap(nums[low], nums[mid]);
            low++;
            mid++;
        } else if (nums[mid] == 1) {
            mid++;
        } else {
            swap(nums[mid], nums[high]);
            high--;
        }
    }
}
```

**Complexity:**
- **Time:** $O(n)$ — Single pass through the array, each element is processed at most once.
- **Space:** $O(1)$ — Only a few pointers are used.

**Practice:** https://leetcode.com/problems/sort-colors/

::: keypoint
The Dutch National Flag algorithm efficiently partitions an array into three segments in a single pass using three pointers.
:::

### Majority Element I
Find the majority element in an array of size `n`, defined as the element that appears more than `n / 2` times. You may assume that the majority element always exists in the array.

**Intuition / approach:**
- **Brute force:** Count the occurrences of each element using a nested loop. Takes $O(n^2)$ time.
- **Better:** Use a hashmap to store the frequencies of elements. Return the element with a frequency greater than `n / 2`. Takes $O(n)$ time and $O(n)$ space.
- **Optimal (Boyer–Moore Voting Algorithm):** Maintain a candidate for the majority element and a counter. Iterate through the array. If the counter is 0, pick the current element as the candidate and set the counter to 1. If the current element matches the candidate, increment the counter; otherwise, decrement it. Because the majority element appears more than `n / 2` times, it will always survive the cancellation process.

```cpp
#include <vector>

using namespace std;

int majorityElement(vector<int>& nums) {
    int candidate = 0;
    int count = 0;
    
    for (int num : nums) {
        if (count == 0) {
            candidate = num;
        }
        if (num == candidate) {
            count++;
        } else {
            count--;
        }
    }
    
    return candidate;
}
```

**Complexity:**
- **Time:** $O(n)$ — Single pass through the array.
- **Space:** $O(1)$ — Only two variables are used.

**Practice:** https://leetcode.com/problems/majority-element/

::: keypoint
Boyer-Moore Voting Algorithm relies on the fact that if you cancel out each occurrence of an element with a different element, the majority element will eventually be the only one left standing.
:::

### Kadane's Algorithm
Find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

**Intuition / approach:**
- **Brute force:** Check every possible subarray by picking a starting index and an ending index, then computing the sum. Takes $O(n^3)$ or $O(n^2)$ time depending on implementation.
- **Optimal (Kadane's Algorithm):** Keep a running sum as you iterate through the array. If the running sum drops below 0, it is no longer useful for maximizing the sum of future subarrays, so reset it to 0. Keep track of the maximum sum encountered so far.

```cpp
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int maxSubArray(vector<int>& nums) {
    long long maxi = LONG_MIN; 
    long long sum = 0;
    
    for (int num : nums) {
        sum += num;
        if (sum > maxi) {
            maxi = sum;
        }
        // If sum becomes negative, reset it to 0
        if (sum < 0) {
            sum = 0;
        }
    }
    
    return maxi;
}
```

**Complexity:**
- **Time:** $O(n)$ — Single pass through the array.
- **Space:** $O(1)$ — Uses a few variables for tracking max and current sum.

**Practice:** https://leetcode.com/problems/maximum-subarray/

::: keypoint
Kadane's algorithm elegantly drops negative prefix sums because they can never contribute to a larger maximum subarray sum.
:::

### Print the Subarray with Maximum Sum
Instead of just returning the maximum subarray sum, print or return the actual subarray that yields this sum.

**Intuition / approach:**
- **Brute force:** Keep track of the start and end indices in the $O(n^2)$ check.
- **Optimal (Kadane's Algorithm with indices):** Extend Kadane's algorithm by tracking where a potential maximum subarray starts. Whenever we reset `sum` to 0, the next element will be the start of a new subarray. Whenever `sum > maxi`, we update `maxi` and record the current start index and the current element's index as the bounds of the best subarray found so far.

```cpp
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

vector<int> printMaxSubArray(vector<int>& nums) {
    long long maxi = LONG_MIN;
    long long sum = 0;
    int start = 0;
    int ansStart = -1, ansEnd = -1;
    
    for (int i = 0; i < nums.size(); ++i) {
        if (sum == 0) {
            start = i;
        }
        sum += nums[i];
        
        if (sum > maxi) {
            maxi = sum;
            ansStart = start;
            ansEnd = i;
        }
        
        if (sum < 0) {
            sum = 0;
        }
    }
    
    vector<int> result;
    if (ansStart != -1 && ansEnd != -1) {
        for (int i = ansStart; i <= ansEnd; ++i) {
            result.push_back(nums[i]);
        }
    }
    return result;
}
```

**Complexity:**
- **Time:** $O(n)$ — Single pass to find indices, and at most $O(n)$ to copy the subarray.
- **Space:** $O(n)$ — In the worst case, returning the entire array requires $O(n)$ space for the result. Auxiliary space is $O(1)$.

**Practice:** GeeksforGeeks / Striver A2Z sheet

### Stock Buy and Sell
You are given an array `prices` where `prices[i]` is the price of a given stock on the `i`th day. You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.

**Intuition / approach:**
- **Brute force:** For every day, try selling on all future days to see which yields the maximum profit. Takes $O(n^2)$ time.
- **Optimal:** As we iterate through the array, keep track of the minimum price seen so far. The maximum profit if we sell on the current day is the current price minus this minimum price. Track the global maximum profit encountered.

```cpp
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int maxProfit(vector<int>& prices) {
    int minPrice = INT_MAX;
    int maxPro = 0;
    
    for (int price : prices) {
        minPrice = min(minPrice, price);
        maxPro = max(maxPro, price - minPrice);
    }
    
    return maxPro;
}
```

**Complexity:**
- **Time:** $O(n)$ — Single pass through the array.
- **Space:** $O(1)$ — Only a couple of variables are used.

**Practice:** https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

### Rearrange Array Elements by Sign
Given a 0-indexed integer array `nums` of even length consisting of an equal number of positive and negative integers, rearrange the elements such that they alternate in sign, preserving their relative order.

**Intuition / approach:**
- **Brute force:** Create two separate arrays for positive and negative numbers. Iterate through the array to populate these, then merge them back alternately. Takes $O(n)$ time and $O(n)$ extra space.
- **Optimal:** Use a single pass with a result array. Maintain two pointers: one for the next positive position (starts at 0) and one for the next negative position (starts at 1). As we iterate, place the number in its respective position and increment that pointer by 2. This is optimal because the problem requires preserving relative order, which fundamentally requires $O(n)$ extra space.

```cpp
#include <vector>

using namespace std;

vector<int> rearrangeArray(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n, 0);
    int posIndex = 0, negIndex = 1;
    
    for (int i = 0; i < n; i++) {
        if (nums[i] > 0) {
            ans[posIndex] = nums[i];
            posIndex += 2;
        } else {
            ans[negIndex] = nums[i];
            negIndex += 2;
        }
    }
    
    return ans;
}
```

**Complexity:**
- **Time:** $O(n)$ — Single pass through the array.
- **Space:** $O(n)$ — Required for the resulting array.

**Practice:** https://leetcode.com/problems/rearrange-array-elements-by-sign/

### Next Permutation
Find the next lexicographically greater permutation of an array of numbers. If such arrangement is not possible, the array must be rearranged as the lowest possible order (i.e., sorted in ascending order).

**Intuition / approach:**
- **Brute force:** Generate all possible permutations in lexicographical order, find the current one, and return the next. Takes $O(n! \times n)$ time.
- **Better:** Use C++ STL `next_permutation()`, though the goal in an interview is often to implement it.
- **Optimal:**
  1. Find the first element from the right that breaks the descending order (i.e., `nums[i] < nums[i+1]`). Call this index `ind`.
  2. If no such element exists, the array is entirely in descending order. Reverse it to get the smallest permutation.
  3. If `ind` exists, find the smallest element from the right that is strictly greater than `nums[ind]`. Swap them.
  4. Finally, reverse the suffix array from `ind + 1` to the end to get the smallest lexicographical order for the remaining suffix.

```cpp
#include <vector>
#include <algorithm>

using namespace std;

void nextPermutation(vector<int>& nums) {
    int n = nums.size();
    int ind = -1;
    
    // Step 1: Find the break point
    for (int i = n - 2; i >= 0; i--) {
        if (nums[i] < nums[i + 1]) {
            ind = i;
            break;
        }
    }
    
    // Step 2: If no break point, reverse the whole array
    if (ind == -1) {
        reverse(nums.begin(), nums.end());
        return;
    }
    
    // Step 3: Find the next greater element and swap
    for (int i = n - 1; i > ind; i--) {
        if (nums[i] > nums[ind]) {
            swap(nums[i], nums[ind]);
            break;
        }
    }
    
    // Step 4: Reverse the right half
    reverse(nums.begin() + ind + 1, nums.end());
}
```

**Complexity:**
- **Time:** $O(n)$ — Finding the break point, finding the swap candidate, and reversing the suffix all take linear time.
- **Space:** $O(1)$ — Sorting/swapping happens in place.

**Practice:** https://leetcode.com/problems/next-permutation/

::: keypoint
The suffix after the break point is always monotonically decreasing, which allows us to simply reverse it instead of sorting.
:::

### Leaders in an Array
An element is a leader if it is strictly greater than all elements to its right side. Find all the leaders in an array.

**Intuition / approach:**
- **Brute force:** For each element, iterate through all elements to its right to check if it's strictly greater. Takes $O(n^2)$ time.
- **Optimal (Scan from right):** Start traversing from the rightmost element. Keep track of the maximum element seen so far. If the current element is strictly greater than the maximum seen, it is a leader. Update the maximum and add the element to the results. Reverse the results at the end if the leaders must be reported in original left-to-right order.

```cpp
#include <vector>
#include <algorithm>

using namespace std;

vector<int> leaders(vector<int>& nums) {
    vector<int> ans;
    int n = nums.size();
    if (n == 0) return ans;
    
    int maxi = nums[n - 1];
    ans.push_back(maxi); // Rightmost is always a leader
    
    for (int i = n - 2; i >= 0; i--) {
        if (nums[i] > maxi) {
            ans.push_back(nums[i]);
            maxi = nums[i];
        }
    }
    
    // Reverse to get the leaders in original array order
    reverse(ans.begin(), ans.end());
    return ans;
}
```

**Complexity:**
- **Time:** $O(n)$ — Single pass from right to left, plus an $O(n)$ reverse.
- **Space:** $O(n)$ — To store the leaders in the worst case (e.g., array is strictly decreasing).

**Practice:** GeeksforGeeks: Leaders in an array

### Longest Consecutive Sequence
Given an unsorted array of integers, return the length of the longest consecutive elements sequence.

**Intuition / approach:**
- **Brute force:** Sort the array and then iterate to find the longest sequence. Takes $O(n \log n)$ time.
- **Optimal (Hash set):** Insert all elements into an unordered set to allow $O(1)$ lookups. Then, iterate through the set. For each element, check if it is the *start* of a sequence (i.e., `num - 1` does not exist in the set). If it is a starting number, keep checking for `num + 1`, `num + 2`, etc., tracking the length of the sequence. This ensures each element is visited at most twice.

```cpp
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

int longestConsecutive(vector<int>& nums) {
    unordered_set<int> st(nums.begin(), nums.end());
    int longest = 0;
    
    for (int num : st) {
        // Only start counting if 'num' is the first element of a sequence
        if (st.find(num - 1) == st.end()) {
            int currentNum = num;
            int currentStreak = 1;
            
            while (st.find(currentNum + 1) != st.end()) {
                currentNum += 1;
                currentStreak += 1;
            }
            
            longest = max(longest, currentStreak);
        }
    }
    
    return longest;
}
```

**Complexity:**
- **Time:** $O(n)$ — Each number is inserted into the set ($O(1)$ average), and each sequence is iterated over exactly once.
- **Space:** $O(n)$ — To store the hash set.

**Practice:** https://leetcode.com/problems/longest-consecutive-sequence/

::: keypoint
By only building a sequence when `num - 1` is absent, we guarantee that the inner `while` loop only runs $n$ times total across all iterations, preserving $O(n)$ time complexity.
:::

### Set Matrix Zeroes
Given an $m \times n$ integer matrix, if an element is 0, set its entire row and column to 0's. You must do it in place.

**Intuition / approach:**
- **Brute force:** Iterate through the matrix. Whenever a 0 is found, mark its row and column with a placeholder (like -1, assuming -1 is not a valid matrix value) to avoid cascading. Finally, replace all placeholders with 0s. This takes $O(m \times n \times (m + n))$ time.
- **Better:** Use two separate boolean arrays to keep track of which rows and columns need to be zeroed. Takes $O(m \times n)$ time and $O(m + n)$ space.
- **Optimal (In-place markers):** Use the first row and first column of the matrix itself to store the zeroing flags. Since the first element `matrix[0][0]` represents both the first row and first column, use an extra variable (`col0`) to track the state of the first column separately. Traverse the matrix leaving markers, then traverse again to apply zeroes based on the markers, and finally update the first row and column.

```cpp
#include <vector>

using namespace std;

void setZeroes(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    int col0 = 1;
    
    // First pass: set markers in first row and column
    for (int i = 0; i < m; i++) {
        if (matrix[i][0] == 0) col0 = 0;
        for (int j = 1; j < n; j++) {
            if (matrix[i][j] == 0) {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }
    
    // Second pass: use markers to set zeroes (skip first row/col)
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                matrix[i][j] = 0;
            }
        }
    }
    
    // Third pass: set first row zeroes
    if (matrix[0][0] == 0) {
        for (int j = 0; j < n; j++) {
            matrix[0][j] = 0;
        }
    }
    
    // Fourth pass: set first column zeroes
    if (col0 == 0) {
        for (int i = 0; i < m; i++) {
            matrix[i][0] = 0;
        }
    }
}
```

**Complexity:**
- **Time:** $O(m \times n)$ — Two full passes over the matrix.
- **Space:** $O(1)$ — Markers are kept within the given matrix.

**Practice:** https://leetcode.com/problems/set-matrix-zeroes/

### Rotate Matrix by 90 Degrees
You are given an $n \times n$ 2D matrix representing an image, rotate the image by 90 degrees (clockwise). You have to rotate the image in-place.

**Intuition / approach:**
- **Brute force:** Create a new $n \times n$ matrix. Iterate through the original matrix and place each element at its new position: `newMatrix[j][n - 1 - i] = matrix[i][j]`. Takes $O(n^2)$ time and $O(n^2)$ extra space.
- **Optimal (Transpose + Reverse):** A 90-degree clockwise rotation is mathematically equivalent to transposing the matrix (swapping `matrix[i][j]` with `matrix[j][i]`), and then reversing each individual row. This modifies the matrix in place.

```cpp
#include <vector>
#include <algorithm>

using namespace std;

void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    
    // Step 1: Transpose the matrix
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    
    // Step 2: Reverse each row
    for (int i = 0; i < n; i++) {
        reverse(matrix[i].begin(), matrix[i].end());
    }
}
```

**Complexity:**
- **Time:** $O(n^2)$ — Visiting each element for transposing and reversing.
- **Space:** $O(1)$ — Entirely in-place swaps.

**Practice:** https://leetcode.com/problems/rotate-image/

### Print the Matrix in Spiral Manner
Given an $m \times n$ matrix, return all elements of the matrix in spiral order.

**Intuition / approach:**
- **Optimal:** Maintain four boundaries: `top`, `bottom`, `left`, and `right`. Use a while loop that runs as long as `top <= bottom` and `left <= right`. Traverse from left to right along the `top` row, then increment `top`. Next, traverse down the `right` column, then decrement `right`. Next, if `top <= bottom`, traverse right to left along the `bottom` row and decrement `bottom`. Finally, if `left <= right`, traverse up the `left` column and increment `left`. This peeling of boundaries produces the spiral.

```cpp
#include <vector>

using namespace std;

vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<int> ans;
    if (matrix.empty() || matrix[0].empty()) return ans;
    
    int top = 0, bottom = matrix.size() - 1;
    int left = 0, right = matrix[0].size() - 1;
    
    while (top <= bottom && left <= right) {
        // Traverse Right
        for (int i = left; i <= right; i++) {
            ans.push_back(matrix[top][i]);
        }
        top++;
        
        // Traverse Down
        for (int i = top; i <= bottom; i++) {
            ans.push_back(matrix[i][right]);
        }
        right--;
        
        // Traverse Left
        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                ans.push_back(matrix[bottom][i]);
            }
            bottom--;
        }
        
        // Traverse Up
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                ans.push_back(matrix[i][left]);
            }
            left++;
        }
    }
    
    return ans;
}
```

**Complexity:**
- **Time:** $O(m \times n)$ — Each element is visited exactly once.
- **Space:** $O(m \times n)$ — Storing the answer array (or $O(1)$ auxiliary space if returning the result isn't counted).

**Practice:** https://leetcode.com/problems/spiral-matrix/

## Hard Array Problems

### Count Subarrays with Given Sum
Given an array of integers and an integer `k`, find the total number of continuous subarrays whose sum equals to `k`.

**Intuition / approach:**
The brute force approach is to check every possible subarray using two loops and sum their elements (or three loops without a running sum), but this takes $O(n^2)$ time. A better, optimal approach uses the **prefix-sum** technique alongside a hashmap. We maintain a running prefix sum as we iterate. If the current prefix sum is `sum`, and we've seen a prefix sum of `sum - k` earlier, it means the subarray between that previous point and the current point sums to `k`. The hashmap stores the frequency of each prefix sum encountered so far. We initialize the hashmap with `(0, 1)` to handle subarrays starting from index 0.

```cpp
#include <vector>
#include <unordered_map>

using namespace std;

int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefixCounts;
    prefixCounts[0] = 1;
    
    int currentSum = 0;
    int count = 0;
    
    for (int num : nums) {
        currentSum += num;
        
        if (prefixCounts.find(currentSum - k) != prefixCounts.end()) {
            count += prefixCounts[currentSum - k];
        }
        
        prefixCounts[currentSum]++;
    }
    
    return count;
}
```
**Complexity:** $O(n)$ time on average (hashmap operations), $O(n)$ space for the hashmap.
**Practice:** https://leetcode.com/problems/subarray-sum-equals-k/

### Pascal's Triangle
Given an integer `numRows`, generate the first `numRows` of Pascal's triangle. (Variant 1: generate whole triangle. Variant 2: get specific row. Variant 3: get element at (r, c)).

**Intuition / approach:**
The naive way to compute the whole triangle is using the recursive relation $C(n, k) = C(n-1, k-1) + C(n-1, k)$, but this can be slow if not memoized. A better approach generates the triangle row by row: each row starts and ends with 1, and the inner elements are the sum of the two elements directly above them from the previous row. 
For generating a specific row or element (Variant 2 & 3), we can use combinatorics: the element at row `r` and column `c` (0-indexed) is $\binom{r}{c}$. We can compute this in $O(r)$ time instead of generating the full triangle up to that point.

```cpp
#include <vector>

using namespace std;

// Variant 1: Generate the entire triangle
vector<vector<int>> generate(int numRows) {
    vector<vector<int>> triangle;
    for (int i = 0; i < numRows; ++i) {
        vector<int> row(i + 1, 1);
        for (int j = 1; j < i; ++j) {
            row[j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }
        triangle.push_back(row);
    }
    return triangle;
}

// Variant 2: Get a specific row (0-indexed)
vector<int> getRow(int rowIndex) {
    vector<int> row;
    long long ans = 1;
    row.push_back(1);
    for (int i = 1; i <= rowIndex; ++i) {
        ans = ans * (rowIndex - i + 1) / i;
        row.push_back((int)ans);
    }
    return row;
}

// Variant 3: Get element at r, c (0-indexed)
int getElement(int r, int c) {
    long long ans = 1;
    for (int i = 0; i < c; ++i) {
        ans = ans * (r - i) / (i + 1);
    }
    return (int)ans;
}
```
**Complexity:** $O(n^2)$ time and space for generating the full triangle. $O(n)$ time and $O(n)$ space for a specific row. $O(c)$ time and $O(1)$ space for a specific element.
**Practice:** https://leetcode.com/problems/pascals-triangle/

### Majority Element II
Given an integer array of size `n`, find all elements that appear more than `\lfloor n/3 \rfloor` times.

**Intuition / approach:**
A brute force approach checks the count of every element in $O(n^2)$ time. A better approach uses a hashmap to count frequencies in $O(n)$ time but takes $O(n)$ extra space. The optimal approach is an extension of the **Boyer–Moore Voting Algorithm**. Since we want elements appearing strictly more than $n/3$ times, there can be at most two such elements. We keep track of two potential candidates and their counts. If we see a candidate, we increment its count; if a count is 0, we assign a new candidate; otherwise, we decrement both counts. After finding the two potential candidates, we do a second pass to verify if their actual counts exceed $n/3$.

```cpp
#include <vector>

using namespace std;

vector<int> majorityElement(vector<int>& nums) {
    int count1 = 0, count2 = 0;
    int candidate1 = -1, candidate2 = -1;
    
    // Pass 1: Find potential candidates
    for (int num : nums) {
        if (count1 > 0 && num == candidate1) {
            count1++;
        } else if (count2 > 0 && num == candidate2) {
            count2++;
        } else if (count1 == 0) {
            candidate1 = num;
            count1 = 1;
        } else if (count2 == 0) {
            candidate2 = num;
            count2 = 1;
        } else {
            count1--;
            count2--;
        }
    }
    
    // Pass 2: Verify candidates
    vector<int> result;
    count1 = 0; count2 = 0;
    for (int num : nums) {
        if (num == candidate1) count1++;
        else if (num == candidate2) count2++;
    }
    
    int n = nums.size();
    if (count1 > n / 3) result.push_back(candidate1);
    if (count2 > n / 3) result.push_back(candidate2);
    
    return result;
}
```
**Complexity:** $O(n)$ time (two passes), $O(1)$ auxiliary space.
**Practice:** https://leetcode.com/problems/majority-element-ii/

### 3 Sum
Given an integer array `nums`, return all the triplets `[nums[i], nums[j], nums[k]]` such that `i != j`, `i != k`, and `j != k`, and `nums[i] + nums[j] + nums[k] == 0`. Notice that the solution set must not contain duplicate triplets.

**Intuition / approach:**
The brute force solution involves three nested loops, giving $O(n^3)$ time, which is too slow. A better approach uses two loops and a hashset to find the third element, taking $O(n^2)$ time but $O(n)$ space, with duplicate handling being cumbersome. The optimal approach is to **sort the array** and use a **two-pointer** technique. For each element `nums[i]`, we set a left pointer at `i + 1` and a right pointer at the end of the array. We then search for a sum of 0. If the sum is too small, we move the left pointer right; if it's too large, we move the right pointer left. Crucially, we skip adjacent duplicate elements for `i`, `left`, and `right` to avoid duplicate triplets.

```cpp
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());
    int n = nums.size();
    
    for (int i = 0; i < n; i++) {
        // Skip duplicate elements for the first number
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        
        int left = i + 1;
        int right = n - 1;
        
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            
            if (sum < 0) {
                left++;
            } else if (sum > 0) {
                right--;
            } else {
                result.push_back({nums[i], nums[left], nums[right]});
                left++;
                right--;
                
                // Skip duplicate elements for the second and third numbers
                while (left < right && nums[left] == nums[left - 1]) left++;
                while (left < right && nums[right] == nums[right + 1]) right--;
            }
        }
    }
    
    return result;
}
```

::: keypoint
Sorting the array first makes it trivial to skip duplicates and enables the $O(n^2)$ two-pointer scan.
:::

**Complexity:** $O(n^2)$ time ($O(n \log n)$ for sorting + $O(n^2)$ for nested loops). Space is $O(1)$ auxiliary (or $O(n)$ depending on the sorting algorithm implementation).
**Practice:** https://leetcode.com/problems/3sum/

### 4 Sum
Given an array `nums` of `n` integers, return an array of all the unique quadruplets `[nums[a], nums[b], nums[c], nums[d]]` such that the sum of the elements is `target`.

**Intuition / approach:**
Similar to 3 Sum, a brute force 4-loop is $O(n^4)$. We optimize this by sorting the array and using two outer loops with a **two-pointer** inner scan, dropping the time to $O(n^3)$. We must be careful to avoid overflow when summing four integers; we cast to `long long` before summing. As with 3 Sum, we skip duplicates at every level to ensure unique quadruplets.

```cpp
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> fourSum(vector<int>& nums, int target) {
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());
    int n = nums.size();
    
    for (int i = 0; i < n; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        
        for (int j = i + 1; j < n; j++) {
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;
            
            int left = j + 1;
            int right = n - 1;
            
            while (left < right) {
                long long sum = (long long)nums[i] + nums[j] + nums[left] + nums[right];
                
                if (sum < target) {
                    left++;
                } else if (sum > target) {
                    right--;
                } else {
                    result.push_back({nums[i], nums[j], nums[left], nums[right]});
                    left++;
                    right--;
                    
                    while (left < right && nums[left] == nums[left - 1]) left++;
                    while (left < right && nums[right] == nums[right + 1]) right--;
                }
            }
        }
    }
    
    return result;
}
```
**Complexity:** $O(n^3)$ time, $O(1)$ auxiliary space (ignoring sorting overhead).
**Practice:** https://leetcode.com/problems/4sum/

### Largest Subarray with Sum 0
Given an array having both positive and negative integers. The task is to compute the length of the largest subarray with sum 0.

**Intuition / approach:**
The brute force solution computes the sum of every possible subarray in $O(n^2)$ time and updates the maximum length when a sum of 0 is found. The optimal approach uses **prefix sums** and a hashmap. We iterate through the array, maintaining a running prefix sum. If the prefix sum is 0, the subarray from the start to the current index has a sum of 0. If the prefix sum has been seen before (stored in our hashmap), it means the elements between the first occurrence of this prefix sum and the current index sum to 0. We store the *first* index where each prefix sum is encountered to maximize the subarray length.

```cpp
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int maxLen(vector<int>& arr) {
    unordered_map<int, int> prefixIndices;
    int max_len = 0;
    int current_sum = 0;
    
    for (int i = 0; i < arr.size(); i++) {
        current_sum += arr[i];
        
        if (current_sum == 0) {
            max_len = i + 1;
        } else {
            if (prefixIndices.find(current_sum) != prefixIndices.end()) {
                max_len = max(max_len, i - prefixIndices[current_sum]);
            } else {
                prefixIndices[current_sum] = i;
            }
        }
    }
    
    return max_len;
}
```
**Complexity:** $O(n)$ expected time, $O(n)$ space for the hashmap.
**Practice:** https://www.geeksforgeeks.org/find-the-largest-subarray-with-0-sum/

### Count Subarrays with Given XOR K
Given an array of integers `A` and an integer `B`. Find the total number of subarrays having bitwise XOR of all elements equals to `B`.

**Intuition / approach:**
Brute force takes $O(n^2)$ by computing the XOR of all subarrays. The optimal approach mirrors "Count Subarrays with Given Sum" but replaces addition with XOR. We maintain a running prefix XOR. A fundamental property of XOR is that if `x ^ y = k`, then `x ^ k = y`. If our current prefix XOR is `current_xor`, we want to find how many previous prefixes had an XOR of `current_xor ^ B`. We use a hashmap to store the frequencies of prefix XORs encountered.

```cpp
#include <vector>
#include <unordered_map>

using namespace std;

int solve(vector<int>& A, int B) {
    unordered_map<int, int> prefixXORCounts;
    prefixXORCounts[0] = 1;
    
    int current_xor = 0;
    int count = 0;
    
    for (int num : A) {
        current_xor ^= num;
        
        int target = current_xor ^ B;
        if (prefixXORCounts.find(target) != prefixXORCounts.end()) {
            count += prefixXORCounts[target];
        }
        
        prefixXORCounts[current_xor]++;
    }
    
    return count;
}
```

::: keypoint
The identity `x ^ k = y` allows the prefix-sum hashmap technique to work perfectly for XOR queries.
:::

**Complexity:** $O(n)$ expected time, $O(n)$ space.
**Practice:** https://www.interviewbit.com/problems/subarray-with-given-xor/

### Merge Overlapping Subintervals
Given an array of `intervals` where `intervals[i] = [start_i, end_i]`, merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.

**Intuition / approach:**
Brute force involves comparing every interval with every other interval to merge them, which is $O(n^2)$. The optimal approach is to **sort the intervals based on their starting times**. Once sorted, overlapping intervals will be adjacent. We iterate through the sorted intervals, maintaining a list of merged intervals. If the current interval overlaps with the last merged interval (i.e., its start is less than or equal to the last merged interval's end), we update the end of the last merged interval. Otherwise, we add the current interval as a new merged interval.

```cpp
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> merge(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};
    
    // Sort by starting time
    sort(intervals.begin(), intervals.end());
    
    vector<vector<int>> merged;
    merged.push_back(intervals[0]);
    
    for (int i = 1; i < intervals.size(); i++) {
        // Overlap condition
        if (intervals[i][0] <= merged.back()[1]) {
            merged.back()[1] = max(merged.back()[1], intervals[i][1]);
        } else {
            merged.push_back(intervals[i]);
        }
    }
    
    return merged;
}
```
**Complexity:** $O(n \log n)$ time due to sorting, $O(1)$ auxiliary space (excluding the output array).
**Practice:** https://leetcode.com/problems/merge-intervals/

### Merge Two Sorted Arrays Without Extra Space
Given two sorted arrays `arr1` and `arr2` of sizes `n` and `m` in non-decreasing order. Merge them in sorted order without using any extra space.

**Intuition / approach:**
A naive approach uses a third array of size $n+m$ to store the merged result, taking $O(n+m)$ space. A better approach (two pointers) compares elements and swaps when necessary, sorting the second array after each swap, but this can take $O(n \times m)$ time. The optimal optimal approach uses the **gap method**, inspired by Shell Sort. We start with an initial gap of $\lceil (n+m)/2 \rceil$. We compare elements separated by the gap across both arrays, swapping them if they are out of order. We then reduce the gap to $\lceil \text{gap}/2 \rceil$ and repeat until the gap becomes 0.

```cpp
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void merge(long long arr1[], long long arr2[], int n, int m) {
    int len = n + m;
    int gap = (len / 2) + (len % 2);
    
    while (gap > 0) {
        int left = 0;
        int right = left + gap;
        
        while (right < len) {
            // Both pointers in arr2
            if (left >= n) {
                if (arr2[left - n] > arr2[right - n]) {
                    swap(arr2[left - n], arr2[right - n]);
                }
            }
            // left in arr1, right in arr2
            else if (left < n && right >= n) {
                if (arr1[left] > arr2[right - n]) {
                    swap(arr1[left], arr2[right - n]);
                }
            }
            // Both pointers in arr1
            else {
                if (arr1[left] > arr1[right]) {
                    swap(arr1[left], arr1[right]);
                }
            }
            left++;
            right++;
        }
        
        if (gap == 1) break;
        gap = (gap / 2) + (gap % 2);
    }
}
```
**Complexity:** $O((n+m) \log(n+m))$ time, $O(1)$ space.
**Practice:** https://www.geeksforgeeks.org/merge-two-sorted-arrays-o1-extra-space/

### Find the Repeating and Missing Number
You are given a read only array of `n` integers from 1 to `n`. Each integer appears exactly once except A which appears twice and B which is missing.

**Intuition / approach:**
Brute force counts the frequency of each number using nested loops ($O(n^2)$). A better approach uses a frequency array/hashmap taking $O(n)$ space. An optimal approach uses math (sum of first $n$ numbers and sum of squares of first $n$ numbers) to form two equations with two variables ($x-y$ and $x^2-y^2$). Another optimal approach uses bit manipulation (XOR), similar to finding two unique numbers in an array where others appear twice. The math approach is simpler to write but can risk integer overflow if `n` is large (so we use `long long`).

```cpp
#include <vector>

using namespace std;

vector<int> repeatedNumber(const vector<int> &A) {
    long long n = A.size();
    
    long long sum_n = (n * (n + 1)) / 2;
    long long sum_sq_n = (n * (n + 1) * (2 * n + 1)) / 6;
    
    long long sum_a = 0;
    long long sum_sq_a = 0;
    
    for (int num : A) {
        sum_a += (long long)num;
        sum_sq_a += (long long)num * (long long)num;
    }
    
    // sum_a - sum_n = X - Y (where X is repeating, Y is missing)
    long long val1 = sum_a - sum_n;
    
    // sum_sq_a - sum_sq_n = X^2 - Y^2
    long long val2 = sum_sq_a - sum_sq_n;
    
    // X + Y = (X^2 - Y^2) / (X - Y)
    val2 = val2 / val1;
    
    long long x = (val1 + val2) / 2;
    long long y = x - val1;
    
    return {(int)x, (int)y};
}
```
**Complexity:** $O(n)$ time, $O(1)$ space.
**Practice:** https://www.interviewbit.com/problems/repeat-and-missing-number-array/

### Count Inversions
Given an array of integers, find the inversion count in the array. Two elements `a[i]` and `a[j]` form an inversion if `a[i] > a[j]` and `i < j`.

**Intuition / approach:**
The brute force solution checks every pair using two nested loops in $O(n^2)$ time. The optimal approach is a modification of **Merge Sort**. While merging two sorted halves (say `left` and `right`), if `left[i] > right[j]`, then all elements from `left[i]` to the end of the `left` half will also be greater than `right[j]` (because the `left` half is sorted). Thus, we can count `mid - i + 1` inversions at once and move the `j` pointer forward.

```cpp
#include <vector>

using namespace std;

long long mergeAndCount(vector<long long>& arr, int left, int mid, int right) {
    vector<long long> temp;
    int i = left;
    int j = mid + 1;
    long long invCount = 0;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i++]);
        } else {
            temp.push_back(arr[j++]);
            invCount += (mid - i + 1); // Count inversions
        }
    }
    
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);
    
    for (int k = left; k <= right; k++) {
        arr[k] = temp[k - left];
    }
    
    return invCount;
}

long long mergeSortAndCount(vector<long long>& arr, int left, int right) {
    long long invCount = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        invCount += mergeSortAndCount(arr, left, mid);
        invCount += mergeSortAndCount(arr, mid + 1, right);
        invCount += mergeAndCount(arr, left, mid, right);
    }
    return invCount;
}

long long getInversions(vector<long long> arr, int n) {
    return mergeSortAndCount(arr, 0, n - 1);
}
```

::: keypoint
Piggybacking on merge sort allows us to count $O(n^2)$ potential inversions in just $O(n \log n)$ time.
:::

**Complexity:** $O(n \log n)$ time, $O(n)$ auxiliary space for the temporary merge array.
**Practice:** https://www.naukri.com/code360/problems/count-inversions_615

### Reverse Pairs
Given an integer array `nums`, return the number of reverse pairs in the array. A reverse pair is a pair `(i, j)` where `i < j` and `nums[i] > 2 * nums[j]`.

**Intuition / approach:**
Brute force pairs check takes $O(n^2)$ time. This is a direct variant of counting inversions, so we again modify **Merge Sort**. Unlike simple inversions, we cannot count reverse pairs *during* the standard merge step because the condition `nums[i] > 2 * nums[j]` might not imply that elements can be safely merged in that same order. Instead, *before* merging the two sorted halves, we use two pointers to count the valid pairs. For each element in the left half, we advance a pointer in the right half as long as the condition holds, adding the count.

```cpp
#include <vector>

using namespace std;

void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp;
    int i = left;
    int j = mid + 1;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i++]);
        } else {
            temp.push_back(arr[j++]);
        }
    }
    
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);
    
    for (int k = left; k <= right; k++) {
        arr[k] = temp[k - left];
    }
}

int countPairs(vector<int>& arr, int left, int mid, int right) {
    int count = 0;
    int j = mid + 1;
    
    for (int i = left; i <= mid; i++) {
        while (j <= right && arr[i] > 2LL * arr[j]) {
            j++;
        }
        count += (j - (mid + 1));
    }
    return count;
}

int mergeSort(vector<int>& arr, int left, int right) {
    int count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        count += mergeSort(arr, left, mid);
        count += mergeSort(arr, mid + 1, right);
        count += countPairs(arr, left, mid, right);
        merge(arr, left, mid, right);
    }
    return count;
}

int reversePairs(vector<int>& nums) {
    return mergeSort(nums, 0, nums.size() - 1);
}
```
**Complexity:** $O(n \log n)$ time (counting pairs takes $O(n)$ in total across the merge step), $O(n)$ auxiliary space.
**Practice:** https://leetcode.com/problems/reverse-pairs/

### Maximum Product Subarray
Given an integer array `nums`, find a subarray that has the largest product, and return the product.

**Intuition / approach:**
Brute force computes the product of all possible subarrays in $O(n^2)$. A better approach tries to adapt Kadane's algorithm by tracking both the maximum and minimum product ending at each position (since a negative number multiplied by the minimum negative product becomes a large positive product). An even simpler optimal approach observes that if the array has no zeros, the maximum product is either a prefix product or a suffix product. Zeros reset the contiguous product to 0. Thus, we can compute prefix products and suffix products in two sweeps (or one simultaneous sweep) and take the maximum.

```cpp
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int maxProduct(vector<int>& nums) {
    int n = nums.size();
    long long max_prod = LLONG_MIN;
    long long prefix = 1, suffix = 1;
    
    for (int i = 0; i < n; i++) {
        if (prefix == 0) prefix = 1;
        if (suffix == 0) suffix = 1;
        
        prefix *= nums[i];
        suffix *= nums[n - i - 1];
        
        max_prod = max(max_prod, max(prefix, suffix));
    }
    
    return max_prod;
}
```
**Complexity:** $O(n)$ time, $O(1)$ auxiliary space.
**Practice:** https://leetcode.com/problems/maximum-product-subarray/

::: interview
What interviewers probe here: recognizing array patterns on sight. You should immediately map range sums/XORs to **prefix sums**, subarray contiguous sums to **Kadane's**, counting pairs with comparisons to **merge sort**, space-optimized counting to **Boyer–Moore**, 0/1/2 sorting to **Dutch-flag**, and $O(n^2)$ pair scanning to **two-pointers** on a sorted array.
:::
