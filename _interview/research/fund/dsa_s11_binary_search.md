# Binary Search

::: heavy
Binary search operates on a sorted or monotonic space to locate a target in logarithmic time. A robust binary search uses an invariant-based template: the target always exists within the search window `[lo, hi]`. At each step, a midpoint is evaluated, and the search space is halved while strictly maintaining this invariant. This same template extends beyond exact matching to finding boundaries—specifically, the lower bound (the first element $\ge$ target) and the upper bound (the first element $>$ target). These boundary templates map directly to the STL functions `std::lower_bound` and `std::upper_bound` (covered in Part I).
:::

A critical step in any template is finding the midpoint safely.

::: trap
Writing `int mid = (lo + hi) / 2;` can cause an integer overflow if `lo` and `hi` are large, resulting in a negative midpoint and a segmentation fault. Always use the overflow-safe formula: `int mid = lo + (hi - lo) / 2;`.
:::

::: keypoint
Almost every binary search bug stems from an off-by-one error in the boundary update (e.g., writing `lo = mid` instead of `lo = mid + 1`, causing an infinite loop). Pick ONE template for exact matches and ONE for boundaries, and keep it consistently.
:::

## Binary Search on 1D Arrays

### Search X in a Sorted Array
Given a sorted array of distinct integers and a target integer `X`, return the index if the target is found. If not, return `-1`.

**Intuition / approach**: 
A brute force linear scan checks every element, taking $O(n)$ time. Since the array is sorted, this is unnecessary. We can check the middle element. If it matches `X`, we return its index. If it is less than `X`, the target must reside in the right half, so we discard the left half. If it is greater than `X`, we discard the right half. This halves the search space at each step until the target is found or the space is exhausted.

**C++ solution**:
```cpp
#include <vector>

int search(const std::vector<int>& nums, int target) {
    int lo = 0;
    int hi = nums.size() - 1;
    
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return -1;
}
```

**Complexity**: 
- **Time:** $O(\log n)$ because the search space is halved at each step.
- **Space:** $O(1)$ as only a few integer variables are used.

**Practice:** https://leetcode.com/problems/binary-search/

### Lower Bound
Implement the lower bound function: given a sorted array and a target, find the index of the first element that is greater than or equal to the target. If all elements are smaller, return the array size.

**Intuition / approach**: 
The brute force approach is to scan from the beginning until a value $\ge$ target is found. Optimally, we can use binary search. We maintain a variable `ans` initialized to the array size. At each step, if the middle element is greater than or equal to the target, it is a potential answer, so we record its index and search the left half for an even earlier occurrence. If it is less than the target, the lower bound must be in the right half.

**C++ solution**:
```cpp
#include <vector>

int lowerBound(const std::vector<int>& arr, int target) {
    int lo = 0;
    int hi = arr.size() - 1;
    int ans = arr.size();
    
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] >= target) {
            ans = mid;
            hi = mid - 1; // Look for smaller index on the left
        } else {
            lo = mid + 1; // Target is greater, look on the right
        }
    }
    return ans;
}
```

**Complexity**: 
- **Time:** $O(\log n)$ because the search space is halved iteratively.
- **Space:** $O(1)$ auxiliary space used.

**Practice:** https://www.geeksforgeeks.org/problems/floor-in-a-sorted-array-1587115620/1

### Upper Bound
Implement the upper bound function: given a sorted array and a target, find the index of the first element that is strictly greater than the target. If all elements are smaller than or equal to the target, return the array size.

**Intuition / approach**: 
Similar to the lower bound, a linear search is $O(n)$. For an optimal $O(\log n)$ approach, we perform binary search. If the middle element is strictly greater than the target, we record its index as a potential answer and continue searching the left half to find an earlier index. If it is less than or equal to the target, the upper bound must be in the right half.

**C++ solution**:
```cpp
#include <vector>

int upperBound(const std::vector<int>& arr, int target) {
    int lo = 0;
    int hi = arr.size() - 1;
    int ans = arr.size();
    
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] > target) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}
```

**Complexity**: 
- **Time:** $O(\log n)$ as the array is split in half each iteration.
- **Space:** $O(1)$ requiring only pointers.

**Practice:** https://www.geeksforgeeks.org/problems/floor-in-a-sorted-array-1587115620/1

### Search Insert Position
Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

**Intuition / approach**: 
This is exactly the definition of the lower bound. We need to find the first index where the element is greater than or equal to the target. If the target exists, lower bound gives its exact index. If it doesn't exist, lower bound gives the index where the target should be inserted to maintain sorted order.

**C++ solution**:
```cpp
#include <vector>

int searchInsert(const std::vector<int>& nums, int target) {
    int lo = 0;
    int hi = nums.size() - 1;
    int ans = nums.size();
    
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] >= target) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}
```

**Complexity**: 
- **Time:** $O(\log n)$ to binary search the insertion point.
- **Space:** $O(1)$ constant extra space.

**Practice:** https://leetcode.com/problems/search-insert-position/

### Floor and Ceil in a Sorted Array
Given a sorted array and a value `x`, find the floor (largest element $\le x$) and ceiling (smallest element $\ge x$) of `x` in the array. If they do not exist, return `-1`.

**Intuition / approach**: 
The ceiling of `x` is simply the lower bound of `x`. The floor of `x` can be found similarly: whenever we see an element $\le x$ at the midpoint, it is a potential floor, so we record it and search the right half for a potentially larger element that is still $\le x$. A brute force scan takes $O(n)$, while two independent binary searches (or one modified search) yield the answer in $O(\log n)$.

**C++ solution**:
```cpp
#include <vector>
#include <utility>

std::pair<int, int> getFloorAndCeil(const std::vector<int>& arr, int x) {
    int floor_val = -1;
    int ceil_val = -1;
    
    // Find floor
    int lo = 0;
    int hi = arr.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] <= x) {
            floor_val = arr[mid];
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    
    // Find ceil
    lo = 0;
    hi = arr.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] >= x) {
            ceil_val = arr[mid];
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    
    return {floor_val, ceil_val};
}
```

**Complexity**: 
- **Time:** $O(\log n)$ for performing two independent binary searches.
- **Space:** $O(1)$ extra space.

**Practice:** https://www.geeksforgeeks.org/problems/ceil-the-floor2802/1

### First and Last Occurrence
Given an array of integers sorted in non-decreasing order, find the starting and ending position of a given target value. If target is not found in the array, return `[-1, -1]`.

