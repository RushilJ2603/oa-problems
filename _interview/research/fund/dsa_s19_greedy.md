# Greedy Algorithms

::: heavy
The **greedy paradigm** is perhaps the most natural way human beings solve optimization problems: at each step, make the choice that looks best right now, without ever reconsidering past choices.
:::

::: definition
A **greedy algorithm** builds a solution piece by piece, always choosing the next piece that offers the most immediate benefit. For a greedy algorithm to yield the globally optimal solution, the problem must exhibit the **greedy-choice property** (a local optimum leads to a global optimum) and **optimal substructure** (an optimal solution contains optimal solutions to subproblems).
:::

To rigorously prove that a greedy choice is safe—and this is exactly how you justify a greedy approach in an interview—we typically use an **exchange argument**. You assume, for the sake of contradiction, that there exists an optimal solution that *does not* make the greedy choice. You then show that you can swap elements to transform that hypothetical optimal solution into the greedy solution without worsening its score. Because the swapped solution is at least as good, the greedy choice is always safe to make.

::: trap
Greedy algorithms are seductive but often **wrong**. For example, in the 0/1 Knapsack problem, greedily taking the most valuable items often leaves wasted space, leading to a suboptimal total. Always ask, "Can I prove the greedy choice is safe?" before committing. If the answer is no, the problem likely requires Dynamic Programming.
:::

## Easy Problems

### Assign Cookies
Given two arrays representing the greed factors of children and the sizes of available cookies, maximize the number of content children. A child is content if they receive a cookie with a size greater than or equal to their greed factor.

**Intuition / approach:** To maximize the number of children fed, we should always satisfy the least greedy children first, using the smallest possible cookies that meet their requirements. If the smallest cookie cannot satisfy the least greedy child, it cannot satisfy any other child, so we discard it.
**Greedy choice:** Assign the smallest available valid cookie to the child with the smallest unmet greed. This is safe because giving a larger cookie to a less greedy child is a waste; that larger cookie could have satisfied a more demanding child later.

```cpp
#include <vector>
#include <algorithm>

using namespace std;

int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    
    int child = 0;
    int cookie = 0;
    
    while (child < g.size() && cookie < s.size()) {
        if (s[cookie] >= g[child]) {
            child++; // The child is content
        }
        cookie++; // Always move to the next cookie
    }
    
    return child;
}
```
**Complexity:** Time: $O(n \log n + m \log m)$ to sort both arrays, space: $O(1)$ ignoring the space used by the sorting algorithm.
**Practice:** https://leetcode.com/problems/assign-cookies/

### Fractional Knapsack
Given the weights and values of $n$ items, maximize the total value in a knapsack of capacity $W$. Unlike 0/1 knapsack, you can break items into fractions.

**Intuition / approach:** We want the maximum bang for our buck. We calculate the value-to-weight ratio for each item. We sort the items in descending order of this ratio and greedily take as much of the highest-ratio items as possible until the knapsack is full.
**Greedy choice:** Always take the item with the highest value-to-weight ratio. This is safe because taking a lower-ratio item instead would strictly decrease the total value per unit of weight.

::: keypoint
The ability to take fractions of an item is what makes the greedy choice safe. If we could not take fractions (the 0/1 Knapsack problem), the greedy approach fails and we must use Dynamic Programming.
:::

```cpp
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int value;
    int weight;
};

double fractionalKnapsack(int W, vector<Item>& items) {
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return (double)a.value / a.weight > (double)b.value / b.weight;
    });
    
    double totalValue = 0.0;
    
    for (const auto& item : items) {
        if (W >= item.weight) {
            totalValue += item.value;
            W -= item.weight;
        } else {
            totalValue += item.value * ((double)W / item.weight);
            break;
        }
    }
    
    return totalValue;
}
```
**Complexity:** Time: $O(n \log n)$ to sort the items, space: $O(1)$.
**Practice:** https://practice.geeksforgeeks.org/problems/fractional-knapsack-1587115620/1

### Lemonade Change
Customers stand in a queue to buy a $5 lemonade. They pay with a $5, $10, or $20 bill. You start with no change. Return true if you can provide every customer with correct change.

