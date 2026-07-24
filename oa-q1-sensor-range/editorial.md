# Editorial — Sensor Range Overlap

For sensor `i`, the needed increment is `d[i] = max(0, min_{j≠i} (|p[i]−p[j]| − r[i] − r[j]))`.

A naive `O(n^2)` double loop is correct and fine for small `n`. To do it in `O(n log n)`, sort by
position and split the distance by side:

- For a sensor `j` to the **left** (`p[j] ≤ p[i]`): `|p[i]−p[j]| − r[j] = p[i] − (p[j] + r[j])`, so
  you want the **maximum** `p[j] + r[j]` seen so far — one left-to-right sweep.
- For a sensor `j` to the **right** (`p[j] ≥ p[i]`): `|p[i]−p[j]| − r[j] = (p[j] − r[j]) − p[i]`, so
  you want the **minimum** `p[j] − r[j]` — one right-to-left sweep.

Take the better of the two, subtract `r[i]`, and clamp at 0. Watch out for overflow: distances and
ranges reach `10^9`, so use 64-bit integers.
