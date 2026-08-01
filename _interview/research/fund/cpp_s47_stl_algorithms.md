# STL Algorithms

::: heavy
The Standard Template Library (STL) provides a vast collection of algorithms that operate over data structures. Rather than tying algorithms as member functions to specific containers, C++ decouples them: algorithms are free functions that operate on **iterator ranges**.
:::

## Iterators, Ranges, and Predicates

Almost all STL algorithms operate on a range defined by two iterators: `[first, last)`. The range is **half-open**, meaning it includes `first` but goes up to, and does *not* include, `last`. If `first == last`, the range is empty.

Algorithms are heavily **parameterised by predicates** or function objects. A predicate is a function (often a lambda) that returns a boolean, used to define custom behaviour like a sorting order or a search condition.

::: keypoint
In Python, you might use `sorted(data, key=lambda x: x.prop)` or built-ins like `filter()`, `map()`, and `functools.reduce()`. In C++, this same functional style is achieved by passing a lambda expression as a predicate to an STL algorithm.
:::

::: trap
Half-open ranges `[first, last)` mean `last` is **past-the-end**, never dereferenced. Passing `end()` as both bounds is a valid empty range; dereferencing `end()` is undefined behaviour. Off-by-one bugs almost always come from treating `last` as inclusive.
:::

### Comparator, predicate, and projection idiom

- A **unary predicate** takes one element and returns `bool` (e.g. for `find_if`, `count_if`, `remove_if`).
- A **binary predicate** / **comparator** takes two elements and returns `bool` (e.g. for `sort`, `lower_bound`). A comparator must induce a **strict weak ordering** (typically `operator<` semantics: irreflexive, transitive, and equivalence via `!(a<b) && !(b<a)`).
- From C++20, many algorithms accept a **projection** (`proj`) — a callable applied to each element *before* the predicate/comparator sees it. Classic C++17 style achieves the same with a capturing lambda.

```cpp
#include <algorithm>
#include <string>
#include <vector>

struct Person { std::string name; int age; };

std::vector<Person> people = {{"Ann", 30}, {"Bob", 25}};

// Comparator: sort by age ascending
std::sort(people.begin(), people.end(),
          [](const Person& a, const Person& b) { return a.age < b.age; });

// Predicate: find first adult
auto it = std::find_if(people.begin(), people.end(),
                       [](const Person& p) { return p.age >= 18; });

// C++20 ranges: projection instead of hand-rolled comparator
// std::ranges::sort(people, std::less{}, &Person::age);
```

::: keypoint
Prefer a named lambda or a small struct with `operator()` when the same comparator is reused; prefer an inline lambda for one-off calls. Never pass a floating-point comparator that can return `true` for both `(a,b)` and `(b,a)` — that breaks sorting.
:::

## Non-Modifying Sequence Operations

These algorithms (`<algorithm>`) read from a range but never alter the elements.

### Inspection and counting
- **`std::for_each`**: Applies a function to every element.
- **`std::count` / `std::count_if`**: Returns the number of elements matching a value or predicate.

```cpp
template <class InputIt, class UnaryFunction>
UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f);
```

```cpp
template <class InputIt, class T>
typename iterator_traits<InputIt>::difference_type
count(InputIt first, InputIt last, const T& value);

template <class InputIt, class UnaryPred>
typename iterator_traits<InputIt>::difference_type
count_if(InputIt first, InputIt last, UnaryPred p);
```

**Complexity:** $O(N)$ — exactly `last - first` applications of the callable / comparisons.

```cpp
std::vector<int> v = {1, 2, 3, 4, 5, 5};

// Apply a function to each element
std::for_each(v.begin(), v.end(), [](int n) { std::cout << n << " "; });

// Count occurrences
int fives = std::count(v.begin(), v.end(), 5);

// Count with a predicate (how many evens?)
int evens = std::count_if(v.begin(), v.end(), [](int n) { return n % 2 == 0; });
```

::: definition
**`std::for_each`** returns the (possibly moved-from) function object after the walk — useful when the callable accumulates state in member variables. Prefer a capturing lambda and ignore the return for simple side effects.
:::

### Quantifiers: all / any / none

```cpp
template <class InputIt, class UnaryPred>
bool all_of(InputIt first, InputIt last, UnaryPred p);   // true if empty

template <class InputIt, class UnaryPred>
bool any_of(InputIt first, InputIt last, UnaryPred p);   // false if empty

template <class InputIt, class UnaryPred>
bool none_of(InputIt first, InputIt last, UnaryPred p);  // true if empty
```

**Purpose:** short-circuiting universal / existential checks. **Complexity:** $O(N)$ worst case; may exit early.

```cpp
bool all_positive = std::all_of(v.begin(), v.end(), [](int n) { return n > 0; });
bool any_even = std::any_of(v.begin(), v.end(), [](int n) { return n % 2 == 0; });
bool none_negative = std::none_of(v.begin(), v.end(), [](int n) { return n < 0; });
```

### Searching and querying
- **`std::find` / `std::find_if` / `std::find_if_not`**: Finds the first element matching a value or predicate.
- **`std::all_of` / `std::any_of` / `std::none_of`**: Checks if all, any, or no elements satisfy a predicate.
- **`std::search`**: Finds the first occurrence of a sub-range.
- **`std::adjacent_find`**: Finds the first pair of identical (or predicate-matching) adjacent elements.

