# Custom Comparators and Sorting

Mastering the custom comparator is a major milestone in C++. Once the underlying rule is understood, almost anything can be sorted — vectors of pairs, custom structs, or strings ordered by length. This section provides the complete syntax for custom sorting across various algorithms and containers, the different forms a comparator can take, and the time-complexity reasoning that separates correct-but-slow code from fast code.

::: heavy
Dense section — slow down. Comparators sit under every sorted algorithm and every ordered container. Getting the ordering wrong is not a logic bug: it is **undefined behaviour**.
:::

## The golden rule of comparators

Every custom sorting function takes two parameters — call them `a` and `b` — that represent any two elements from the collection. The function answers a single question:

> *Should `a` be placed strictly **before** `b` in the final sorted array?*

- If it returns `true`, `a` goes first.
- If it returns `false`, `b` goes first (or they are treated as tied).

::: definition
A **comparator** (also called a comparison function or ordering predicate) is a callable that takes two elements and returns whether the first should be considered *strictly less than* the second under the desired order. Default algorithms use `operator<` via `std::less`.
:::

::: keypoint
In Python, sorting often uses a `key=` function to transform an element into a sortable value. In C++, you provide a comparator that directly compares two elements.
:::

## The fatal trap: strict weak ordering

::: heavy
Dense subsection — this is the mathematical contract every comparator must obey. Analogy first, then properties, then the classic UB crash.
:::

**Analogy.** Think of a strict ranking board where every athlete is either *clearly ahead of* another, *clearly behind*, or *tied*. Nobody is allowed to be "ahead of themselves", and if A beats B and B beats C, A must beat C. If two athletes are tied with each other, they must also sit in the same "equivalence class" relative to everyone else. Break any of those rules and the ranking algorithm's assumptions collapse.

<!-- FIG s48: strict weak ordering — irreflexive / asymmetric / transitive / incomparability classes -->

The comparator must implement a **strict weak ordering**.

::: trap
A comparator must never return `true` for equal elements. Never use `<=` or `>=`. If you do, the sorting algorithm may access out-of-bounds memory or enter an infinite loop, causing undefined behaviour and crashes.
:::

A strict weak ordering requires that an element cannot come strictly before itself. If you use `<=` and `a` equals `b`, the function returns `true`; but if it checks `a` against `a`, it also returns `true`. A comparator that reports an element should come before itself confuses algorithms like `std::sort`, which rely on this mathematical property to find boundaries efficiently. Always compare strictly with `<` or `>`.

### The four properties (technical)

Write `comp(a, b)` for "a should come strictly before b". A valid strict weak ordering requires:

1. **Irreflexive** — `comp(x, x)` is always `false`. Nothing precedes itself.
2. **Asymmetric** — if `comp(a, b)` is `true`, then `comp(b, a)` must be `false`.
3. **Transitive** — if `comp(a, b)` and `comp(b, c)`, then `comp(a, c)`.
4. **Transitivity of incomparability** — define `equiv(a, b)` as "neither precedes the other" (`!comp(a,b) && !comp(b,a)`). If `equiv(a, b)` and `equiv(b, c)`, then `equiv(a, c)`. Equivalence classes must be consistent.

```cpp
// WRONG — breaks irreflexivity when a == b (or a compared to itself)
bool bad(int a, int b) { return a <= b; }

// CORRECT — strict
bool good(int a, int b) { return a < b; }
```

