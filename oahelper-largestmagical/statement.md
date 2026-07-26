# Largest Magical Binary String

A studio engineer is polishing a *magical* binary soundtrack cue. A binary string is **magical** when:

1. It contains equally many `0`s and `1`s, and
2. In every prefix, the number of `1`s is at least the number of `0`s.

Any magical string splits uniquely into contiguous **top-level magical blocks** (places where the running balance returns to zero). Inside each block the characters between the leading `1` and the trailing `0` form another magical string, so the structure is recursive — like nested parentheses.

You may repeatedly swap two **adjacent** magical substrings whenever the whole string stays magical. Your goal is to obtain the lexicographically largest magical string reachable by such swaps.

## Input

A single line containing a magical binary string `s`.

## Output

Print the lexicographically largest magical string obtainable.

## Constraints

- Each character of `s` is `0` or `1`
- \(1 \le |s| \le 50\)
- `s` is guaranteed to be magical

## Examples

### Example 1

**Input**
```
11011000
```

**Output**
```
11100100
```

Swap adjacent magical pieces `10` and `1100` (among others) to reach `11100100`.

### Example 2

**Input**
```
1100
```

**Output**
```
1100
```

There is only one top-level block; nothing can be rearranged.

### Example 3

**Input**
```
1010111000
```

**Output**
```
1110001010
```

The top-level blocks can be reordered to put the larger piece `111000` first.