**Intuition / approach:** When a customer pays with $5, we just take it. For a $10 bill, we must give a $5 bill. For a $20 bill, we can either give one $10 and one $5, or three $5 bills. Since $5 bills are more versatile (they can be used to make change for both $10 and $20), we should hold onto them as long as possible.
**Greedy choice:** When making change for $20, always prefer giving one $10 and one $5 bill over three $5 bills. This is safe because $5 bills are strictly more useful for future transactions.

```cpp
#include <vector>

using namespace std;

bool lemonadeChange(vector<int>& bills) {
    int fives = 0;
    int tens = 0;
    
    for (int bill : bills) {
        if (bill == 5) {
            fives++;
        } else if (bill == 10) {
            if (fives == 0) return false;
            fives--;
            tens++;
        } else { // bill == 20
            if (tens > 0 && fives > 0) {
                tens--;
                fives--;
            } else if (fives >= 3) {
                fives -= 3;
            } else {
                return false;
            }
        }
    }
    return true;
}
```
**Complexity:** Time: $O(n)$ to process the queue once, space: $O(1)$.
**Practice:** https://leetcode.com/problems/lemonade-change/

### Valid Parenthesis Checker
Given a string containing '(', ')', and '*', return whether the string is a valid parenthesis sequence. An asterisk '*' can represent '(', ')', or an empty string.

**Intuition / approach:** A standard parenthesis checker uses a counter or stack for open parentheses. With '*', the exact number of open parentheses becomes a range. We track the minimum and maximum possible number of open parentheses at any point.
**Greedy choice:** At each step, update the range of possible open parentheses. If the maximum possible open count ever becomes negative, there are too many closing parentheses, so we return false. We cap the minimum possible open count at 0 because an open count cannot be negative.

```cpp
#include <string>
#include <algorithm>

using namespace std;

bool checkValidString(string s) {
    int low = 0;  // Minimum possible open parentheses
    int high = 0; // Maximum possible open parentheses
    
    for (char c : s) {
        if (c == '(') {
            low++;
            high++;
        } else if (c == ')') {
            low--;
            high--;
        } else { // c == '*'
            low--;  // Treat as ')'
            high++; // Treat as '('
        }
        
        if (high < 0) return false; // More ')' than we could possibly match
        low = max(low, 0); // Open count cannot be negative
    }
    
    return low == 0; // Valid if all open parentheses can be closed
}
```
**Complexity:** Time: $O(n)$ for a single pass, space: $O(1)$.
**Practice:** https://leetcode.com/problems/valid-parenthesis-string/

## Medium / Hard

### N Meetings in One Room
Given $n$ meetings with their start and end times, find the maximum number of meetings that can be accommodated in a single room.

**Intuition / approach:** To fit the maximum number of meetings, we should finish meetings as early as possible. This leaves the most remaining time to accommodate subsequent meetings.
**Greedy choice:** Sort meetings by their end times. Always pick the next meeting that starts after the current meeting ends. This is the classic activity selection problem; an exchange argument proves that swapping out an early-ending meeting for a later-ending one can only decrease or keep the same the number of remaining valid meetings.

```cpp
#include <vector>
#include <algorithm>

using namespace std;

struct Meeting {
    int start;
    int end;
    int pos;
};

int maxMeetings(int start[], int end[], int n) {
    vector<Meeting> meet(n);
    for (int i = 0; i < n; i++) {
        meet[i] = {start[i], end[i], i + 1};
    }
    
    // Sort by end time
    sort(meet.begin(), meet.end(), [](const Meeting& a, const Meeting& b) {
        return a.end < b.end;
    });
    
    int count = 1;
    int freeTime = meet[0].end;
    
    for (int i = 1; i < n; i++) {
        if (meet[i].start > freeTime) {
            count++;
            freeTime = meet[i].end;
        }
    }
    
    return count;
}
```
**Complexity:** Time: $O(n \log n)$ to sort the meetings, space: $O(n)$ to store them.
**Practice:** https://practice.geeksforgeeks.org/problems/n-meetings-in-one-room-1587115620/1

### Jump Game I
Given an array of non-negative integers where each element represents your maximum jump length at that position, determine if you can reach the last index.

**Intuition / approach:** We can keep track of the maximum index we can reach so far. We iterate through the array, updating this maximum reach. If we ever arrive at an index that is beyond our maximum reach, we are stuck.
**Greedy choice:** At each step, update the farthest reachable index to be the maximum of its current value and the reach from the current position (`i + nums[i]`). This is safe because moving forward only opens up more possibilities.

