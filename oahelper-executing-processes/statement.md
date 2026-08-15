# Executing Processes

A modern CPU scheduler manages an array of $n$ tasks waiting to be executed. Each task $i$ has an assigned priority value, represented by `priorities[i]`. The CPU executes these tasks sequentially in reverse order, starting from the $(n-1)$-th index down to the $0$-th index. Each task takes exactly 1 unit of time to execute.

A task is considered to suffer from *starvation* if a task with a **strictly lower** priority value is executed before it. The starvation period for task $i$ begins when the earliest task with a lower priority starts executing, and it ends when task $i$ itself finally begins execution. 

If no lower-priority task executes before task $i$, its starvation time is $0$. Otherwise, the starvation time is the difference between the execution time of the earliest lower-priority task and the execution time of task $i$. Since tasks execute sequentially in reverse order (and each takes 1 unit of time), this time difference is exactly equal to the difference in their indices.

Your goal is to calculate the starvation time for every task.

## Input Format

- The first line contains a single integer $n$, the number of tasks.
- The second line contains $n$ space-separated integers, where the $i$-th integer represents `priorities[i]`.

## Output Format

- Output a single line with $n$ space-separated integers, where the $i$-th integer represents the starvation time of the $i$-th task.

## Constraints

- $1 \le n \le 3 \cdot 10^5$
- $1 \le \text{priorities}[i] \le 10^9$

## Example 1

**Input:**
```
4
6 10 9 7
```

**Output:**
```
0 2 1 0
```

**Explanation:**
- Task 3 (`priorities[3] = 7`): No tasks execute before it (it is the first to execute). Starvation = $0$.
- Task 2 (`priorities[2] = 9`): Task 3 executes before it and has a lower priority ($7 < 9$). Starvation = $3 - 2 = 1$.
- Task 1 (`priorities[1] = 10`): Task 3 is the earliest executed lower-priority task ($7 < 10$). Starvation = $3 - 1 = 2$.
- Task 0 (`priorities[0] = 6`): No lower-priority tasks execute before it (tasks 3, 2, 1 have priorities 7, 9, 10, none of which are $< 6$). Starvation = $0$.

## Example 2

**Input:**
```
7
8 2 11 4 9 4 7
```

**Output:**
```
6 0 4 0 2 0 0
```

**Explanation:**
- Task 6 (`priorities[6] = 7`): Starvation = $0$.
- Task 5 (`priorities[5] = 4`): Starvation = $0$.
- Task 4 (`priorities[4] = 9`): Earliest lower-priority task is task 6 (priority 7). Starvation = $6 - 4 = 2$.
- Task 3 (`priorities[3] = 4`): Starvation = $0$.
- Task 2 (`priorities[2] = 11`): Earliest lower-priority task is task 6 (priority 7). Starvation = $6 - 2 = 4$.
- Task 1 (`priorities[1] = 2`): Starvation = $0$.
- Task 0 (`priorities[0] = 8`): Earliest lower-priority task is task 6 (priority 7). Starvation = $6 - 0 = 6$.
