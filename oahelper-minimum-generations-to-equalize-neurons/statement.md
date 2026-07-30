# Minimum Generations to Equalize Neurons

A research lab runs a neural network with `n` layers. Layer `i` currently holds `layer[i]` neurons. Neurons can only be **added**, never removed. In each generation the lab may adjust **at most one** layer:

- On **odd** generations (`1, 3, 5, …`): add **exactly 1** neuron to one layer, or do nothing.
- On **even** generations (`2, 4, 6, …`): add **exactly 2** neurons to one layer, or do nothing.

Find the **minimum** generation number `G` after which it is possible for every layer to hold the **same** number of neurons. If the layers are already equal, the answer is `0`.

The final common height must be at least the current maximum (you cannot shrink any layer). Raising the common target above that maximum is allowed and sometimes optimal.

## Input

- First line: integer `n` — the number of layers.
- Each of the next `n` lines: one integer `layer[i]`.

## Output

A single integer — the minimum number of generations needed.

## Constraints

- `1 ≤ n ≤ 10^5`
- `1 ≤ layer[i] ≤ 10^9`

## Examples

### Example 1

**Input**
```
4
1
1
2
4
```

**Output**
```
6
```

**Explanation**

One optimal schedule equalizes every layer to `4` by generation `6` (a generation may intentionally do nothing so that the next even/odd slot is usable).

### Example 2

**Input**
```
3
3
3
6
```

**Output**
```
4
```

**Explanation**

Bring both smaller layers up to `6` using two `+1` and two `+2` operations; generation `4` is enough.

### Example 3

**Input**
```
5
10
10
10
10
10
```

**Output**
```
0
```

**Explanation**

Already equalized.