**Intuition / approach**: 
A naive approach scans from the left to find the first occurrence and from the right for the last occurrence, taking $O(n)$ time. Optimally, we can find the first occurrence using the lower bound logic (recording the index when we match and moving left). The last occurrence is found by a similar binary search, recording the index on a match and moving right to find any later occurrences.

**C++ solution**:
```cpp
#include <vector>

std::vector<int> searchRange(const std::vector<int>& nums, int target) {
    int first = -1;
    int last = -1;
    
    // First occurrence
    int lo = 0;
    int hi = nums.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) {
            first = mid;
            hi = mid - 1;
        } else if (nums[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    
    // Last occurrence
    lo = 0;
    hi = nums.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) {
            last = mid;
            lo = mid + 1;
        } else if (nums[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    
    return {first, last};
}
```

**Complexity**: 
- **Time:** $O(\log n)$ to run two binary searches.
- **Space:** $O(1)$ constant space used.

**Practice:** https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/

### Count Occurrences in a Sorted Array
Given a sorted array of integer and a target value `X`, count the number of occurrences of `X` in the array.

**Intuition / approach**: 
The brute force solution is a linear scan which takes $O(n)$ time. Since the array is sorted, all occurrences of `X` are contiguous. We can find the first and last occurrence of `X` using the logic from the previous problem. The total count will be `last - first + 1`. If `X` is not present, the count is `0`.

**C++ solution**:
```cpp
#include <vector>

int countOccurrences(const std::vector<int>& arr, int target) {
    int first = -1;
    int last = -1;
    
    int lo = 0;
    int hi = arr.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) {
            first = mid;
            hi = mid - 1;
        } else if (arr[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    
    if (first == -1) return 0;
    
    lo = 0;
    hi = arr.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) {
            last = mid;
            lo = mid + 1;
        } else if (arr[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    
    return last - first + 1;
}
```

**Complexity**: 
- **Time:** $O(\log n)$ to find the boundary indices.
- **Space:** $O(1)$ extra space.

**Practice:** https://www.geeksforgeeks.org/problems/number-of-occurrence2259/1

### Search in Rotated Sorted Array I
Given an integer array `nums` sorted in ascending order (with distinct values) that has been possibly rotated at an unknown pivot, and an integer `target`, return the index of `target` if it is in `nums`, or `-1` if it is not.

**Intuition / approach**: 
A simple linear search would take $O(n)$ time. To achieve $O(\log n)$ time, we must use binary search. Even though the array is rotated, one of the two halves defined by the midpoint will always be perfectly sorted.

::: keypoint
The core invariant for rotated arrays: at any midpoint, at least one half of the array (either `lo` to `mid` or `mid` to `hi`) is strictly sorted. By identifying the sorted half, we can easily check if the target lies within its bounds.
:::

If the left half is sorted, we check if the target falls between `nums[lo]` and `nums[mid]`. If it does, we discard the right half; otherwise, we discard the left. We apply the symmetric logic if the right half is the sorted one.

**C++ solution**:
```cpp
#include <vector>

int searchRotated(const std::vector<int>& nums, int target) {
    int lo = 0;
    int hi = nums.size() - 1;
    
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) {
            return mid;
        }
        
        // Left half is sorted
        if (nums[lo] <= nums[mid]) {
            if (nums[lo] <= target && target < nums[mid]) {
                hi = mid - 1; // Target is in the sorted left half
            } else {
                lo = mid + 1; // Target is in the right half
            }
        } 
        // Right half is sorted
        else {
            if (nums[mid] < target && target <= nums[hi]) {
                lo = mid + 1; // Target is in the sorted right half
            } else {
                hi = mid - 1; // Target is in the left half
            }
        }
    }
    return -1;
}
```

**Complexity**: 
- **Time:** $O(\log n)$ as the search space is cut in half unconditionally.
- **Space:** $O(1)$ utilizing only primitive variables.

**Practice:** https://leetcode.com/problems/search-in-rotated-sorted-array/

### Search in Rotated Sorted Array II
Given an integer array `nums` sorted in ascending order (with duplicates) that has been rotated, and a `target`, return `true` if `target` is in `nums`, or `false` if it is not.

**Intuition / approach**: 
When duplicates are present, the condition `nums[lo] <= nums[mid]` is no longer sufficient to guarantee the left half is strictly sorted. 

::: trap
If `nums[lo] == nums[mid] == nums[hi]`, it is impossible to know which half is sorted (e.g., `[3, 1, 2, 3, 3, 3, 3]`). This ambiguous state prevents us from eliminating a full half.
:::

When we encounter this edge case, the only safe operation is to shrink the search space by incrementally moving `lo` and `hi` inward (`lo++` and `hi--`) until we restore identifiability. In the worst case (all identical elements), this degenerates to $O(n)$ time.

**C++ solution**:
```cpp
#include <vector>

bool searchRotatedII(const std::vector<int>& nums, int target) {
    int lo = 0;
    int hi = nums.size() - 1;
    
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) {
            return true;
        }
        
        // Shrink bounds if we cannot determine the sorted half
        if (nums[lo] == nums[mid] && nums[mid] == nums[hi]) {
            lo++;
            hi--;
            continue;
        }
        
        // Left half is sorted
        if (nums[lo] <= nums[mid]) {
            if (nums[lo] <= target && target < nums[mid]) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        } 
        // Right half is sorted
        else {
            if (nums[mid] < target && target <= nums[hi]) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
    }
    return false;
}
```

**Complexity**: 
- **Time:** Average $O(\log n)$, worst case $O(n)$ if the array consists mostly of duplicates of the same value.
- **Space:** $O(1)$ constant space.

**Practice:** https://leetcode.com/problems/search-in-rotated-sorted-array-ii/

### Find Minimum in Rotated Sorted Array
Given an array of distinct integers sorted in ascending order and then rotated an unknown number of times, return the minimum element of this array.

**Intuition / approach**: 
A naive scan takes $O(n)$ time. We can achieve $O(\log n)$ using binary search. If we identify the sorted half, the minimum of that specific half is simply its leftmost element. We can record this value as a potential minimum, and then we strictly search the *other* (unsorted) half to see if a smaller element exists. We continuously maintain the global minimum seen so far.

