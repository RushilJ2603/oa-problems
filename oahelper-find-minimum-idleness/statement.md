# Find Minimum Idleness

A real-time game engine renders a sequence of shaders on two GPUs labeled `a` and `b`. You are given a string `shader` of length \(n\), where `shader[i]` is the GPU assigned to the \(i\)-th shader.

The **idleness** of an assignment is the length of the longest contiguous run of the same GPU. For example, `aabbba` has runs of lengths 2, 3, and 1, so its idleness is 3.

You may perform the following operation at most `switchCount` times:

- Pick any index and flip that character (`a` ↔ `b`).

Find the minimum idleness achievable after at most `switchCount` flips.

## Input Format

- Line 1: the string `shader` consisting only of characters `a` and `b`
- Line 2: an integer `switchCount`

## Output Format

A single integer — the minimum achievable idleness.

## Constraints

- \(1 \le |shader| \le 2 \cdot 10^5\)
- \(1 \le\) `switchCount` \(\le |shader|\)
- `shader` contains only `a` and `b`

## Examples

### Example 1

**Input**
```
aaaaa
1
```

**Output**
```
2
```

**Explanation**

Flip index 2 to get `aabaa`. The longest run has length 2.

### Example 2

**Input**
```
ababa
5
```

**Output**
```
1
```

**Explanation**

The string already alternates, so idleness is already 1. No flips are required.

### Example 3

**Input**
```
aabbbaaaa
2
```

**Output**
```
2
```

**Explanation**

One optimal sequence of flips yields `aabababaa`, whose longest run has length 2.
