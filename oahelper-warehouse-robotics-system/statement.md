# Warehouse Robotics System

Amazon warehouse robots are either **Operating** or **Standby**. Robot **i** has a coordination threshold **t[i]**.

A robot malfunctions if:

- it is Operating and the number of *other* Operating robots is strictly less than **t[i]**, or
- it is Standby and the total number of Operating robots is greater than or equal to **t[i]**.

A configuration (assignment of each robot to Operating or Standby) is valid when no robot malfunctions. Count the number of distinct valid configurations.

## Input Format

- Line 1: integer **n** — number of robots
- Next **n** lines: integers **t[0], t[1], …, t[n−1]** (one threshold per line)

## Output Format

Print a single integer: the number of valid configurations.

## Constraints

- \(2 \le n \le 2 \cdot 10^5\)
- \(0 \le t[i] \le n - 1\)

## Examples

### Example 1

**Input**
```
5
3
0
0
3
3
```

**Output**
```
2
```

Valid configurations: robots `{1,2}` Operating, or all robots Operating.

### Example 2

**Input**
```
7
0
1
2
3
4
5
6
```

**Output**
```
1
```

Only the all-Operating configuration works.

### Example 3

**Input**
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

**Output**
```
3
```