::: trap
In libstdc++ (GCC's STL), `std::sort` often uses introsort / introspective partitioning that *assumes* `comp(x, x) == false`. A `<=` comparator can make the partition step walk past `end()`, producing **out-of-bounds reads/writes**, heap corruption, or an apparent infinite loop. This is not a "wrong answer" — it is **undefined behaviour**. The same trap appears in `std::stable_sort`, `std::partial_sort`, `std::nth_element`, `std::set`/`std::map` insertion, and `std::priority_queue`.
:::

```cpp
#include <algorithm>
#include <vector>

// Classic UB — looks harmless, can crash on real libstdc++ builds
std::vector<int> v = {3, 1, 4, 1, 5};
// std::sort(v.begin(), v.end(), [](int a, int b) { return a <= b; }); // NEVER

std::sort(v.begin(), v.end(), [](int a, int b) { return a < b; }); // OK
```

::: keypoint
Equality under a comparator means *neither* comes before the other. You never need `==` inside a sort comparator for ordering; return a strict `<`-style test only.
:::

## Sorting algorithms: signatures and when to use which

All of these live in `<algorithm>`. Default comparator is `std::less<>` (i.e. `operator<`).

### `std::sort` — full unstable sort

```cpp
template<class RandomIt>
void sort(RandomIt first, RandomIt last);

template<class RandomIt, class Compare>
void sort(RandomIt first, RandomIt last, Compare comp);
```

- **Does:** rearranges `[first, last)` into non-decreasing order under `comp`.
- **Complexity:** $O(N \log N)$ comparisons on average and in the worst case (Introsort: quicksort + heapsort fallback + insertion sort for tiny partitions).
- **Stability:** **unstable** — equivalent elements may swap relative order.
- **Use when:** you need a fully sorted range and do not care about tie order.

```cpp
#include <algorithm>
#include <vector>

std::vector<int> a = {5, 2, 8, 1, 9};
std::sort(a.begin(), a.end());                      // ascending
std::sort(a.begin(), a.end(), std::greater<int>()); // descending
```

### `std::stable_sort` — full stable sort

```cpp
template<class RandomIt>
void stable_sort(RandomIt first, RandomIt last);

template<class RandomIt, class Compare>
void stable_sort(RandomIt first, RandomIt last, Compare comp);
```

- **Does:** same as `sort`, but preserves the relative order of equivalent elements.
- **Complexity:** $O(N \log N)$ if enough extra memory is available; up to $O(N \log^2 N)$ otherwise (merge-sort family).
- **Stability:** **stable**.
- **Use when:** multi-pass sorts (sort by secondary key, then stably by primary), or when original order among ties must survive.

### `std::partial_sort` — top $K$ in order

```cpp
template<class RandomIt>
void partial_sort(RandomIt first, RandomIt middle, RandomIt last);

template<class RandomIt, class Compare>
void partial_sort(RandomIt first, RandomIt middle, RandomIt last, Compare comp);
```

- **Does:** the range `[first, middle)` contains the smallest `(middle - first)` elements in **sorted** order. The remainder `[middle, last)` contains the leftover elements in unspecified order.
- **Complexity:** roughly $O(N \log K)$ where $K = middle - first$.
- **Use when:** "give me the $K$ smallest (or largest, with a reversed comparator) **in sorted order**".

```cpp
#include <algorithm>
#include <vector>

std::vector<int> v = {9, 1, 8, 2, 7, 3, 6};
// After: first 3 positions hold 1, 2, 3 in order; rest unsorted leftovers
std::partial_sort(v.begin(), v.begin() + 3, v.end());
```

### `std::nth_element` — partition around the $n$-th

```cpp
template<class RandomIt>
void nth_element(RandomIt first, RandomIt nth, RandomIt last);

template<class RandomIt, class Compare>
void nth_element(RandomIt first, RandomIt nth, RandomIt last, Compare comp);
```

- **Does:** after the call, `*nth` is the element that would be there if the whole range were sorted. Every element before `nth` is $\le$ it; every element after is $\ge$ it. Neither side is fully sorted.
- **Complexity:** average $O(N)$; worst case typically $O(N^2)$ in naive quickselect-style implementations, but quality libraries aim for good average behaviour.
- **Use when:** median, $k$-th order statistic, or "top $K$ unordered" (then optionally sort only the $K$ prefix).

```cpp
#include <algorithm>
#include <vector>

std::vector<int> v = {9, 1, 8, 2, 7, 3, 6};
std::nth_element(v.begin(), v.begin() + 3, v.end());
// v[3] is the element that would be at index 3 in a fully sorted array
// v[0..2] are the three smaller-or-equal values (any order)
```

![`sort` fully orders the range; `partial_sort` orders only the first k; `nth_element` places just one element.](assets/s48_sort_variants.png)

::: keypoint
Need full order → `sort` / `stable_sort`. Need top $K$ **sorted** → `partial_sort`. Need the $k$-th value or an unordered top-$K$ partition → `nth_element` (cheaper).
:::

| Algorithm | Fully sorted? | Ties preserve order? | Typical cost | Classic use |
|---|---|---|---|---|
| `sort` | yes | no | $O(N \log N)$ | default full sort |
| `stable_sort` | yes | yes | $O(N \log N)$–$O(N \log^2 N)$ | multi-key via multi-pass |
| `partial_sort` | first $K$ only | no | $O(N \log K)$ | top $K$ ranked |
| `nth_element` | only the $n$-th slot | no | avg $O(N)$ | median / $k$-th |

## Basic sorting and `std::greater`

The `<algorithm>` header provides `std::sort`, which by default uses the `<` operator of the elements being sorted.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> nums = {5, 2, 8, 1, 9};
    
    // Sorts in ascending order using operator<
    std::sort(nums.begin(), nums.end()); 
    // nums is now {1, 2, 5, 8, 9}
    
    return 0;
}
```

To sort in descending order, you do not need to write a custom comparator. The `<functional>` header provides `std::greater<>`, a standard comparator that uses `>`.

```cpp
#include <functional>

