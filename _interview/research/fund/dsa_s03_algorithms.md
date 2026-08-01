# Built-in Algorithms: <algorithm> and <numeric>

This section covers the standard algorithms provided by the C++ STL, primarily found in the `<algorithm>` and `<numeric>` headers. These functions are highly optimized, universally understood by C++ developers, and essential for competitive programming and technical interviews. Relying on them saves time and prevents bugs that arise from manually writing loops for fundamental operations.

## Sorting and selection

The standard library provides several sorting algorithms, all of which operate on ranges defined by iterators.

### `sort` and custom comparators

`std::sort` is an $O(n \log n)$ comparison-based sort. It is typically implemented as Introsort (a hybrid of Quicksort, Heapsort, and Insertion Sort).

```cpp
vector<int> v = {4, 1, 3, 2};
sort(v.begin(), v.end()); // {1, 2, 3, 4}
sort(v.begin() + 1, v.begin() + 3); // Sorts a sub-range
sort(v.begin(), v.end(), greater<int>()); // Sorts descending: {4, 3, 2, 1}
```

Sorting a `vector<pair<int, int>>` automatically compares elements lexicographically (first by `.first`, then by `.second`). For custom sorting, you must provide a comparator. A comparator is a boolean-returning callable that takes two arguments, `a` and `b`, and returns `true` if `a` must appear strictly before `b` in the sorted sequence.

**Lambda comparator (modern C++ approach):**
```cpp
vector<pair<int, int>> v = {{1, 3}, {2, 2}, {1, 5}};
// Sort by second element ascending
sort(v.begin(), v.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
    return a.second < b.second;
});
```

**Functor (struct with `operator()`):**
```cpp
struct Comp {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
        return a.second < b.second;
    }
};
sort(v.begin(), v.end(), Comp());
```

**Custom struct with `operator<`:**
```cpp
struct Interval {
    int start, end;
    bool operator<(const Interval& other) const {
        if (start != other.start) return start < other.start;
        return end < other.end;
    }
};
vector<Interval> intervals = {{1, 3}, {2, 2}, {1, 5}};
sort(intervals.begin(), intervals.end());
```

::: trap
A custom comparator must enforce a **strict weak ordering**. Specifically, it must return `false` when comparing two identical elements or elements that should be considered equal in sorting order. Returning `a <= b` instead of `a < b` is undefined behavior (UB) and will often crash the program with a segmentation fault.
:::

### `stable_sort`, `partial_sort`, `nth_element`, and `is_sorted`

- `stable_sort`: Like `sort`, but preserves the relative order of equivalent elements. Useful when doing multiple passes of sorting by different criteria. It is $O(n \log^2 n)$ or $O(n \log n)$ if enough extra memory is available.
- `partial_sort`: Sorts the range such that the first $k$ elements are the smallest $k$ elements in sorted order. Time complexity is $O(n \log k)$.
- `nth_element`: Partially sorts the range such that the element at the $k$-th position is the one that would be there if the entire range were sorted. Elements before it are $\le$ to it, and elements after it are $\ge$. It operates in $O(n)$ average time (QuickSelect).
- `is_sorted`: Returns `true` if the range is sorted. Time complexity is $O(n)$.

```cpp
vector<int> v = {9, 2, 7, 3, 1, 8, 4, 6, 5};

// Find the 3rd smallest element (0-indexed position 2)
nth_element(v.begin(), v.begin() + 2, v.end());
cout << v[2]; // Outputs 3

// Sort only the first 3 elements
partial_sort(v.begin(), v.begin() + 3, v.end());

bool sorted = is_sorted(v.begin(), v.end());
```

## Binary search on sorted ranges

These algorithms perform binary search on a sorted sequence. They assume the range is ordered according to the comparator used (default is `<`). Their time complexity is $O(\log n)$ for random-access iterators (like vectors or arrays).

- `binary_search(begin, end, val)`: Returns a boolean indicating whether `val` exists in the range.
- `lower_bound(begin, end, val)`: Returns an iterator to the **first** element that is **not less than** (`>=`) `val`.
- `upper_bound(begin, end, val)`: Returns an iterator to the **first** element that is **strictly greater than** (`>`) `val`.
- `equal_range(begin, end, val)`: Returns a `pair` of iterators representing the half-open interval `[lower_bound, upper_bound)` containing all elements equivalent to `val`.

