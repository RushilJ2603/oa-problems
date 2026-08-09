# The Toll You Only Pay Once

## Step 1 — stop thinking about the journey

The free-on-reuse rule looks like it makes the *route* complicated: now the cost of a step depends on
where you have already been, so the obvious model is a state space of (current junction, set of roads
already paid for). That set has `2^m` values and the problem dies there.

The rule is much simpler than it looks. Read it again as an accounting statement:

> You pay for a road the first time you use it, and never again.

So the **total you pay is exactly the sum of the tolls of the distinct roads you drove on at least
once**. How many times you drove each one, and in what order, never enters the bill.

That kills the whole notion of a route. What you are really choosing is a **set of roads to buy**.
The journey is only there to say which sets are legal: you must be able to get from `a` to `c` and
from `c` to `b` using bought roads — which is exactly the condition that **`a`, `b` and `c` all lie in
the same connected component of the roads you bought**.

So: *buy the cheapest set of roads that connects `a`, `b` and `c`.* That is a **minimum Steiner tree
with three terminals**.

## Step 2 — a three-terminal Steiner tree has a shape

Steiner tree is NP-hard in general, which is why recognising this reduction and stopping there would
be a bad trade. With **three** terminals it is not hard at all, because a tree connecting three
vertices can only look one way: three paths leaving a single meeting point `v`.

(If the tree is a bare path, that is the same picture with `v` at one of the terminals and one branch
of length zero. And `v` is allowed to *be* a terminal, which is what makes the degenerate inputs
work.)

Each of the three branches must be a shortest path — otherwise swap it for one and the tree gets
cheaper. So:

```
answer = min over every junction v of  d(a,v) + d(b,v) + d(c,v)
```

Three Dijkstras from `a`, `b` and `c`, then one linear scan over the junctions. `O((n + m) log n)`.

**Why the scan is over *every* junction, not just the terminals:** the meeting point is usually
neither `a`, `b` nor `c`. In example 1 it is junction 2, which is not a terminal at all.

### Why the bound is tight both ways

- **`answer <= min_v(...)`** — for any `v`, the three shortest paths together connect all three
  terminals, and their union weighs no more than the sum (less, if they overlap).
- **`answer >= min_v(...)`** — take the optimal bought set, take a spanning tree `T` of it, and let
  `v` be the vertex where the three tree-paths meet. Those three paths are edge-disjoint inside `T`,
  so `d_T(a,v) + d_T(b,v) + d_T(c,v) <= weight(T)`, and each true distance `d(·,v)` is at most its
  tree distance.

## The wrong answers this catches

**`d(a,c) + d(c,b)` — two independent shortest paths.** This is the natural first answer and it is
what the free-reuse rule exists to punish. In example 1 it pays 4 where 3 is possible; the shared
road `2–3` is charged twice by a solver that treats the legs as separate problems. `tests/edge/08.in`
makes the gap explicit with a 199-road trunk that both legs ride.

**Overflow.** With `n = 10^5` junctions and tolls up to `10^9`, a single branch can reach `10^14` and
the answer can exceed `2 * 10^14`. A 32-bit accumulator silently wraps. `tests/edge/09.in` and
`tests/edge/10.in` both return values past `10^12`, so an `int` fails them outright.

**The degenerate terminals.** `a == b == c`, or `a == c`, are legal inputs. They need no special
casing — the formula already handles them, because `v` may be a terminal: with `a == c`, taking
`v = a` gives `0 + d(a,b) + 0`, which is the single leg you actually have to drive. Special-casing
them by hand is where bugs get added, not removed. (`tests/edge/04.in`, `tests/edge/05.in`.)

**Unreachable.** If no junction has all three distances finite, the three terminals are not in one
component and the answer is `-1`. Checking only "is `c` reachable from `a`" misses the case where the
second leg is the impossible one — `tests/edge/03.in` is exactly that.

## Complexity

| Step | Cost |
|---|---|
| Three Dijkstras | `O((n + m) log n)` |
| Scan for the meeting point | `O(n)` |
| **Total** | **`O((n + m) log n)`** |

Measured on the max-scale test (`n = 10^5`, `m = 2·10^5`): 0.33s in C++, 1.9s in Python.

## Generalising, if they push

For `k` terminals this becomes the **Dreyfus–Wagner** DP: `dp[S][v]` = cheapest tree spanning the
terminal subset `S` plus vertex `v`, built by merging two sub-trees that meet at `v` and then running
a Dijkstra relaxation over the whole `dp[S]` row. It is `O(3^k n + 2^k (n log n + m))` — fine for
`k <= 10`, and it degenerates to exactly the formula above at `k = 3`. That DP is what `brute.py`
runs, precisely so the cross-check does not assume the shortcut it is meant to be checking.
