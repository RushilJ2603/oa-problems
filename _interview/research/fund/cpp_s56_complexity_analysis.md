# Complexity and Asymptotic Analysis

Every algorithm section in these notes quotes a Big-O cost. This section teaches what that notation actually *means*, how to derive it from C++ code, when it misleads, and how competitive-programming constraints turn a complexity class into a yes/no decision.

::: heavy
Dense primer — slow down. Asymptotics are used everywhere in Part V and the CP toolkit, but never derived from first principles there. Read growth and Big-O carefully before the derivation rules and the amortised argument.
:::

## Why we measure growth, not seconds

Wall-clock time depends on the machine, the compiler, optimisation flags, cache state, and what else is running. Two solutions that both “feel fast” on $n = 100$ can diverge violently at $n = 10^6$. **Asymptotic analysis** asks a machine-independent question:

> As the input size $n$ grows, how does the *number of elementary operations* grow?

We count abstract steps — comparisons, arithmetic, pointer follows, array accesses — not nanoseconds. A loop that does $3n + 7$ additions is treated as growing like $n$. The absolute constant $3$ matters in practice (see *When Big-O lies*), but the *shape* of the growth decides whether an algorithm survives large $n$.

::: keypoint
Complexity is a statement about **growth rate** with respect to input size $n$. It is not a stopwatch reading, and it is deliberately independent of hardware and compiler.
:::

## Big-O, Big-Omega, and Big-Theta

### Big-O — an upper bound

Analogy: saying a journey is $O(100\,\mathrm{km})$ means “it will not take more road than roughly a constant times $100\,\mathrm{km}$” — you may arrive sooner, but you will not exceed that order of distance.

::: definition
A function $f(n)$ is **$O(g(n))$** (read “big-O of $g(n)$”) if there exist constants $c > 0$ and $n_0$ such that for all $n \ge n_0$,
$$0 \le f(n) \le c \cdot g(n).$$
In plain English: eventually, $f$ never grows faster than a constant multiple of $g$. Big-O is an **upper bound** on growth — it need not be tight.
:::

So $2n + 5$ is $O(n)$, and also $O(n^2)$ (a true but loose upper bound). In algorithm talk we almost always mean the *tightest simple* upper bound we can state.

### Big-Omega and Big-Theta (briefly)

- **Big-Omega** ($\Omega$): a **lower** bound. $f(n)$ is $\Omega(g(n))$ if $f$ grows at least as fast as a constant times $g$ (eventually).
- **Big-Theta** ($\Theta$): a **tight** bound. $f(n)$ is $\Theta(g(n))$ if it is both $O(g(n))$ and $\Omega(g(n))$ — same order, sandwiching constants from above and below.

We mostly write Big-O in interviews and contests, even when we really mean $\Theta$. Saying “merge sort is $O(n\log n)$” is understood as “tightly of that order,” not “could be anything slower.”

### Dropping constants and lower-order terms

If $f(n) = 5n^2 + 100n + 7$:

1. Drop lower-order terms → $5n^2$ dominates $100n$ and $7$ as $n \to \infty$.
2. Drop the leading constant → $O(n^2)$.

**Why.** Asymptotics compare *families* of growth. For large enough $n$, $n^2$ outruns $n$ no matter how big the constant in front of $n$ is. Multiplying by $5$ does not change the family. Keeping every constant would re-introduce machine-dependent noise and bury the signal.

::: trap
Dropping constants is correct for *asymptotic class*, and wrong as a performance prophecy when $n$ is small or when two algorithms share the same Big-O. An $O(n)$ scan of a linked list can lose badly to an $O(n)$ scan of a `vector` — same class, different constants and locality (cross-ref s44 / s49).
:::

## The complexity ladder

![How the common complexity classes grow with n.](assets/s56_growth.png)

From slowest-growing to fastest (for large $n$). Each rung has a one-line intuition and a tiny C++ sketch.

### $O(1)$ — constant

Work does not grow with $n$: a fixed number of operations.

