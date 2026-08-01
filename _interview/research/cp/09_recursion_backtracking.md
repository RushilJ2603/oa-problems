# 09 — Recursion & Backtracking

**Placement value:** High | Foundational for nearly all OA graph/matrix pathfinding and combination generation.
**Prereq topics:** Basic Recursion, Time Complexity Analysis, Bitwise Operations (for subset masking)
**Pattern in one paragraph:** The core idea is to explore all possible states (subsets, permutations, or paths) by building a candidate incrementally and abandoning it ("backtracking") the moment we realize it cannot yield a valid solution. In problem statements, this is recognized by extremely small constraints ($N \le 20$), keywords like "find all valid combinations", "generate", or "how many ways" (without a modulo), or when searching for an explicit path on a small matrix.

## Ladder (easy -> hard, ~18-28 problems)
- [ ] [Subsets](https://leetcode.com/problems/subsets/) — `LeetCode` `Medium` — `subsets` — **(core)** The foundational template for take-it-or-leave-it recursion (NeetCode 150, Striver).
- [ ] [Apple Division](https://cses.fi/problemset/task/1623) — `CSES` `Introductory` — `subsets` — **(core)** A direct application of subset generation, minimizing differences; classic CP starter (USACO Bronze).
- [ ] [Combinations](https://leetcode.com/problems/combinations/) — `LeetCode` `Medium` — `combinations` — **(core)** Essential template for generating size-K subsets; frequent in OAs.
- [ ] [Combination Sum](https://leetcode.com/problems/combination-sum/) — `LeetCode` `Medium` — `combination-sum` — **(core)** Demonstrates reusing elements in a recursive tree; universally recommended (NeetCode 150).
- [ ] [Permutations](https://leetcode.com/problems/permutations/) — `LeetCode` `Medium` — `permutations` — **(core)** The canonical O(N!) generation template; appears constantly as a building block.
- [ ] [Creating Strings](https://cses.fi/problemset/task/1622) — `CSES` `Introductory` — `permutations` — **(core)** The competitive programming equivalent of Permutations, introducing duplicates.
- [ ] [Subsets II](https://leetcode.com/problems/subsets-ii/) — `LeetCode` `Medium` — `subsets-with-duplicates` — Standard technique to skip duplicate states using array sorting and adjacent checks.
- [ ] [Permutations II](https://leetcode.com/problems/permutations-ii/) — `LeetCode` `Medium` — `permutations-with-duplicates` — Expands duplicate skipping to permutations via frequency maps or skipped visited nodes.
- [ ] [Combination Sum II](https://leetcode.com/problems/combination-sum-ii/) — `LeetCode` `Medium` — `combination-sum-with-duplicates` — Consolidates the duplicate-skipping logic learned in previous problems.
- [ ] [Combination Sum III](https://leetcode.com/problems/combination-sum-iii/) — `LeetCode` `Medium` — `combination-sum` — A constrained variation of combination sum, solidifying K-element selection.
- [ ] [Letter Combinations of a Phone Number](https://leetcode.com/problems/letter-combinations-of-a-phone-number/) — `LeetCode` `Medium` — `combinations` — **(core)** Massive OA classic; tests mapping numbers to variable-length choices and generating all paths.
- [ ] [Generate Parentheses](https://leetcode.com/problems/generate-parentheses/) — `LeetCode` `Medium` — `constrained-generation` — **(core)** Beautiful problem highlighting state parameters (open vs closed counts) to prune invalid branches.
- [ ] [Petr and a Combination Lock](https://codeforces.com/problemset/problem/1097/B) — `Codeforces` `1200` — `subsets` — Core CF Div2B problem requiring simple 2^N generation to hit a target sum modulo 360.
- [ ] [Preparing Olympiad](https://codeforces.com/problemset/problem/550/B) — `Codeforces` `1300` — `subsets` — Canonical CF problem testing subset generation with multiple validity conditions (min, max, sum).
- [ ] [Lucky Numbers (easy)](https://codeforces.com/problemset/problem/96/B) — `Codeforces` `1300` — `constrained-generation` — Excellent DP-less generation task, demonstrating state branching until a length limit is hit.
- [ ] [Synthetic Kadomatsu](https://atcoder.jp/contests/abc119/tasks/abc119_c) — `AtCoder` `944` — `multi-way-branching` — **(core)** A fantastic 4-way branching state problem; canonical for AtCoder C/D backtracking (USACO Silver).
- [ ] [Hanjo](https://atcoder.jp/contests/abc196/tasks/abc196_d) — `AtCoder` `1100` — `grid-backtracking` — Grid state generation with varying tile sizes, a staple pattern in AtCoder and heavy OAs.
- [ ] [Palindrome Partitioning](https://leetcode.com/problems/palindrome-partitioning/) — `LeetCode` `Medium` — `partitioning` — **(core)** Core template for string partitioning (NeetCode 150); bridges backtracking into DP later on.
- [ ] [Matchsticks to Square](https://leetcode.com/problems/matchsticks-to-square/) — `LeetCode` `Medium` — `partitioning` — Famous K-partition problem; teaches vital pruning mechanics like sorting descending.
- [ ] [Word Search](https://leetcode.com/problems/word-search/) — `LeetCode` `Medium` — `matrix-backtracking` — **(core)** The most ubiquitous 2D grid DFS backtracking problem in placement interviews.
- [ ] [Chessboard and Queens](https://cses.fi/problemset/task/1624) — `CSES` `Introductory` — `n-queens` — **(core)** Foundational N-Queens; introduces diagonal tracking arrays for $O(1)$ validity checks.
- [ ] [N-Queens](https://leetcode.com/problems/n-queens/) — `LeetCode` `Hard` — `n-queens` — The full standard format of N-Queens asking for string representations; universally famous.
- [ ] [Sudoku Solver](https://leetcode.com/problems/sudoku-solver/) — `LeetCode` `Hard` — `matrix-backtracking` — **(stretch)** The ultimate grid state backtracking test; a capstone for interview prep.
- [ ] [Grid Paths](https://cses.fi/problemset/task/1625) — `CSES` `Introductory` — `matrix-backtracking` — **(stretch)** Famous $7 \times 7$ path counting; demands extreme pruning heuristics (e.g. wall-hitting rules) for execution time.

## Must-internalize checklist (5-10 bullets)
- **Subsets Template:** Write standard take-it-or-leave-it subset generation cleanly.
- **Permutations Template:** Write `O(N!)` generation both via swap-based logic and via a boolean `visited` array.
- **Duplicate Skipping:** Know how to handle duplicate elements in subsets/permutations by sorting the array and using `if (i > start && nums[i] == nums[i-1]) continue;`.
- **String Partitioning Template:** Master iterating through string lengths and making recursive calls on suffixes (crucial for Palindrome Partitioning & later DP).
- **2D Grid DFS:** Standardize a DFS with a `visited` array (or modifying the grid in-place temporarily like `board[i][j] = '*'`) for matrix paths.
- **Diagonal Tracking (N-Queens):** Represent diagonals linearly in arrays using `row + col` and `row - col + n - 1` for O(1) checks.
- **Pruning Mechanisms:** Immediately terminate branches that exceed limits (e.g., sum > target) or enforce sorting largest-first (Matchsticks to Square) to fail faster.
- **Bitmask Alternates:** Know how to map $0$ to $2^N-1$ into binary strings as an alternate, iterative way to generate subsets.

## Where it appears in OAs / interviews
- **String Pathfinding in 2D Matrices:** Very common to see "Word Search" disguised as finding a specific sequences of characters on a grid with obstacles (Amazon/Microsoft).
- **Distributing Items into Buckets:** Partitioning tasks equally among $K$ servers or finding if weights can be split into valid blocks (essentially Matchsticks to Square).
- **Valid Combinations under Budget:** Given a set of items with weights/costs, output all combinations that exactly meet a budget constraint without duplicates (Capital One).
- **Brute Force "Impossible" Constraints:** Encountering an OA problem with $N \le 20$ or $N \le 15$ and thinking it's DP, when in reality it's a simple backtracking tree with some pruning logic.
