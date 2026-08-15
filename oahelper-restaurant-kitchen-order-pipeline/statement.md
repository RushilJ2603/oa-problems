# Restaurant Kitchen Order Pipeline

A high-volume restaurant kitchen is equipped with $S$ specialized cooking stations (such as a grill, saute station, fryer, etc.), labeled $1$ to $S$.

When a complex dish is ordered, its preparation is broken down into a sequence of $N$ preparation steps, labeled $1$ to $N$. Each step $i$ must be performed on a specific station `station[i]` and takes exactly `duration[i]` units of time to complete. 

The preparation steps have dependencies that form a Directed Acyclic Graph (DAG). You are given $M$ rules of the form $(u, v)$, meaning that step $u$ MUST be completely finished before step $v$ can even begin. 

The kitchen operates under the following rules:
1. **Station Capacity:** Each station can process only ONE step at a time.
2. **Ready State:** A step becomes "ready" to start as soon as ALL of its prerequisite steps are fully finished. If a step has no prerequisites, it is ready at time $0$. The ready time of a step is exactly the maximum finish time of all its prerequisites (or $0$).
3. **Execution:** As soon as a step is ready AND its required station is free, it begins processing immediately.
4. **Contention Resolution:** If multiple ready steps are competing for the same free station at the same time, the step with the **earliest ready time** is scheduled first. If there is still a tie in ready times, the step with the **smaller step ID** is scheduled first. 
Once a step starts, it occupies the station for its entire duration uninterrupted.

Your task is to simulate this kitchen pipeline and compute the exact time each of the $N$ steps finishes, as well as the overall "makespan" (the time the last step finishes).

## Input Format

- The first line contains two space-separated integers, $N$ and $S$: the number of steps and the number of stations.
- The next $N$ lines describe the steps. The $i$-th line (for $1 \le i \le N$) contains two integers: `station[i]` and `duration[i]`.
- The next line contains a single integer $M$, the number of dependencies.
- The next $M$ lines describe the dependencies. Each line contains two integers $u$ and $v$, indicating that step $u$ must finish before step $v$ starts.

## Output Format

- Print two lines.
- The first line must contain $N$ space-separated integers, where the $i$-th integer is the completion time of step $i$.
- The second line must contain a single integer, the overall makespan (the maximum completion time among all steps).

## Constraints

- $1 \le N \le 100,000$
- $1 \le S \le N$
- $1 \le \text{duration}[i] \le 10^4$
- $0 \le M \le 200,000$
- The dependencies are guaranteed to form a valid Directed Acyclic Graph (DAG).
- $1 \le \text{station}[i] \le S$

## Example 1

**Input:**
```
5 2
1 4
1 3
2 5
2 2
1 1
4
1 3
2 3
3 5
4 5
```

**Output:**
```
4 7 12 2 13
13
```

**Explanation:**
- Step 1 (station 1, dur 4): no deps $\rightarrow$ ready at 0, runs 0..4. Finish 4.
- Step 2 (station 1, dur 3): no deps $\rightarrow$ ready at 0. It competes with step 1 on station 1. Step 1 wins (smaller id). Step 2 starts when station 1 frees at 4; runs 4..7. Finish 7.
- Step 4 (station 2, dur 2): no deps $\rightarrow$ ready at 0, runs 0..2. Finish 2.
- Step 3 (station 2, dur 5): deps (1, 2) done at $\max(4, 7) = 7 \rightarrow$ ready at 7. Station 2 is free at 2 $\le$ 7 $\rightarrow$ starts at 7; runs 7..12. Finish 12.
- Step 5 (station 1, dur 1): deps (3, 4) done at $\max(12, 2) = 12 \rightarrow$ ready at 12. Station 1 is free at 7 $\le$ 12 $\rightarrow$ starts 12; runs 12..13. Finish 13.
- Makespan = 13.

## Example 2

**Input:**
```
3 1
1 2
1 3
1 4
2
1 2
2 3
```

**Output:**
```
2 5 9
9
```