```cpp
#include <vector>

int first(const std::vector<int>& v) {
    return v[0];          // one index; independent of v.size()
}
```

Hash-table average lookup (ideal case), stack `top()`, array index — all $O(1)$.

### $O(\log n)$ — logarithmic

Each step **halves** (or otherwise shrinks by a constant fraction) the remaining search space. Doubling $n$ adds only a constant amount of work.

```cpp
#include <vector>

// Binary search on a sorted range — ~log2(n) iterations
int lower(const std::vector<int>& a, int x) {
    int lo = 0, hi = static_cast<int>(a.size());
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] < x) lo = mid + 1;
        else            hi = mid;
    }
    return lo;
}
```

Balanced BST operations (`std::map` / `std::set`) are $O(\log n)$ for the same reason: tree height is logarithmic.

### $O(n)$ — linear

A constant amount of work per element, once through.

```cpp
#include <vector>

long long sum(const std::vector<int>& a) {
    long long s = 0;
    for (int x : a) s += x;   // n iterations
    return s;
}
```

### $O(n\log n)$ — linearithmic

Typically: “do an $O(\log n)$ thing $n$ times,” or “divide into two halves, solve both, then combine in $O(n)$” (merge sort, heap sort, efficient comparison sorts).

```cpp
#include <algorithm>
#include <vector>

void sort_all(std::vector<int>& a) {
    std::sort(a.begin(), a.end());   // introsort: O(n log n)
}
```

### $O(n^2)$ — quadratic

Nested loops over the same $n$, or “for each pair.” Doubling $n$ roughly *quadruples* the work.

```cpp
#include <vector>

bool has_duplicate_pair(const std::vector<int>& a) {
    const int n = static_cast<int>(a.size());
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (a[i] == a[j]) return true;   // up to ~n^2/2 comparisons
    return false;
}
```

### $O(2^n)$ — exponential

Each element adds a binary choice (take / skip). Feasible only for tiny $n$ (roughly $n \le 20$–$25$ with light per-state work).

```cpp
// Count subsets that sum to target — 2^n subsets
int count_subsets(const std::vector<int>& a, int target, int i, int sum) {
    if (i == static_cast<int>(a.size())) return sum == target ? 1 : 0;
    return count_subsets(a, target, i + 1, sum)
         + count_subsets(a, target, i + 1, sum + a[i]);
}
```

Bitmask DP over $n$ items is the disciplined cousin of this pattern (see s55).

### $O(n!)$ — factorial

Permute $n$ distinct items. Grows faster than exponential; practical only for $n \lesssim 11$.

```cpp
#include <algorithm>
#include <vector>

long long count_perms(std::vector<int> a) {
    long long c = 0;
    std::sort(a.begin(), a.end());
    do { ++c; } while (std::next_permutation(a.begin(), a.end()));
    return c;   // exactly n!
}
```

::: keypoint
Ladder intuition: $O(1) < O(\log n) < O(n) < O(n\log n) < O(n^2) < O(2^n) < O(n!)$ for large $n$. Contests are almost always fought in the $O(n)$–$O(n\log n)$ band for $n \sim 10^5$.
:::

## Deriving complexity from code

### Sequential statements add

```cpp
f(n);   // say O(n)
g(n);   // say O(n log n)
// total: O(n) + O(n log n) = O(n log n)   — dominant term wins
```

### Nested loops multiply

Independent nested loops whose bounds are both $\Theta(n)$ give $\Theta(n^2)$. If the inner bound depends on the outer index, count carefully:

```cpp
// i from 0..n-1, j from 0..i-1 → 0+1+...+(n-1) = n(n-1)/2 = O(n^2)
for (int i = 0; i < n; ++i)
    for (int j = 0; j < i; ++j)
        work();
```

### Loop bounds matter

A loop `for (int i = 0; i < n; i += 2)` is still $O(n)$ (about $n/2$ iterations — constant factor). A loop `for (int i = 1; i <= n; i *= 2)` is $O(\log n)$.

### Halving loops → $\log n$

