# Best Glued Substring

## Splitting the two joins apart

A substring is a pair `(i, j)` — where it starts and where it ends. The left join only looks at the
first few characters, so it depends on `i` alone. The right join only looks at the last few, so it
depends on `j` alone. Neither depends on the other. That is the whole reason this is not a cubic
problem.

So the two questions to answer for every position are:

- for a start `i` and a length `k`: is `s[i .. i+k)` equal to the **last** `k` characters of `p`?
- for an end `j` and a length `k`: is `s[j-k .. j)` equal to the **first** `k` characters of `q`?

The second is a Z-function away. Build `g[x] = |LCP(s[x..], q)|` from
`Z(q + '\x01' + s)`; then `s[j-k .. j)` matches `q`'s first `k` characters exactly when
`g[j-k] >= k`.

The first is the same question read backwards. A **suffix** of `p` meeting a **prefix** of `s[i..]`
becomes a **prefix** of `reverse(p)` meeting a **suffix** of `reverse(s)`. So build
`h[y] = |LCP(reverse(s)[y..], reverse(p))|` and the test becomes `h[n-i-k] >= k`.

## The trap: a valid overlap does not imply a shorter valid one

The natural next step is to define `A[i]` as "the biggest overlap available at start `i`" and score
a substring of length `L` as `min(A[i], L)`. **This is wrong**, and it is wrong in a way that
passes every small hand-written example.

`k` valid does not imply `k-1` valid. The two tests compare *different pairs of characters*: length
`k` compares `p`'s last `k` against `s[i..i+k)`, while length `k-1` compares `p`'s last `k-1` — a
different slice of `p` — against a different slice of `s`. Neither implies the other.

Sample 3 is the smallest case that punishes it. With `s = cbdcaec`, `q = ca`, look at the position
just after `cbdca`. The overlap `ca` (length 2) is valid there. The overlap of length 1 is not: the
character before that point is `a`, and `q` starts with `c`. So a substring of length 1 ending
there — the single `a` — scores **0** on its right join, while `min(2, 1) = 1` claims it scores 1.
That one phantom point makes `a` tie the true winner, and since `a` is lexicographically smaller,
the wrong answer is printed.

The fix is to ask for the largest valid `k` **that is at most `L`**, which is a running maximum
rather than a cap:

```cpp
// growing the piece by one makes exactly one new length reachable: k = L
if (L <= np && h[n - i - L] >= L) pfx = L;
```

For the right join the length grows as `i` moves, not `j`, so precompute per end position
`pbest[j][m] = max{ valid k <= m }` — again a running maximum, over `m`.

## Putting it together

Scan every `(i, j)`. For a fixed `i`, walk `j` upward and keep the left running maximum; read the
right one out of `pbest`. That is O(|s|²) pairs at O(1) each.

## The tie-break

Comparing two candidate substrings character by character turns O(n²) candidates into O(n³) work.
Precompute `lcp[i][j] = |LCP(s[i..], s[j..])|` with the one-line recurrence

```cpp
lcp[i][j] = (s[i] == s[j]) ? lcp[i+1][j+1] + 1 : 0;
```

and any two substrings compare in O(1): if their common prefix already covers the shorter one, the
shorter one is smaller; otherwise the first differing character decides. At `|s| = 2000` that table
is 16 MB of `int`, which fits the limit comfortably.

Total: O(|s|² + |s|·|p| + |s|·|q|) time.

## Smaller things that catch people

- **Empty substrings.** `t` must be non-empty, otherwise the empty string scores 0 and wins every
  tie by being lexicographically smallest.
- **The joins are independent.** For a one-character `t`, the same character may fuse on both
  sides — `s = p = q = "a"` scores 2, not 1.
- **Ties are common**, not exotic. Over a two-letter alphabet most positions tie, so a solution that
  keeps "the first best found" instead of "the lexicographically smallest best" fails almost every
  large test rather than a rare one.
