# Equalize Network Layers

A neural network has **n** layers. Layer *i* currently has `layer[i]` neurons.

The network upgrades itself over discrete generations:

- In an **odd** generation (1, 3, 5, …) you may add **exactly 1** neuron to **at most one** layer (or do nothing).
- In an **even** generation (2, 4, 6, …) you may add **exactly 2** neurons to **at most one** layer (or do nothing).

You cannot remove neurons. Find the **minimum generation number** after which it is possible for every layer to have the **same** number of neurons. If they are already equal, the answer is `0`.

Note that the common final value may be strictly larger than today’s maximum: sometimes overshooting the current max by one yields a shorter schedule because of parity constraints on the odd/even additions.

## Input

- First line: integer `n` — the number of layers.
- Second line: `n` integers `layer[1..n]`.

## Output

- A single integer — the minimum generation at which all layers can be equal.

## Constraints

- \(1 \le n \le 10^5\)
- \(1 \le layer[i] \le 10^9\)

## Examples

### Example 1

**Input**
```
4
1 1 2 4
```

**Output**
```
6
```

**Explanation**

One optimal schedule that equalizes at value 4:

| Generation | Action | Layers |
| --- | --- | --- |
| 1 | +1 to layer 0 | `[2, 1, 2, 4]` |
| 2 | +2 to layer 0 | `[4, 1, 2, 4]` |
| 3 | +1 to layer 1 | `[4, 2, 2, 4]` |
| 4 | +2 to layer 1 | `[4, 4, 2, 4]` |
| 5 | skip | `[4, 4, 2, 4]` |
| 6 | +2 to layer 2 | `[4, 4, 4, 4]` |

Generation 5 must be skipped: an odd +1 would leave a deficit that cannot finish on the next even step.

### Example 2

**Input**
```
3
3 3 6
```

**Output**
```
4
```

**Explanation**

Equalize at 6 in four generations: `+1,+2,+1,+2` applied to the two smaller layers.