```cpp
template <class InputIt, class T>
InputIt find(InputIt first, InputIt last, const T& value);

template <class InputIt, class UnaryPred>
InputIt find_if(InputIt first, InputIt last, UnaryPred p);

template <class InputIt, class UnaryPred>
InputIt find_if_not(InputIt first, InputIt last, UnaryPred p);
```

**Complexity:** $O(N)$. Returns `last` if not found.

```cpp
// Searching
auto it = std::find(v.begin(), v.end(), 3);
if (it != v.end()) { /* Found */ }

auto even_it = std::find_if(v.begin(), v.end(), [](int n) { return n % 2 == 0; });
auto not_even = std::find_if_not(v.begin(), v.end(), [](int n) { return n % 2 == 0; });

// Querying
bool all_positive = std::all_of(v.begin(), v.end(), [](int n) { return n > 0; });
bool any_even = std::any_of(v.begin(), v.end(), [](int n) { return n % 2 == 0; });
bool none_negative = std::none_of(v.begin(), v.end(), [](int n) { return n < 0; });

// Sub-range searching
std::vector<int> sub = {4, 5};
auto search_it = std::search(v.begin(), v.end(), sub.begin(), sub.end());

auto adj_it = std::adjacent_find(v.begin(), v.end()); // points to first 5
```

### `find_end`, `find_first_of`, `search`, `search_n`, `adjacent_find`

```cpp
template <class ForwardIt1, class ForwardIt2>
ForwardIt1 find_end(ForwardIt1 first, ForwardIt1 last,
                    ForwardIt2 s_first, ForwardIt2 s_last);
// Last (rightmost) occurrence of subsequence [s_first, s_last) in [first, last).
// Complexity: O((N-M+1)*M) typical; returns last if not found.

template <class InputIt, class ForwardIt>
InputIt find_first_of(InputIt first, InputIt last,
                      ForwardIt s_first, ForwardIt s_last);
// First element in [first, last) that equals any element in [s_first, s_last).
// Complexity: O(N*M).

template <class ForwardIt1, class ForwardIt2>
ForwardIt1 search(ForwardIt1 first, ForwardIt1 last,
                  ForwardIt2 s_first, ForwardIt2 s_last);
// First occurrence of subsequence. Complexity: O((N-M+1)*M).

template <class ForwardIt, class Size, class T>
ForwardIt search_n(ForwardIt first, ForwardIt last, Size count, const T& value);
// First run of `count` consecutive elements equal to `value`. Complexity: O(N).

template <class ForwardIt>
ForwardIt adjacent_find(ForwardIt first, ForwardIt last);
// First of two equal adjacent elements (or first pair satisfying binary pred). O(N).
```

```cpp
#include <algorithm>
#include <vector>

std::vector<int> hay = {1, 2, 3, 2, 3, 4};
std::vector<int> needle = {2, 3};

auto first_occ = std::search(hay.begin(), hay.end(), needle.begin(), needle.end());
// points to hay[1]

auto last_occ = std::find_end(hay.begin(), hay.end(), needle.begin(), needle.end());
// points to hay[3] — rightmost {2,3}

std::vector<int> keys = {9, 3, 7};
auto hit = std::find_first_of(hay.begin(), hay.end(), keys.begin(), keys.end());
// points to 3

std::vector<int> runs = {1, 1, 1, 2, 2};
auto three_ones = std::search_n(runs.begin(), runs.end(), 3, 1); // points to first 1
auto two_twos   = std::search_n(runs.begin(), runs.end(), 2, 2); // points to first 2
```

::: interview
`search` finds the **first** subsequence match; `find_end` finds the **last**. `find_first_of` is “any of these values,” not a contiguous subsequence — do not confuse it with `search`.
:::

### Comparison
- **`std::equal`**: Checks if two ranges contain the same elements.
- **`std::mismatch`**: Finds the first position where two ranges differ.

```cpp
template <class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2);
// Compares [first1, last1) to [first2, first2 + (last1-first1)).
// C++14 also: equal(first1, last1, first2, last2) — safer when lengths may differ.

template <class InputIt1, class InputIt2>
std::pair<InputIt1, InputIt2>
mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2);
// First differing position; both iterators equal their ends if ranges match.
```

**Complexity:** $O(N)$.

```cpp
std::vector<int> v2 = {1, 2, 3};
bool same = std::equal(v2.begin(), v2.end(), v.begin());
auto mismatch_pair = std::mismatch(v2.begin(), v2.end(), v.begin());
```

::: trap
The three-iterator `equal` / `mismatch` overloads assume the second range is **at least as long** as the first. If it is shorter, you read past its end — undefined behaviour. Prefer the four-iterator overloads (C++14) when lengths are not obviously equal.
:::

## Modifying Sequence Operations

These algorithms alter the elements in the range, or copy them to a destination range. When writing to a destination, you must ensure the destination has enough pre-allocated space or use an inserter (like `std::back_inserter`).

### Copying and moving
- **`std::copy` / `std::copy_if` / `std::copy_n`**: Copies elements to another range.
- **`std::move`**: Moves elements to another range (using move semantics).

