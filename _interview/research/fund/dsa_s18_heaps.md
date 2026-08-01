# Heaps and Priority Queues

::: heavy
The foundational mechanisms of heaps are dense; a precise understanding of the underlying array math and sift operations is required before tackling heap problems.
:::

## Heap Theory and Concept Build-Up

::: definition
A **heap** is a complete binary tree that satisfies the heap-order property. In a max-heap, the value of any node is greater than or equal to the values of its children. In a min-heap, the value is less than or equal to its children.
:::

![A heap is a complete binary tree with the heap-order property; the array stores it level by level.](../assets/ss_260.png)

A complete binary tree is completely filled on all levels except possibly the lowest, which is filled from the left. Because there are no gaps, a heap is optimally represented as a flat array without storing pointers. If a node is at index $i$ (0-indexed):
- Its **left child** is at $2i + 1$.
- Its **right child** is at $2i + 2$.
- Its **parent** is at $\lfloor (i - 1) / 2 \rfloor$.

### Insertion and Bubble-Up

To insert a new element, append it to the end of the array to preserve the complete tree property. Because this new element might violate the heap-order property, the heap is restored by repeatedly swapping the new element with its parent as long as the parent is smaller (in a max-heap) or larger (in a min-heap). This process is known as **bubble-up** or **sift-up**. The time complexity is $O(\log n)$ because the tree height is logarithmic.

![Heap insertion: append at the end, then bubble the new value up while it beats its parent.](../assets/ss_264.png)

### Deletion and Sift-Down (Heapify)

The most common deletion operation is removing the root (the maximum or minimum element). The root is replaced with the last element in the array, and the heap size is reduced by 1. The new root typically violates the heap property. It is restored by repeatedly swapping the node with its largest child (in a max-heap) or smallest child (in a min-heap) until the property holds. This is known as **sift-down** or **heapify**. The time complexity is $O(\log n)$.

![Heapify: sift a node down, swapping with its larger (max-heap) child, to restore the heap property.](../assets/ss_270.png)

### Building a Heap

Building a heap from an unsorted array by inserting elements one by one takes $O(n \log n)$ time. An optimal bottom-up approach starts from the last internal node (the parent of the last leaf) and calls heapify (sift-down) on each node moving backward up to the root.

![Building a heap bottom-up by heapifying every internal node from the last one up to the root.](../assets/ss_273.png)

::: keypoint
The bottom-up build-heap process runs in $O(n)$ time, not $O(n \log n)$.
:::

This $O(n)$ complexity emerges because most nodes reside near the bottom of the tree and have a small maximum sift-down distance. Half the nodes are leaves (height $0$), a quarter are at height $1$, an eighth at height $2$, and so on. The total work is proportional to $\sum_{h=0}^{\log n} \frac{n}{2^{h+1}} h$, which geometrically converges to $O(n)$.

### Heap Sort

Heap sort first builds a max-heap from the array. The maximum element sits at the root. Swapping it with the last element of the heap places it in its final sorted position. The heap size is reduced by 1, and heapify is called on the new root. Repeating this process $n-1$ times leaves the array fully sorted.

![Heap sort: repeatedly swap the root to the end of the array and re-heapify the shrinking heap.](../assets/ss_285.png)

Heap sort operates in $O(n \log n)$ time and $O(1)$ auxiliary space, making it an in-place algorithm. However, it is not a stable sort.

### Standard Library `std::priority_queue`

In C++, heaps are provided via `std::priority_queue` in the `<queue>` header.

::: trap
`priority_queue<int>` is a **max**-heap by default — a frequent surprise.
:::

To instantiate a min-heap, the underlying container and the comparator must be explicitly specified: `std::priority_queue<int, std::vector<int>, std::greater<int>>`.

For custom comparators, define a struct with an `operator()` that returns `true` if the first argument has *lower* priority than the second. (The comparator reverses standard logic: returning `true` moves the element lower down the extraction order).

```cpp
#include <iostream>
#include <queue>
#include <vector>

struct CustomCompare {
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
        // Create a min-heap based on the second element.
        // Return true if 'a' has lower priority (larger second element) than 'b'.
        return a.second > b.second;
    }
};

int main() {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, CustomCompare> pq;
    pq.push({1, 10});
    pq.push({2, 5});
    
    // Outputs 2 because it has the smaller second element (5 < 10)
    std::cout << pq.top().first << '\n';
    return 0;
}
```