// Sorts in descending order using std::greater
std::sort(nums.begin(), nums.end(), std::greater<int>());
// nums is now {9, 8, 5, 2, 1}
```

### `std::less`, `std::greater`, and transparent operators

```cpp
#include <functional>

// Ascending (default — usually unnecessary to write explicitly)
std::sort(nums.begin(), nums.end(), std::less<int>());

// Descending
std::sort(nums.begin(), nums.end(), std::greater<int>());

// C++14 transparent functors — empty <> (or void)
// Useful with heterogeneous lookup on associative containers:
// std::set<std::string, std::less<>> can find with string_view without allocating
std::sort(nums.begin(), nums.end(), std::greater<>{});
std::sort(nums.begin(), nums.end(), std::less<>{});
```

::: definition
A **transparent** comparator (`std::less<>`, `std::greater<>`, `std::less<void>`, …) has an `is_transparent` nested tag. Ordered containers can then compare a key against a different but compatible type (e.g. `std::string` vs `std::string_view`) without constructing a temporary key.
:::

```cpp
#include <set>
#include <string>
#include <string_view>

std::set<std::string, std::less<>> words; // transparent
words.insert("alpha");
auto it = words.find(std::string_view{"alpha"}); // no temporary std::string required
```

## The three forms of custom comparators

When you need custom logic, you must supply your own comparator. C++ allows this in three ways: a free function (or static member function), a functor, or a lambda.

### 1. Free function or static member function

You can write a standard function and pass its name (a **function pointer**) to `std::sort`. If the function is inside a class, it must be marked `static`. A non-static member function is tied to a specific object instance, and `std::sort` has no object through which to call it.

```cpp
#include <vector>
#include <algorithm>

struct Interval {
    int start;
    int end;
};

// Free function comparator
bool compareByEnd(const Interval& a, const Interval& b) {
    return a.end < b.end;
}

class Solution {
public:
    // Static member function comparator
    static bool compareByStart(const Interval& a, const Interval& b) {
        return a.start < b.start;
    }