::: keypoint
`lower_bound` and `upper_bound` return iterators. To convert these iterators to a 0-based integer index in a vector, subtract `v.begin()`.
:::

```cpp
vector<int> v = {10, 20, 20, 20, 30, 40};

bool exists = binary_search(v.begin(), v.end(), 20); // true

auto it_lb = lower_bound(v.begin(), v.end(), 20);
int idx_lb = it_lb - v.begin(); // 1 (index of the first 20)

auto it_ub = upper_bound(v.begin(), v.end(), 20);
int idx_ub = it_ub - v.begin(); // 4 (index of 30)

// Count occurrences of 20:
int count = idx_ub - idx_lb; // 3
```

::: heavy
Note that `std::set` and `std::map` have their own `.lower_bound()` and `.upper_bound()` member functions. You must use those members rather than the free functions from `<algorithm>`, as `std::lower_bound` on a tree structure takes $O(n)$ time due to non-random-access iterators, whereas the member function takes $O(\log n)$. Cross-reference section 02.
:::

## Permutations and min-max

### Permutations

- `next_permutation`: Transforms the range into the next lexicographically greater permutation. Returns `true` if a next permutation exists, and `false` if the range is already sorted descending (meaning it just wrapped around to the lexicographically smallest permutation).
- `prev_permutation`: The inverse of `next_permutation`.

Both run in $O(n)$ time per call. The standard idiom to generate all permutations is to sort the array first, then loop:

```cpp
vector<int> v = {1, 2, 3};
// Sort to ensure we start at the lexicographically smallest permutation
sort(v.begin(), v.end());
do {
    // Process permutation v
} while (next_permutation(v.begin(), v.end()));
```

### Min and max

- `min(a, b)` and `max(a, b)`: Return the minimum or maximum of two values.
- `min({a, b, c, ...})` and `max({a, b, c, ...})`: An initializer list can be passed to find the min or max of multiple elements simultaneously.
- `clamp(v, lo, hi)` (C++17): Returns `v` if it is within `[lo, hi]`, `lo` if `v < lo`, and `hi` if `v > hi`.
- `min_element` and `max_element`: Return an iterator to the minimum or maximum element in a range. They run in $O(n)$ time.
- `minmax_element`: Returns a `pair` of iterators `(min_it, max_it)` in a single $O(n)$ pass.

```cpp
int mx = max({10, 5, 20, 15}); // 20
int bounded = clamp(25, 0, 10); // 10

vector<int> v = {4, 1, 3, 2};
auto it = min_element(v.begin(), v.end());
int min_val = *it; // 1

auto [min_it, max_it] = minmax_element(v.begin(), v.end());
```

## Search, count, and modify

These algorithms operate in $O(n)$ time and perform sequential scans or transformations over a range.

### Search and count

- `count(begin, end, val)`: Counts occurrences of `val`.
- `count_if(begin, end, pred)`: Counts elements where the predicate `pred` returns `true`.
- `find(begin, end, val)`: Returns an iterator to the first element equal to `val`, or `end` if not found.
- `find_if(begin, end, pred)` / `find_if_not`: Returns an iterator to the first element where `pred` is true (or false).
- `search(begin1, end1, begin2, end2)`: Finds the first occurrence of the sub-range `[begin2, end2)` within `[begin1, end1)`.
- `all_of`, `any_of`, `none_of`: Return a boolean indicating whether all, any, or no elements satisfy a predicate.

```cpp
vector<int> v = {1, 2, 3, 4, 5};
int evens = count_if(v.begin(), v.end(), [](int x){ return x % 2 == 0; });
bool has_neg = any_of(v.begin(), v.end(), [](int x){ return x < 0; });
auto it = find(v.begin(), v.end(), 3);
```

### Modify and transform