Why? Starting from $n$, after $k$ halvings you have $n / 2^k$. You stop when that drops to $1$: $n / 2^k \approx 1 \Rightarrow k \approx \log_2 n$. Binary search, binary lifting steps, and “keep `mid = (lo+hi)/2`” all live here.

### Recursion → a recurrence

A recursive function’s cost is expressed as a **recurrence**. Classic merge sort:

$$T(n) = 2\,T(n/2) + O(n), \qquad T(1) = O(1).$$

Two subproblems of half size, plus $O(n)$ work to merge.

**Master-theorem intuition (light):** for $T(n) = a\,T(n/b) + O(n^d)$, compare $n^{\log_b a}$ to $n^d$. Merge sort has $a=2$, $b=2$, $d=1$, so $\log_b a = 1$ matches $d$ — the combine cost repeats across $\log n$ levels, each costing $O(n)$, total $O(n\log n)$.

![The recursion tree for T(n)=2T(n/2)+O(n): every level costs n, and there are log n levels.](assets/s56_recursion_tree.png)

**Recursion-tree picture.** Root costs $cn$. Two children cost $c(n/2)$ each → $cn$ together. Four grandchildren → $cn$ again. There are $\Theta(\log n)$ levels, each summing to $cn$, so $T(n) = \Theta(n\log n)$.

```cpp
#include <vector>

// Sketch of the merge-sort recurrence (merge itself is O(n))
void merge_sort(std::vector<int>& a, int lo, int hi) {
    if (hi - lo <= 1) return;
    int mid = lo + (hi - lo) / 2;
    merge_sort(a, lo, mid);      // T(n/2)
    merge_sort(a, mid, hi);      // T(n/2)
    // merge a[lo, mid) and a[mid, hi) into a[lo, hi)  — O(n)
}
```

::: interview
"What is the time complexity of this code?" — walk loops/recursion aloud: identify $n$, classify nested vs sequential work, spot halving, write the recurrence if recursive, then drop constants. Name best/average/worst if they differ.
:::

## Time versus space complexity

**Time complexity** counts operations. **Space complexity** counts *extra* memory as a function of $n$ — beyond the input itself (unless the problem asks for total memory).

What counts as space:

- Extra arrays, hash maps, recursion auxiliary buffers.
- **Recursion stack depth**: each active call frame occupies memory. A naive recursion of depth $n$ is $O(n)$ stack space even with $O(1)$ locals per frame.
- Tail-call elimination is *not* something you rely on in portable C++.

```cpp
#include <algorithm>
#include <vector>

// O(n) time, O(1) extra space (iterative)
int max_val(const std::vector<int>& a) {
    int m = a[0];
    for (int x : a) if (x > m) m = x;
    return m;
}

// O(n) time, O(n) stack space (depth-n recursion)
int max_rec(const std::vector<int>& a, int i) {
    if (i + 1 == static_cast<int>(a.size())) return a[i];
    return std::max(a[i], max_rec(a, i + 1));
}
```

Merge sort needs $O(n)$ auxiliary merge buffers (typical implementation) and $O(\log n)$ stack depth. In-place heapsort is $O(1)$ extra memory and $O(n\log n)$ time.

::: keypoint
Always state *extra* space unless asked otherwise. Recursion depth is space. Trading $O(n)$ memory for an $O(n)$ → $O(n\log n)$ or better time upgrade is a standard CP move (prefix sums, hash sets, Fenwick trees).
:::

## Best, average, and worst case

For a fixed algorithm, different inputs of size $n$ can cost different amounts.

| Case | Meaning |
| :--- | :--- |
| **Best** | Cheapest input family of size $n$ |
| **Average** | Expected cost over a distribution of inputs |
| **Worst** | Most expensive input family of size $n$ |

When they differ:

