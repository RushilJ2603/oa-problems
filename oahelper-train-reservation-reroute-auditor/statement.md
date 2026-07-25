# Train Reservation Reroute Auditor

A national rail operator runs a single high-speed line with **M** consecutive segments numbered **1..M**. Throughout the day, **N** reservation events arrive in chronological order. There are two event kinds:

- **BOOK l r p**: a passenger has booked a journey across segments **[l, r]** and is charged a per-segment cost contribution of **p**. After this event, every segment in **[l, r]** increases its cumulative cost by **p**.
- **QUERY l r**: ask for the minimum cumulative cost among segments in **[l, r]** as of right now — i.e., reflecting all preceding BOOK events.

The auditor wants to replay the day's log and emit one answer for every QUERY. It must also produce one final value, the **threshold-event index**: the earliest event index **t** (1-based) such that, after the first **t** events have been applied, some segment's cumulative cost has reached or exceeded the threshold **T** (i.e. is **≥ T**). If no segment ever reaches **T**, output **-1**. This value is always required — it is emitted on every run, including runs that contain no QUERY events.

Process the entire log efficiently: there are up to **2 × 10⁵** events on a line of up to **10⁶** segments.

## Input Format

```
M N T
event_1
event_2
...
event_N
```

- Line 1: three integers **M N T** — number of segments, number of events, and the threshold.
- Lines 2..N+1: each line is one event
  - **BOOK l r p** — \(1 \le l \le r \le M\), \(1 \le p \le 10^4\)
  - **QUERY l r** — \(1 \le l \le r \le M\)

## Output Format

```
query_answer_1
query_answer_2
...
threshold_event
```

- For each QUERY event, output its answer on its own line (in the order queries appear).
- After all events, output one extra line: the earliest event index at which any segment's cumulative cost first reached or exceeded **T**, or **-1** if no segment ever reaches **T**.

## Constraints

- \(1 \le M \le 10^6\)
- \(1 \le N \le 2 \times 10^5\)
- \(1 \le T \le 10^9\)
- \(1 \le l \le r \le M\)
- \(1 \le p \le 10^4\) (for BOOK events)
- Cumulative cost for any segment fits in a 64-bit signed integer

## Examples

### Example 1

**Input:**
```
6 5 15
BOOK 1 3 5
QUERY 1 6
BOOK 4 6 10
QUERY 2 5
BOOK 3 4 6
```

**Output:**
```
0
5
5
```

Six segments, five events, threshold 15.

- After event 1, segments 1–3 cost 5; rest 0.
- After event 2 (query): min over [1..6] is 0 (segments 4–6 still 0). Answer **0**.
- After event 3: segments 4–6 cost 10; segments 1–3 cost 5.
- After event 4 (query): min over [2..5] = min(5, 5, 10, 10) = **5**.
- After event 5: add 6 to segments 3–4. Cost vector: `[5, 5, 11, 16, 10, 10]`.
- Threshold 15 is first reached by segment 4 at event **5** (segment 4 becomes 16 ≥ 15).

### Example 2

**Input:**
```
4 3 100
BOOK 1 1 1
QUERY 1 1
BOOK 2 3 2
```

**Output:**
```
1
-1
```

Single query over segment 1 returns **1**. Segment costs stay below 100, so the threshold-event is **-1**.

### Example 3

**Input:**
```
3 4 5
BOOK 1 1 3
BOOK 2 2 4
BOOK 3 3 6
BOOK 1 3 1
```

**Output:**
```
3
```

No queries. Costs after each event: `[3,0,0]`, `[3,4,0]`, `[3,4,6]`, `[4,5,7]`. Threshold 5 is first reached at event **3** (segment 3 hits 6 ≥ 5).