**C++ solution**:
```cpp
#include <vector>
#include <algorithm>

int findMin(const std::vector<int>& nums) {
    int lo = 0;
    int hi = nums.size() - 1;
    int min_val = nums[0];
    
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        
        // If the entire search space is already sorted, the leftmost element is the minimum.
        if (nums[lo] <= nums[hi]) {
            min_val = std::min(min_val, nums[lo]);
            break;
        }
        
        // Left half is sorted
        if (nums[lo] <= nums[mid]) {
            min_val = std::min(min_val, nums[lo]);
            lo = mid + 1; // Minimum must be in the unsorted right half
        } 
        // Right half is sorted
        else {
            min_val = std::min(min_val, nums[mid]);
            hi = mid - 1; // Minimum must be in the unsorted left half
        }
    }
    return min_val;
}
```

**Complexity**: 
- **Time:** $O(\log n)$ by discarding half the array each step.
- **Space:** $O(1)$ requiring no extra memory allocations.

**Practice:** https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/

### Find How Many Times the Array is Rotated
Given an array of distinct integers sorted in ascending order and rotated, find the number of times it was rotated.

**Intuition / approach**: 
The number of rotations is exactly equal to the index of the minimum element. For example, if the minimum is at index `3`, the array was rotated `3` times rightward. Thus, the brute force $O(n)$ solution is finding the minimum's index linearly. The optimal $O(\log n)$ approach is nearly identical to finding the minimum value, except we track and return the index corresponding to that minimum value instead.

**C++ solution**:
```cpp
#include <vector>

int findKRotation(const std::vector<int>& arr) {
    int lo = 0;
    int hi = arr.size() - 1;
    int min_val = 2e9; // Infinity placeholder
    int min_index = -1;
    
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        
        // If entire range is sorted
        if (arr[lo] <= arr[hi]) {
            if (arr[lo] < min_val) {
                min_val = arr[lo];
                min_index = lo;
            }
            break;
        }
        
        // Left half is sorted
        if (arr[lo] <= arr[mid]) {
            if (arr[lo] < min_val) {
                min_val = arr[lo];
                min_index = lo;
            }
            lo = mid + 1;
        } 
        // Right half is sorted
        else {
            if (arr[mid] < min_val) {
                min_val = arr[mid];
                min_index = mid;
            }
            hi = mid - 1;
        }
    }
    return min_index;
}
```

**Complexity**: 
- **Time:** $O(\log n)$ identical to finding the minimum value.
- **Space:** $O(1)$ constant overhead.

**Practice:** https://www.geeksforgeeks.org/problems/rotation4723/1

### Single Element in a Sorted Array
You are given a sorted array consisting of only integers where every element appears exactly twice, except for one element which appears exactly once. Find this single element that appears only once.

**Intuition / approach**: 
A naive approach computes the XOR of all elements in $O(n)$ time. Because the array is sorted, duplicates are adjacent. In an array where every element appears twice, pairs naturally align on `(even, odd)` indices. Once the single element is introduced, it shifts the alignment of all subsequent pairs to `(odd, even)`. We can use binary search to check the index of a pair. If the indices follow `(even, odd)`, the single element is in the right half; otherwise, it is in the left half.

**C++ solution**:
```cpp
#include <vector>

int singleNonDuplicate(const std::vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];
    if (nums[0] != nums[1]) return nums[0];
    if (nums[n - 1] != nums[n - 2]) return nums[n - 1];
    
    int lo = 1;
    int hi = n - 2;
    
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        
        if (nums[mid] != nums[mid - 1] && nums[mid] != nums[mid + 1]) {
            return nums[mid];
        }
        
        // Check alignment
        if ((mid % 2 == 1 && nums[mid] == nums[mid - 1]) || 
            (mid % 2 == 0 && nums[mid] == nums[mid + 1])) {
            // We are in the left side of the single element
            lo = mid + 1;
        } else {
            // We are in the right side
            hi = mid - 1;
        }
    }
    return -1;
}
```

**Complexity**: 
- **Time:** $O(\log n)$ leveraging the pattern of indices.
- **Space:** $O(1)$ space.

**Practice:** https://leetcode.com/problems/single-element-in-a-sorted-array/

### Find Peak Element
A peak element is an element that is strictly greater than its neighbors. Given a 0-indexed integer array `nums`, find a peak element, and return its index. If the array contains multiple peaks, return the index to any of the peaks. You may imagine that `nums[-1] = nums[n] = -\infty`.

**Intuition / approach**: 
A linear scan checking neighbors takes $O(n)$ time. For an $O(\log n)$ approach, we observe that moving in the direction of the strictly increasing slope guarantees we will eventually hit a peak (because the array bounds drop to $-\infty$). We can evaluate the slope at `mid`. If `nums[mid] < nums[mid + 1]`, the slope is rising to the right, so a peak must exist on the right side. Otherwise, the slope is falling to the right (or rising to the left), so a peak exists on the left side.

**C++ solution**:
```cpp
#include <vector>

int findPeakElement(const std::vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return 0;
    if (nums[0] > nums[1]) return 0;
    if (nums[n - 1] > nums[n - 2]) return n - 1;
    
    int lo = 1;
    int hi = n - 2;
    
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        
        if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1]) {
            return mid;
        }
        
        // If we are on a rising slope, there must be a peak on the right
        if (nums[mid] > nums[mid - 1]) {
            lo = mid + 1;
        } 
        // If we are on a falling slope, there must be a peak on the left
        else {
            hi = mid - 1;
        }
    }
    return -1;
}
```

**Complexity**: 
- **Time:** $O(\log n)$ via binary search over the gradients.
- **Space:** $O(1)$ auxiliary space.

**Practice:** https://leetcode.com/problems/find-peak-element/

## Binary Search on Answers

Many problems ask us to find the minimum or maximum value that satisfies a certain condition. When the search space (the range of possible answers) is monotonic—meaning that if a value $x$ is valid, then all values greater than $x$ are also valid (or vice-versa)—we can use the **binary search on the answer space** pattern. Instead of searching through a given array, we binary-search a numeric range and test the feasibility of each midpoint.

::: keypoint
The core of this pattern is separating the binary search logic from the feasibility test. Write a helper function `bool isValid(mid)` that returns true if `mid` is a valid answer. The binary search then just finds the boundary where `isValid` changes from false to true.
:::

### Find Square Root of a Number

Given an integer $n$, find the floor of its square root without using any built-in math functions.

