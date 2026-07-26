# Conference Channel Optimization

A company is redesigning its internal communication network. There are `n` departments numbered from `1` to `n`, and `m` bidirectional channels. Channel `i` connects departments `u_i` and `v_i` and has an associated cost `w_i` (costs may be negative, zero, or positive). Self-loops are allowed.

The network must remain **fully connected**: every department must be reachable from every other department through some sequence of kept channels. Among all subsets of channels that keep the network connected, you want the subset whose **removed** channels have the **maximum possible total cost**.

Return that maximum removable total. If it is impossible to keep the network connected no matter which channels you keep, return `-1`.

**Clarifications**

- If `n = 0`, there are no departments; treat the answer as `0`.
- If `n = 1`, the single department is already connected (even with no channels); the answer is the sum of all self-loop costs that can be removed (all of them), or `0` if there are none.
- Negative-cost channels should never be removed in an optimal answer (removing them decreases the removed total). Zero-cost removals do not change the total.

## Input

- First line: two integers `n` and `m` (`0 ≤ n ≤ 100000`, `0 ≤ m ≤ 200000`).
- Next `m` lines: three integers `u_i`, `v_i`, `w_i` (`1 ≤ u_i, v_i ≤ n` when `n ≥ 1`; `|w_i| ≤ 2·10^9`).

## Output

- A single integer: the maximum sum of costs of removable channels, or `-1` if the graph cannot be made connected.

## Examples

### Example 1

**Input**

```
3 3
1 2 -2
1 3 4
3 1 -1
```

**Output**

```
4
```

The only channel that can be removed while keeping connectivity is the one of cost `4`.

### Example 2

**Input**

```
4 6
1 2 1
2 3 2
3 4 3
1 3 4
1 4 5
2 4 6
```

**Output**

```
15
```

### Example 3

**Input**

```
4 2
1 2 -5
3 4 7
```

**Output**

```
-1
```

The graph has two components and cannot be connected.