```cpp
template <class InputIt, class OutputIt>
OutputIt copy(InputIt first, InputIt last, OutputIt d_first);

template <class InputIt, class OutputIt, class UnaryPred>
OutputIt copy_if(InputIt first, InputIt last, OutputIt d_first, UnaryPred pred);

template <class InputIt, class Size, class OutputIt>
OutputIt copy_n(InputIt first, Size count, OutputIt result);

template <class BidirIt1, class BidirIt2>
BidirIt2 copy_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last);
// Copies [first, last) into the range ending at d_last (writes right-to-left).
// Use when destination overlaps source and d_last is to the right of last.

template <class InputIt, class OutputIt>
OutputIt move(InputIt first, InputIt last, OutputIt d_first);  // <algorithm>
```

**Complexity:** $O(N)$ assignments/moves. Return value is past-the-end of the written output.

```cpp
std::vector<int> dest;
// std::back_inserter creates an iterator that calls push_back on the container
std::copy_if(v.begin(), v.end(), std::back_inserter(dest), [](int n){ return n > 2; });

std::vector<int> target(3);
std::copy_n(v.begin(), 3, target.begin()); // Requires pre-allocated space
std::move(v.begin(), v.end(), std::back_inserter(dest));
```

```cpp
// Overlapping copy to the right: copy_backward is the safe choice
std::vector<int> buf = {1, 2, 3, 4, 5, 0, 0};
std::copy_backward(buf.begin(), buf.begin() + 5, buf.end());
// buf becomes {1, 2, 1, 2, 3, 4, 5} — shifted right by 2
```

::: keypoint
`std::move` the algorithm (`#include <algorithm>`) is not the same as `std::move` the cast (`#include <utility>`). The algorithm walks a range and move-assigns each element into the destination; afterwards, source elements are in a valid but unspecified state.
:::

### Transforming and generating
- **`std::transform`**: Applies a function to elements, writing the results to a destination. Has unary and binary forms.
- **`std::fill` / `std::fill_n`**: Fills a range with a specific value.
- **`std::generate`**: Fills a range with values produced by calling a function.

```cpp
template <class InputIt, class OutputIt, class UnaryOp>
OutputIt transform(InputIt first1, InputIt last1, OutputIt d_first, UnaryOp unary_op);

template <class InputIt1, class InputIt2, class OutputIt, class BinaryOp>
OutputIt transform(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                   OutputIt d_first, BinaryOp binary_op);

template <class ForwardIt, class T>
void fill(ForwardIt first, ForwardIt last, const T& value);

template <class OutputIt, class Size, class T>
OutputIt fill_n(OutputIt first, Size count, const T& value);

template <class ForwardIt, class Generator>
void generate(ForwardIt first, ForwardIt last, Generator g);

template <class OutputIt, class Size, class Generator>
OutputIt generate_n(OutputIt first, Size count, Generator g);
```

**Complexity:** $O(N)$ for all of the above.

```cpp
// Unary transform (similar to map in Python)
std::transform(v.begin(), v.end(), v.begin(), [](int n) { return n * 2; });

// Binary transform (combining two ranges)
std::vector<int> v1 = {1, 2}, v2 = {3, 4}, out(2);
std::transform(v1.begin(), v1.end(), v2.begin(), out.begin(), 
               [](int a, int b) { return a + b; });

// Generation
std::fill(out.begin(), out.end(), 0);
std::fill_n(out.begin(), 2, 1);
std::generate(out.begin(), out.end(), []() { return 42; }); // Fills with 42
```

### Replacing and rearranging
- **`std::replace` / `std::replace_if`**: Replaces elements matching a condition.
- **`std::reverse`**: Reverses the order of elements.
- **`std::rotate`**: Rotates the order of elements so that a chosen middle element becomes the new first element.
- **`std::swap_ranges`**: Swaps elements between two ranges.

```cpp
template <class ForwardIt, class T>
void replace(ForwardIt first, ForwardIt last, const T& old_value, const T& new_value);

template <class ForwardIt, class UnaryPred, class T>
void replace_if(ForwardIt first, ForwardIt last, UnaryPred p, const T& new_value);

template <class BidirIt>
void reverse(BidirIt first, BidirIt last);                     // O(N/2) swaps

template <class ForwardIt>
ForwardIt rotate(ForwardIt first, ForwardIt middle, ForwardIt last);
// Element at middle becomes first; returns iterator to where *first moved. O(N).

template <class ForwardIt1, class ForwardIt2>
ForwardIt2 swap_ranges(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2);
```

```cpp
std::replace(v.begin(), v.end(), 5, 99);
std::replace_if(v.begin(), v.end(), [](int n) { return n < 0; }, 0);

std::reverse(v.begin(), v.end());
std::rotate(v.begin(), v.begin() + 2, v.end()); // Shifts elements left by 2
std::swap_ranges(v1.begin(), v1.end(), v2.begin());
```

### `unique`, `shuffle`, and `sample`

