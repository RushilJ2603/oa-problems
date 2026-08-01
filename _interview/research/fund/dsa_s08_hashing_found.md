# Hashing Foundations

::: heavy
Hashing is a fundamental technique for achieving lightning-fast lookups, a cornerstone of countless array and string interview problems. The core concept bridges the gap between the data itself and where it is stored in memory.
:::

::: definition
A **hash** is a mechanism that maps a key (like a number or a string) directly to an index or "bucket", allowing for data retrieval in (amortized) $O(1)$ time.
:::

When the keys are small, non-negative integers, the simplest and fastest hash table is just a plain array. This is known as **number hashing** or using a **frequency array**. For example, if all keys are guaranteed to be between $0$ and $10^{5}$, an array `cnt[100005]` where the index represents the key and the value represents its frequency IS the hash table. This provides strict $O(1)$ access and is extremely cache-friendly. This naturally leads to the **pre-compute-then-query** pattern: process the data once to populate the array, then answer any number of queries instantly.

**Character hashing** is a direct application of this idea. Since characters are represented by ASCII values, an array of size $256$ (`cnt[256]`) can count frequencies for any character. If you know the input consists only of lowercase English letters, you can optimize this to an array of size $26$ by mapping `'a'` to $0$, `'b'` to $1$, etc., using the expression `ch - 'a'`.

When keys are large, sparse, negative, or not integers (like strings), an array is impractical. Here we rely on the standard library. Interviewers will expect you to state the underlying structures plainly:

- `std::unordered_map` and `std::unordered_set` are implemented as **hash tables**. Lookups, insertions, and deletions are $O(1)$ on average, but can degrade to $O(n)$ in the worst case due to collisions.
- `std::map` and `std::set` are implemented as **red-black trees** (self-balancing binary search trees). All operations are strictly $O(\log n)$, and the elements are kept sorted by key.

::: keypoint
Use `unordered_map` or `unordered_set` by default for the $O(1)$ speed. Only switch to `map` or `set` if you explicitly need the keys to be ordered, if you need bounds checking (`lower_bound`), or if you are facing adversarial test cases that trigger worst-case $O(n)$ behavior. (See Part I for the exhaustive STL syntax).
:::

When multiple keys map to the same bucket, a **collision** occurs. There are two main ways hash tables handle this:

- **Chaining:** Each bucket stores a linked list of entries. When a collision happens, the new element is just appended to the list in that bucket. Searching requires traversing the list.
- **Open Addressing:** If a bucket is full, the hash table probes for the next available slot (e.g., sequentially or using a secondary hash function) and places it there.

If too many elements hash to the same bucket (or a few buckets), the linked lists grow long, or probing takes too many steps, and performance degrades from $O(1)$ to $O(n)$. The ratio of elements to buckets is the **load factor**. Hash tables automatically resize when the load factor exceeds a threshold, but collisions can still be forced.

::: trap
In competitive programming, tests often include an **anti-hash test** specifically designed to cause massive collisions in C++'s default `unordered_map<int, int>`, leading to a Time Limit Exceeded (TLE). To mitigate this, either fall back to `std::map`, or use a custom hash function combined with a random seed (`chrono::steady_clock`) and `reserve()` to prevent resizing.
:::

## Learn Basic Hashing

### Basic Hashing / Number & Character Hashing
Given an array of integers and $Q$ queries, for each query, determine how many times a given element appears in the array.

**Intuition:** 
A brute-force approach would scan the entire array for each of the $Q$ queries, taking $O(Q \times n)$ time. We can improve this using the pre-compute-then-query pattern. If the maximum element is small, an array-based hash is ideal. If the maximum element is large (e.g., $10^{9}$), allocating an array of that size is impossible, so we use an `unordered_map`.

**C++ Solution (Array Hash for small integers):**
```cpp
#include <iostream>
#include <vector>

using namespace std;

void numberHashingArray(const vector<int>& arr, const vector<int>& queries) {
    // Pre-compute using an array. Assume max element is <= 10^5
    vector<int> cnt(100005, 0);
    for (int num : arr) {
        cnt[num]++;
    }
    
    // Query
    for (int q : queries) {
        if (q <= 100000) {
            cout << cnt[q] << " ";
        } else {
            cout << 0 << " ";
        }
    }
    cout << "\n";
}
```