**Intuition / approach:**
The brute force approach is to iterate $i$ from 1 to $n$ and return $i - 1$ when $i \times i > n$. This takes $O(n)$ time. Since the sequence of squares is monotonically increasing, we can binary-search the answer space $[1, n]$. We find the largest $mid$ such that $mid \times mid \le n$. To avoid integer overflow when calculating $mid \times mid$, we should test $mid \le n / mid$, or use a larger integer type.

**C++ solution:**
```cpp
int floorSqrt(int n) {
    if (n == 0 || n == 1) return n;
    
    int lo = 1, hi = n, ans = 1;
    while (lo <= hi) {
        long long mid = lo + (hi - lo) / 2;
        if (mid * mid <= n) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return ans;
}
```

**Complexity:**
- **Time Complexity:** $O(\log n)$ because we halve the search space at each step.
- **Space Complexity:** $O(1)$ auxiliary space.

**Practice:** https://leetcode.com/problems/sqrtx/

### Find Nth Root of a Number

Given two integers $n$ and $m$, find the $n$-th root of $m$. If the root is not an integer, return -1.

**Intuition / approach:**
Similar to finding the square root, we know that $x^{n}$ is monotonically increasing for $x > 0$. We can binary search the answer in the range $[1, m]$. To handle large values safely, we write a helper to compute $mid^{n}$. If it exceeds $m$ early, we return a flag indicating it is too large to prevent overflow.

**C++ solution:**
```cpp
// Returns 1 if mid^n == m, 2 if mid^n > m, 0 if mid^n < m
int multiply(int mid, int n, int m) {
    long long ans = 1;
    for (int i = 1; i <= n; i++) {
        ans *= mid;
        if (ans > m) return 2;
    }
    if (ans == m) return 1;
    return 0;
}

int NthRoot(int n, int m) {
    int lo = 1, hi = m;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int val = multiply(mid, n, m);
        
        if (val == 1) return mid;
        if (val == 2) hi = mid - 1;
        else lo = mid + 1;
    }
    return -1;
}
```

**Complexity:**
- **Time Complexity:** $O(n \log m)$, because binary search takes $O(\log m)$ and computing the power takes $O(n)$ in the worst case.
- **Space Complexity:** $O(1)$ auxiliary space.

**Practice:** https://www.geeksforgeeks.org/n-th-root-number/

### Koko Eating Bananas

Given an array of $n$ piles of bananas where the $i$-th pile has `piles[i]` bananas, and a time limit of $h$ hours. Koko can decide her bananas-per-hour eating speed $k$. Each hour, she chooses a pile and eats $k$ bananas from it. If the pile has fewer than $k$ bananas, she eats all of them and will not eat any more bananas during this hour. Return the minimum integer $k$ such that she can eat all the bananas within $h$ hours.

**Intuition / approach:**
The minimum possible speed is 1 (eat one banana per hour). The maximum possible speed is the maximum pile size (eating more per hour does not save any more time since she only eats from one pile per hour). If she can eat all bananas at speed $k$, she can also eat them at any speed $> k$. This monotonicity allows us to binary-search the speed $k \in [1, \max(\text{piles})]$. The feasibility check simply sums up the hours needed for each pile at speed $k$ taking the ceiling of `piles[i] / k`.

::: keypoint
When asked to minimize a maximum value or maximize a minimum value, always look for binary search on the answer space.
:::

**C++ solution:**
```cpp
#include <vector>
#include <algorithm>

using namespace std;

bool canEatInTime(const vector<int>& piles, int speed, int h) {
    long long timeRequired = 0;
    for (int pile : piles) {
        timeRequired += (pile + speed - 1) / speed;
    }
    return timeRequired <= h;
}

int minEatingSpeed(vector<int>& piles, int h) {
    int lo = 1;
    int hi = *max_element(piles.begin(), piles.end());
    int ans = hi;
    
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (canEatInTime(piles, mid, h)) {
            ans = mid;
            hi = mid - 1; // Try to find a smaller valid speed
        } else {
            lo = mid + 1; // Speed is too slow
        }
    }
    return ans;
}
```

**Complexity:**
- **Time Complexity:** $O(N \log(\max(\text{piles})))$ where $N$ is the number of piles. The search space is bounded by the max pile, and each feasibility test takes $O(N)$.
- **Space Complexity:** $O(1)$ auxiliary space.

**Practice:** https://leetcode.com/problems/koko-eating-bananas/

### Minimum Days to Make M Bouquets

You are given an integer array `bloomDay`, an integer $m$ and an integer $k$. You want to make $m$ bouquets. To make a bouquet, you need to use $k$ adjacent flowers from the garden. The garden consists of $n$ flowers, the $i$-th flower will bloom in `bloomDay[i]`. Return the minimum number of days you need to wait to be able to make $m$ bouquets from the garden. If it is impossible, return -1.

**Intuition / approach:**
If $m \times k > n$, we do not have enough flowers, so return -1.
If we wait $d$ days, any flower with `bloomDay[i] \le d` is bloomed. If it is possible at day $d$, it is also possible at day $d+1$. Thus, we can binary search the day $d$ in the range $[\min(\text{bloomDay}), \max(\text{bloomDay})]$. To check feasibility for a day $d$, we iterate through the array and count contiguous bloomed flowers. Whenever we gather $k$ adjacent flowers, we form a bouquet and reset the contiguous count. If total bouquets reach $m$, day $d$ is valid.

**C++ solution:**
```cpp
#include <vector>
#include <algorithm>

using namespace std;

bool possible(const vector<int>& bloomDay, int day, int m, int k) {
    int bouquets = 0, consecutiveBloomed = 0;
    for (int bloom : bloomDay) {
        if (bloom <= day) {
            consecutiveBloomed++;
            if (consecutiveBloomed == k) {
                bouquets++;
                consecutiveBloomed = 0;
            }
        } else {
            consecutiveBloomed = 0;
        }
    }
    return bouquets >= m;
}

int minDays(vector<int>& bloomDay, int m, int k) {
    int n = bloomDay.size();
    if ((long long)m * k > n) return -1;
    
    int lo = *min_element(bloomDay.begin(), bloomDay.end());
    int hi = *max_element(bloomDay.begin(), bloomDay.end());
    int ans = -1;
    
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (possible(bloomDay, mid, m, k)) {
            ans = mid;
            hi = mid - 1; // Try an earlier day
        } else {
            lo = mid + 1; // Need more days
        }
    }
    return ans;
}
```

