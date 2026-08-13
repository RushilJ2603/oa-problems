# Office Placement

## Read the constraints first

`h × w ≤ 27` and `n ≤ 5`. Those two lines are not incidental — they are the answer. The number of
ways to choose 5 plots out of 27 is

```
C(27, 5) = 80,730
```

and scoring one placement costs at most 27 × 5 = 135 distance lookups. That is about 11 million
operations for the largest input in the entire problem, which runs in a few milliseconds.

There is no clever construction to find. The work is recognising that the search space has been
deliberately made small enough to walk through, and then walking through it correctly.

A constraint like `n ≤ 5` sitting next to a grid capped at 27 cells is a strong signal: exponential
in `n` is intended. Compare with the same problem at `h·w ≤ 10^5` — that would be a completely
different question (and a much harder one), which is exactly why the limits are written this way.

## The search

1. Precompute `dist[a][b]` for all pairs of plots — a 27 × 27 table.
2. Enumerate every combination of `n` distinct plots.
3. For each combination, find the plot whose nearest office is farthest away.
4. Keep the smallest such value seen.

Recursion over "next plot index ≥ `from`" generates each combination exactly once. Passing
`from = c + 1` is what keeps offices distinct and stops the same set being generated in 120
different orders.

## The alternative: turn it into a decision problem

Instead of computing the answer directly, ask a yes/no question for each candidate radius:

> can `n` offices put every plot within distance `d`?

Coverage only improves as `d` grows, so the first `d` that answers yes is the answer. At a fixed
`d`, give every plot the bitmask of plots it would serve, then search — always branching on the
**first plot nobody covers yet**, and trying only the offices that would cover it. That pruning is
what makes set cover tractable here.

Both approaches are fast at these limits. The second is the one that survives if the grid gets
bigger, and it is how `brute.py` is written, so the two solutions share nothing.

## Things to get right

- **Manhattan, not Euclidean and not Chebyshev.** `|dr| + |dc|`. On the 2×3 sample all three metrics
  happen to give 1, so a sample-only check will not catch this.
- **Offices are on plots, and those plots count.** A plot holding an office is distance 0 — it does
  not get excluded from the maximum.
- **`n` can equal the number of plots.** Then every plot has an office and the answer is 0; make
  sure the combination generator handles `n = h·w` instead of running off the end.
- **The grid can be a strip.** `1 × 27` and `27 × 1` are both valid, and a solution that assumes
  `h ≤ w` (or indexes `r * h + c` instead of `r * w + c`) gets exactly one of the two right. The
  answer must be symmetric under transposing the grid: `3 9 4` and `9 3 4` are both 2.
- **Nothing about the optimum is evenly spaced.** It is tempting to place offices on a lattice and
  compute the answer arithmetically. For `1 × 27` with 5 offices that reasoning gives the right
  answer, 3; for most 2-D shapes it does not, and the enumeration is the point anyway.