(Refer to the Part I STL reference for an exhaustive treatment of `std::priority_queue` and the three methods for defining custom comparators.)

## Learning

### Implement Min Heap
Implement a min-heap from scratch using a vector. Support `insert`, `getMin`, and `extractMin` operations.

**Intuition:** 
A min-heap ensures the smallest element resides at the root. The structure maps perfectly to an array. Insertion pushes a new element to the end followed by a sift-up. Extraction saves the root, overwrites it with the last element, pops the back, and restores the tree via sift-down.

```cpp
#include <vector>
#include <stdexcept>
#include <algorithm>

class MinHeap {
private:
    std::vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void siftUp(int i) {
        while (i > 0 && heap[parent(i)] > heap[i]) {
            std::swap(heap[parent(i)], heap[i]);
            i = parent(i);
        }
    }

    void siftDown(int i) {
        int minIndex = i;
        int l = leftChild(i);
        if (l < heap.size() && heap[l] < heap[minIndex]) {
            minIndex = l;
        }
        int r = rightChild(i);
        if (r < heap.size() && heap[r] < heap[minIndex]) {
            minIndex = r;
        }
        if (i != minIndex) {
            std::swap(heap[i], heap[minIndex]);
            siftDown(minIndex);
        }
    }

public:
    MinHeap() {}

    void insert(int val) {
        heap.push_back(val);
        siftUp(heap.size() - 1);
    }

    int getMin() {
        if (heap.empty()) throw std::out_of_range("Heap is empty");
        return heap.front();
    }

    int extractMin() {
        if (heap.empty()) throw std::out_of_range("Heap is empty");
        int minVal = heap.front();
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            siftDown(0);
        }
        return minVal;
    }
};
```
**Complexity:** Time: $O(\log n)$ for `insert` and `extractMin`, $O(1)$ for `getMin`. Space: $O(n)$ to store elements.
**Practice:** https://www.geeksforgeeks.org/problems/operations-on-binary-min-heap/1

### Check if an Array Represents a Min Heap
Given an array, determine if it represents a valid min-heap.

**Intuition:** 
A valid min-heap must uphold the heap property where every parent node is less than or equal to its children. Iterating through all internal nodes (up to the parent of the last element) and validating this constraint against existing children verifies the heap.

```cpp
#include <vector>

bool isMinHeap(const std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i <= (n - 2) / 2; i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < n && arr[i] > arr[left]) {
            return false;
        }
        if (right < n && arr[i] > arr[right]) {
            return false;
        }
    }
    return true;
}
```
**Complexity:** Time: $O(n)$ validating each edge exactly once. Space: $O(1)$.
**Practice:** https://www.geeksforgeeks.org/problems/is-binary-tree-heap/1

### Convert Min Heap to Max Heap
Given an array representing a min-heap, convert it into a max-heap in linear time.

**Intuition:** 
The fact that the input is a min-heap is misdirection; it is simply an array of elements that must be restructured into a max-heap. Applying the bottom-up build-heap approach using max-heap sift-down semantics accomplishes this optimally.

```cpp
#include <vector>
#include <algorithm>

void maxHeapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void convertMinToMaxHeap(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = (n - 2) / 2; i >= 0; i--) {
        maxHeapify(arr, n, i);
    }
}
```
**Complexity:** Time: $O(n)$ identical to standard bottom-up build-heap. Space: $O(\log n)$ recursion depth, reducible to $O(1)$ iteratively.
**Practice:** https://www.geeksforgeeks.org/problems/convert-min-heap-to-max-heap-1666385109/1

## Medium

### Kth Largest Element in an Array
Given an integer array and an integer $k$, return the $k$-th largest element in the array.

**Intuition:** 
Sorting the array takes $O(n \log n)$ time. To optimize, maintain a min-heap bounded to size $k$. As elements stream in, push them into the heap. If the size exceeds $k$, pop the minimum. The heap effectively traps the largest $k$ elements, and the smallest among them (the root) is the $k$-th largest overall. 