**Complexity:**
- **Time Complexity:** $O(N \log(\max - \min))$ where $N$ is the number of flowers. Testing feasibility takes $O(N)$ and we do it for each binary search step.
- **Space Complexity:** $O(1)$ auxiliary space.

**Practice:** https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/

### Find the Smallest Divisor Given a Threshold

Given an array of integers `nums` and an integer `threshold`, we will choose a positive integer `divisor`, divide all the array by it, and sum the division's result. Find the smallest `divisor` such that the result mentioned above is less than or equal to `threshold`. Each result of the division is rounded to the nearest integer greater than or equal to that element (i.e., ceiling).

**Intuition / approach:**
A larger divisor yields a smaller sum. This monotonicity means we can binary search the divisor. The minimum divisor is 1, and the maximum useful divisor is $\max(\text{nums})$ (any divisor larger than the max element yields a sum of $N$, which is the minimum possible sum). For a chosen `mid`, we compute the sum using ceiling division. If the sum $\le$ `threshold`, `mid` is valid, and we search for a smaller divisor.

**C++ solution:**
```cpp
#include <vector>
#include <algorithm>

using namespace std;

bool isSumValid(const vector<int>& nums, int divisor, int threshold) {
    long long sum = 0;
    for (int num : nums) {
        sum += (num + divisor - 1) / divisor;
    }
    return sum <= threshold;
}

int smallestDivisor(vector<int>& nums, int threshold) {
    int lo = 1;
    int hi = *max_element(nums.begin(), nums.end());
    int ans = hi;
    
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (isSumValid(nums, mid, threshold)) {
            ans = mid;
            hi = mid - 1; // Try a smaller divisor
        } else {
            lo = mid + 1; // Divisor too small, sum too large
        }
    }
    return ans;
}
```

**Complexity:**
- **Time Complexity:** $O(N \log(\max(\text{nums})))$ where $N$ is the array size.
- **Space Complexity:** $O(1)$ auxiliary space.

**Practice:** https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/

### Capacity to Ship Packages Within D Days

A conveyor belt has packages that must be shipped from one port to another within `days` days. The $i$-th package on the conveyor belt has a weight of `weights[i]`. Each day, we load the ship with packages on the conveyor belt (in the order given). We may not load more weight than the maximum weight capacity of the ship. Return the least weight capacity of the ship that will result in all the packages being shipped within `days` days.

**Intuition / approach:**
The minimum possible capacity must be at least the maximum weight of any single package (otherwise that package can never be shipped). The maximum capacity would be the sum of all packages (shipping everything in 1 day). This gives our search space $[\max(\text{weights}), \sum(\text{weights})]$. The monotonic property holds: if capacity $C$ works, $C+1$ also works. To check if capacity $C$ is valid, we greedily pack packages into days, incrementing the day count when the next package exceeds the remaining capacity for the current day.

**C++ solution:**
```cpp
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

bool canShip(const vector<int>& weights, int capacity, int days) {
    int daysNeeded = 1;
    int currentLoad = 0;
    
    for (int weight : weights) {
        if (currentLoad + weight > capacity) {
            daysNeeded++;
            currentLoad = weight;
        } else {
            currentLoad += weight;
        }
    }
    return daysNeeded <= days;
}

int shipWithinDays(vector<int>& weights, int days) {
    int lo = *max_element(weights.begin(), weights.end());
    int hi = accumulate(weights.begin(), weights.end(), 0);
    int ans = hi;
    
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (canShip(weights, mid, days)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}
```

**Complexity:**
- **Time Complexity:** $O(N \log(\sum\text{weights} - \max\text{weights}))$ where $N$ is the size of the weights array.
- **Space Complexity:** $O(1)$ auxiliary space.

**Practice:** https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/

### Kth Missing Positive Number

Given an array `arr` of positive integers sorted in a strictly increasing order, and an integer $k$. Return the $k$-th positive integer that is missing from this array.

**Intuition / approach:**
For an array sorted in strictly increasing order, if there were no missing elements, the element at index $i$ would be $i + 1$. Thus, the number of missing elements strictly before `arr[i]` is `arr[i] - (i + 1)`. Since `arr` is sorted, this count is monotonically increasing. We can binary search the index $i$ such that the number of missing elements before `arr[i]` is less than $k$. The answer will be found using the low pointer $lo$ which gives the insertion point; the missing element is `lo + k`.

**C++ solution:**
```cpp
#include <vector>

using namespace std;

int findKthPositive(vector<int>& arr, int k) {
    int lo = 0, hi = arr.size() - 1;
    
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int missing = arr[mid] - (mid + 1);
        
        if (missing < k) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return lo + k;
}
```

**Complexity:**
- **Time Complexity:** $O(\log N)$ where $N$ is the array length.
- **Space Complexity:** $O(1)$ auxiliary space.

**Practice:** https://leetcode.com/problems/kth-missing-positive-number/

### Aggressive Cows

You are given an array of integers representing stall coordinates and an integer $k$ representing the number of aggressive cows. Place all $k$ cows in the stalls such that the minimum distance between any two of them is maximized.

**Intuition / approach:**
We want to maximize a minimum distance, a classic binary search on answer problem. If we can place cows with at least distance $D$ between them, we can also place them with any distance $< D$. We first sort the stalls. The search space for the distance is $[1, \max(\text{stall}) - \min(\text{stall})]$. To check feasibility for a distance $D$, we greedily place the first cow in the first stall, and then iterate through the sorted stalls, placing the next cow as soon as a stall is at least distance $D$ away from the last placed cow. If we can place all $k$ cows, distance $D$ is possible.

::: keypoint
Greedy placement works because placing the leftmost cow as early as possible strictly maximizes the remaining distance available for subsequent cows. Sorting the array first is mandatory.
:::

**C++ solution:**
```cpp
#include <vector>
#include <algorithm>

using namespace std;

bool canPlaceCows(const vector<int>& stalls, int minDist, int k) {
    int cowsPlaced = 1;
    int lastPos = stalls[0];
    
    for (int i = 1; i < stalls.size(); i++) {
        if (stalls[i] - lastPos >= minDist) {
            cowsPlaced++;
            lastPos = stalls[i];
            if (cowsPlaced == k) return true;
        }
    }
    return false;
}

int aggressiveCows(vector<int>& stalls, int k) {
    sort(stalls.begin(), stalls.end());
    int lo = 1;
    int hi = stalls.back() - stalls.front();
    int ans = 1;
    
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (canPlaceCows(stalls, mid, k)) {
            ans = mid;
            lo = mid + 1; // Try for a larger minimum distance
        } else {
            hi = mid - 1;
        }
    }
    return ans;
}
```