```cpp
template <class ForwardIt>
ForwardIt unique(ForwardIt first, ForwardIt last);
// Collapses consecutive equal elements; returns new logical end. O(N).
// Does NOT erase — pair with container erase (same idiom as remove).

template <class RandomIt, class URBG>
void shuffle(RandomIt first, RandomIt last, URBG&& g);  // C++11, <algorithm>
// Uniform random permutation. O(N). Needs a UniformRandomBitGenerator.

template <class PopulationIt, class SampleIt, class Distance, class URBG>
SampleIt sample(PopulationIt first, PopulationIt last,
                SampleIt out, Distance n, URBG&& g);    // C++17
// Selects n elements (without replacement) into out. O(N).
```

```cpp
#include <algorithm>
#include <random>
#include <vector>

std::vector<int> sorted = {1, 1, 2, 2, 2, 3};
sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());
// {1, 2, 3} — unique only collapses *consecutive* duplicates; sort first if needed

std::vector<int> deck = {1, 2, 3, 4, 5, 6};
std::mt19937 rng{std::random_device{}()};
std::shuffle(deck.begin(), deck.end(), rng);

std::vector<int> picks(3);
std::sample(deck.begin(), deck.end(), picks.begin(), 3, rng);
```

::: trap
`std::random_shuffle` is **removed** in C++17. Always use `std::shuffle` with an explicit engine (`std::mt19937`). `std::unique` without a prior `sort` only removes runs of duplicates already sitting next to each other.
:::

## The Erase-Remove Idiom

The interaction between STL algorithms and container sizes is a notorious stumbling block. Algorithms only operate on iterators; they cannot fundamentally alter the container holding the elements.

Imagine sweeping dust and debris to the end of a long hallway. You have separated the good space from the rubbish, but the hallway itself has not become any shorter. You need a separate operation to construct a wall and shrink the hallway.

![The erase–remove idiom: `std::remove` packs kept elements to the front, then `erase()` truncates the tail.](assets/s47_erase_remove.png)

```cpp
template <class ForwardIt, class T>
ForwardIt remove(ForwardIt first, ForwardIt last, const T& value);

template <class ForwardIt, class UnaryPred>
ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPred p);
// Relocate kept elements to [first, new_end); return new_end. O(N).
// Relative order of kept elements is preserved. Trailing junk is unspecified.
```

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {1, 99, 2, 99, 3};
    
    // 1. std::remove shifts non-99 elements forward. 
    // It returns an iterator to the new logical end of the valid elements.
    auto new_end = std::remove(v.begin(), v.end(), 99);
    
    // The vector still has 5 elements! Its contents might be {1, 2, 3, 99, 3}
    
    // 2. Erase the "rubbish" at the end to physically shrink the container.
    v.erase(new_end, v.end()); 
    
    // v is now exactly {1, 2, 3}
    return 0;
}
```

The plain-English rule is: `std::remove` overwrites elements to gather the ones you want to keep at the front, returning an iterator just past the last kept element. However, it cannot resize the container. You must explicitly call the container's `.erase()` method to remove the trailing elements.

Technically, `std::remove` (and `std::unique`) only require `ForwardIterators`. They have no knowledge of the underlying container type or its `.erase()` method. 

Typically, this is written in a single line, known as the **erase-remove idiom**:

```cpp
v.erase(std::remove(v.begin(), v.end(), 99), v.end());

// Works with remove_if and lambdas too
v.erase(std::remove_if(v.begin(), v.end(), [](int n){ return n % 2 == 0; }), v.end());
```

::: trap
`std::remove`, `std::remove_if`, and `std::unique` do NOT change the size of the underlying container. They merely shift the elements to keep to the front and return an iterator to the new logical end. You must always pair them with a container's `erase()` method.
:::

*(Note: `std::unique` removes consecutive duplicate elements, operating under the exact same principles. It is usually called on an already sorted range.)*

::: interview
Write `v.erase(std::remove_if(v.begin(), v.end(), pred), v.end());` from memory. Explain why `remove` cannot call `erase` itself (algorithms are container-agnostic). From C++20, `std::erase` / `std::erase_if` free functions wrap this for standard containers.
:::

## Partitioning

Partitioning algorithms divide a range into two groups: those that satisfy a predicate, and those that do not.
- **`std::partition`**: Reorders elements. Returns an iterator to the first element of the second group.
- **`std::stable_partition`**: Like `partition`, but preserves the relative original order of elements within each group.
- **`std::partition_point`**: Finds the partition point in an already-partitioned range.

```cpp
template <class ForwardIt, class UnaryPred>
ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPred p);
// O(N). Relative order within each group is NOT preserved.

template <class BidirIt, class UnaryPred>
BidirIt stable_partition(BidirIt first, BidirIt last, UnaryPred p);
// O(N log N) if extra memory unavailable; O(N) with enough buffer. Order preserved.

template <class InputIt, class UnaryPred>
bool is_partitioned(InputIt first, InputIt last, UnaryPred p);
// true if all elements satisfying p precede those that do not. O(N).

template <class ForwardIt, class UnaryPred>
ForwardIt partition_point(ForwardIt first, ForwardIt last, UnaryPred p);
// Binary search for the boundary in an already-partitioned range. O(log N).
// Requires random-access for true logarithmic behaviour (ForwardIt + distance).
```

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
// Put all evens at the front
auto bound = std::partition(v.begin(), v.end(), [](int n) { return n % 2 == 0; });
// v might become {4, 2, 3, 1, 5}, bound points to 3

auto pp = std::partition_point(v.begin(), v.end(), [](int n) { return n % 2 == 0; });
```

