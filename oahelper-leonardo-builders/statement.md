# Leonardo Builders

Leonardo Builders must place a polygonal building on rectangular land without cutting any trees. The land is the axis-aligned rectangle with lower-left corner at `(0, 0)` and upper-right corner at `(Xp, Yp)`. There are `N` trees at given interior points.

The building is a simple polygon given by `K` corners in boundary order. You may translate it and rotate it by multiples of 90 degrees. After placement:

- every building vertex must lie on integer coordinates,
- the entire building (interior and boundary) must lie inside the land rectangle (vertices with coordinates in `[0, Xp] × [0, Yp]` after placement),
- no tree may lie on a corner, on an edge, or strictly inside the building.

Two placements that produce the same covered cell set after rotation deduplication count once per distinct orientation; identical shapes under 90° rotation are not double-counted.

Count the number of valid placements.

## Input

- Line 1: `Xp Yp N`
- Next `N` lines: tree coordinates `x y` (strictly inside the land)
- Next line: `K`
- Next `K` lines: building corner coordinates `xi yi` (shape only; may be far from the origin)

## Output

Print a single integer: the number of valid ways to place the building.

## Constraints

- `1 ≤ Xp, Yp ≤ 500`
- `0 ≤ N ≤ Xp * Yp`
- `0 < tree coordinates < Xp, Yp` (strictly inside)
- `3 ≤ K ≤ 200`
- `-10^9 ≤ Xi, Yi ≤ 10^9` for building corners
- After any allowed rotation and translation, vertices must stay on integer coordinates (so only 0°/90°/180°/270° rotations are considered)

## Examples

### Example 1

Input:
```
5 5 0
4
0 0
2 0
2 2
0 2
```

Output:
```
16
```

### Example 2

Input:
```
5 5 1
2 2
4
0 0
2 0
2 2
0 2
```

Output:
```
7
```

### Example 3

Input:
```
4 4 0
4
0 0
2 0
2 1
0 1
```

Output:
```
24
```