QuickSelect provides an alternative $O(n)$ average time solution, though its worst-case is $O(n^2)$. The min-heap strictly guarantees $O(n \log k)$.

```cpp
#include <vector>
#include <queue>

int findKthLargest(std::vector<int>& nums, int k) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    for (int num : nums) {
        minHeap.push(num);
        if (minHeap.size() > k) {
            minHeap.pop();
        }
    }
    return minHeap.top();
}
```
**Complexity:** Time: $O(n \log k)$ because inserting bounds operation to $\log k$. Space: $O(k)$ for the heap footprint.
**Practice:** https://leetcode.com/problems/kth-largest-element-in-an-array/

### Kth Smallest Element
Given an array and a number $k$, find the $k$-th smallest element.

**Intuition:** 
The logic is the inverse of the $k$-th largest problem. Maintain a max-heap of size $k$. Popping the maximum whenever the size breaches $k$ ensures only the $k$ smallest items remain. The root holds the $k$-th smallest value.

```cpp
#include <vector>
#include <queue>

int kthSmallest(std::vector<int>& arr, int k) {
    std::priority_queue<int> maxHeap;
    for (int num : arr) {
        maxHeap.push(num);
        if (maxHeap.size() > k) {
            maxHeap.pop();
        }
    }
    return maxHeap.top();
}
```
**Complexity:** Time: $O(n \log k)$. Space: $O(k)$.
**Practice:** https://www.geeksforgeeks.org/problems/kth-smallest-element5635/1

### Merge K Sorted Lists
You are given an array of $k$ linked-lists, each sorted in ascending order. Merge all the linked-lists into one sorted linked-list and return it.

**Intuition:** 
Collecting all nodes to sort takes $O(N \log N)$ where $N$ is the global node count. Recognizing the local sorted property allows maintaining a pointer to the head of each list. Identifying the smallest node across $k$ candidates efficiently requires a min-heap. Pop the minimum node, append it to the aggregated list, and push its next node back into the heap.

::: keypoint
When merging $k$ sorted streams, use a min-heap of size $k$ tracking the current front of each stream.
:::

```cpp
#include <vector>
#include <queue>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

struct CompareNode {
    bool operator()(ListNode* a, ListNode* b) const {
        return a->val > b->val;
    }
};

ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    std::priority_queue<ListNode*, std::vector<ListNode*>, CompareNode> minHeap;
    
    for (ListNode* head : lists) {
        if (head != nullptr) {
            minHeap.push(head);
        }
    }
    
    ListNode dummy(0);
    ListNode* tail = &dummy;
    
    while (!minHeap.empty()) {
        ListNode* smallest = minHeap.top();
        minHeap.pop();
        
        tail->next = smallest;
        tail = tail->next;
        
        if (smallest->next != nullptr) {
            minHeap.push(smallest->next);
        }
    }
    
    return dummy.next;
}
```
**Complexity:** Time: $O(N \log k)$ where $N$ is the total elements across all lists. Space: $O(k)$ for storing up to $k$ list heads.
**Practice:** https://leetcode.com/problems/merge-k-sorted-lists/

### Replace Elements by Their Rank
Given an array, replace each element with its relative rank. The smallest element receives rank 1, the second smallest rank 2, and so on. Equal elements receive the same rank.

**Intuition:** 
Ranking requires global sorting followed by deduplication (coordinate compression). Duplicate the array, sort it, and remove repeating elements. Store the results in a hash map associating elements to their ranks (index + 1), then map original elements to ranks.

```cpp
#include <vector>
#include <algorithm>
#include <unordered_map>

std::vector<int> arrayRankTransform(std::vector<int>& arr) {
    std::vector<int> sortedArr = arr;
    std::sort(sortedArr.begin(), sortedArr.end());
    sortedArr.erase(std::unique(sortedArr.begin(), sortedArr.end()), sortedArr.end());
    
    std::unordered_map<int, int> rankMap;
    for (int i = 0; i < sortedArr.size(); i++) {
        rankMap[sortedArr[i]] = i + 1;
    }
    
    std::vector<int> result(arr.size());
    for (int i = 0; i < arr.size(); i++) {
        result[i] = rankMap[arr[i]];
    }
    return result;
}
```
**Complexity:** Time: $O(n \log n)$ due to sorting. Space: $O(n)$ mapping cache.
**Practice:** https://leetcode.com/problems/rank-transform-of-an-array/