    void process() {
        std::vector<Interval> intervals = {{1, 10}, {5, 2}, {3, 8}};
        
        // Passing the function pointer
        std::sort(intervals.begin(), intervals.end(), compareByEnd);
        std::sort(intervals.begin(), intervals.end(), compareByStart);
    }
};
```

Function-pointer form — type and call:

```cpp
bool (*cmp)(const Interval&, const Interval&) = compareByEnd;
std::sort(intervals.begin(), intervals.end(), cmp);
```

::: trap
A non-static member function cannot be passed directly to `std::sort`. Use a free function, a `static` member, a functor, or a capturing/non-capturing lambda instead.
:::

### 2. Functors (function objects)

A **functor** is a `struct` or `class` that overloads the function call operator, `operator()`. This allows an object of that class to be called as if it were a function. Functors are powerful because they can hold state (member variables), though they are verbose for simple sorts.

```cpp
struct SortByEndFunctor {
    bool operator()(const Interval& a, const Interval& b) const {
        return a.end < b.end;
    }
};

std::vector<Interval> intervals = {{1, 10}, {5, 2}, {3, 8}};
// Instantiate the functor and pass it
std::sort(intervals.begin(), intervals.end(), SortByEndFunctor());
```

Stateful functor (capture-like behaviour without a lambda):

```cpp
struct CloserTo {
    int target;
    bool operator()(int a, int b) const {
        return std::abs(a - target) < std::abs(b - target);
    }
};

std::vector<int> xs = {1, 8, 3, 10};
std::sort(xs.begin(), xs.end(), CloserTo{5}); // nearest to 5 first
```

### 3. Lambdas (the modern standard)

Writing a separate function or functor is verbose. In modern C++ (C++11 onwards), competitive programmers and industry professionals use **lambdas** — anonymous, inline functions that let the sorting rule be written directly inside the `std::sort` call.

```cpp
std::vector<Interval> intervals = {{1, 10}, {5, 2}, {3, 8}};

// The lambda is defined directly where it is needed
std::sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {
    return a.end < b.end;
});
```

The syntax `[](const Interval& a, const Interval& b) { return a.end < b.end; }` creates a temporary function object on the spot. Pass elements by `const&` (or reference) to avoid wasteful copies.

::: keypoint
Prefer a lambda for one-off algorithm calls. Prefer a named functor type when the same ordering must be a **template argument** of `std::set` / `std::map` / `std::priority_queue`, or when the comparator is reused across many call sites.
:::

## Sorting pairs and tuples (default lexicographic)

`std::pair` and `std::tuple` already define `operator<` lexicographically: compare the first component; on a tie, compare the second; and so on.

```cpp
#include <algorithm>
#include <utility>
#include <tuple>
#include <vector>

std::vector<std::pair<int, int>> pts = {{2, 9}, {1, 5}, {2, 3}};
std::sort(pts.begin(), pts.end());
// → {1,5}, {2,3}, {2,9}   // first by .first, then by .second

std::vector<std::tuple<int, char, double>> rows = {
    {1, 'b', 3.0}, {1, 'a', 9.0}, {0, 'z', 1.0}
};
std::sort(rows.begin(), rows.end());
// → (0,'z',1.0), (1,'a',9.0), (1,'b',3.0)
```

Custom pair order (e.g. sort by second, then first):

```cpp
std::sort(pts.begin(), pts.end(), [](const auto& a, const auto& b) {
    if (a.second != b.second) return a.second < b.second;
    return a.first < b.first;
});
```

## Sorting by multiple keys (the tie-breaker)

This is the most common interview pattern. Suppose a list of students must be sorted by **score (descending)**, but when two students have the exact same score, they must be ordered by **age (ascending)**. The comparator layers the criteria:

```cpp
struct Student {
    int score;
    int age;
};

std::vector<Student> students = {{90, 20}, {95, 22}, {90, 18}};