- `unique`: Removes consecutive duplicate elements. It does not resize the container; it moves the non-duplicate elements to the front and returns an iterator to the new logical end. It is typically combined with `.erase()` in the **erase-unique idiom**.
- `reverse`: Reverses the elements in the range in-place.
- `rotate(begin, mid, end)`: Performs a left rotation such that the element at `mid` becomes the new first element.
- `fill(begin, end, val)` / `fill_n(begin, n, val)`: Assigns `val` to all elements in the range.
- `replace(begin, end, old_val, new_val)`: Replaces occurrences of `old_val` with `new_val`.
- `remove` / `remove_if`: Like `unique`, shifts elements to exclude the removed ones, returning the new logical end. Usually paired with `.erase()` in the **erase-remove idiom**.
- `for_each(begin, end, func)`: Applies a function to each element.
- `transform(begin, end, out_begin, func)`: Applies a function to each element and writes the result to `out_begin` (which can be the same as `begin` for in-place modification).
- `copy` / `copy_if`: Copies elements from one range to another.
- `partition` / `stable_partition`: Rearranges the range so that elements satisfying a predicate precede those that do not.
- `is_permutation`: Checks if one range is a permutation of another.
- `lexicographical_compare`: Compares two ranges lexicographically (used under the hood by container `operator<`).
- `merge`: Merges two sorted ranges into a single sorted destination range.
- `includes`: Checks if one sorted range is a subset of another sorted range.

```cpp
vector<int> v = {1, 2, 2, 3, 2, 2, 4};
// erase-unique idiom requires sorting first if duplicates are not consecutive
sort(v.begin(), v.end()); // {1, 2, 2, 2, 2, 3, 4}
v.erase(unique(v.begin(), v.end()), v.end()); // {1, 2, 3, 4}

// erase-remove idiom
vector<int> w = {1, 2, 3, 2, 4};
w.erase(remove(w.begin(), w.end(), 2), w.end()); // {1, 3, 4}

vector<int> nums = {1, 2, 3, 4, 5};
rotate(nums.begin(), nums.begin() + 2, nums.end()); // {3, 4, 5, 1, 2}
```

## Set algebra on sorted ranges

These functions compute standard set operations on two **sorted** ranges. They require an output iterator (often `back_inserter`) and run in $O(N + M)$ time.

- `set_union`: Computes $A \cup B$.
- `set_intersection`: Computes $A \cap B$.
- `set_difference`: Computes $A \setminus B$ (elements in A but not in B).
- `set_symmetric_difference`: Computes $(A \setminus B) \cup (B \setminus A)$.

```cpp
vector<int> a = {1, 2, 4, 5, 6};
vector<int> b = {2, 3, 5, 7};
vector<int> res;

set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(res));
// res is {2, 5}

res.clear();
set_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(res));
// res is {1, 4, 6}
```

## Manual heap on a vector

While `std::priority_queue` is standard for heap operations, you can manually maintain a heap structure over any random-access container using these $O(\log n)$ operations (or $O(n)$ for `make_heap`). This is useful when you need to inspect the underlying container array, or if you need to build a heap in $O(n)$ time directly on an existing vector without copying.

- `make_heap`: Rearranges elements into a max-heap in $O(n)$ time.
- `push_heap`: Inserts the element at `end - 1` into the heap. You must `push_back` to the vector first. Time: $O(\log n)$.
- `pop_heap`: Swaps the maximum element (at `begin`) with the last element (at `end - 1`) and restores the heap property. You must then `pop_back` from the vector to remove it. Time: $O(\log n)$.
- `sort_heap`: Sorts the elements of the heap in ascending order in $O(n \log n)$ time.

```cpp
vector<int> v = {3, 1, 4, 1, 5, 9};
make_heap(v.begin(), v.end()); // v is now a max-heap

v.push_back(6); // Add element to the end
push_heap(v.begin(), v.end()); // Sift it into the heap

pop_heap(v.begin(), v.end()); // Max element moved to v.back()
int top_val = v.back(); // 9
v.pop_back(); // Remove it entirely
```

## `<numeric>` and math builtins

The `<numeric>` header contains numerical operations over ranges.

