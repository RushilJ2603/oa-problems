# Editorial — Drone Delivery with Battery Swap Stations

A plain BFS over cells is wrong: whether you can keep flying depends on **remaining battery**, and
whether you can swap depends on **remaining vouchers**. So augment the state:

$$\text{state} = (r,\ c,\ \text{battery left},\ \text{vouchers left}).$$

- A **move** to an adjacent open cell costs **1 step** and **1 battery** (needs battery ≥ 1).
- Standing on a **kiosk** with a voucher may refill battery to `B` for **0 steps** (an instant swap).

Edges have weights 0 (swap) and 1 (move), so this is a **0-1 BFS** (a deque: push 0-cost edges to
the front, 1-cost edges to the back) or Dijkstra. The answer is the minimum distance over the end
cell across all battery/voucher values; `-1` if unreachable.

State count is `rows·cols·(B+1)·(K+1) ≤ 50·50·51·11 ≈ 1.4M`, each with O(1) edges — trivially fast.

**Why the state augmentation is forced:** the harness hands you `B` and `K` as separate fields. Any
solution that ignores them (a cell-only BFS) fails the moment a shortest cell-path needs more battery
than a slightly longer path that detours through a kiosk.

**The OA friction** isn't the algorithm (a first-week BFS variant) — it's parsing the 9-section
input into the exact `struct InputData` the harness declares, and realizing you must not touch
`main` / `parse_input` / `format_output`.
