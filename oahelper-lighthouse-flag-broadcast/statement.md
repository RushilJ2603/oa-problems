# Lighthouse Flag Broadcast

Every evening, the keeper of the Saltmere lighthouse raises a sequence of signal flags along the harbour mast. Each flag shows one lowercase letter, and the flags stay in the order they were raised.

The **glow strength** of a flag depends on its letter: `a` has strength 1, `b` has strength 2, …, `z` has strength 26.

The harbour authority requires the keeper to choose **exactly `k` flags** from the sequence **without reordering** them (a subsequence of length `k`). The total glow strength of the chosen flags must be **at least `f`**.

Among all valid choices, output the **lexicographically smallest** string formed by the chosen flags (compare as usual dictionary order on equal-length strings).

**Note:** You are **not** required to pick a contiguous block of flags—any subsequence of length `k` is allowed, as long as relative order is preserved.

## Input

- Line 1: integer `n` — number of flags  
- Line 2: string `s` of length `n` (lowercase letters)  
- Line 3: integer `k` — how many flags to choose  
- Line 4: integer `f` — minimum total glow strength  

## Output

Print one line: the lexicographically smallest valid broadcast string.

## Constraints

- `1 ≤ n ≤ 100000`
- `1 ≤ k ≤ n`
- `s` contains only lowercase English letters
- `0 ≤ f ≤` maximum total strength achievable by any subsequence of length `k`
- At least one valid answer exists
- All values are integers

## Example 1

**Input**

```
5
dcbac
3
7
```

**Output**

```
cac
```

**Explanation:** Flags are `d(4) c(3) b(2) a(1) c(3)`. We need three flags with total strength ≥ 7. Starting with `c` at index 1 beats starting with `d`. Then `a` beats `b` for the second character while still allowing a valid third pick. The choice at indices 2, 4, and 5 (0-based: 1, 3, 4) gives `cac` with strength 3 + 1 + 3 = 7.

## Example 2

**Input**

```
5
abcde
3
0
```

**Output**

```
abc
```

**Explanation:** With `f = 0`, any subsequence of length 3 is valid. The lexicographically smallest length-3 subsequence is the first three characters: `abc`.

## Example 3

**Input**

```
8
bbbbaaaa
4
4
```

**Output**

```
aaaa
```

**Explanation:** We must pick four letters with total strength ≥ 4. The four `a` flags (strength 1 each) sum to 4 and form the smallest possible string among valid selections.