**Complexity:**
- **Time Complexity:** $O(N \log N + N \log(\max - \min))$, where $O(N \log N)$ is for sorting and $O(N \log(\max - \min))$ is for the binary search.
- **Space Complexity:** $O(1)$ auxiliary space.

**Practice:** https://www.spoj.com/problems/AGGRCOW/

### Book Allocation Problem

Given an array of integer `pages` of $n$ books and $m$ students. Allocate all the books such that each student gets at least one book, allocations are contiguous, and the maximum number of pages assigned to a student is minimized. If $m > n$, return -1.

**Intuition / approach:**
Minimizing a maximum is the signal for binary search on the answer. The search space is $[\max(\text{pages}), \sum(\text{pages})]$. If we can allocate books such that no student reads more than $P$ pages, we check if the required number of students is $\le m$. We greedily assign contiguous books to a student until the sum exceeds $P$, at which point we assign the current book to the next student. If total students needed $\le m$, $P$ is a valid maximum capacity.

**C++ solution:**
```cpp
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

bool isValidAllocation(const vector<int>& pages, int maxPages, int m) {
    int students = 1;
    long long currentPages = 0;
    
    for (int p : pages) {
        if (currentPages + p > maxPages) {
            students++;
            currentPages = p;
        } else {
            currentPages += p;
        }
    }
    return students <= m;
}

int findPages(vector<int>& pages, int m) {
    int n = pages.size();
    if (m > n) return -1;
    
    int lo = *max_element(pages.begin(), pages.end());
    long long hi = accumulate(pages.begin(), pages.end(), 0LL);
    int ans = -1;
    
    while (lo <= hi) {
        long long mid = lo + (hi - lo) / 2;
        if (isValidAllocation(pages, mid, m)) {
            ans = mid;
            hi = mid - 1; // Try to minimize the maximum pages
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}
```

**Complexity:**
- **Time Complexity:** $O(N \log(\sum\text{pages} - \max\text{pages}))$ where $N$ is the number of books.
- **Space Complexity:** $O(1)$ auxiliary space.

**Practice:** https://www.geeksforgeeks.org/allocate-minimum-number-pages/

### Split Array — Largest Sum

Given an integer array `nums` and an integer $k$, split `nums` into $k$ non-empty continuous subarrays such that the largest sum of any subarray is minimized.

**Intuition / approach:**
This problem is structurally identical to the Book Allocation Problem. Splitting an array into $k$ subarrays while minimizing the largest sum translates exactly to distributing books to $m$ students while minimizing the maximum pages. We binary search the answer in $[\max(\text{nums}), \sum(\text{nums})]$ and greedily split the array whenever adding an element would exceed the target sum $mid$.

**C++ solution:**
```cpp
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

bool isValidSplit(const vector<int>& nums, int maxSum, int k) {
    int subarrays = 1;
    long long currentSum = 0;
    
    for (int num : nums) {
        if (currentSum + num > maxSum) {
            subarrays++;
            currentSum = num;
        } else {
            currentSum += num;
        }
    }
    return subarrays <= k;
}

int splitArray(vector<int>& nums, int k) {
    int lo = *max_element(nums.begin(), nums.end());
    long long hi = accumulate(nums.begin(), nums.end(), 0LL);
    int ans = hi;
    
    while (lo <= hi) {
        long long mid = lo + (hi - lo) / 2;
        if (isValidSplit(nums, mid, k)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}
```

**Complexity:**
- **Time Complexity:** $O(N \log(\sum\text{nums} - \max\text{nums}))$ where $N$ is the array size.
- **Space Complexity:** $O(1)$ auxiliary space.

**Practice:** https://leetcode.com/problems/split-array-largest-sum/

### Painter's Partition

Given $n$ boards of length represented by an array and $k$ painters. A painter takes 1 unit of time to paint 1 unit of the board. Find the minimum time to get all the boards painted under the constraints that any painter will only paint continuous sections of boards.

**Intuition / approach:**
Once again, this is exactly the same logic as Book Allocation and Split Array Largest Sum. Minimizing the maximum time among contiguous chunks maps directly to binary searching the answer between $\max(\text{boards})$ and $\sum(\text{boards})$.

**C++ solution:**
```cpp
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

bool canPaint(const vector<int>& boards, long long maxTime, int k) {
    int painters = 1;
    long long currentTime = 0;
    
    for (int board : boards) {
        if (currentTime + board > maxTime) {
            painters++;
            currentTime = board;
        } else {
            currentTime += board;
        }
    }
    return painters <= k;
}

int findLargestMinDistance(vector<int>& boards, int k) {
    long long lo = *max_element(boards.begin(), boards.end());
    long long hi = accumulate(boards.begin(), boards.end(), 0LL);
    long long ans = hi;
    
    while (lo <= hi) {
        long long mid = lo + (hi - lo) / 2;
        if (canPaint(boards, mid, k)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}
```

**Complexity:**
- **Time Complexity:** $O(N \log(\sum\text{boards} - \max\text{boards}))$ where $N$ is the array length.
- **Space Complexity:** $O(1)$ auxiliary space.

**Practice:** https://www.geeksforgeeks.org/painters-partition-problem/

### Minimize Max Distance to Gas Station

You are given a sorted integer array `stations` representing gas station positions on the X-axis, and an integer $k$. You add $k$ new gas stations to the X-axis. Return the minimum possible value of the maximum distance between adjacent gas stations after adding the $k$ new stations. The answer will be accepted if it is within $10^{-6}$ of the true value.

**Intuition / approach:**
We need to minimize a maximum distance over continuous segments, which screams binary search. However, the search space is now continuous (floating-point). If we test a distance $D$, the number of new stations we must add between two existing stations $a$ and $b$ to ensure no gap is strictly greater than $D$ is $\lfloor (b - a) / D \rfloor$. We sum this required number of stations over all adjacent pairs. If the sum $\le k$, distance $D$ is achievable. Since the answer must be precise to $10^{-6}$, we use a fixed number of iterations or a threshold on `hi - lo` to terminate the binary search.