```cpp
#include <vector>
#include <algorithm>

using namespace std;

bool canJump(vector<int>& nums) {
    int maxReach = 0;
    int n = nums.size();
    
    for (int i = 0; i < n; i++) {
        if (i > maxReach) {
            return false; // We can't even reach this index
        }
        maxReach = max(maxReach, i + nums[i]);
        if (maxReach >= n - 1) {
            return true; // We can reach the end
        }
    }
    
    return true;
}
```
**Complexity:** Time: $O(n)$ for a single scan, space: $O(1)$.
**Practice:** https://leetcode.com/problems/jump-game/

### Jump Game II
Given an array where each element represents the maximum jump length, find the minimum number of jumps to reach the last index.

**Intuition / approach:** We can group the indices into "levels" akin to a Breadth-First Search. The first level is index 0. The next level contains all indices reachable from level 0, and so on. We want to find the level that contains the last index.
**Greedy choice:** We maintain the `currentEnd` of our current level and the `farthest` index reachable from the current level. When we iterate past `currentEnd`, we have essentially made a jump, and our new level boundary becomes `farthest`.

```cpp
#include <vector>
#include <algorithm>

using namespace std;

int jump(vector<int>& nums) {
    int jumps = 0;
    int currentEnd = 0;
    int farthest = 0;
    
    for (int i = 0; i < nums.size() - 1; i++) {
        farthest = max(farthest, i + nums[i]);
        
        // Once we hit the end of the current jump level, we must jump
        if (i == currentEnd) {
            jumps++;
            currentEnd = farthest;
        }
    }
    
    return jumps;
}
```
**Complexity:** Time: $O(n)$ as we process each element once, space: $O(1)$.
**Practice:** https://leetcode.com/problems/jump-game-ii/

### Minimum Number of Platforms
Given arrival and departure times of all trains that reach a railway station, find the minimum number of platforms required so that no train is kept waiting.

**Intuition / approach:** This problem asks for the maximum number of overlapping intervals at any point in time. We can decompose the intervals into independent events: "a train arrives" and "a train departs".
**Greedy choice:** Sort all arrivals and all departures independently. We sweep a time pointer. If an arrival happens before the next departure, we need a new platform. If a departure happens, a platform becomes free. We track the maximum platforms used. This safely accounts for all overlaps.

```cpp
#include <vector>
#include <algorithm>

using namespace std;

int findPlatform(int arr[], int dep[], int n) {
    sort(arr, arr + n);
    sort(dep, dep + n);
    
    int platforms = 1;
    int maxPlatforms = 1;
    int i = 1; // pointer for arrivals
    int j = 0; // pointer for departures
    
    while (i < n && j < n) {
        if (arr[i] <= dep[j]) {
            platforms++;
            i++;
        } else {
            platforms--;
            j++;
        }
        maxPlatforms = max(maxPlatforms, platforms);
    }
    
    return maxPlatforms;
}
```
**Complexity:** Time: $O(n \log n)$ to sort both arrays, space: $O(1)$ ignoring sort overhead.
**Practice:** https://practice.geeksforgeeks.org/problems/minimum-platforms-1587115620/1

### Job Sequencing Problem
Given a set of $n$ jobs where each job comes with a deadline and a profit, maximize total profit if only one job can be scheduled at a time, each taking 1 unit of time.

**Intuition / approach:** To maximize profit, we should prioritize the highest-paying jobs. We sort the jobs by profit descending. To leave room for other jobs, we should delay the execution of a job as late as possible without missing its deadline.
**Greedy choice:** Sort by profit. Assign each job to the latest possible free slot on or before its deadline. This is safe because taking the highest profit early and putting it in the latest slot leaves earlier slots open for other jobs. (Note: This can be optimized to $O(n \alpha(n))$ using Disjoint Set Union).

