In Amazon's warehouse robotics system, multiple robots operate simultaneously to transport packages efficiently. Each robot can be in one of two states: **Operating** or **Standby**.

For smooth coordination, each robot $i$ has a predefined coordination threshold, `coordinationThreshold[i]`. This threshold determines the conditions under which a robot malfunctions:

- A robot $i$ malfunctions if it is in the Operating state but the total number of **other** robots in the Operating state is strictly less than `coordinationThreshold[i]`.
- A robot $i$ malfunctions if it is in the Standby state but the total number of **other** robots in the Operating state is greater than or equal to `coordinationThreshold[i]`. (Note: when robot $i$ is in Standby, all Operating robots are considered "other" robots).

If any robot malfunctions, the system is considered unstable. Return the total number of distinct valid configurations where no robot malfunctions.

**Note:** A configuration is an assignment of each of the $n$ robots to either Operating or Standby. A configuration is considered valid if no robot malfunctions under that arrangement. Two configurations are distinct if at least one robot is in a different state.

### Input Format

- The first line contains an integer $n$, the number of robots.
- The next $n$ lines each contain an integer representing the array `coordinationThreshold`.

### Output Format

- Output a single integer, the number of valid configurations of robots that ensure system stability.

### Constraints

- $2 \le n \le 2 \times 10^5$
- $0 \le \text{coordinationThreshold}[i] \le n - 1$

### Examples

#### Example 1
**Input:**
```
8
6
0
3
3
6
7
2
7
```
**Output:**
```
3
```
**Explanation:**
The `coordinationThreshold` array is `[6, 0, 3, 3, 6, 7, 2, 7]`.
There are three valid configurations:
1. Only Robot 1 is Operating (`coordinationThreshold[1] = 0`). It meets its threshold since at least 0 other robots are operating. All other robots remain in Standby, and their thresholds are strictly greater than 1.
2. Robots 1, 2, 3, and 6 are Operating (`coordinationThreshold` values: 0, 3, 3, 2). Each operating robot requires at most 3 other robots (and there are exactly 3 others operating). All standby robots require strictly more than 4 operating robots.
3. All 8 robots are Operating. Each operating robot has exactly 7 other operating robots, which is greater than or equal to their threshold.

#### Example 2
**Input:**
```
5
3
0
3
3
3
```
**Output:**
```
2
```
