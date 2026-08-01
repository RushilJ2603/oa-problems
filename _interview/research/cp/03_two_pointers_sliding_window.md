# 03 — Two Pointers & Sliding Window

**Placement value:** High (appears constantly in modern OAs and interviews, especially FAANG).
**Prereq topics:** Arrays, Sorting, Prefix Sums, basic Hash Maps.
**Pattern in one paragraph:** The core idea is maintaining a valid segment of an array using two index pointers (`L` and `R`), exploiting the monotonicity of a property (e.g., as the segment grows, its sum only increases). By avoiding resetting the `L` pointer, you optimize nested loops ($O(N^2)$) down to a linear $O(N)$ scan. Recognize it when you need to find a contiguous subarray, substring, or pair satisfying a condition, or when the problem asks for the "longest," "shortest," or "number of" valid contiguous sequences in an array/string.

## Ladder (easy -> hard, 27 problems)
- [ ] [Sereja and Dima](https://codeforces.com/problemset/problem/381/A) — `Codeforces` `800` — opposite ends pointers — Introduces moving pointers from both ends towards the center (A2OJ, USACO Guide).
- [ ] [Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/) — `LeetCode` `Medium` — opposite ends pointers — The most foundational two-pointer problem for interviews (NeetCode 150, Striver). **(core)**
- [ ] [Mishka and the Last Exam](https://codeforces.com/problemset/problem/1093/C) — `Codeforces` `1100` — opposite ends pointers — Good for grasping greedy pointer construction.
- [ ] [Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/) — `LeetCode` `Medium` — sliding window — The absolute canonical sliding window problem for interviews (NeetCode 150, Blind 75). **(core)**
- [ ] [BerSU Ball](https://codeforces.com/problemset/problem/489/B) — `Codeforces` `1200` — two arrays pointers — Classic matching problem, frequent in basic algorithmic rounds (A2OJ). **(core)**
- [ ] [Ternary String](https://codeforces.com/problemset/problem/1354/B) — `Codeforces` `1200` — sliding window — Find the shortest window containing all required elements; heavily reused pattern (CP-31). **(core)**
- [ ] [Binary Deque](https://codeforces.com/problemset/problem/1692/E) — `Codeforces` `1200` — sliding window — OA classic for finding a fixed-sum window with maximum length (CP-31).
- [ ] [Dora and Search](https://codeforces.com/problemset/problem/1793/C) — `Codeforces` `1200` — opposite ends pointers — Great for teaching condition-based pointer advancement on permutations.
- [ ] [Books](https://codeforces.com/problemset/problem/279/B) — `Codeforces` `1300` — sliding window — Canonical "longest window with sum <= k" (CF Edu). **(core)**
- [ ] [Number of Pairs](https://codeforces.com/problemset/problem/1538/C) — `Codeforces` `1300` — opposite ends pointers — Counting pairs satisfying a sum range; directly mirrors common OA questions (CP-31). **(core)**
- [ ] [Sum of Two Values](https://cses.fi/problemset/task/1640) — `CSES` `Sorting and Searching` — opposite ends pointers — The canonical competitive programming equivalent of Two Sum (CSES).
- [ ] [Playlist](https://cses.fi/problemset/task/1141) — `CSES` `Sorting and Searching` — sliding window — Longest unique subarray, reinforcing concepts across all platforms (CSES, USACO Guide). **(core)**
- [ ] [Approximating a Constant Range](https://codeforces.com/problemset/problem/602/B) — `Codeforces` `1400` — sliding window + multiset — Tracking min/max frequencies within a dynamically resizing window.
- [ ] [Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/) — `LeetCode` `Medium` — sliding window — Most famous sliding window utilizing frequency maps (NeetCode 150). **(core)**
- [ ] [Cellular Network](https://codeforces.com/problemset/problem/702/C) — `Codeforces` `1500` — two arrays pointers — Teaches monotonicity across two independently sorted arrays (CF Edu).
- [ ] [Vasya and String](https://codeforces.com/problemset/problem/676/C) — `Codeforces` `1500` — sliding window — Extremely common character replacement variant often seen in HackerRank tests.
- [ ] [They Are Everywhere](https://codeforces.com/problemset/problem/701/C) — `Codeforces` `1500` — sliding window — Shortest window containing all unique elements of the array. **(core)**
- [ ] [Kefa and Company](https://codeforces.com/problemset/problem/580/B) — `Codeforces` `1500` — sliding window / two pointers — Maximizing weight subject to an absolute difference constraint.
- [ ] [Hard Process](https://codeforces.com/problemset/problem/660/C) — `Codeforces` `1600` — sliding window — Maximum 1s by flipping at most k 0s; a canonical pattern (A2OJ). **(core)**
- [ ] [Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/) — `LeetCode` `Hard` — sliding window — The ultimate placement sliding window challenge, a must-know FAANG staple (NeetCode 150). **(core)**
- [ ] [Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/) — `LeetCode` `Hard` — sliding window + monotonic queue — Core requirement for top-tier tech OAs (NeetCode 150, Striver). **(core)**
- [ ] [Eugene and an array](https://codeforces.com/problemset/problem/1333/C) — `Codeforces` `1600` — two pointers + prefix sums — Excellent rating-builder for counting valid subarrays with no zero-sum subsegments. **(stretch)**
- [ ] [Sum of Three Values](https://cses.fi/problemset/task/1641) — `CSES` `Sorting and Searching` — 3-pointers — The standard extension of Two Sum to 3 elements (CSES, USACO Guide). **(stretch)**
- [ ] [Sliding Window Median](https://cses.fi/problemset/task/1076) — `CSES` `Sorting and Searching` — sliding window + two sets — Classic data structure extension of the window pattern (CSES). **(stretch)**
- [ ] [Sliding Window Cost](https://cses.fi/problemset/task/1077) — `CSES` `Sorting and Searching` — sliding window + two sets — Builds directly on Sliding Window Median (CSES). **(stretch)**
- [ ] [Maximum Subarray Sum II](https://cses.fi/problemset/task/1644) — `CSES` `Sorting and Searching` — sliding window + monotonic queue — Solving bounded subarray length constraints (CSES). **(stretch)**
- [ ] [Minimal Segment Cover](https://codeforces.com/problemset/problem/1175/E) — `Codeforces` `1900` — two pointers + binary lifting — Beautiful combination of greedy pointers with advanced data structures. **(stretch)**

## Must-internalize checklist (5-10 bullets)
- **The $O(N)$ sliding window template:** A `for` loop for `R` expanding the window, and a `while` loop inside advancing `L` to shrink it when constraints are violated.
- **Counting subarrays:** Understanding that when a window `[L, R]` is valid, it adds `R - L + 1` valid subarrays ending at `R`.
- **Opposite ends pointers:** Using `L = 0` and `R = N - 1` on sorted arrays to find pairs (Two Sum II pattern).
- **Two pointers on two arrays:** Traversing `A` and `B` simultaneously without nested loops (e.g., merging sorted arrays or finding the closest pair).
- **Monotonic queue extension:** Maintaining a `std::deque` to retrieve the sliding maximum/minimum of a window in $O(1)$ amortized time.
- **Frequency map states:** Using an array (or `std::unordered_map`) and an integer `distinct_count` to track conditions in $O(1)$ time per pointer movement, avoiding recalculation.

## Where it appears in OAs / interviews
- **"Find the longest continuous server uptime" or "Longest continuous subarray":** Standard disguise for sliding window (often a variant of finding the longest segment satisfying a sum/condition).
- **"Maximum items within a budget" / "Subarray sum equals K":** A sliding window where you shrink from the left the moment the sum exceeds the budget constraint (if array is strictly positive).
- **"Target sum from two different databases / lists":** Classic opposite-ends or two-array pointers on sorted inputs.
- **"Minimum window to cover all required skills" (Amazon/Google):** Direct reskin of LeetCode's Minimum Window Substring.