std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
    // Condition 1: If scores differ, sort by highest score
    if (a.score != b.score) {
        return a.score > b.score;
    }
    // Condition 2: Scores tie! Sort by lowest age
    return a.age < b.age;
});
// Result: {95, 22}, {90, 18}, {90, 20}
```

The structure generalises to any number of criteria: check the primary key first and return if the elements differ; only when they tie do you fall through to the secondary key, and so on.

::: interview
**Classic ask:** "Write a comparator to sort by X then Y." Pattern: if the primary keys differ, return the primary comparison; otherwise return the secondary comparison. Keep every branch a *strict* `<`/`>` — never `<=`/`>=`. Example: sort events by start ascending, then by end ascending on ties.
:::

```cpp
struct Event { int start; int end; };

std::sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
    if (a.start != b.start) return a.start < b.start; // primary: X
    return a.end < b.end;                             // secondary: Y
});
```

Three keys with the same pattern:

```cpp
std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
    if (a.priority != b.priority) return a.priority > b.priority; // higher first
    if (a.time     != b.time)     return a.time < b.time;         // earlier first
    return a.id < b.id;                                           // stable-ish tie-break
});
```

## Sorting a struct, by a projected key, and by indices

### Sorting a struct

Define `operator<` on the type **or** pass a comparator. Prefer an external comparator when the type has more than one natural order.

```cpp
struct Point {
    int x, y;
};

// One-off order: by x ascending, then y ascending
std::vector<Point> pts = {{2, 1}, {1, 9}, {1, 3}};
std::sort(pts.begin(), pts.end(), [](const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
});
```

### Sorting by a projected key (pre-C++20)

"Project" means: compare a derived key (member, length, absolute value) rather than the whole object.

```cpp
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> words = {"pear", "fig", "apple"};
std::sort(words.begin(), words.end(),
          [](const std::string& a, const std::string& b) {
              return a.size() < b.size(); // project to length
          });
// → "fig", "pear", "apple"  (ties among equal lengths are unstable)
```

Precompute when the projection is expensive (see the complexity section below).

### Sorting indices (argsort)

Keep the data array untouched; sort a parallel index array.

```cpp
#include <numeric>
#include <vector>
#include <algorithm>

std::vector<int> vals = {40, 10, 30, 20};
std::vector<int> idx(vals.size());
std::iota(idx.begin(), idx.end(), 0); // 0, 1, 2, 3

std::sort(idx.begin(), idx.end(), [&](int i, int j) {
    return vals[i] < vals[j];
});
// idx → positions in ascending value order, e.g. {1, 3, 2, 0}
// vals[idx[0]] is the smallest element
```

::: keypoint
Index sorting is ideal when you must report original positions, rearrange multiple parallel arrays together, or avoid moving heavy objects.
:::

## Stable sorting

`std::sort` is an unstable algorithm. If two elements compare as equal (neither comes strictly before the other), their relative order may change during sorting. If you need to preserve the original relative order of equivalent elements, use `std::stable_sort`.

```cpp
#include <algorithm>

// Sorts students by score descending.
// Students with the exact same score will remain in the order they originally appeared.
std::stable_sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
    return a.score > b.score;
});
```

`std::stable_sort` is slower and requires extra memory, so only use it when stability is explicitly required.

### Stable vs unstable — when it matters

| Need | Choice |
|---|---|
| Fast full sort; ties may shuffle | `std::sort` |
| Preserve input order among ties | `std::stable_sort` |
| Sort by last name, *then* by first name via two passes | first `stable_sort` by first name, then `stable_sort` by last name |
| Top-$K$ / median only | `partial_sort` / `nth_element` (both unstable) |

```cpp
// Multi-pass stable sort: secondary key first, then primary
std::stable_sort(people.begin(), people.end(),
    [](const Person& a, const Person& b) { return a.first_name < b.first_name; });
std::stable_sort(people.begin(), people.end(),
    [](const Person& a, const Person& b) { return a.last_name < b.last_name; });