**C++ Solution (Map Hash for large integers):**
```cpp
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void numberHashingMap(const vector<int>& arr, const vector<int>& queries) {
    // Pre-compute using a hash map for large keys
    unordered_map<int, int> cnt;
    for (int num : arr) {
        cnt[num]++;
    }
    
    // Query
    for (int q : queries) {
        cout << cnt[q] << " ";
    }
    cout << "\n";
}
```

**Complexity:** For the array hash, Time is $O(n + Q)$ and Space is $O(\max(arr))$. For the map hash, Time is $O(n + Q)$ (average) and Space is $O(n)$ in the worst case for storing unique elements.

**Practice:** https://www.geeksforgeeks.org/problems/frequency-of-array-elements-1587115620/1

### Counting Frequencies of Array Elements
Given an array, count the frequency of all elements and print them.

**Intuition:** 
Similar to the basic hashing problem, we can use an `unordered_map` to build the frequencies. The key difference here is that we then iterate over the map itself to report the counts, rather than answering specific queries.

**C++ Solution:**
```cpp
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void countFrequencies(const vector<int>& arr) {
    unordered_map<int, int> freq;
    for (int num : arr) {
        freq[num]++;
    }
    
    // Iterate over the map to print frequencies
    for (auto const& [key, val] : freq) {
        cout << key << " " << val << "\n";
    }
}
```

**Complexity:** Time is $O(n)$ average to build and iterate, and Space is $O(n)$ to store the map.

**Practice:** https://leetcode.com/problems/count-elements-with-maximum-frequency/

### Highest / Lowest Occurring Element in an Array
Given an array, find the highest and lowest occurring elements. If there's a tie for the frequency, return the smaller element.

**Intuition:** 
We need one pass to count all frequencies using an `unordered_map`. Then, we do a second pass over the map's key-value pairs to find the maximum and minimum frequencies. To break ties (when frequencies are equal), we check if the current element is smaller than our stored answer.

**C++ Solution:**
```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>

using namespace std;

void highestAndLowestFrequency(const vector<int>& arr) {
    unordered_map<int, int> freq;
    for (int num : arr) {
        freq[num]++;
    }
    
    int maxFreq = 0, minFreq = INT_MAX;
    int maxEle = INT_MAX, minEle = INT_MAX;
    
    for (auto const& [element, count] : freq) {
        // Update highest occurring element
        if (count > maxFreq) {
            maxFreq = count;
            maxEle = element;
        } else if (count == maxFreq) {
            maxEle = min(maxEle, element);
        }
        
        // Update lowest occurring element
        if (count < minFreq) {
            minFreq = count;
            minEle = element;
        } else if (count == minFreq) {
            minEle = min(minEle, element);
        }
    }
    
    cout << "Highest Frequency Element: " << maxEle << "\n";
    cout << "Lowest Frequency Element: " << minEle << "\n";
}
```

**Complexity:** Time is $O(n)$ average, as finding frequencies takes $O(n)$ and traversing the unique elements in the map takes $O(k)$ where $k \le n$. Space is $O(n)$ in the worst case for the map.

**Practice:** https://www.geeksforgeeks.org/problems/maximum-repeating-number2012/1

::: interview
Interviewers expect you to recognize hashing patterns instantly on sight:
1. **Frequency counting**: "How many times does this occur?"
2. **"Seen" sets**: Using an `unordered_set` for deduplication or `unordered_map` for two-sum-style $O(1)$ lookups of complements.
3. **Grouping**: Using `unordered_map<string, vector<string>>` to group anagrams.
4. **Prefix-sum + hashmap**: Keeping track of seen prefix sums to count subarrays with a specific sum.

These core hashing patterns power a massive fraction of the array and string problems you will encounter in Part III.
:::
