# Contain the Outbreak with Walls

You have been appointed Health Incharge of a district and must contain the spread of an infection by building walls that separate infected areas from healthy ones. The district is a grid of size \(N \times M\). Each cell holds `0` (a healthy area) or `1` (an infected area).

A wall can be erected between any two adjacent areas, on their shared boundary. With limited resources, in **one day you can install walls around only one infected region** — one 4-directionally connected block of infected cells — sealing it off completely. Any infected region that is not sealed spreads: by the next day every healthy area orthogonally adjacent (East, West, North, South) to it also becomes infected. Walls, once erected, cannot be removed, and a fully walled region can never spread again.

Your goal is to erect walls so that **as many areas as possible stay healthy**. If several strategies keep the same number of areas healthy, choose the one that needs the **minimum number of walls**. Print the number of walls that strategy uses.

## Input Format

The first line contains two integers \(N\) and \(M\), the number of rows and columns. Each of the next \(N\) lines contains \(M\) space-separated integers, each `0` or `1`.

## Output Format

A single line containing the minimum number of walls required to contain the infection while keeping as many areas as possible healthy.

## Constraints

- \(2 \le N \le 100\)
- \(2 \le M \le 100\)

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

All bordering areas are infected and the central four are healthy. Walling the single infected region off from the four central cells costs 8 walls and no new area gets infected.

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

There are two infected regions. Sealing the two-cell region first costs 6 walls, but the other region then spreads over 7 new areas and needs more walls later — fewer walls overall, but fewer areas stay healthy. Sealing the three-cell region first costs 7 walls; the other region spreads and needs more walls afterward — 17 walls total, but more areas stay healthy. Keeping areas healthy comes first, so the answer is 17.

### Example 3

**Input**
```
2 2
0 0
0 0
```

**Output**
```
0
```

### Example 4

**Input**
```
2 2
1 1
1 1
```

**Output**
```
0
```

### Example 5

**Input**
```
2 2
1 0
0 1
```

**Output**
```
2
```
