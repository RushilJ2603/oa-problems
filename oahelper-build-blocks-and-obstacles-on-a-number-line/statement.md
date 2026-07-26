# Build Blocks and Obstacles on a Number Line

You have an infinite integer number line and must process a sequence of operations that place obstacles or check whether a block can be built.

There are two operation types:

- `1 x` — place an obstacle at coordinate `x`. It is guaranteed that `x` does not already contain an obstacle.
- `2 x size` — check whether a block of length `size` can be built on the half-open interval of coordinates that ends immediately before `x`, i.e. on `[x - size, x - 1]`. Output `1` if every coordinate in that range is free of obstacles, otherwise `0`. This operation only checks; it does **not** place the block.

Return a binary string formed by concatenating the answers to every type-2 operation, in order.

## Input Format

- The first line contains an integer `n` — the number of operations.
- Each of the next `n` lines describes one operation:
  - Type 1: `1 x`
  - Type 2: `2 x size`

## Output Format

Print a single binary string (no spaces) consisting of the answers to all type-2 operations, followed by a newline. If there are no type-2 operations, print an empty line.

## Constraints

- \(1 \le n \le 10^5\)
- All coordinates satisfy \(-10^9 \le x \le 10^9\)
- For type-2 operations, \(1 \le size \le 10^9\)
- Type-1 coordinates are unique (no duplicate obstacles)

## Examples

### Example 1

**Input**
```
6
1 2
1 5
2 5 2
2 6 3
2 2 1
2 3 2
```

**Output**
```
1010
```

**Explanation**

- Obstacles are placed at `2` and `5`.
- `[2, 5, 2]` checks `[3, 4]` → free → `1`
- `[2, 6, 3]` checks `[3, 5]` → obstacle at `5` → `0`
- `[2, 2, 1]` checks `[1, 1]` → free → `1`
- `[2, 3, 2]` checks `[1, 2]` → obstacle at `2` → `0`

### Example 2

**Input**
```
1
2 0 1
```

**Output**
```
1
```

**Explanation**

No obstacles exist, so the single-cell block on `[-1, -1]` can be built.