**C++ solution:**
```cpp
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

bool isPossible(const vector<int>& stations, double dist, int k) {
    int requiredStations = 0;
    for (int i = 1; i < stations.size(); i++) {
        double diff = stations[i] - stations[i - 1];
        requiredStations += static_cast<int>(ceil(diff / dist)) - 1;
    }
    return requiredStations <= k;
}

double minmaxGasDist(vector<int>& stations, int k) {
    double lo = 0.0;
    double hi = stations.back() - stations.front();
    
    // For precision 10^-6, 100 iterations yields precision ~ 10^-30
    for (int step = 0; step < 100; step++) {
        double mid = lo + (hi - lo) / 2.0;
        if (isPossible(stations, mid, k)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    return hi;
}
```

**Complexity:**
- **Time Complexity:** $O(N \times \text{iterations})$ where $N$ is the number of stations and iterations is 100. Thus, it is $O(N)$ time.
- **Space Complexity:** $O(1)$ auxiliary space.

**Practice:** https://leetcode.com/problems/minimize-max-distance-to-gas-station/

### Median of Two Sorted Arrays

Given two sorted arrays `nums1` and `nums2` of size $m$ and $n$ respectively, return the median of the two sorted arrays. The overall run time complexity should be $O(\log(m+n))$.

**Intuition / approach:**
The median divides an array into two halves of equal length. For two arrays, we can partition `nums1` at index $i$ and `nums2` at index $j$ such that the total number of elements in the left half is $(m + n + 1) / 2$. This implies $j = (m + n + 1) / 2 - i$. We binary search the partition index $i$ in the smaller array to minimize the search space. A valid partition requires the maximum element on the left of `nums1` to be $\le$ the minimum element on the right of `nums2`, and vice-versa. If `nums1` left max is greater, the partition $i$ is too far right.

::: keypoint
Always binary search on the **smaller** array. This guarantees that $j$ (the partition index in the larger array) will not go out of bounds. The boundary checks (`INT_MIN` and `INT_MAX` for out-of-bounds partitions) neatly handle edge cases where all elements of an array fall on one side.
:::

**C++ solution:**
```cpp
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    if (nums1.size() > nums2.size()) {
        return findMedianSortedArrays(nums2, nums1);
    }
    
    int m = nums1.size();
    int n = nums2.size();
    int lo = 0, hi = m;
    
    while (lo <= hi) {
        int i = lo + (hi - lo) / 2;
        int j = (m + n + 1) / 2 - i;
        
        int left1 = (i == 0) ? INT_MIN : nums1[i - 1];
        int right1 = (i == m) ? INT_MAX : nums1[i];
        
        int left2 = (j == 0) ? INT_MIN : nums2[j - 1];
        int right2 = (j == n) ? INT_MAX : nums2[j];
        
        if (left1 <= right2 && left2 <= right1) {
            if ((m + n) % 2 == 0) {
                return (max(left1, left2) + min(right1, right2)) / 2.0;
            } else {
                return max(left1, left2);
            }
        } else if (left1 > right2) {
            hi = i - 1; // Partition in nums1 is too far right
        } else {
            lo = i + 1; // Partition in nums1 is too far left
        }
    }
    return 0.0;
}
```

**Complexity:**
- **Time Complexity:** $O(\log(\min(m, n)))$ because we binary search the smaller array.
- **Space Complexity:** $O(1)$ auxiliary space.

**Practice:** https://leetcode.com/problems/median-of-two-sorted-arrays/

### Kth Element of Two Sorted Arrays

Given two sorted arrays of size $m$ and $n$ respectively, find the $k$-th element of the final sorted array.

**Intuition / approach:**
Finding the $k$-th element is a generalization of finding the median. We want exactly $k$ elements in the left partition. So $j = k - i$. We binary search $i$ in the smaller array, but the valid range for $i$ is constrained: we cannot take more than $m$ elements from the first array, and we must take at least $k - n$ elements if $k > n$. So our search bounds for $i$ become $[\max(0, k - n), \min(m, k)]$. The validity condition remains the same cross-check between left maxes and right mins.

**C++ solution:**
```cpp
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int kthElement(vector<int>& nums1, vector<int>& nums2, int k) {
    if (nums1.size() > nums2.size()) {
        return kthElement(nums2, nums1, k);
    }
    
    int m = nums1.size();
    int n = nums2.size();
    
    int lo = max(0, k - n);
    int hi = min(m, k);
    
    while (lo <= hi) {
        int i = lo + (hi - lo) / 2;
        int j = k - i;
        
        int left1 = (i == 0) ? INT_MIN : nums1[i - 1];
        int right1 = (i == m) ? INT_MAX : nums1[i];
        
        int left2 = (j == 0) ? INT_MIN : nums2[j - 1];
        int right2 = (j == n) ? INT_MAX : nums2[j];
        
        if (left1 <= right2 && left2 <= right1) {
            return max(left1, left2);
        } else if (left1 > right2) {
            hi = i - 1;
        } else {
            lo = i + 1;
        }
    }
    return 1; // Unreachable for valid inputs
}
```

**Complexity:**
- **Time Complexity:** $O(\log(\min(m, k)))$ since we binary search on at most $\min(m, k)$ elements.
- **Space Complexity:** $O(1)$ auxiliary space.

**Practice:** https://www.geeksforgeeks.org/k-th-element-two-sorted-arrays/

## Binary Search on 2D Arrays

### Find the Row with Maximum 1's

Given an $M \times N$ boolean matrix where every row is sorted in ascending order (0s followed by 1s), find the 0-indexed row containing the maximum number of 1s.

**Intuition**: A brute force solution traverses the entire matrix in $O(M \times N)$ time. Since each row is sorted, a better approach uses binary search to find the first occurrence of `1` in each row. The number of 1s in that row is the total columns minus the index of the first `1`. We can maintain the maximum count and the corresponding row index across all rows.

**C++ Solution**:
```cpp
#include <vector>
#include <algorithm>
using namespace std;

int rowWithMax1s(vector<vector<int>>& matrix) {
    int m = matrix.size();
    if (m == 0) return -1;
    int n = matrix[0].size();
    
    int max1s = 0;
    int index = -1;
    
    for (int i = 0; i < m; i++) {
        auto it = lower_bound(matrix[i].begin(), matrix[i].end(), 1);
        int count = matrix[i].end() - it;
        if (count > max1s) {
            max1s = count;
            index = i;
        }
    }
    
    return index;
}
```

