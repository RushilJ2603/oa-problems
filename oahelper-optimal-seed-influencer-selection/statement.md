Your team at a leading technology company is launching a cutting-edge networking product. To generate buzz, you are running a targeted social media campaign. You have a limited marketing **budget** to send premium trial units to a select group of "seed" influencers on a professional network.

Each potential influencer has a different **cost** to engage. Each user also has a **market value** reflecting their role and influence. Selecting a seed reaches that seed and everyone within **d** degrees of separation on the friendship graph (`d = 0` reaches only the seed itself, `d = 1` adds direct friends, and so on). The **value of a campaign** is the sum of market values of the set of *distinct* users reached by at least one chosen seed.

A brute-force search over every subset of seeds is infeasible, so you must use the following deterministic **greedy heuristic**:

1. Start with an empty seed set, total cost 0, and an empty reached set.
2. Among the potential seeds that are *not yet chosen* and whose cost fits the remaining budget (running cost + cost ≤ budget), compute each candidate's **marginal gain** = the sum of market values of the users in its depth-≤`d` reach that are *not already reached*. Ignore any candidate whose marginal gain is ≤ 0.
3. Choose the candidate with the highest ratio `marginal_gain / cost`. Break ties, in order, by: (a) larger marginal gain, then (b) smaller cost, then (c) smaller user id.
4. Add the chosen seed to the seed set, add its cost to the running cost, and mark every user in its reach as reached (accumulating their value once).
5. Repeat from step 2 until no candidate qualifies (none affordable with positive marginal gain). Then stop.

**Notes & rules:**

- The graph is **undirected**. Self-loops and duplicate edges have no additional effect. Edge endpoints outside `[1, n]` are ignored.
- Only ids listed in the seeds section may be chosen. A seed id outside `[1, n]` is invalid and is ignored. If the same id appears multiple times, each listed `(id, cost)` entry is a candidate, but once that id has been chosen it cannot be chosen again.
- The reach of a seed is computed once, on the original graph; choosing a seed does not change anyone's reach.
- Compare efficiency ratios using cross-multiplication (avoid floating point): prefer A over B when `gainA * costB > gainB * costA`.

### Input Format

```
Line 1: n                      (number of users, numbered 1..n)
Line 2: num_connections        (number of connection lines that follow)
Next num_connections lines: u v   (an undirected connection between u and v)
Next line: num_seeds           (number of potential-seed lines that follow)
Next num_seeds lines: id cost  (a potential seed and its cost)
Next line: n space-separated integers  (value[i] is the market value of user i)
Next line: budget              (total available budget)
Next line: d                   (maximum influence depth)
```

### Output Format

Three lines:

```
[id1,id2,...]   (chosen seed ids in selection order; empty list prints [])
<total market value of all distinct reached users>
<total cost of the chosen seeds>
```

### Constraints

- `1 <= n <= 2000`
- `0 <= num_connections <= min(n*(n-1)/2, 20000)`
- `0 <= num_seeds <= 200`
- `0 <= cost, budget <= 10^9`
- `0 <= value[i] <= 10^9`
- `0 <= d <= n`

### Example 1

Input:
```
5
3
1 2
1 3
4 5
2
1 50
4 60
10 20 30 5 5
100
1
```

Output:
```
[1]
60
50
```

Candidate 1: cost 50, reach `{1,2,3}`, value 60, efficiency 1.2. Candidate 4: cost 60, reach `{4,5}`, value 10, efficiency ≈0.167. Seed 1 is chosen; seed 4 no longer fits the remaining budget.

### Example 2

Input:
```
5
4
1 2
1 3
4 3
4 5
2
1 60
4 70
5 10 20 5 30
150
1
```

Output:
```
[4,1]
70
130
```

Seed 4 is chosen first (higher efficiency). Then seed 1 adds the remaining uncovered users `{1,2}` and is selected.
