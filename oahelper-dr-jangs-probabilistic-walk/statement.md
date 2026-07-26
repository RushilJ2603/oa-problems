# Dr. Jang's Probabilistic Walk

Dr. Jang tours company divisions all day, never lingering more than 10 minutes at a stretch. When he stays longer, he does so in whole 10-minute blocks.

You are given a directed probabilistic graph of his moves. He always starts at **division 1**. Every 10 minutes he takes one transition: from his current division he follows an outgoing edge according to its probability. Travel time is zero. For every division that has outgoing edges, those probabilities sum to 1.

If he arrives at a division with **no** outgoing edges, that visit is his last: after those 10 minutes he leaves work and is no longer in any division.

Given a time `T` (minutes since start), find the division where he is most likely to be after exactly `T` minutes, and that probability.

Moves happen at the 10-minute marks. The number of moves after time `T` is `T / 10` (integer division):

- `0 ≤ T ≤ 9`: still at division 1 (probability 1)
- `10 ≤ T ≤ 19`: one move completed
- and so on

## Input

The input contains one or more test cases, read until EOF.

Each test case is two lines:

1. Three integers `N`, `E`, `T` — number of divisions, number of directed edges, and the query time in minutes.
2. `E` triples `u v p` — an edge from division `u` to `v` with probability `p` (real number in `[0, 1]`). Divisions are numbered `1 … N`.

## Output

For the `x`-th test case (1-based), print one line:

- If the maximum probability of being in any division is 0 (he has already left): `#x 0`
- Otherwise: `#x D P` where `D` is the most likely division and `P` is that probability printed with exactly 6 digits after the decimal point.

If several divisions share the highest probability, choose the **smallest** division number.

Absolute or relative error up to `1e-6` is acceptable for the probability.

## Constraints

- `1 ≤ N ≤ 100`
- `0 ≤ E ≤ N·N`
- `0 ≤ T ≤ 1000`
- Each `p` is a real in `[0, 1]`; outgoing probabilities from a non-terminal division sum to 1

## Examples

### Example 1

**Input**
```
6 10 40
1 2 0.3 1 3 0.7 3 3 0.2 3 4 0.8 2 4 1.0 4 5 0.9 4 4 0.1 5 6 1.0 6 3 0.5 6 6 0.5
```

**Output**
```
#1 6 0.774000
```

After 4 moves (`T = 40`), division 6 has the highest probability ≈ 0.774.

### Example 2

**Input**
```
6 10 10
1 2 0.3 1 3 0.7 3 3 0.2 3 4 0.8 2 4 1.0 4 5 0.9 4 4 0.1 5 6 1.0 6 3 0.5 6 6 0.5
```

**Output**
```
#1 3 0.700000
```

After one move, division 3 is most likely (probability 0.7).

### Example 3

**Input**
```
6 10 9
1 2 0.3 1 3 0.7 3 3 0.2 3 4 0.8 2 4 1.0 4 5 0.9 4 4 0.1 5 6 1.0 6 3 0.5 6 6 0.5
```

**Output**
```
#1 1 1.000000
```

Before the first move he is still at division 1.

### Example 4

**Input**
```
6 7 50
1 2 0.3 1 3 0.7 2 4 1.0 3 4 0.7 3 6 0.3 4 5 1.0 5 6 1.0
```

**Output**
```
#1 0
```

Division 6 is a sink. By `T = 50` every path has already left work, so the answer is `0`.