### Task Scheduler
Given an array of CPU tasks represented by letters and an integer $n$ (the cooldown period between identical tasks), find the minimum intervals required to complete all tasks.

**Intuition:** 
Greedy scheduling minimizes idle slots. Prioritize tasks boasting the highest remaining frequencies. A max-heap naturally surfaces the most urgent tasks. Process items in blocks of $n+1$ cycles, extracting the top distinct tasks, reducing their frequencies, and pushing survivors back after the cycle. A mathematical formula derived from the max frequency also solves this in $O(T)$ without simulation.

```cpp
#include <vector>
#include <queue>
#include <unordered_map>

int leastInterval(std::vector<char>& tasks, int n) {
    std::unordered_map<char, int> counts;
    for (char task : tasks) counts[task]++;
    
    std::priority_queue<int> maxHeap;
    for (auto const& [task, count] : counts) {
        maxHeap.push(count);
    }
    
    int time = 0;
    while (!maxHeap.empty()) {
        std::vector<int> waitlist;
        int cycle = n + 1;
        
        while (cycle > 0 && !maxHeap.empty()) {
            int currentFreq = maxHeap.top();
            maxHeap.pop();
            if (currentFreq > 1) {
                waitlist.push_back(currentFreq - 1);
            }
            time++;
            cycle--;
        }
        
        for (int freq : waitlist) {
            maxHeap.push(freq);
        }
        
        if (!maxHeap.empty()) {
            time += cycle; // Add necessary idle time
        }
    }
    
    return time;
}
```
**Complexity:** Time: $O(T \log 26) = O(T)$ given $T$ tasks and bounded character scope. Space: $O(1)$ fixed constraint mapped to 26 letters.
**Practice:** https://leetcode.com/problems/task-scheduler/

### Hand of Straights
Given an integer array `hand` and a group size `groupSize`, return `true` if the hand can be rearranged into groups of `groupSize` consecutive cards.

**Intuition:** 
Organizing consecutive sequences must originate greedily from the smallest available card. Use an ordered map (functioning similarly to a sorted frequency heap) to track inventory. Identify the smallest key and attempt to deduct uniform counts extending $groupSize$ sequentially.

```cpp
#include <vector>
#include <map>

bool isNStraightHand(std::vector<int>& hand, int groupSize) {
    if (hand.size() % groupSize != 0) return false;
    
    std::map<int, int> cardCounts;
    for (int card : hand) {
        cardCounts[card]++;
    }
    
    for (auto it = cardCounts.begin(); it != cardCounts.end(); ++it) {
        if (it->second > 0) {
            int count = it->second;
            int startCard = it->first;
            
            for (int i = 0; i < groupSize; i++) {
                if (cardCounts[startCard + i] < count) {
                    return false;
                }
                cardCounts[startCard + i] -= count;
            }
        }
    }
    
    return true;
}
```
**Complexity:** Time: $O(n \log n)$ tree-map operations. Space: $O(n)$ mapping layout.
**Practice:** https://leetcode.com/problems/hand-of-straights/

## Hard

### Design Twitter
Design a simplified version of Twitter where users can post tweets, follow/unfollow another user, and fetch the 10 most recent tweets in their news feed (from themselves and their followees).

**Intuition:** 
Fetching the news feed mimics merging $K$ sorted streams. Every user produces a sequence of chronological tweets. To yield the most recent 10, poll the latest posts from the user and their followees, dump them into a max-heap (sorted by an internal timestamp counter), and extract the heaviest 10.