// Result: ordered by last name; within equal last names, first-name order preserved
```

## Comparators as template parameters

Algorithms like `std::sort` take the comparator as a **run-time argument** (a function parameter). You pass the function or lambda directly to the `sort` call.

However, ordered associative containers (`std::set`, `std::map`) and `std::priority_queue` use the comparator to maintain their internal tree or heap structure at all times. For these, the comparator must be part of the container's **type**. You pass it as a template parameter.

Because a template parameter requires a type, you cannot easily pass a free function pointer. You must provide a **functor type** (or the `decltype` of a lambda, though a functor is much cleaner here).

```cpp
#include <queue>
#include <set>
#include <vector>

// Functor for ordering
struct MinHeapComparator {
    bool operator()(int a, int b) const {
        return a > b; // > creates a min-heap (smallest at the top)
    }
};

// Priority queue takes the TYPE of the functor
std::priority_queue<int, std::vector<int>, MinHeapComparator> minHeap;

// Set takes the TYPE of the functor
std::set<int, std::greater<int>> descendingSet;
```

::: keypoint
`std::sort` takes a comparator instance as a function argument. `std::set`, `std::map`, and `std::priority_queue` take a comparator type as a template argument.
:::

### Capturing lambdas: `sort` vs containers (`decltype`)

A **non-capturing** lambda converts to a function pointer and has a unique unnamed closure type. A **capturing** lambda does not convert to a function pointer; its closure type still works as a value passed to `std::sort`, but wiring it into a container type needs `decltype` and an instance.

```cpp
#include <set>
#include <vector>
#include <algorithm>

int threshold = 10;

// OK — capturing lambda passed by value to sort
std::vector<int> v = {5, 20, 3, 15};
std::sort(v.begin(), v.end(), [threshold](int a, int b) {
    // example: push values below threshold first, then normal order
    bool a_low = a < threshold, b_low = b < threshold;
    if (a_low != b_low) return a_low > b_low; // true before false? adjust as needed
    return a < b;
});

// Container: need the lambda's TYPE + a constructor argument (the lambda instance)
auto cmp = [](int a, int b) { return a > b; };
std::set<int, decltype(cmp)> descending(cmp);

// Capturing version — same pattern
int pivot = 0;
auto cmp2 = [pivot](int a, int b) {
    // order by distance to pivot (strict!)
    return std::abs(a - pivot) < std::abs(b - pivot);
};
std::set<int, decltype(cmp2)> by_dist(cmp2);
```

::: trap
`std::set<int, decltype(cmp)> s;` without passing `cmp` default-constructs the comparator. That works for stateless lambdas/functors, but a **capturing** lambda's closure is typically not default-constructible before C++20, and even then you usually want to pass the instance explicitly so captures are present.
:::

## `std::function` overhead vs lambda / functor

`std::function` type-erases a callable. Convenient for storing heterogeneous comparators, but it blocks inlining and adds indirect calls (and possible heap allocation for large captures).

```cpp
#include <functional>
#include <algorithm>
#include <vector>

// Slow path — type erasure; hard for the compiler to inline
std::function<bool(int, int)> cmp = [](int a, int b) { return a > b; };
std::sort(v.begin(), v.end(), cmp);

// Fast path — concrete closure / functor type; easily inlined into introsort
std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
std::sort(v.begin(), v.end(), std::greater<>{});
```

::: keypoint
In hot sorting loops and competitive programming, pass a lambda or functor **by value** with a concrete type. Reach for `std::function` only when you must store or swap comparators behind a uniform type.
:::

## C++20 Ranges: a brief note

In C++20, `std::ranges::sort` simplifies sorting by allowing you to pass a collection directly without `begin()` and `end()`, and supports **projections**, which let you specify *what* to sort by rather than *how* to compare.

```cpp
// C++20: Sort students by score in ascending order using a projection
std::ranges::sort(students, std::less<>{}, &Student::score);
```

Further C++20 forms:

```cpp
#include <algorithm>
#include <ranges>

std::ranges::sort(students);                              // uses operator<
std::ranges::sort(students, std::greater<>{});            // descending on whole object
std::ranges::sort(students, std::less<>{}, &Student::age); // project to age
std::ranges::sort(students, {}, &Student::score);         // {} = default less, project score

