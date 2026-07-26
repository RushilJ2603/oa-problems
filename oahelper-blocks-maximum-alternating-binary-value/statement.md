# Blocks: Maximum Alternating Binary Value

Ravi works on a firmware packing tool at Infosys. The tool receives `N` contiguous runs of bit `1`
(with lengths given by array `A`) and `N` contiguous runs of bit `0` (with lengths given by
array `B`). He must lay every run into one long bitstring so that **runs of the same bit never sit
next to each other** — the bit types must strictly alternate.

Every run is used exactly once. The finished string is read as a binary integer (MSB on the left).
Among all valid layouts, Ravi wants the **largest possible integer value**. Because the true value
can be enormous, print that maximum **modulo** `10^9 + 7` (the modulo is only for printing; the
layout itself must maximize the real integer, not the residue).

## Rules

- You have exactly the `N` one-runs from `A` and the `N` zero-runs from `B`.
- Adjacent runs in the layout must have different bit values (so the sequence is either
  `1-run, 0-run, 1-run, 0-run, …` or `0-run, 1-run, 0-run, 1-run, …`).
- You may start with either bit type.
- Do **not** build the bitstring explicitly — its length can reach `2 · 10^{11}`.

## Input Format

```
N
A[0]
...
A[N-1]
B[0]
...
B[N-1]
```

The first line contains an integer `N`. Each of the next `N` lines contains an integer `A[i]`.
Each of the following `N` lines contains an integer `B[i]`.

## Output Format

Print a single integer — the maximum binary value modulo `10^9 + 7`.

## Constraints

- `1 ≤ N ≤ 10^5`
- `1 ≤ A[i] ≤ 10^6`
- `1 ≤ B[i] ≤ 10^6`

## Sample Input 1

```
1
2
1
```

## Sample Output 1

```
6
```

**Explanation.** `N = 1`, `A = [2]`, `B = [1]`. Starting with the one-run then the zero-run gives
`110`, which equals `6`. Starting with zeros would give `011` = `3`, which is smaller.

## Sample Input 2

```
3
2
1
2
2
2
1
```

## Sample Output 2

```
868
```

**Explanation.** `A = [2, 1, 2]`, `B = [2, 2, 1]`. An optimal layout is the one-runs in descending
size interleaved with the zero-runs in ascending size, starting with a one-run:
`A[2], B[2], A[0], B[1], A[1], B[0]` → binary `1101100100` = `868`.