```cpp
bool ok = std::is_partitioned(v.begin(), v.end(), [](int n) { return n % 2 == 0; });
// After partition, ok == true; pp should equal bound
```

::: keypoint
`partition_point` is binary search on a **predicate boundary**, not on sorted values. Calling it on an unpartitioned range yields a meaningless iterator — always `is_partitioned` (or know you just partitioned) first.
:::

## Sorting and Ordered-Range Operations

Sorting algorithms require random-access iterators (like those from `std::vector` or `std::deque`). 

- **`std::sort`**: Sorts a range (usually via Introsort, $O(N \log N)$).
- **`std::stable_sort`**: Sorts but preserves the relative order of equal elements (useful for multi-pass sorting, e.g. sort by last name, then first name).
- **`std::partial_sort`**: Partially sorts a range so that the top $K$ elements are in their final sorted positions.
- **`std::nth_element`**: Places the element that *would* be in the $n$-th position if the range were fully sorted into that exact position. Elements before it are lesser, elements after are greater, but they are not fully sorted. Highly efficient for "find the median" or "find the top $K$" problems.
- **`std::is_sorted`**: Checks if a range is sorted.

```cpp
template <class RandomIt>
void sort(RandomIt first, RandomIt last);                    // ~O(N log N), not stable

template <class RandomIt>
void stable_sort(RandomIt first, RandomIt last);             // O(N log N); stable

template <class RandomIt>
void partial_sort(RandomIt first, RandomIt middle, RandomIt last);
// [first, middle) sorted; remaining unsorted but all ≥ last of sorted part. O(N log K).

template <class InputIt, class RandomIt>
RandomIt partial_sort_copy(InputIt first, InputIt last,
                           RandomIt d_first, RandomIt d_last);
// Copies the smallest min(N, d_last-d_first) elements into dest, sorted. O(N log K).

template <class RandomIt>
void nth_element(RandomIt first, RandomIt nth, RandomIt last);
// *nth is where it would be in sorted order; left ≤ *nth ≤ right. Avg O(N).

template <class ForwardIt>
bool is_sorted(ForwardIt first, ForwardIt last);             // O(N)

template <class ForwardIt>
ForwardIt is_sorted_until(ForwardIt first, ForwardIt last);
// Iterator to first out-of-order element (or last if fully sorted). O(N).
```

```cpp
std::vector<int> v = {5, 1, 4, 2, 3};

// Full sort
std::sort(v.begin(), v.end());

// Sort with a custom key/comparator using a lambda
std::sort(v.begin(), v.end(), [](int a, int b) { 
    return a > b; // Descending order
});

// Partial sort: only guarantee the first 2 elements are the absolute smallest
std::partial_sort(v.begin(), v.begin() + 2, v.end());

// Nth element: guarantee the element at index 2 is the median
std::nth_element(v.begin(), v.begin() + 2, v.end());

bool is_ordered = std::is_sorted(v.begin(), v.end());
```

```cpp
std::vector<int> src = {9, 1, 8, 2, 7, 3};
std::vector<int> top3(3);
std::partial_sort_copy(src.begin(), src.end(), top3.begin(), top3.end());
// top3 == {1, 2, 3}; src unchanged

std::vector<int> almost = {1, 2, 3, 0, 4};
auto break_at = std::is_sorted_until(almost.begin(), almost.end());
// *break_at == 0
```

::: interview
Need the top $K$ in order → `partial_sort` ($O(N \log K)$). Need only the $K$-th / median / unordered top $K$ → `nth_element` (average $O(N)$). Need a full stable multi-key sort → `stable_sort` or successive `sort`s from least to most significant key.
:::

### Binary Search (Sorted Ranges)

These algorithms operate in $O(\log N)$ time but strictly require the range to already be sorted.

- **`std::binary_search`**: Returns `true` if an element exists.
- **`std::lower_bound`**: Returns an iterator to the first element *not less than* (i.e. $\ge$) a value.
- **`std::upper_bound`**: Returns an iterator to the first element *strictly greater than* ($>$) a value.
- **`std::equal_range`**: Returns a pair of iterators `[lower_bound, upper_bound)` representing all elements equal to the value.

```cpp
template <class ForwardIt, class T>
ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value);

template <class ForwardIt, class T>
ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T& value);

template <class ForwardIt, class T>
std::pair<ForwardIt, ForwardIt>
equal_range(ForwardIt first, ForwardIt last, const T& value);

template <class ForwardIt, class T>
bool binary_search(ForwardIt first, ForwardIt last, const T& value);
```

**Complexity:** $O(\log N)$ comparisons with random-access iterators ($O(N)$ iterator advances on non-random-access). Range **must** be partitioned / sorted w.r.t. the same comparator.

```cpp
std::vector<int> sorted_v = {1, 3, 3, 5, 7};

bool found = std::binary_search(sorted_v.begin(), sorted_v.end(), 3); // true

auto lb = std::lower_bound(sorted_v.begin(), sorted_v.end(), 3); // points to first 3
auto ub = std::upper_bound(sorted_v.begin(), sorted_v.end(), 3); // points to 5
auto range = std::equal_range(sorted_v.begin(), sorted_v.end(), 3); // [lb, ub)
```

