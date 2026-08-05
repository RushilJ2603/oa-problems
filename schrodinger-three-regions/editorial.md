# Three Regions, One Reorganisation

## The shape of a plan is forced

A region that transfers its machines away is spent — it cannot be one of the three finalists. So
every region ends in exactly one of four roles:

- it is the region that will hold `finalMachineCount[0]`, or `[1]`, or `[2]`, or
- it is left alone.

Regions in the same role form a **group**: one of them survives and the others are poured into it.
Once you know which regions form a group, the cost is fixed and does not depend on which member
survives:

```
cost(group, target) = (|group| - 1) * shiftingCost      one transfer per region poured in
                    + |sum(group) - target|             one unit per machine added or removed
```

The three groups must be disjoint and non-empty; everything else is free.

## Algorithm

Label every region with one of `{0, 1, 2, unused}` and take the best labelling. With `n <= 10` that
is at most `4^10 = 1,048,576` labellings, each evaluated in O(n) — about ten million operations.

The labelling already decides which regions serve which target, so there is no separate permutation
loop; matching regions to targets is what the labels *are*.

A subset DP over the `3^n` ways to split a chosen subset into three groups is also fine, and an
O(3^n) or O(2^n · 3) formulation is asymptotically better, but at `n <= 10` none of that is needed.

**Complexity:** O(4^n · n) time, O(1) extra memory.

## Traps

- **64-bit.** Ten regions of 10⁹ machines sum to 10¹⁰, and an answer can exceed 3 × 10⁹ — both
  overflow a 32-bit integer. The enumeration computes every group sum, including the ones that are
  never optimal, so the overflow happens even on inputs whose *answer* is small.
- **Leftover regions are free.** There is no requirement to empty or use the other `n - 3` regions.
  A plan that tries to account for them is solving a harder problem than the one asked.
- **`n = 3` allows no transfers at all.** Every region is needed as a finalist, so the answer is the
  best of the six matchings of regions to targets, with no shifting cost anywhere.
- **A region cannot be emptied and refilled.** When a region holds far more machines than any
  target, the only options are to cut it down one machine at a time or to leave it alone — dumping
  it elsewhere spends it.
- **Transfers are charged per transfer.** Pouring three regions into one costs `2 * shiftingCost`,
  not one. An off-by-one here (`|group|` instead of `|group| - 1`) passes any test where every group
  is a singleton, which includes the most obvious hand-written cases.