- **Quicksort**: best/average $O(n\log n)$; worst $O(n^2)$ on already-sorted data with a naive pivot. `std::sort` uses introsort (quicksort + heapsort fallback) to guarantee $O(n\log n)$ worst case.
- **Hash tables** (`std::unordered_map` / `unordered_set`): average $O(1)$ lookup/insert; worst $O(n)$ under pathological collisions (cross-ref s49, s55 anti-hash notes).
- **Linear search**: best $O(1)$ (hit first), worst $O(n)$ (miss or hit last).

::: interview
Interviewers often want the *worst-case* unless they say "average." For hash maps, say "average $O(1)$, worst $O(n)$"; for `std::map`, say "guaranteed $O(\log n)$."
:::

## Amortised analysis

Analogy: you rarely buy a new bookshelf. Most days you just place one book ($O(1)$). Occasionally you buy a wider shelf and move every book ($O(n)$). Amortised analysis asks: *averaged over a long sequence of operations*, what is the cost per operation?

### `vector::push_back` and the doubling argument

`std::vector` `push_back` is **$O(1)$ amortised**: a single call may trigger an $O(n)$ reallocation, but a long sequence of $n$ pushes costs only $O(n)$ total.

**Doubling argument.** Suppose capacity grows $1 \to 2 \to 4 \to \cdots \to n$ (powers of two). Reallocation when growing to size $2^k$ copies $2^{k-1}$ elements. Total copy work over growth up to $n$:

$$1 + 2 + 4 + \cdots + n/2 < n.$$

Geometric series: total copying across all reallocations is $< n$. Adding the $n$ cheap placements themselves gives $< 2n$ work for $n$ pushes — **$O(1)$ per push on average across the sequence**. That average-over-a-sequence is the **amortised** cost. (Details and invalidation: s44.)

```cpp
#include <vector>

std::vector<int> v;
v.reserve(1'000'000);     // optional: pay allocation once up front
for (int i = 0; i < 1'000'000; ++i)
    v.push_back(i);       // amortised O(1) each; total O(n)
```

### Amortised ≠ average ≠ worst

| Notion | What it means |
| :--- | :--- |
| **Worst-case (single op)** | One `push_back` *can* be $O(n)$ |
| **Amortised** | Over any sequence of $n$ pushes, total is $O(n)$ → $O(1)$ per op |
| **Average-case** | Expectation over a *random input distribution* (e.g. hash lookups) |