- `accumulate(begin, end, init)`: Sums the elements with the initial value `init`. **Trap:** the type of `init` dictates the type of the sum. If the sum might overflow a 32-bit integer, you must pass `0LL` as the initial value, not `0`.
- `partial_sum(begin, end, out_begin)`: Computes the prefix sums.
- `adjacent_difference(begin, end, out_begin)`: Computes the differences between adjacent elements.
- `inner_product`: Computes the dot product of two ranges.
- `iota(begin, end, start_val)`: Fills the range with sequentially increasing values starting from `start_val`.
- `reduce`: Similar to `accumulate` but permits out-of-order evaluation (introduced in C++17 for parallelism).

```cpp
vector<int> v = {1, 2, 3, 4};
// Force long long addition to prevent overflow
long long sum = accumulate(v.begin(), v.end(), 0LL); 

vector<int> pref(v.size());
partial_sum(v.begin(), v.end(), pref.begin()); // {1, 3, 6, 10}

vector<int> ids(5);
iota(ids.begin(), ids.end(), 1); // {1, 2, 3, 4, 5}
```

### GCD and LCM

In C++17, `<numeric>` provides `std::gcd` and `std::lcm`. Prior to C++17, CP code heavily used the compiler-specific `__gcd(a, b)`.

```cpp
int g = std::gcd(12, 18); // 6
int l = std::lcm(12, 18); // 36
```

### Compiler bit builtins

GCC and Clang provide highly optimized compiler intrinsic functions for bitwise operations. They map down to single assembly instructions.

- `__builtin_popcount(x)`: Returns the number of set bits (1s) in `x`. Use `__builtin_popcountll(x)` for `long long`.
- `__builtin_clz(x)`: Returns the count of leading zeros (starting from the most significant bit).
- `__builtin_ctz(x)`: Returns the count of trailing zeros (starting from the least significant bit).
- `__builtin_parity(x)`: Returns the parity (number of set bits modulo 2).
- `std::__lg(x)`: Returns the base-2 logarithm of `x` (integer truncation), which is identical to the index of the most significant set bit.

::: trap
`__builtin_clz(0)` and `__builtin_ctz(0)` are undefined behavior. Always check `x != 0` before calling them.
:::

### Common bit tricks

- `x & -x`: Extracts the lowest set bit (e.g., `12 & -12` is `4`). Fundamental to Fenwick Trees.
- `x & (x - 1)`: Drops the lowest set bit. If `x & (x - 1) == 0` (and `x > 0`), then `x` is a power of two.
- Submask iteration: Iterates through all submasks of a bitmask `m`.
  ```cpp
  for (int s = m; s > 0; s = (s - 1) & m) {
      // s is a submask of m
  }
  ```

### Math pitfalls

- `abs(x)`: Computes the absolute value. Note that `abs(INT_MIN)` is undefined behavior due to integer overflow.
- **Integer square root:** `std::sqrt` returns a floating-point number. Precision errors can cause `sqrt(x) * sqrt(x)` to be slightly off. For integer math, use an integer-based binary search or carefully cast and round `round(sqrt(x))`.
- **Power function:** `std::pow` operates on `double`. Using it for integers like `pow(2, 10)` can result in slight inaccuracies like `1023.9999` which truncates to `1023` when cast to `int`. Always use bit shifts (`1LL << k`) for powers of 2, or implement fast modular exponentiation iteratively for other bases.

```cpp
// Fast modular exponentiation: computes (base^exp) % mod in O(log exp)
long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}
```

## Essential algorithms cheat sheet

::: keypoint
The ten most frequently used algorithms in coding interviews with their one-line call form:
1. Sort: `sort(v.begin(), v.end())` or `sort(v.begin(), v.end(), greater<int>())`
2. Erase-unique: `v.erase(unique(v.begin(), v.end()), v.end())`
3. Erase-remove: `v.erase(remove(v.begin(), v.end(), val), v.end())`
4. Reverse: `reverse(v.begin(), v.end())`
5. Lower bound index: `lower_bound(v.begin(), v.end(), val) - v.begin()`
6. Next permutation: `next_permutation(v.begin(), v.end())`
7. Accumulate (safe): `accumulate(v.begin(), v.end(), 0LL)`
8. Iota (fill 0 to N-1): `iota(v.begin(), v.end(), 0)`
9. Max element: `*max_element(v.begin(), v.end())`
10. Count condition: `count_if(v.begin(), v.end(), [](int x){ return x > 0; })`
:::