```cpp
// Insertion point for a new value while keeping sorted order:
auto pos = std::lower_bound(sorted_v.begin(), sorted_v.end(), 4);
sorted_v.insert(pos, 4); // {1, 3, 3, 4, 5, 7}

// Count occurrences of 3 without a linear scan:
auto [lo, hi] = std::equal_range(sorted_v.begin(), sorted_v.end(), 3);
auto how_many = std::distance(lo, hi);
```

::: trap
`binary_search` only answers existence. For “where is it?” or “how many?” use `lower_bound` / `equal_range`. Passing an unsorted range is undefined behaviour in practice (wrong answers, not a clean error).
:::

## Merge and Set Operations (Sorted Ranges)

These algorithms compute mathematical set operations in $O(N)$ time, but the input ranges **must** be sorted.

- **`std::set_union`**
- **`std::set_intersection`**
- **`std::set_difference`**
- **`std::set_symmetric_difference`**
- **`std::merge`**: Combines two sorted ranges into a single sorted range.

```cpp
template <class InputIt1, class InputIt2, class OutputIt>
OutputIt merge(InputIt1 first1, InputIt1 last1,
               InputIt2 first2, InputIt2 last2, OutputIt d_first);
// Stable merge of two sorted ranges into d_first. O(N+M).

template <class BidirIt>
void inplace_merge(BidirIt first, BidirIt middle, BidirIt last);
// Merges two consecutive sorted halves [first, middle) and [middle, last)
// into one sorted [first, last). O(N) with buffer, O(N log N) without.

template <class InputIt1, class InputIt2>
bool includes(InputIt1 first1, InputIt1 last1,
              InputIt2 first2, InputIt2 last2);
// true iff every element of sorted range 2 appears in sorted range 1. O(N+M).

template <class InputIt1, class InputIt2, class OutputIt>
OutputIt set_union(InputIt1 first1, InputIt1 last1,
                   InputIt2 first2, InputIt2 last2, OutputIt d_first);
// Sorted union (duplicates: max multiplicity of either input).

template <class InputIt1, class InputIt2, class OutputIt>
OutputIt set_intersection(InputIt1 first1, InputIt1 last1,
                          InputIt2 first2, InputIt2 last2, OutputIt d_first);
// Sorted intersection (min multiplicity).

template <class InputIt1, class InputIt2, class OutputIt>
OutputIt set_difference(InputIt1 first1, InputIt1 last1,
                        InputIt2 first2, InputIt2 last2, OutputIt d_first);
// Elements in first range not in second.

template <class InputIt1, class InputIt2, class OutputIt>
OutputIt set_symmetric_difference(InputIt1 first1, InputIt1 last1,
                                  InputIt2 first2, InputIt2 last2, OutputIt d_first);
// Elements in exactly one of the two ranges.
```

```cpp
std::vector<int> v1 = {1, 2, 5}, v2 = {2, 4, 5}, dest;
std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), 
                      std::back_inserter(dest)); 
// dest is now {2, 5}
```

```cpp
std::vector<int> a = {1, 3, 5}, b = {2, 3, 4}, merged;
std::merge(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(merged));
// merged == {1, 2, 3, 3, 4, 5}

std::vector<int> both = {1, 4, 7, 2, 5, 8}; // two sorted halves
std::inplace_merge(both.begin(), both.begin() + 3, both.end());
// both == {1, 2, 4, 5, 7, 8}

bool subset = std::includes(merged.begin(), merged.end(), a.begin(), a.end()); // true

std::vector<int> only_a, only_xor;
std::set_difference(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(only_a));
// only_a == {1, 5}
std::set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(),
                              std::back_inserter(only_xor));
// only_xor == {1, 2, 4, 5}
```

::: keypoint
These are **sequence** algorithms on sorted ranges, not member functions of `std::set`. They work on any sorted iterator range (`vector`, C array, etc.) and write to an output iterator — pre-size or use `back_inserter`.
:::

## Heap Operations

A max-heap is a tree-like structure flattened into an array where the largest element is always at the front. It is the underlying structure of `std::priority_queue`.

- **`std::make_heap`**: Rearranges a range into a heap.
- **`std::push_heap`**: Adds a newly appended element into the heap structure.
- **`std::pop_heap`**: Swaps the largest element (at the front) to the back and re-establishes the heap structure for the rest.
- **`std::sort_heap`**: Turns a heap into a fully sorted range.

```cpp
template <class RandomIt>
void make_heap(RandomIt first, RandomIt last);     // O(N)

template <class RandomIt>
void push_heap(RandomIt first, RandomIt last);     // O(log N)
// Precondition: [first, last-1) is a heap; *--last is the new element.

template <class RandomIt>
void pop_heap(RandomIt first, RandomIt last);      // O(log N)
// Swaps *first with *(last-1), then heapifies [first, last-1).

template <class RandomIt>
void sort_heap(RandomIt first, RandomIt last);     // O(N log N)
// Precondition: range is a heap; result is ascending sorted (no longer a heap).

template <class RandomIt>
bool is_heap(RandomIt first, RandomIt last);       // O(N)

template <class RandomIt>
RandomIt is_heap_until(RandomIt first, RandomIt last);
// First position that breaks the heap property (or last). O(N).
```