```cpp
#include <vector>
#include <algorithm>

using namespace std;

struct Job {
    int id;
    int dead;
    int profit;
};

vector<int> JobScheduling(Job arr[], int n) {
    sort(arr, arr + n, [](Job a, Job b) {
        return a.profit > b.profit;
    });
    
    int maxDeadline = 0;
    for (int i = 0; i < n; i++) {
        maxDeadline = max(maxDeadline, arr[i].dead);
    }
    
    vector<int> slot(maxDeadline + 1, -1);
    
    int countJobs = 0;
    int jobProfit = 0;
    
    for (int i = 0; i < n; i++) {
        // Find a free slot starting from the job's deadline
        for (int j = arr[i].dead; j > 0; j--) {
            if (slot[j] == -1) {
                slot[j] = i;
                countJobs++;
                jobProfit += arr[i].profit;
                break;
            }
        }
    }
    
    return {countJobs, jobProfit};
}
```
**Complexity:** Time: $O(n \log n + n \times D)$ where $D$ is the maximum deadline, space: $O(D)$.
**Practice:** https://practice.geeksforgeeks.org/problems/job-sequencing-problem-1587115620/1

### Candy
There are $n$ children standing in a line, each with a rating. You must give at least one candy to each child. Children with a higher rating must get more candies than their neighbors. Find the minimum candies required.

**Intuition / approach:** A local condition (rating comparison with neighbors) governs the distribution. We can break this into two passes: ensure every child has more candies than their left neighbor if their rating is higher, then ensure they have more candies than their right neighbor.
**Greedy choice:** Initialize all candies to 1. Scan left-to-right to fix left-neighbor constraints. Then scan right-to-left to fix right-neighbor constraints, taking the maximum of the current candies and `right_neighbor_candies + 1`. This safely fulfills all conditions minimally.

::: keypoint
The two-pass approach cleanly isolates the dependencies. A single pass would fail because a change triggered by a right neighbor could invalidate a previously established left-neighbor relationship.
:::

```cpp
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int candy(vector<int>& ratings) {
    int n = ratings.size();
    vector<int> candies(n, 1);
    
    // Left to right pass
    for (int i = 1; i < n; i++) {
        if (ratings[i] > ratings[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }
    
    // Right to left pass
    for (int i = n - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1]) {
            candies[i] = max(candies[i], candies[i + 1] + 1);
        }
    }
    
    return accumulate(candies.begin(), candies.end(), 0);
}
```
**Complexity:** Time: $O(n)$ for two linear passes, space: $O(n)$ for the candies array.
**Practice:** https://leetcode.com/problems/candy/

### Shortest Job First
Given an array of burst times of $n$ processes, schedule them to minimize the average waiting time.

**Intuition / approach:** If a long job runs first, all subsequent jobs wait for its entire duration. By scheduling the shortest job first, we minimize the accumulation of wait times for all following jobs.
**Greedy choice:** Sort the jobs by their burst times in ascending order. This guarantees the minimum total waiting time.

```cpp
#include <vector>
#include <algorithm>

using namespace std;

long long solve(vector<int>& bt) {
    sort(bt.begin(), bt.end());
    
    long long waitTime = 0;
    long long totalWaitTime = 0;
    
    for (int i = 0; i < bt.size(); i++) {
        totalWaitTime += waitTime;
        waitTime += bt[i];
    }
    
    return totalWaitTime / bt.size(); // Integer division generally intended, adjust for float if required
}
```
**Complexity:** Time: $O(n \log n)$ to sort the burst times, space: $O(1)$.
**Practice:** https://practice.geeksforgeeks.org/problems/shortest-job-first/1

### LRU Page Replacement
Given a sequence of pages accessed by a CPU and the memory capacity (number of frames), find the total number of page faults using the Least Recently Used (LRU) replacement algorithm.

**Intuition / approach:** We must count page faults. A page fault occurs when a required page is not in memory. When memory is full, LRU evicts the page that was accessed least recently.
**Greedy choice:** Maintain a record of pages and their most recent access indices. When eviction is necessary, scan the current pages in memory and replace the one with the oldest access index. Note that this problem focuses on the simulation and counting, not necessarily building the $O(1)$ LRU cache data structure itself.

```cpp
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int pageFaults(int N, int C, int pages[]) {
    unordered_map<int, int> recentAccess; // page -> last index accessed
    int faults = 0;
    
    for (int i = 0; i < N; i++) {
        int page = pages[i];
        
        if (recentAccess.find(page) == recentAccess.end()) {
            faults++;
            if (recentAccess.size() == C) {
                // Find least recently used page
                int lruPage = -1;
                int minIndex = N;
                for (auto const& [p, idx] : recentAccess) {
                    if (idx < minIndex) {
                        minIndex = idx;
                        lruPage = p;
                    }
                }
                recentAccess.erase(lruPage);
            }
        }
        recentAccess[page] = i; // Update access index
    }
    
    return faults;
}
```
**Complexity:** Time: $O(n \times C)$ where $C$ is the capacity (for searching the minimum), space: $O(C)$ to store pages in memory.
**Practice:** https://practice.geeksforgeeks.org/problems/page-faults-in-lru5603/1