```cpp
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

class Twitter {
private:
    int time;
    std::unordered_map<int, std::unordered_set<int>> followers;
    std::unordered_map<int, std::vector<std::pair<int, int>>> tweets;

public:
    Twitter() : time(0) {}
    
    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back({time++, tweetId});
    }
    
    std::vector<int> getNewsFeed(int userId) {
        std::priority_queue<std::pair<int, int>> maxHeap;
        
        for (auto const& tweet : tweets[userId]) {
            maxHeap.push(tweet);
        }
        
        if (followers.find(userId) != followers.end()) {
            for (int followeeId : followers[userId]) {
                for (auto const& tweet : tweets[followeeId]) {
                    maxHeap.push(tweet);
                }
            }
        }
        
        std::vector<int> feed;
        while (!maxHeap.empty() && feed.size() < 10) {
            feed.push_back(maxHeap.top().second);
            maxHeap.pop();
        }
        return feed;
    }
    
    void follow(int followerId, int followeeId) {
        if (followerId != followeeId) {
            followers[followerId].insert(followeeId);
        }
    }
    
    void unfollow(int followerId, int followeeId) {
        if (followers.find(followerId) != followers.end()) {
            followers[followerId].erase(followeeId);
        }
    }
};
```
**Complexity:** Time: $O(F \cdot T \log(F \cdot T))$ bound by $F$ followees and $T$ tweets pushed to the heap. Lazy traversal trims this to $O(F \log F)$. Space: $O(\text{users} + \text{tweets})$.
**Practice:** https://leetcode.com/problems/design-twitter/

### Minimum Cost to Connect Sticks
You have some number of sticks with positive integer lengths. You can connect any two sticks of lengths $x$ and $y$ into one stick by paying a cost of $x + y$. Return the minimum cost to connect all sticks into one.

**Intuition:** 
A greedy policy applies: continually bond the two shortest loose sticks. Cost cascades, so deferring large lengths limits multiplicative penalties. A min-heap manages the active lengths. Extract the two minimums, record their sum as incurred cost, and reinject the newly fused stick. (This maps mathematically to constructing a Huffman Tree).

```cpp
#include <vector>
#include <queue>

int connectSticks(std::vector<int>& sticks) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap(sticks.begin(), sticks.end());
    int totalCost = 0;
    
    while (minHeap.size() > 1) {
        int stick1 = minHeap.top(); minHeap.pop();
        int stick2 = minHeap.top(); minHeap.pop();
        
        int cost = stick1 + stick2;
        totalCost += cost;
        minHeap.push(cost);
    }
    
    return totalCost;
}
```
**Complexity:** Time: $O(n \log n)$ initiating and collapsing $n-1$ pairs. Space: $O(n)$ containing the heap.
**Practice:** https://leetcode.com/problems/minimum-cost-to-connect-sticks/

### Kth Largest in a Stream
Design a class to find the $k$-th largest element in a stream.

**Intuition:** 
When bounds change dynamically and only the top $k$ values matter, a dedicated min-heap of size exactly $k$ solves it continuously. The array contents within the heap equate to the elite $k$ seen so far. Fresh items surpassing the root unseat it and cascade downward.

```cpp
#include <vector>
#include <queue>

class KthLargest {
private:
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    int k;

public:
    KthLargest(int k, std::vector<int>& nums) {
        this->k = k;
        for (int num : nums) {
            add(num);
        }
    }
    
    int add(int val) {
        minHeap.push(val);
        if (minHeap.size() > k) {
            minHeap.pop();
        }
        return minHeap.top();
    }
};
```
**Complexity:** Time: $O(\log k)$ per `add()` operation, $O(n \log k)$ base build. Space: $O(k)$.
**Practice:** https://leetcode.com/problems/kth-largest-element-in-a-stream/

### Maximum Sum Combination
Given two integer arrays $A$ and $B$ of size $n$, find the maximum $k$ valid sum combinations $A[i] + B[j]$.

**Intuition:** 
A naive double traversal computes $n^2$ pairs, demanding $O(n^2 \log k)$ cycles. Optimizing this involves sorting both inputs descending. The absolute largest aggregate is fundamentally $A[0] + B[0]$. The subsequent largest strictly belongs to the edges $A[1] + B[0]$ or $A[0] + B[1]$. Utilize a max-heap tracking `(sum, i, j)` paired with a visited set. Pop the peak sum and sequentially query its spatial neighbors `(i+1, j)` and `(i, j+1)`.