```cpp
std::vector<int> v = {3, 1, 4, 1, 5, 9};
std::make_heap(v.begin(), v.end()); 
// The largest element (9) is now at v.front()

// Adding an element
v.push_back(2);
std::push_heap(v.begin(), v.end());

// Removing the largest element
std::pop_heap(v.begin(), v.end()); // Moves 9 to the back
v.pop_back();                      // Actually removes 9

// Sort the remaining heap
std::sort_heap(v.begin(), v.end());
```

```cpp
bool heap_ok = std::is_heap(v.begin(), v.end()); // false after sort_heap
```

![A max-heap embedded in an array: parent at i, children at 2i+1 and 2i+2.](assets/s45_heap_array.png)

## Minimum and Maximum

- **`std::min` / `std::max` / `std::minmax`**: Operates on two values or an initialiser list.
- **`std::min_element` / `std::max_element` / `std::minmax_element`**: Finds the iterators pointing to the min/max values in a range.
- **`std::clamp`** (C++17): Restricts a value between a minimum and maximum bound.

```cpp
template <class T>
const T& min(const T& a, const T& b);
template <class T>
T min(std::initializer_list<T> ilist);

template <class T>
const T& max(const T& a, const T& b);
template <class T>
T max(std::initializer_list<T> ilist);

template <class T>
std::pair<const T&, const T&> minmax(const T& a, const T& b);

template <class ForwardIt>
ForwardIt min_element(ForwardIt first, ForwardIt last);   // O(N); last if empty

template <class ForwardIt>
ForwardIt max_element(ForwardIt first, ForwardIt last);

template <class ForwardIt>
std::pair<ForwardIt, ForwardIt>
minmax_element(ForwardIt first, ForwardIt last);          // ~1.5N comparisons

template <class T>
constexpr const T& clamp(const T& v, const T& lo, const T& hi); // C++17
// Returns lo if v < lo, hi if hi < v, else v. Requires !(hi < lo).
```

```cpp
int a = std::min(10, 20); // 10
int b = std::max({1, 5, 3}); // 5
int c = std::clamp(25, 0, 10); // Clamped to 10

auto it_min = std::min_element(v.begin(), v.end());
auto [min_it, max_it] = std::minmax_element(v.begin(), v.end());
```

## Permutations

```cpp
template <class BidirIt>
bool next_permutation(BidirIt first, BidirIt last);
// Transforms [first, last) into the next lexicographical permutation.
// Returns false and resets to sorted ascending if already the last. O(N).

template <class BidirIt>
bool prev_permutation(BidirIt first, BidirIt last);
// Previous lexicographical permutation; returns false at the first. O(N).

template <class ForwardIt1, class ForwardIt2>
bool is_permutation(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2);
// true if [first2, ...) is a rearrangement of [first1, last1). O(N^2) typical
// (better if sorted / with C++14 four-iterator form and extra constraints).
```

```cpp
#include <algorithm>
#include <vector>
#include <iostream>

std::vector<int> p = {1, 2, 3};
do {
    // visit current permutation
} while (std::next_permutation(p.begin(), p.end()));
// Exhausts all 3! = 6 permutations iff you start from sorted ascending

std::vector<int> x = {1, 2, 3}, y = {3, 1, 2};
bool same_multiset = std::is_permutation(x.begin(), x.end(), y.begin()); // true
```

::: interview
Classic CP pattern: sort the array, then `do { … } while (next_permutation(...));` to enumerate all distinct permutations. If the range is not sorted first, you miss earlier permutations and the loop stops early.
:::

## Numeric Operations (`<numeric>`)

The `<numeric>` header contains algorithms specifically geared towards mathematics.

- **`std::accumulate`**: Sums up elements (or folds them with a custom binary operation).
- **`std::reduce`** (C++17): Like `accumulate`, but allows out-of-order execution for parallelisation.
- **`std::inner_product`**: Computes the dot product of two ranges.
- **`std::transform_reduce`** (C++17): Parallel-friendly combination of `transform` and `reduce`.
- **`std::partial_sum`**: Computes a running total.
- **`std::adjacent_difference`**: Computes differences between adjacent elements.
- **`std::iota`**: Fills a range with sequentially increasing values (e.g. 1, 2, 3...).

```cpp
template <class InputIt, class T>
T accumulate(InputIt first, InputIt last, T init);
// Fold left: init = op(init, *it) with op defaulting to +. Left-associative. O(N).

template <class InputIt, class T>
T reduce(InputIt first, InputIt last, T init);           // C++17
// May reorder / reassociate — op should be commutative & associative for a defined result.

template <class InputIt1, class InputIt2, class T>
T inner_product(InputIt1 first1, InputIt1 last1, InputIt2 first2, T init);
// Dot product: init + Σ a_i * b_i (custom ops allowed). O(N).

template <class InputIt, class T, class BinaryOp, class UnaryOp>
T transform_reduce(InputIt first, InputIt last, T init,
                   BinaryOp reduce_op, UnaryOp transform_op);  // C++17
// Map then reduce; parallel-friendly when used with an execution policy.

template <class InputIt, class OutputIt>
OutputIt partial_sum(InputIt first, InputIt last, OutputIt d_first);
// Prefix sums: out[i] = a[0] + … + a[i]. O(N). Competitive-programming staple.

template <class InputIt, class OutputIt>
OutputIt adjacent_difference(InputIt first, InputIt last, OutputIt d_first);
// out[0] = a[0]; out[i] = a[i] - a[i-1]. O(N).

template <class ForwardIt, class T>
void iota(ForwardIt first, ForwardIt last, T value);
// *first = value; *++it = ++value; …  O(N).

template <class M>
constexpr M gcd(M a, M b);   // C++17, <numeric>
template <class M>
constexpr M lcm(M a, M b);   // C++17, <numeric>
// Greatest common divisor / least common multiple; non-negative result.
```