**Complexity**: Time $O(M \log N)$ because we perform a binary search on each of the $M$ rows of size $N$. Space $O(1)$ auxiliary.

**Practice:** https://www.geeksforgeeks.org/find-the-row-with-maximum-number-1s/

### Search in a 2D Matrix

Given an $M \times N$ matrix where each row is sorted and the first integer of each row is greater than the last integer of the previous row, determine if a target value exists.

**Intuition**: The matrix properties guarantee that if we flatten the 2D matrix into a 1D array, it will be strictly sorted. A brute force search takes $O(M \times N)$. To optimize, we can perform a binary search over the conceptual 1D array of size $M \times N$. We map any 1D index `mid` back to a 2D coordinate using `row = mid / N` and `col = mid % N`.

**C++ Solution**:
```cpp
#include <vector>
using namespace std;

bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size();
    if (m == 0) return false;
    int n = matrix[0].size();
    
    int low = 0;
    int high = m * n - 1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int row = mid / n;
        int col = mid % n;
        
        if (matrix[row][col] == target) {
            return true;
        } else if (matrix[row][col] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    return false;
}
```

**Complexity**: Time $O(\log (M \times N))$ since we are binary searching a flattened space of $M \times N$ elements. Space $O(1)$ auxiliary.

**Practice:** https://leetcode.com/problems/search-a-2d-matrix/

### Search in a 2D Matrix II

Given an $M \times N$ matrix where rows are sorted left-to-right and columns are sorted top-to-bottom, find if a target value exists. 

**Intuition**: The matrix cannot be treated as a flattened 1D sorted array. A brute force search takes $O(M \times N)$. A better approach performs binary search on each row, yielding $O(M \log N)$. The optimal approach leverages both row and column sorting using a "staircase search". Starting from the top-right corner, we compare the current element with the target. If the current element is greater than the target, the target cannot be in the current column, so we move left. If it is less, the target cannot be in the current row, so we move down.

::: keypoint
The staircase search is optimal because it systematically eliminates an entire row or column in $O(1)$ time at each step, relying on the sorted nature of both dimensions.
:::

**C++ Solution**:
```cpp
#include <vector>
using namespace std;

bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size();
    if (m == 0) return false;
    int n = matrix[0].size();
    
    int row = 0;
    int col = n - 1;
    
    while (row < m && col >= 0) {
        if (matrix[row][col] == target) {
            return true;
        } else if (matrix[row][col] > target) {
            col--;
        } else {
            row++;
        }
    }
    
    return false;
}
```

**Complexity**: Time $O(M + N)$ as we traverse at most $M$ rows and $N$ columns. Space $O(1)$ auxiliary.

**Practice:** https://leetcode.com/problems/search-a-2d-matrix-ii/

### Find Peak Element II

Given an $M \times N$ matrix, find any peak element. An element is a peak if it is strictly greater than its adjacent neighbors (left, right, up, and down).

**Intuition**: Brute force scans all elements in $O(M \times N)$ time. We can optimize this by applying binary search on the columns. We select the middle column and find the row with the maximum element in that column. We then compare this maximum element with its left and right neighbors. Because it is the maximum in its column, it is already greater than its top and bottom neighbors. If it is greater than its left and right neighbors, we have found a peak. If the left neighbor is greater, a peak must exist in the left half of the matrix. Otherwise, a peak exists in the right half.

**C++ Solution**:
```cpp
#include <vector>
using namespace std;

int findMaxRowIndex(const vector<vector<int>>& matrix, int col) {
    int maxVal = -1;
    int maxRow = -1;
    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i][col] > maxVal) {
            maxVal = matrix[i][col];
            maxRow = i;
        }
    }
    return maxRow;
}

vector<int> findPeakGrid(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int maxRow = findMaxRowIndex(matrix, mid);
        
        int left = mid - 1 >= 0 ? matrix[maxRow][mid - 1] : -1;
        int right = mid + 1 < n ? matrix[maxRow][mid + 1] : -1;
        
        if (matrix[maxRow][mid] > left && matrix[maxRow][mid] > right) {
            return {maxRow, mid};
        } else if (matrix[maxRow][mid] < left) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return {-1, -1};
}
```

**Complexity**: Time $O(M \log N)$ because we find the maximum element in a column of size $M$ over $\log N$ binary search steps. Space $O(1)$ auxiliary.

**Practice:** https://leetcode.com/problems/find-a-peak-element-ii/

### Matrix Median

Given a row-wise sorted $M \times N$ matrix where $M \times N$ is odd, find the overall median of the matrix.

**Intuition**: The median of an odd number of elements is the element where exactly $(M \times N) / 2$ elements are strictly less than or equal to it. The brute force approach flattens the matrix, sorts it, and picks the middle element in $O(M \times N \log(M \times N))$ time. The optimal approach uses binary search on the answer space, which ranges from the minimum element to the maximum element in the matrix. For a chosen `mid` value, we count how many elements in the matrix are less than or equal to `mid` using `std::upper_bound` on each row. If the count is less than or equal to $(M \times N) / 2$, the median must be strictly greater than `mid`.

**C++ Solution**:
```cpp
#include <vector>
#include <algorithm>
using namespace std;

int countLessEqual(const vector<int>& row, int mid) {
    return upper_bound(row.begin(), row.end(), mid) - row.begin();
}

int findMedian(vector<vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    
    int low = matrix[0][0], high = matrix[0][n - 1];
    for (int i = 0; i < m; i++) {
        low = min(low, matrix[i][0]);
        high = max(high, matrix[i][n - 1]);
    }

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int count = 0;
        
        for (int i = 0; i < m; i++) {
            count += countLessEqual(matrix[i], mid);
        }
        
        if (count <= (m * n) / 2) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return low;
}
```

**Complexity**: Time $O(M \log (\text{max} - \text{min}) \log N)$ because the outer binary search runs $\log (\text{max} - \text{min})$ times, and in each step, we perform $M$ binary searches (`upper_bound`) taking $O(\log N)$ each. Space $O(1)$ auxiliary.

**Practice:** https://www.interviewbit.com/problems/matrix-median/

::: interview
What interviewers probe here: The ability to recognize when binary search applies. Binary search is not just for sorted arrays; it is a mindset for solving problems where the input is sorted OR the "answer space" has a monotonic feasibility predicate. The answer-space pattern is an interview favorite because it tests your ability to abstract a problem into a simple true/false condition that flips exactly once.
:::