// Custom comparator + projection
std::ranges::sort(words, std::less<>{}, &std::string::size); // by length
```

::: keypoint
A **projection** is the C++20 equivalent of Python's `key=`: the algorithm applies the projection to each element, then compares the projected values with the comparator (`std::less<>` by default).
:::

## The time complexity of sorting with a comparator

A classic interview trap asks: is `std::sort` always $O(N \log N)$? The short answer is **no**. The C++ sorting engine is guaranteed to make exactly $O(N \log N)$ **comparisons**, but the *total time* a program takes depends entirely on how much work is forced *inside* the comparator. The true formula is:

$$\text{Total Time} = O(N \log N) \times O(\text{Time of your comparator})$$

How this plays out ranges from harmless to dangerous.

### Scenario 1 — the $O(1)$ comparator

If the comparator only uses basic math, checks integer values, or looks up pre-calculated properties, it executes instantly in $O(1)$ time.

```cpp
// O(1) comparison
[](const Student& a, const Student& b) {
    return a.score > b.score;
}
```

Total sorting time: $O(1) \times O(N \log N) = O(N \log N)$.

### Scenario 2 — the $O(K)$ string comparator

When sorting an array of strings alphabetically, comparing `a < b` does not happen instantly. It must check the first letter, then the second, then the third, until it finds a difference. If the strings have an average length of $K$, the comparator takes $O(K)$ time.

```cpp
// O(K) comparison, where K is string length
[](const std::string& a, const std::string& b) {
    return a < b;
}
```

Total sorting time: $O(K) \times O(N \log N) = O(K \cdot N \log N)$. If you are sorting 10,000 strings that are each 1,000 characters long, this becomes noticeably heavy.

### Scenario 3 — the "heavy math" trap

Imagine a list of $(x, y)$ coordinates that must be sorted by how close each point is to a specific target point. The rookie mistake is to compute the distance *inside* the comparator:

```cpp
// Calculating distance inside the comparator
[](const Point& a, const Point& b) {
    double distA = std::sqrt(std::pow(a.x - target.x, 2) + std::pow(a.y - target.y, 2));
    double distB = std::sqrt(std::pow(b.x - target.x, 2) + std::pow(b.y - target.y, 2));
    return distA < distB;
}
```

Because `std::sort` makes $O(N \log N)$ comparisons, when $N$ is 100,000 this heavy math runs roughly 1.6 million times. Worse, it recomputes the exact same distances over and over for the same points as they are shuffled around.

**The "pro" fix — precomputation.** To keep the sort strictly $O(N \log N)$, never put heavy calculations inside the comparator. Instead, calculate the distances once in an $O(N)$ loop, store them in pairs alongside the points, and then sort based on the pre-calculated distances using a simple $O(1)$ comparator.

```cpp
// Precompute once, then O(1) compares
std::vector<std::pair<double, Point>> keyed;
keyed.reserve(points.size());
for (const Point& p : points) {
    double d = /* distance to target — once per point */;
    keyed.push_back({d, p});
}
std::sort(keyed.begin(), keyed.end(),
          [](const auto& a, const auto& b) { return a.first < b.first; });
```

### The takeaway

`std::sort` is a highly optimised engine: it uses an algorithm called **Introsort**, a hybrid of Quicksort, Heapsort, and Insertion Sort. It will always do its job in $O(N \log N)$ steps. The programmer's responsibility is to make sure the payload handed to it inside the lambda is as lightweight as physically possible.

::: interview
Expect questions checking your fundamental grasp of sorting. You should be able to explain **strict weak ordering** (never use `<=`), how to sort **descending** (use `std::greater`), when to use **stable vs unstable sort** (preserving original order of ties), and the difference between passing a comparator as a **template argument** (for `std::set`/`std::priority_queue`) versus a **function argument** (for `std::sort`).
:::