```cpp
#include <numeric>
std::vector<int> v = {1, 2, 3, 4};

// Sum of all elements, starting with an initial value of 0
int sum = std::accumulate(v.begin(), v.end(), 0);

// Inner product (dot product) of a vector with itself
int dot = std::inner_product(v.begin(), v.end(), v.begin(), 0);

std::vector<int> out(4);
std::partial_sum(v.begin(), v.end(), out.begin()); // 1, 3, 6, 10
std::adjacent_difference(v.begin(), v.end(), out.begin()); 

// Fill with 10, 11, 12, 13
std::iota(v.begin(), v.end(), 10); 
```

```cpp
#include <numeric>
#include <vector>
#include <cstdint>

std::vector<int> big = {1'000'000'000, 1'000'000'000, 1'000'000'000};

// TRAP: init type dictates the accumulation type
long long bad  = std::accumulate(big.begin(), big.end(), 0);      // int math — overflow!
long long good = std::accumulate(big.begin(), big.end(), 0LL);    // long long — OK

long long sum2 = std::reduce(big.begin(), big.end(), 0LL);

std::vector<int> vals = {1, 2, 3, 4};
auto sum_of_squares = std::transform_reduce(
    vals.begin(), vals.end(), 0LL,
    std::plus<>{},
    [](int x) { return 1LL * x * x; });  // 1+4+9+16 = 30

std::vector<int> prefix(vals.size());
std::partial_sum(vals.begin(), vals.end(), prefix.begin());
// range sum [L, R] = prefix[R] - (L ? prefix[L-1] : 0)

int g = std::gcd(12, 18);   // 6
int l = std::lcm(4, 6);     // 12
```

::: trap
`std::accumulate`'s **init type** is the running type. `accumulate(v.begin(), v.end(), 0)` with `vector<long long>` or large `int`s still accumulates in **`int`** and can silently overflow. Always pass `0LL`, `0.0`, or an explicit typed zero matching the desired result type.
:::

::: trap
`std::reduce` (and parallel `transform_reduce`) may reorder operations. Do **not** use them with non-associative ops (e.g. floating subtraction) or with stateful callables that assume left-to-right order — prefer `accumulate` when order matters.
:::

::: interview
Prefix sums via `partial_sum` (or a hand-rolled loop) answer range-sum queries in $O(1)$ after $O(N)$ preprocess. Know `accumulate` vs `reduce`, the init-type overflow trap, and that `iota` is the idiomatic way to fill `0..n-1` index vectors.
:::

## Modern C++ Additions

### Execution Policies (C++17)

Many algorithms in `<algorithm>` and `<numeric>` accept an **execution policy** as their first argument, allowing trivial parallelisation or vectorisation.

```cpp
#include <execution>
// Policies (in namespace std::execution):
//   seq            — ordinary sequential execution
//   par            — parallelise across threads (no overlapping element access races)
//   par_unseq      — parallel + vectorised; callables must allow interleaving
//   unseq          — C++20; vectorised on one thread

// Sorts the vector in parallel using multiple threads
std::sort(std::execution::par, v.begin(), v.end());

std::reduce(std::execution::par, v.begin(), v.end(), 0LL);
```

::: trap
With `par` / `par_unseq`, element access and user callables must be thread-safe. Concurrently mutating the same element from overlapping algorithm invocations is a data race. Exceptions from parallel algorithms may call `std::terminate`. Link with the parallel STL (implementation-defined; e.g. Intel TBB on some libstdc++ builds).
:::

### C++20 Ranges

C++20 introduced the `std::ranges` namespace, significantly cleaning up algorithm syntax by allowing you to pass the container directly instead of `begin()`/`end()` iterator pairs.

```cpp
// C++17 and older
std::sort(v.begin(), v.end());

// C++20 Ranges
std::ranges::sort(v);
```

Ranges algorithms also take optional **projections** and return richer result types (`std::ranges::subrange`, `in_out_result`, etc.) instead of a bare iterator. The classic iterator-pair overloads remain valid and are what most interview whiteboards still expect.

::: interview
Be prepared to write the **erase-remove idiom** flawlessly. Know the difference between `std::lower_bound` (returns an iterator to the first element $\ge$ value, excellent for insertion or exact matches) and `std::binary_search` (only returns a boolean). Expect questions on how to sort by a custom key (pass a lambda comparator), and the performance differences between `std::sort` (full sort), `std::partial_sort` (top $K$), and `std::nth_element` (median finding or partitioning around the $K$-th element).
:::
