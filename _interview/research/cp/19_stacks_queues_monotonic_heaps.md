# 19 — Stacks, Queues, Monotonic Deque & Priority Queue

**Placement value:** High (These are foundational data structures that appear constantly in both FAANG OAs and Codeforces greedy/simulation tasks.)
**Prereq topics:** Arrays, Two Pointers, Basic Greedy
**Pattern in one paragraph:** 
Stacks resolve LIFO dependencies (matching, parsing, recursive simulation), while queues handle FIFO processing (BFS, fair scheduling). The **monotonic stack/deque** pattern maintains a strictly increasing or decreasing sequence of elements to efficiently find the "next greater/smaller element" or compute sliding window extrema in $O(N)$ time. **Heaps/Priority Queues** are used when you need dynamic access to the running maximum or minimum (e.g., top $K$ elements, greedy choices, Dijkstra's algorithm), often serving to optimize a greedy strategy by allowing you to "undo" or continually pick the best available option.

## Ladder (easy -> hard, ~24 problems)
- [ ] [Valid Parentheses](https://leetcode.com/problems/valid-parentheses/) — `LeetCode` `Easy` — Stack basics — **(core)** The ultimate OA-classic for stack simulation and LIFO state tracking (NeetCode 150).
- [ ] [Implement Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/) — `LeetCode` `Easy` — Stack/Queue design — Classic interview warmup to test understanding of amortized $O(1)$ operations.
- [ ] [Move Brackets](https://codeforces.com/problemset/problem/1374/C) — `Codeforces` `1000` — Stack / Greedy — **(core)** Fundamental CP bracket balancing logic; shows up constantly as a subproblem (CP-31).
- [ ] [Min Stack](https://leetcode.com/problems/min-stack/) — `LeetCode` `Medium` — Stack design — **(core)** Foundational interview question teaching state preservation in stacks (NeetCode 150, Striver).
- [ ] [Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/) — `LeetCode` `Medium` — Priority Queue — **(core)** The canonical max/min-heap problem for maintaining a top-K running set (NeetCode 150, Striver).
- [ ] [Asteroid Collision](https://leetcode.com/problems/asteroid-collision/) — `LeetCode` `Medium` — Stack simulation — Excellent test of resolving sequence collisions with a stack (NeetCode 150).
- [ ] [Task Scheduler](https://leetcode.com/problems/task-scheduler/) — `LeetCode` `Medium` — Priority Queue / Greedy — Highly recurring OA question involving PQ simulation and cooldown periods (NeetCode 150).
- [ ] [Room Allocation](https://cses.fi/problemset/task/1164) — `CSES` `Sorting and Searching` — Priority Queue — **(core)** Canonical interval/sweep-line problem using a min-heap to reuse freed resources (CSES, USACO Guide).
- [ ] [Constructing the Array](https://codeforces.com/problemset/problem/1353/D) — `Codeforces` `1500` — Priority Queue — **(core)** Beautiful CP rating-builder that uses a max-heap to simulate dividing segments by length.
- [ ] [Nearest Smaller Values](https://cses.fi/problemset/task/1645) — `CSES` `Sorting and Searching` — Monotonic Stack — **(core)** The purest, most canonical introduction to the monotonic stack concept (CSES).
- [ ] [Daily Temperatures](https://leetcode.com/problems/daily-temperatures/) — `LeetCode` `Medium` — Monotonic Stack — **(core)** The gold standard OA problem for finding the "Next Greater Element" (NeetCode 150, Striver).
- [ ] [Car Fleet](https://leetcode.com/problems/car-fleet/) — `LeetCode` `Medium` — Monotonic Stack — Fantastic conceptual application of tracking bottlenecks via a stack (NeetCode 150).
- [ ] [Playlist](https://codeforces.com/problemset/problem/1140/C) — `Codeforces` `1600` — Priority Queue / Greedy — **(core)** Essential rating-builder combining sorting with a running min-heap to optimize a metric.
- [ ] [Potions (Hard Version)](https://codeforces.com/problemset/problem/1526/C2) — `Codeforces` `1600` — Priority Queue / Greedy — **(core)** Canonical CP trick (Regret Greedy) where you use a PQ to "undo" previous suboptimal choices (CP-31).
- [ ] [Producing Snow](https://codeforces.com/problemset/problem/923/B) — `Codeforces` `1600` — Priority Queue — Teaches maintaining aggregate changes over a heap or using prefix sums with binary search.
- [ ] [Cashback](https://codeforces.com/problemset/problem/940/E) — `Codeforces` `1600` — Monotonic Deque / DP — Shows how sliding window minimums can heavily optimize 1D DP transitions.
- [ ] [Valid BFS?](https://codeforces.com/problemset/problem/1037/D) — `Codeforces` `1700` — Queue / Trees — **(stretch)** Advanced queue validation; tests if you truly understand how BFS tree traversal works.
- [ ] [Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/) — `LeetCode` `Hard` — Monotonic Stack — **(core)** The boss-level monotonic stack problem; a must-know for FAANG interviews (NeetCode 150, Striver).
- [ ] [Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/) — `LeetCode` `Hard` — Monotonic Stack / Two Pointers — **(core)** The most famous hard OA problem, solvable conceptually via stacks or pointers (NeetCode 150, Striver).
- [ ] [Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/) — `LeetCode` `Hard` — Monotonic Deque — **(core)** The absolute canonical problem for learning the $O(N)$ Monotonic Deque trick (NeetCode 150, Striver).
- [ ] [Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/) — `LeetCode` `Hard` — Two Priority Queues — **(stretch)** The definitive two-heap pattern for tracking running medians (NeetCode 150).
- [ ] [Sliding Window Median](https://cses.fi/problemset/task/1077) — `CSES` `Sorting and Searching` — Two PQs / Policy DS — **(stretch)** A step above standard sliding window, requiring lazy deletion in heaps or C++ PBDS (CSES).
- [ ] [Longest Regular Bracket Sequence](https://codeforces.com/problemset/problem/5/C) — `Codeforces` `1900` — Stack / DP — **(stretch)** A fantastic historical CF problem merging stack-based bracket matching with dynamic programming.
- [ ] [R2D2 and Droid Army](https://codeforces.com/problemset/problem/514/D) — `Codeforces` `1900` — Monotonic Deque / Sparse Table — **(stretch)** Hard rating-builder that brilliantly combines binary search with Monotonic Deque sliding windows.

## Must-internalize checklist (5-10 bullets)
- **Standard Stack Operations:** Be able to instantly write state-tracking stacks for parsing string problems, matching brackets, or evaluating postfix notation.
- **Next Greater/Smaller Element:** Memorize the $O(N)$ monotonic stack template. Know when to maintain an increasing vs. decreasing stack.
- **Histogram Rectangles:** Understand the mechanism of popping from a monotonic stack to compute widths (`current_index - stack.top() - 1`) and areas.
- **$O(N)$ Sliding Window Extrema:** Memorize the monotonic deque template (`std::deque` in C++) to find the maximum or minimum in all windows of size $K$ in strictly linear time.
- **Top $K$ Tracking:** Instantly reach for a Min-Heap of size $K$ to find the Top $K$ largest elements in a stream, avoiding $O(N \log N)$ full sorting.
- **Regret Greedy (Undo Trick):** Recognize when a greedy approach might fail and use a Priority Queue to track and "swap out" the worst previously accepted choice.
- **Two-Heap Pattern:** Master the Max-Heap (lower half) / Min-Heap (upper half) combo for running medians.

## Where it appears in OAs / interviews
- **Amazon OA (Delivery Optimization):** "Given a stream of incoming packages, constantly report the median weight of the last $K$ packages." (Direct translation of Sliding Window Median).
- **Google OA (Server Loads):** "You have a sequence of server loads. For each sub-segment of length $M$, find the maximum load and return the minimum of these maximums." (Requires Monotonic Deque).
- **Citadel/HR (Stock Span):** "Given daily price quotes for a stock, return an array of spans where span is the number of consecutive days prior where the price was lower." (Classic Next Greater/Smaller element via Monotonic Stack).
- **Uber OA (Task Scheduling):** Scheduling intervals where overlapping jobs require a new resource; solved optimally by sorting by start time and using a Min-Heap of end times (Room Allocation).
