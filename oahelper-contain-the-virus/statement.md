# Contain the Virus

You have been appointed Health Incharge of a district. Your task is to contain the spread of infection by building walls that separate infected areas from healthy ones.

The district is an `N × M` grid. Each cell is `0` (healthy) or `1` (infected).

A **wall** can be placed on any shared boundary between two adjacent cells (four-directional: north, south, east, west). In one day you may completely wall in **exactly one** infected region — a contiguous 4-connected block of infected cells. You always choose the region that **threatens the most healthy areas**: the region adjacent to the largest number of **distinct** healthy cells. It is guaranteed there is never a tie.

Overnight, every infected region that was **not** walled in spreads: each healthy cell it touches becomes infected. Walled regions never spread again. Walls cannot be removed.

Find the **total number of walls** required to contain the virus completely while keeping as many cells healthy as possible.

**Important:** the number of walls a region needs is the number of shared boundaries with healthy cells (an edge count). The threat count is the number of distinct healthy neighbours. These two numbers can differ when one healthy cell borders a region on multiple sides.

## Input Format

The first line contains two integers `N` and `M`.

Each of the next `N` lines contains `M` space-separated integers (each `0` or `1`).

## Output Format

Print a single integer — the total number of walls required.

## Constraints

- \(1 \le N, M \le 100\)
- Every cell is `0` or `1`
- On every day, the infected region that threatens the most healthy areas is unique

## Examples

### Example 1

**Input**
```
4 4
1 1 1 1
1 0 0 1
1 0 0 1
1 1 1 1
```

**Output**
```
8
```

**Explanation**

One infected ring surrounds four healthy cells. Wall that region in one day: 8 walls, and nothing spreads.

### Example 2

**Input**
```
5 5
0 0 0 0 0
0 1 1 0 0
0 0 0 0 0
0 0 1 1 1
0 0 0 0 0
```

**Output**
```
17
```

**Explanation**

Day 1: wall the lower region (threat 7) for 7 walls. The upper region then spreads into 6 cells. Day 2: wall the enlarged upper region for 10 walls. Total \(7 + 10 = 17\).
