# Parade Uniform Swaps

In HackerLand, parade organizers line people up in a single row. Each person wears either a red uniform (`0`) or a blue uniform (`1`).

The organizers repeatedly apply the following rule every second:

- Every contiguous pair `01` is replaced by `10` **simultaneously** across the whole line.

The process stops when no `01` pair remains (all blues stand to the left of all reds).

Given the initial binary string `color`, compute how many seconds elapse until the process stops.

## Input Format

A single line containing the binary string `color`.

## Output Format

A single integer — the number of seconds until no `01` remains.

## Constraints

- \(1 \le |color| \le 3 \cdot 10^5\)
- `color` consists only of characters `0` and `1`

## Examples

### Example 1

**Input**
```
0101
```

**Output**
```
2
```

**Explanation**

- \(t = 0\): `0101`
- \(t = 1\): `1010`
- \(t = 2\): `1100`

### Example 2

**Input**
```
1111
```

**Output**
```
0
```

**Explanation**

There is no substring `01`, so the process never starts.
