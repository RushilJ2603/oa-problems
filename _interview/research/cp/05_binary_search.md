# 05 — Binary Search & Parametric Search

**Placement value:** High (appears constantly as optimal/hidden constraints in arrays)
**Prereq topics:** Arrays, Sorting, Prefix Sums

**Pattern in one paragraph:** The core idea is that if a search space is monotonic (e.g., if you can complete a task in $X$ time, you can also complete it in $X+1$ time; if a number is $\ge k$, all larger numbers are $\ge k$), you can find the boundary (the minimum or maximum valid answer) in $O(\log(\text{search space}))$ time using Binary Search. In problem statements, this is heavily signaled by phrases like "minimize the maximum", "maximize the minimum", "find the smallest $K$ such that...", or constraints where the answer range is massive (e.g., up to $10^{14}$) but validating a guessed answer takes only $O(N)$ time.

## Ladder (easy -> hard, 24 problems)
- [ ] [Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/) — `LeetCode` `Medium` — lower/upper bound — The absolute fundamental for array BS. (core)
- [ ] [Burning Midnight Oil](https://codeforces.com/problemset/problem/165/B) — `Codeforces` `1200` — binary search on answer — Simplest introduction to BS on answer with a monotonic predicate. (core)
- [ ] [Vanya and Lanterns](https://codeforces.com/problemset/problem/492/B) — `Codeforces` `1200` — floating-point binary search — Classic intro to floating point BS from A2OJ.
- [ ] [Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/) — `LeetCode` `Medium` — binary search on answer — Extremely famous OA classic, appears in almost every interview prep sheet. (core)
- [ ] [Maximum Median](https://codeforces.com/problemset/problem/1201/C) — `Codeforces` `1300` — binary search on answer — Highly canonical "can we make the median X" CP-31 problem. (core)
- [ ] [Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/) — `LeetCode` `Medium` — modified binary search — Essential for tech interviews, finding the inflection point. (core)
- [ ] [Books](https://codeforces.com/problemset/problem/279/B) — `Codeforces` `1400` — binary search / two pointers — Famous A2OJ / Codeforces Edu problem to practice prefix sums + BS.
- [ ] [Schedule Management](https://codeforces.com/problemset/problem/1701/C) — `Codeforces` `1400` — binary search on answer — Good practice for worker-task distribution scenarios common in OAs.
- [ ] [Capacity To Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/) — `LeetCode` `Medium` — binary search on answer — Standard NeetCode / Striver problem for grouping contiguous subarrays. (core)
- [ ] [Magic Powder - 2](https://codeforces.com/problemset/problem/670/D2) — `Codeforces` `1500` — binary search on answer — CF Edu classic on max items you can craft given resources and wildcards. (core)
- [ ] [Factory Machines](https://cses.fi/problemset/task/1620) — `CSES` `Sorting and Searching` — binary search on answer — The canonical CSES BS on answer problem. (core)
- [ ] [Balanced Stone Heaps](https://codeforces.com/problemset/problem/1623/C) — `Codeforces` `1500` — binary search on answer — CP-31 problem combining BS with greedy backward propagation.
- [ ] [Hamburgers](https://codeforces.com/problemset/problem/371/C) — `Codeforces` `1600` — binary search on answer — One of the most famous BS problems on CF, "can I cook X items". (core)
- [ ] [Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/) — `LeetCode` `Hard` — min-max binary search — Extremely common OA hard pattern (identical to Painter's Partition / Book Allocation). (core)
- [ ] [Array Division](https://cses.fi/problemset/task/1085) — `CSES` `Sorting and Searching` — min-max binary search — CSES equivalent of Split Array Largest Sum. (core)
- [ ] [Coffee and Coursework (Hard Version)](https://codeforces.com/problemset/problem/1118/D2) — `Codeforces` `1600` — binary search on answer — CP-31 classic involving sorting and BS with penalty decay.
- [ ] [Exams](https://codeforces.com/problemset/problem/732/D) — `Codeforces` `1600` — binary search on answer — Famous Codeforces Edu problem with greedy scheduling inside the BS validation.
- [ ] [Pipeline](https://codeforces.com/problemset/problem/287/B) — `Codeforces` `1700` — binary search / math — A2OJ classic mixing BS with arithmetic progressions.
- [ ] [Water the Trees](https://codeforces.com/problemset/problem/1661/C) — `Codeforces` `1700` — binary search on answer — CP-31 problem testing modular validation inside BS. (stretch)
- [ ] [New Year's Problem](https://codeforces.com/problemset/problem/1619/D) — `Codeforces` `1700` — binary search on answer — Great stretch problem asking "is min over people of max over shops >= X". (stretch)
- [ ] [Cleaning the Phone](https://codeforces.com/problemset/problem/1475/D) — `Codeforces` `1800` — two pointers / binary search — High value CP-31 problem on minimizing cost with two arrays. (stretch)
- [ ] [Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/) — `LeetCode` `Hard` — advanced binary search — The most famous BS interview question, finding median via partition. (stretch)
- [ ] [Odd-Even Subsequence](https://codeforces.com/problemset/problem/1370/D) — `Codeforces` `2000` — min-max binary search — Exceptional rating-builder for BS validation logic on subsequences. (stretch)
- [ ] [Minimax Problem](https://codeforces.com/problemset/problem/1288/D) — `Codeforces` `2000` — binary search on answer + bitmasks — Masterpiece CF Edu problem combining BS with subset bitmasks. (stretch)

## Must-internalize checklist (5-10 bullets)
- Can write `std::lower_bound` / `std::upper_bound` logic (or Python `bisect`) from scratch without off-by-one errors.
- Understands how to formulate the `isValid(mid)` function for "binary search on answer".
- Knows the template for integer binary search: `l = min_possible, r = max_possible; while(l <= r) { mid = l + (r-l)/2; ... }`.
- Can cleanly handle floating-point binary search using `for (int i = 0; i < 100; i++)` instead of `while(r - l > EPS)` to avoid precision TLE.
- Recognizes the "minimize the maximum" or "maximize the minimum" wording as a hard giveaway for BS on answer.
- Can solve continuous-allocation / capacity problems (like Book Allocation or Painter's Partition) optimally.

## Where it appears in OAs / interviews
- **Resource Allocation OAs:** E.g., Amazon OA asking to partition packages into $K$ days minimizing the maximum daily weight.
- **Speed/Rate Problems:** E.g., "Find the minimum rate at which a worker must process items to finish in $H$ hours" (like Koko Eating Bananas).
- **Subsequence / Subarray Optimization:** An OA might ask to pick a subsequence of length $K$ where the maximum difference between elements is minimized, heavily signaling sorting + BS.
- **Hidden Optimization:** "Find the maximum radius of circles such that no two overlap..." which resolves to parametric float BS.
