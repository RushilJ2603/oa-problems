# Escape Room Capacity

## Stop thinking about scheduling

The story says "figure out if she can schedule all the game shows" and that word does a lot of
damage — it suggests you get to *choose* something. You do not. Every show runs at the time it says
it runs, on one room. There is no assignment to make and nothing to search over. The only question
is: **what is the largest number of people in the room at any instant, and is it more than
`capacity`?**

## The timeline is finite

Occupancy is a step function. It changes only when a show starts (goes up) or ends (goes down), so
the entire infinite timeline collapses to at most `2N` interesting instants. Record two deltas per
show and sweep them in time order:

```
+attendees at start_time        -attendees at end_time
```

```cpp
map<long long, long long> delta;
for (auto &s : shows) { delta[s.start] += s.att; delta[s.end] -= s.att; }
long long inside = 0;
for (auto &kv : delta) {
    inside += kv.second;
    if (inside > capacity) return false;
}
return true;
```

`O(N log N)` for the ordering, `O(N)` after that.

You do not need to check the whole step function either. Occupancy only ever *rises* at a start, so
if the room is ever over capacity it is over capacity at some show's `start_time`. That is the
observation `brute.py` leans on to check the answer straight from the definition.

## Trap 1: what happens at the shared instant

This is the one the problem is really about. Show A runs `[1, 5)`, show B runs `[5, 9)`. Do they
overlap at time `5`?

**No.** A's attendees are gone by `5`; B's arrive at `5`. Sample 3 is exactly this case and its
answer is `True` — the peak is `5`, not `10`.

If you build an explicit event list instead of a map, this becomes a sort-order requirement:
**departures at time `t` must be applied before arrivals at time `t`.** Sort by `(time, delta)` —
negative before positive — and not by `(time, index)`. Getting it backwards turns every back-to-back
chain into a false alarm, and `edge/12` is a chain of 100 000 such shows whose correct answer is
`True`.

Using a `map<time, sum-of-deltas>` sidesteps the issue entirely: both deltas at time `t` land in the
same bucket and are applied together before the total is inspected. That is the reason to prefer it.

## Trap 2: `int`

`N` reaches `10^5` and `attendees` reaches `10^9`, so the running total reaches `10^14`. In a 32-bit
accumulator that wraps — usually to a *negative* number, which then compares happily against the
capacity and the wrong answer is `True`. `edge/08` needs only two shows to reach `2 · 10^9` and
`edge/11` goes all the way to `10^14`. The capacity itself fits in 32 bits, which is what makes this
easy to miss.

## Trap 3: shows of zero length

`end_time >= start_time`, so `start_time == end_time` is legal. Such a show occupies the room over
the empty interval `[t, t)` and therefore never contributes — `edge/03` puts a billion attendees
into three zero-length shows with a capacity of `0` and the answer is still `True`. In the delta
formulation this is free: `+a` and `-a` land on the same key and cancel before anything is read. In
a hand-rolled event list it is free only if departures sort before arrivals — the same discipline as
trap 1, which is why both bugs tend to appear and disappear together.

## Trap 4: over-capacity means *strictly* over

`peak == capacity` is fine. `edge/06` (`peak = 10`, `capacity = 10` → `True`) and `edge/07`
(`peak = 10`, `capacity = 9` → `False`) are the same two shows either side of the line, and a `>=`
where a `>` belongs flips both.

## Complexity

Time `O(N log N)`, dominated by ordering the `2N` events. Space `O(N)`. Coordinate values go up to
`10^9`, so a plain array indexed by time is not an option — the map (or a sorted event vector) is
doing the compression for you.
