# Balance the Two Baskets

## Why every greedy fails

The objective is `min(totA, totB)`, and a minimum is not a sum — it cannot be built up index by
index, because whether an index helps depends on which basket is currently behind, and that changes
as you pick. Three greedies look reasonable and all of them are wrong. These are not hypothetical;
each is a curated test:

| Greedy | Counterexample | Optimal | Greedy gets |
|---|---|---|---|
| top `k` by `a[i]` | `edge/07`: `a = [1,2,9,2,6]`, `b = [10,1,9,4,1]`, `k = 3` | 16 | 11 |
| top `k` by `min(a[i], b[i])` | same case | 16 | 12 |
| top `k` by `a[i] + b[i]` | `edge/08`: `a = [2,3,3,3,1,3]`, `b = [10,8,3,10,10,8]`, `k = 5` | 14 | 12 |

Sorting by `a[i] + b[i]` is the most seductive of the three, because maximising the total *is* the
right instinct for most selection problems. It fails here for a specific reason: `a + b` treats a
lopsided index `(1, 19)` as identical to a balanced `(10, 10)`, and only one of those two is useful
when basket `a` is the one lagging.

## The state that makes it work

You cannot track `min(totA, totB)` as you go — a partial minimum tells you nothing about the final
one, since a later pick can rescue the lagging basket. So track the two sums instead. Both of them
in the state would be `O(n · k · S_a · S_b)` and far too much, but you do not need both: **put one
sum in the state and maximise the other.**

```
dp[j][s] = the largest totB reachable, using exactly j chosen indices, whose totA is exactly s
```

with `dp[0][0] = 0` and everything else unreachable (`-1`). Each index is offered once, in a
descending `j` sweep so it cannot be taken twice:

```cpp
for (int i = 0; i < n; i++)
    for (int j = min(i, k - 1); j >= 0; j--)
        for (int s = S - a[i]; s >= 0; s--)
            if (dp[j][s] >= 0)
                dp[j+1][s + a[i]] = max(dp[j+1][s + a[i]], dp[j][s] + b[i]);
```

At the end every reachable `totA` is a row entry, and the paired `totB` is its value, so the answer
is a single scan:

```cpp
answer = max over s with dp[k][s] >= 0 of min(s, dp[k][s]);
```

The final `min` is where the whole problem lives. The DP never optimises the objective directly — it
enumerates the **Pareto frontier** of `(totA, totB)` pairs at exactly `k` picks, and the `min` is
applied once at the end, when both numbers are known.

## Why the constraints are what they are

Carrying `totA` in the state is only affordable because it is bounded: `n <= 50` and `a[i] <= 100`
cap it at `5000`. The table is `(k+1) × (S+1) <= 51 × 5001` and the work is
`O(n · k · S) = 50 · 50 · 5000 ≈ 1.25 × 10^7`. Measured: 0.00s in C++, 0.14s in Python.

That bound on the *values* is the real constraint, not `n`. If `a[i]` could be `10^9` this DP would
be dead and the problem would be genuinely intractable — which is worth saying out loud in an
interview, because it shows you know which number you are actually exploiting.

## On "isn't this bitmask DP?"

It is the natural first guess, and it is worth being precise about why it is not:

- `2^50 ≈ 1.13 × 10^15` subsets. Not close.
- `C(50, 25) ≈ 1.26 × 10^14` even restricted to the right size.
- Meet-in-the-middle splits it into two halves of 25, but `2^25 ≈ 3.4 × 10^7` **per half** must then
  be merged on two keys at once (count *and* one of the sums), so it is both slower and much fiddlier
  than the knapsack — and it only becomes the right tool when the values are too large for the DP.

A bitmask over indices is the right shape when `n <= ~20`. At `n = 50` with small values, the count
goes in one axis and a sum goes in the other. Recognising which of `n` or `max value` is the small
number is the whole decision.

## Complexity

| Approach | Time | Verdict |
|---|---|---|
| Enumerate all `C(n,k)` subsets | `O(C(n,k) · k)` | hopeless past `n ≈ 20` |
| Bitmask over indices | `O(2^n · n)` | hopeless at `n = 50` |
| Meet in the middle | `~O(2^(n/2) · n)` | works, but needed only for large values |
| **Count × sum knapsack** | **`O(n · k · S)`** | **intended** |