```cpp
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

std::vector<int> solve(std::vector<int>& A, std::vector<int>& B, int C) {
    std::sort(A.begin(), A.end(), std::greater<int>());
    std::sort(B.begin(), B.end(), std::greater<int>());
    
    std::priority_queue<std::pair<int, std::pair<int, int>>> maxHeap;
    std::set<std::pair<int, int>> visited;
    
    maxHeap.push({A[0] + B[0], {0, 0}});
    visited.insert({0, 0});
    
    std::vector<int> result;
    for (int count = 0; count < C; count++) {
        auto top = maxHeap.top();
        maxHeap.pop();
        
        result.push_back(top.first);
        int i = top.second.first;
        int j = top.second.second;
        
        if (i + 1 < A.size() && visited.find({i + 1, j}) == visited.end()) {
            maxHeap.push({A[i + 1] + B[j], {i + 1, j}});
            visited.insert({i + 1, j});
        }
        if (j + 1 < B.size() && visited.find({i, j + 1}) == visited.end()) {
            maxHeap.push({A[i] + B[j + 1], {i, j + 1}});
            visited.insert({i, j + 1});
        }
    }
    
    return result;
}
```
**Complexity:** Time: $O(n \log n + k \log k)$. Sorting takes $O(n \log n)$, extracting logic iterates $k$ bounds. Space: $O(k)$ for concurrent tracking.
**Practice:** https://www.interviewbit.com/problems/maximum-sum-combinations/

### Find Median from Data Stream
Design a data structure that supports adding numbers from a data stream and finding the median of all elements seen so far.

**Intuition:** 
The median slices a sorted stream equally into a lower bracket and an upper bracket. Maintain a **max-heap** encapsulating the lower numbers to yield the peak of the bottom half instantly. Oppositely, host a **min-heap** encompassing the upper magnitude numbers to tap the lowest of the upper echelon.

::: keypoint
To find the running median, use two heaps: a max-heap for the lower half and a min-heap for the upper half. Maintain a size difference of at most 1.
:::

When ingesting items, append to the max-heap, funnel its peak directly to the min-heap to preserve bounds, and rebound any size imbalances back to the max-heap.

```cpp
#include <queue>
#include <vector>

class MedianFinder {
private:
    std::priority_queue<int> maxHeap; // Lower half
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap; // Upper half

public:
    MedianFinder() {}
    
    void addNum(int num) {
        maxHeap.push(num);
        minHeap.push(maxHeap.top());
        maxHeap.pop();
        
        if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double findMedian() {
        if (maxHeap.size() > minHeap.size()) {
            return maxHeap.top();
        }
        return (maxHeap.top() + minHeap.top()) / 2.0;
    }
};
```
**Complexity:** Time: $O(\log n)$ per `addNum`, $O(1)$ scaling for `findMedian`. Space: $O(n)$ footprint caching the sequence.
**Practice:** https://leetcode.com/problems/find-median-from-data-stream/

### Top K Frequent Elements
Given an integer array and an integer $k$, return the $k$ most frequent elements.

**Intuition:** 
Generate occurrence frequencies universally into a map. Pass these through a min-heap constrained tightly to size $k$. The layout pairs `(frequency, element)`. Alternatively, a frequency map transposed into lists acts as Bucket Sort delivering strict $O(n)$ boundaries.

```cpp
#include <vector>
#include <unordered_map>
#include <queue>

std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
    std::unordered_map<int, int> counts;
    for (int num : nums) {
        counts[num]++;
    }
    
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> minHeap;
    
    for (auto const& [num, freq] : counts) {
        minHeap.push({freq, num});
        if (minHeap.size() > k) {
            minHeap.pop();
        }
    }
    
    std::vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().second);
        minHeap.pop();
    }
    return result;
}
```
**Complexity:** Time: $O(n \log k)$ mapping traversal against heap. Space: $O(n)$ hash array plus $O(k)$ capacity.
**Practice:** https://leetcode.com/problems/top-k-frequent-elements/

## Conclusion

::: interview
What interviewers probe here:
- **K-th or Top K problems:** Recognize that finding the $k$-th largest requires a **min-heap** of size $k$, while the $k$-th smallest needs a **max-heap** of size $k$.
- **Streaming Median:** Immediately associate this with the two-heaps approach.
- **Merge K Sorted Streams:** Map this to a min-heap of size $k$ holding the head nodes.
- **Build-Heap Complexity:** Be ready to justify why bottom-up heap construction is $O(n)$ and not $O(n \log n)$.
:::
