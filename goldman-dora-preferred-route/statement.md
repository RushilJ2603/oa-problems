# Dora's Preferred Route

Dora loves bike riding, and every weekend she plans a trip. This weekend she is travelling from her
source city **S** to a destination city **D**. There are several other cities nearby, so she wants
the route that lets her **visit as many cities as possible** before reaching D — but visiting any
city **at most once**. She prepares a map as a graph `G` where each node is a city and each edge is
a road between two cities.

Given the graph `G` as an adjacency matrix, the number of cities `n` (labelled `0` to `n-1`), the
source `S`, and the destination `D`, print the route from S to D covering the **maximum number of
cities**, with the cities listed in the order they are visited. If multiple such routes exist, print
the **lexicographically smallest** one.

## Input
```
n
row 0 of the n x n adjacency matrix (n space-separated 0/1)
...
row n-1
S D
```
`G[i][j] = 1` means there is a road between city `i` and city `j`.

## Output
A single line: the sequence of cities on the chosen route from S to D, space-separated.

## Constraints
- `0 < n < 50`
- `G[i][j]` is `0` or `1`
- `0 ≤ S, D < n`

## Example 1
Input:
```
5
0 1 1 1 0
1 0 1 1 0
1 1 0 1 0
1 1 1 0 1
0 0 0 1 0
0 1
```
Output:
```
0 2 3 1
```
Both `0 → 2 → 3 → 1` and `0 → 3 → 2 → 1` cover cities 2 and 3; `0 2 3 1` is lexicographically smaller.

## Example 2
Input:
```
9
0 1 1 0 0 0 0 0 0
1 0 0 0 1 0 0 0 0
1 0 0 0 1 0 0 0 0
0 0 0 1 0 0 0 0 0
0 1 0 0 0 0 0 1 0
0 0 0 0 0 0 1 0 0
0 0 0 0 0 1 0 0 1
0 0 0 0 1 0 0 0 1
0 0 0 0 0 0 0 1 0
2 7
```
Output:
```
2 0 1 4 7
```