Amortised is a guarantee about *sequences of operations on one structure*, proved by accounting (aggregate, banker's, or potential methods). Average-case is probabilistic over inputs. They are not interchangeable.

::: trap
Amortised $O(1)$ is **not** worst-case $O(1)$. A single `push_back` may still take $O(n)$ time. Real-time or latency-sensitive code cannot treat "amortised" as "every call is fast." Contest TLE is usually about *total* work — amortised bounds are exactly what you need there.
:::

::: keypoint
`std::vector` / `std::string` end-insert: amortised $O(1)$. `std::deque` end operations: similarly cheap at both ends. Never confuse this with middle `insert` / `erase`, which are $O(n)$ (s44, s49).
:::

## When Big-O lies

Big-O hides constant factors, lower-order terms, and the memory hierarchy.

1. **Constant factors.** $1000n$ and $n$ are both $O(n)$; at $n = 10^6$ the former may TLE under a tight limit while the latter passes.
2. **Small $n$.** For $n = 10$, $n!$ might still finish, and an $O(n^2)$ solution can beat a fancy $O(n\log n)$ one because of simpler code and lower constants.
3. **Cache locality.** Contiguous memory (vector, array) streams through cache lines; pointer-chasing (`std::list`, trees, fragmented nodes) pays cache misses every step. Same $O(n)$ asymptotic class — often $5$–$50\times$ wall-clock difference. Prefer `vector` as the default container (s44, s49).

```cpp
#include <list>
#include <vector>

// Both O(n) — vector almost always wins on wall-clock time
long long sum_vec(const std::vector<int>& v) {
    long long s = 0;
    for (int x : v) s += x;
    return s;
}
long long sum_list(const std::list<int>& l) {
    long long s = 0;
    for (int x : l) s += x;
    return s;
}
```

::: keypoint
Use Big-O to reject impossible algorithms and to compare *classes*. Then refine with constants, memory layout, and measured behaviour when two candidates share a class.
:::

## CP complexity budgets

Rule of thumb on typical online judges: about **$10^8$ simple operations per second** (roughly; some judges closer to $10^7$–$5\cdot10^8$ depending on what “simple” means). One second → design for $\lesssim 10^8$ elementary steps.

| Input size $n$ (order) | Complexity you can usually afford | Typical algorithms |
| :--- | :--- | :--- |
| $n \le \sim 11$ | $O(n!)$ | permutations, brute TSP toy cases |
| $n \le \sim 20$–$22$ | $O(2^n)$ or $O(2^n\cdot n)$ | bitmask DP, subset enumeration |
| $n \le \sim 500$ | $O(n^3)$ | Floyd–Warshall, dense DP |
| $n \le \sim 5000$ | $O(n^2)$ | nested loops, simple DP |
| $n \le \sim 10^5$–$10^6$ | $O(n\log n)$ | sort, trees, Fenwick/segment, binary search on answer |
| $n \le \sim 10^7$–$10^8$ | $O(n)$ | linear scans, two pointers, prefix sums |

**How to pick an algorithm from constraints.**

1. Read $n$, $m$, time limit, and what must be computed.
2. Estimate $n \times$ (work per element). If $n = 10^5$ and you wrote $O(n^2)$, expect $\sim 10^{10}$ ops → TLE.
3. Choose the slowest class that still fits the budget (simpler code wins ties).
4. Watch hidden factors: `map` is $O(\log n)$ with a large constant vs `unordered_map`; `endl` and slow I/O can dominate (s54, s55).

```cpp
// Constraint: 1 <= n <= 1e5.
// Need: sorted unique values → sort + unique is O(n log n), fits.
// Nested O(n^2) loop would be ~1e10 — reject immediately.
```

::: interview
"Given $n \le 10^5$, what complexity do you need?" — answer "$O(n\log n)$ or better; $O(n^2)$ will TLE." Naming the $10^8$ rule and mapping $n$ to a class is a standard CP / screening question.
:::

## Quick reference — common complexities

Recap mapping (full syntax and caveats in s49; growth/amortisation in s44). Average-case noted where it differs from worst.

| Structure / algorithm | Operation | Typical complexity |
| :--- | :--- | :--- |
| `std::vector` / `std::array` | index access | $O(1)$ |
| `std::vector` | `push_back` / `pop_back` | amortised $O(1)$ / $O(1)$ |
| `std::vector` | insert/erase middle | $O(n)$ |
| `std::deque` | push/pop either end | amortised $O(1)$ |
| `std::list` / `forward_list` | insert/erase at known iterator | $O(1)$ (finding the spot is $O(n)$) |
| `std::stack` / `queue` | push/pop/top (or front) | $O(1)$ |
| `std::priority_queue` | push / pop | $O(\log n)$ |
| `std::priority_queue` | top | $O(1)$ |
| `std::set` / `map` | find / insert / erase | $O(\log n)$ |
| `std::unordered_set` / `map` | find / insert / erase | avg $O(1)$, worst $O(n)$ |
| `std::sort` | sort range | $O(n\log n)$ |
| `std::stable_sort` | sort range | $O(n\log n)$ (often more memory) |
| `std::lower_bound` (random-access, sorted) | binary search | $O(\log n)$ |
| `std::merge` / set algorithms on sorted ranges | merge-like | $O(n)$ |
| Binary heap build (`std::make_heap`) | build | $O(n)$ |
| DFS / BFS on graph | traverse | $O(n + m)$ |
| Dijkstra (binary heap) | SSSP | $O((n+m)\log n)$ |

::: keypoint
Default container: `std::vector`. Default ordered associative: `std::map` / `set` when you need order or guaranteed $O(\log n)$. Default unordered: `unordered_map` / `set` when average $O(1)$ matters and adversarial hashing is not a threat — else custom hash or fall back to `map` (s49, s55).
:::