### Insert Interval
Given a set of non-overlapping intervals sorted by their start time, insert a new interval into the intervals (merge if necessary).

**Intuition / approach:** The intervals are already sorted. We can build the answer by scanning left to right. We encounter three phases: intervals entirely before the new interval, intervals overlapping with the new interval, and intervals entirely after.
**Greedy choice:** Add non-overlapping intervals unchanged. When overlapping, greedily merge them into the new interval by taking the minimum start time and maximum end time. Once the overlaps end, add the merged interval and the remaining intervals.

```cpp
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    vector<vector<int>> res;
    int i = 0;
    int n = intervals.size();
    
    // Phase 1: Add intervals entirely before the new interval
    while (i < n && intervals[i][1] < newInterval[0]) {
        res.push_back(intervals[i]);
        i++;
    }
    
    // Phase 2: Merge overlapping intervals
    while (i < n && intervals[i][0] <= newInterval[1]) {
        newInterval[0] = min(newInterval[0], intervals[i][0]);
        newInterval[1] = max(newInterval[1], intervals[i][1]);
        i++;
    }
    res.push_back(newInterval);
    
    // Phase 3: Add remaining intervals
    while (i < n) {
        res.push_back(intervals[i]);
        i++;
    }
    
    return res;
}
```
**Complexity:** Time: $O(n)$ for a single pass, space: $O(n)$ to store the result.
**Practice:** https://leetcode.com/problems/insert-interval/

### Merge Intervals
Given an array of intervals, merge all overlapping intervals.

**Intuition / approach:** To easily find overlaps, we should process intervals sequentially. If we sort by the start time, any overlapping intervals will be adjacent in the sorted list.
**Greedy choice:** Sort by start time. Initialize an interval with the first element. Iterate through the list; if the current interval overlaps with our running interval (i.e., its start time is less than or equal to the running interval's end time), we extend the running interval's end. If it doesn't overlap, we push the running interval and start a new one.

```cpp
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> merge(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};
    
    sort(intervals.begin(), intervals.end());
    
    vector<vector<int>> merged;
    merged.push_back(intervals[0]);
    
    for (int i = 1; i < intervals.size(); i++) {
        if (merged.back()[1] >= intervals[i][0]) {
            merged.back()[1] = max(merged.back()[1], intervals[i][1]);
        } else {
            merged.push_back(intervals[i]);
        }
    }
    
    return merged;
}
```
**Complexity:** Time: $O(n \log n)$ to sort, space: $O(n)$ for the returned list.
**Practice:** https://leetcode.com/problems/merge-intervals/

### Non-overlapping Intervals
Given an array of intervals, return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

**Intuition / approach:** This is the dual of the activity selection problem (N Meetings in One Room). Minimizing removals is identical to maximizing the number of non-overlapping intervals kept.
**Greedy choice:** Sort the intervals by their end times. Always select the interval that ends earliest and doesn't overlap with the previously selected interval. If it overlaps, it must be removed. This choice is safe because an interval that ends early leaves the maximum possible space for subsequent intervals.

```cpp
#include <vector>
#include <algorithm>

using namespace std;

int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    if (intervals.empty()) return 0;
    
    sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1];
    });
    
    int count = 0;
    int end = intervals[0][1];
    
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] >= end) {
            end = intervals[i][1];
        } else {
            count++;
        }
    }
    
    return count;
}
```
**Complexity:** Time: $O(n \log n)$ to sort, space: $O(1)$.
**Practice:** https://leetcode.com/problems/non-overlapping-intervals/

## Close

::: interview
In interviews, greedy solutions send strong signals. When a problem asks for scheduling intervals, always think "sort by end time." When a problem asks to minimize or maximize something with what seems like a safe local choice, you are likely looking at a greedy approach. 

However, you must be disciplined: never code a greedy solution until you have mentally verified it with an exchange argument. Many problems that "look greedy" actually fail on edge cases and require Dynamic Programming (which we cover in the next Part). Prove it before you write it.
:::
