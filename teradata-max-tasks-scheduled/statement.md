> **Statement only.** Transcribed from the Teradata OA (2 hours, 3 questions, 50 points). There is
> no auto-judge for this one — read it, solve it on paper or in the Compiler tab.

You want to maximize the number of tasks completed before their deadlines.

Return the maximum number of tasks that can be completed on time respecting the cooling period
constraint.

**Function Description:** You need to implement the function `maxTasksScheduled`.

**Parameters:**
- `N`: An integer representing the number of tasks.
- `tasks`: A list of integers representing the task IDs.
- `deadline`: A list of integers representing deadlines of the tasks.
- `cooldown`: An integer representing the minimum cooldown period between two same task IDs.

**Return:** An integer representing the maximum number of tasks completed on or before their
deadlines while respecting the cooldown period.

**Input Format:**
- The first line contains an integer `N`.
- The second line contains `N` space-separated integers `tasks[i]`.
- The third line contains `N` space-separated integers `deadline[i]`.
- The fourth line contains a single integer `cooldown`.

**Output Format:** Return a single integer — the maximum number of tasks completed on time
respecting cooldown.

**Constraints:**
- `1 <= N <= 10^5`
- `1 <= tasks[i] <= 10^9`
- `1 <= deadline[i] <= 10^9`
- `0 <= cooldown <= 10^5`

**Sample Input 1:**
```
6
1 2 1 2 1 3
3 2 5 6 7 10
2
```
**Sample Output 1:**
```
5
```
**Explanation:** One optimal schedule is:

- Time 1: Task 1 (deadline 3)
- Time 2: Task 2 (deadline 2)
- Time 3: Task 3 (deadline 10)
- Time 4: Task 1 (deadline 5) *[cooldown 2 units respected since last task 1 was at time 1]*
- Time 5: Task 2 (deadline 6) *[cooldown respected]*

The last task 1 cannot be scheduled on time respecting cooldown, so max tasks on time = 5.

---

**Given signature (C++17):**
```cpp
int maxTasksScheduled(int N, vector<int> tasks, vector<int> deadline, int cooldown) {
    // Write your code here
}
```

**OA limits as shown:** Time 5.0 sec/input file · Memory 256 MB · Source 1024 KB.
Scoring: score is assigned if any testcase passes. Worth 50.00 points.
