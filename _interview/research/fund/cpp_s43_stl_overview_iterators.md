# The Standard Template Library (STL) and Iterators

The **Standard Template Library** (STL) is a powerful library of generic classes and functions. It is designed around a brilliant architectural decision: the separation of data structures from the algorithms that operate upon them.

## The four pillars of the STL

The STL achieves its flexibility by decoupling data storage from logic using four core components (with a fifth, allocators, managing memory behind the scenes):

1. **Containers**: Data structures that store collections of objects (e.g., vectors, lists, maps).
2. **Iterators**: Generalised pointers that provide a uniform way to step through elements of any container.
3. **Algorithms**: Functions that perform operations (like searching, sorting, counting) on ranges of elements.
4. **Function Objects** (Functors/Lambdas): Objects that can be called like functions, used to customise the behaviour of algorithms.

Because algorithms operate on iterators rather than containers directly, they are completely decoupled. You do not need a special `sort` function for a vector and a different one for a deque; one `std::sort` algorithm can sort any container whose iterators support the required operations.

### The header map

When working with the STL, you will frequently include the following headers:
- `<vector>`, `<map>`, etc., for the specific **containers**.
- `<algorithm>` for the vast majority of **algorithms** (e.g., `std::copy`, `std::find`, `std::sort`).
- `<numeric>` for mathematical algorithms (e.g., `std::accumulate`).
- `<iterator>` for **iterator** helpers and adaptors.

::: heavy
The remainder of this section delves into iterators. Understanding iterators and half-open ranges is absolutely critical for using the STL effectively.
:::

## Iterators: the generalised pointer

Imagine reading a physical encyclopaedia. You use a bookmark to keep your place. The bookmark does not care if the encyclopaedia is leather-bound or paperback, nor does it care how the pages are bound to the spine. It simply points to the current page and can be moved forward to the next page.

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> nums = {10, 20, 30};
    
    // 'it' acts as our bookmark, initially pointing to the first element
    std::vector<int>::iterator it = nums.begin();
    
    std::cout << *it << "\n"; // Dereference to read the value (10)
    ++it;                     // Move the bookmark forward
    std::cout << *it << "\n"; // Now reads 20
    
    return 0;
}
```

The plain-English rule is: an **iterator** is an object that acts like a cursor. It points to an element inside a container, allows you to read or write that element, and can be moved to point to other elements.

Technically, an iterator is an abstraction that mimics the interface of a raw memory pointer. It overloads operators such as `*` (dereference), `->` (member access), and `++` (increment) to interact seamlessly with the underlying data structure, shielding the programmer from the container's internal memory layout.

::: definition
An **iterator** is a type that provides a pointer-like interface (`*`, `++`, and usually `==`/`!=`) so that algorithms can traverse a sequence without knowing whether that sequence lives in a `vector`, a `list`, a stream, or a raw array.
:::

<!-- FIG s43: bookmark analogy — iterator as cursor into container storage -->

## The half-open range `[begin, end)`

To apply an algorithm to a sequence of elements, you must specify a range. The STL universally relies on the **half-open range**, denoted mathematically as `[begin, end)`.

::: keypoint
A half-open range includes the `begin` element but strictly excludes the `end` element. 
:::

Every standard container provides member functions to retrieve these iterators:
- `begin()`: Returns an iterator pointing to the very first element.
- `end()`: Returns an iterator pointing to the theoretical element *one-past-the-last*.

Because `end()` points outside the valid elements, **it must never be dereferenced**. It acts purely as a sentinel or boundary marker.

```cpp
std::vector<int> v = {1, 2, 3};
for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << " "; // Traverses 1, 2, 3
}
```

This design has several elegant properties:
1. An empty container simply has `begin() == end()`.
2. The number of elements in the range is exactly `end - begin` (if the iterator category supports subtraction).
3. Loops terminate naturally when `it != end()`.

::: keypoint
In Python, objects become iterable by implementing `__iter__` and `__next__`. The C++ half-open range `[begin, end)` is conceptually identical to Python's `range(start, stop)` or slice notation `a[start:stop]`, where the upper boundary is always excluded.
:::

::: trap
Never dereference `end()` (or `rend()`, `cend()`, etc.). It is a sentinel, not an element. Writing `*v.end()` is undefined behaviour — the same class of bug as reading past the last index of an array.
:::

### Iterator accessors

Containers provide several variations of begin and end to support different traversal needs. Here are their signatures:

```cpp
// 1. Mutating iteration
iterator begin();
iterator end();

// 2. Read-only iteration (used implicitly when the container is const)
const_iterator begin() const;
const_iterator end() const;

// 3. Explicit read-only iteration
const_iterator cbegin() const;
const_iterator cend() const;

// 4. Reverse iteration (starts at the end, goes backwards via ++)
reverse_iterator rbegin();
reverse_iterator rend();

// 5. Read-only reverse iteration (const overloads and explicit versions)
const_reverse_iterator rbegin() const;
const_reverse_iterator rend() const;
const_reverse_iterator crbegin() const;
const_reverse_iterator crend() const;
```

#### Member accessors in practice

| Accessor | Points to | Traversal | Mutability |
|---|---|---|---|
| `begin()` / `end()` | first / one-past-last | forward | mutating (non-`const` container) |
| `cbegin()` / `cend()` | first / one-past-last | forward | always read-only |
| `rbegin()` / `rend()` | last / one-before-first | reverse (`++` goes backwards) | mutating |
| `crbegin()` / `crend()` | last / one-before-first | reverse | always read-only |

```cpp
#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> words = {"alpha", "beta", "gamma"};

    // Forward, mutating
    for (auto it = words.begin(); it != words.end(); ++it)
        *it += "!";

    // Forward, read-only (even though words is non-const)
    for (auto it = words.cbegin(); it != words.cend(); ++it)
        std::cout << *it << " ";   // alpha! beta! gamma!
    std::cout << "\n";

    // Reverse: rbegin() points at "gamma!", ++ moves toward "alpha!"
    for (auto it = words.rbegin(); it != words.rend(); ++it)
        std::cout << *it << " ";   // gamma! beta! alpha!
    std::cout << "\n";

    return 0;
}
```

::: keypoint
`rbegin()` is a **reverse iterator** over the last element; `rend()` is the reverse sentinel "one before the first". Incrementing a reverse iterator walks the container backwards. Prefer `crbegin`/`crend` when you only need to read.
:::

#### Free functions: `std::begin` / `std::end` and friends

Additionally, `std::begin()` and `std::end()` are generic free functions that can return iterators for both STL containers and built-in raw arrays (which lack `.begin()` and `.end()` member functions).

```cpp
#include <iterator>
#include <vector>

// Approximate signatures (C++11 onwards; overloads exist for arrays and containers)
template<class C> auto begin(C& c) -> decltype(c.begin());
template<class C> auto end(C& c)   -> decltype(c.end());
template<class C> auto begin(const C& c) -> decltype(c.begin());
template<class C> auto end(const C& c)   -> decltype(c.end());

template<class T, std::size_t N> T* begin(T (&arr)[N]) noexcept;
template<class T, std::size_t N> T* end(T (&arr)[N]) noexcept;

template<class C> auto cbegin(const C& c) -> decltype(std::begin(c));
template<class C> auto cend(const C& c)   -> decltype(std::end(c));
template<class C> auto rbegin(C& c);      // likewise crbegin / rend / crend
```

```cpp
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    int raw[] = {10, 20, 30};          // no member begin/end
    std::vector<int> v = {10, 20, 30};

    // Same algorithm works for both — free begin/end is the glue
    for (auto it = std::begin(raw); it != std::end(raw); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    for (auto it = std::cbegin(v); it != std::cend(v); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    return 0;
}
```

::: keypoint
Prefer `std::begin(x)` / `std::end(x)` in generic code: they work for containers *and* built-in arrays. Member `.begin()` fails on raw arrays. Range-based `for` uses this free-function lookup (ADL-aware) under the hood.
:::

## `iterator` versus `const_iterator`

Just as there are pointers to variables and pointers to constant variables, there are mutating iterators and read-only iterators.

- **`iterator`**: Allows reading and modifying the pointed-to element.
- **`const_iterator`**: Allows only reading.

```cpp
std::vector<int> vec = {10, 20, 30};

// We intend only to read, so we prefer a const_iterator
std::vector<int>::const_iterator cit = vec.cbegin();
std::cout << *cit << "\n"; // Valid: reading is allowed
// *cit = 15;              // ERROR: cannot modify through a const_iterator
```

### Const-correctness of iterators

Const-correctness has two orthogonal axes: whether the *container* is `const`, and whether the *iterator* itself may mutate elements.

| Expression | Container | Iterator type | `*it = …`? |
|---|---|---|---|
| `v.begin()` on non-`const` `v` | mutable | `iterator` | yes |
| `v.begin()` on `const` `v` | const | `const_iterator` | no |
| `v.cbegin()` | either | `const_iterator` | no |
| `civ.begin()` where `civ` is `const vector&` | const | `const_iterator` | no |

```cpp
#include <vector>

void read_only(const std::vector<int>& v) {
    // On a const container, begin() already yields const_iterator
    auto it = v.begin();
    // *it = 42;   // ERROR
    int x = *it;   // OK — reading
    (void)x;
}

void prefer_cbegin(std::vector<int>& v) {
    // Container is mutable, but we still want a read-only cursor
    for (auto it = v.cbegin(); it != v.cend(); ++it) {
        // *it = 0;  // ERROR — cbegin forces const_iterator
        (void)*it;
    }
}
```

A common subtlety: an `iterator` may convert to a `const_iterator`, but not the other way around (same idea as `T*` → `const T*`).

```cpp
std::vector<int> v = {1, 2, 3};
std::vector<int>::iterator it = v.begin();
std::vector<int>::const_iterator cit = it;   // OK: widening conversion
// it = cit;                                 // ERROR: cannot drop const
```

::: trap
`const_iterator` is *not* the same as a `const iterator`. A `const iterator` cannot be reseated (`++it` fails) but may still allow `*it = value` if it is a mutating iterator. A `const_iterator` can be advanced but forbids writing through `*it`.
:::

```cpp
std::vector<int> v = {1, 2, 3};

std::vector<int>::iterator const fixed = v.begin(); // const iterator
// ++fixed;     // ERROR: cannot move a const iterator object
*fixed = 99;    // OK: element is still mutable

std::vector<int>::const_iterator read = v.begin();  // const_iterator
++read;         // OK: the iterator object is mutable
// *read = 99;  // ERROR: element is treated as const
```

## Iterator categories

Algorithms demand certain capabilities from their iterators; for instance, `std::sort` requires the ability to jump around instantly, while `std::count` only requires stepping forward one by one. Iterators are thus classified into a hierarchy of categories based on the operations they support.

![The iterator category hierarchy: each category refines the previous one with more capabilities.](assets/s43_iterator_hierarchy.png)

1. **Input Iterator**: Single-pass read-only. 
   - Operations: `*it` (read), `it->member`, `++it`, `it1 == it2`, `it1 != it2`.
2. **Output Iterator**: Single-pass write-only.
   - Operations: `*it = value` (write), `++it`.
3. **Forward Iterator**: Multi-pass read/write, strictly moving forwards.
   - Includes all Input/Output operations, plus the ability to iterate over the same range multiple times.
4. **Bidirectional Iterator**: Can move both forwards and backwards.
   - Includes all Forward operations, plus `--it` and `it--`.
   - Provided by: `std::list`, `std::map`, `std::set`.
5. **Random-Access Iterator**: Can jump by arbitrary amounts in constant time.
   - Includes all Bidirectional operations, plus arithmetic: `it + n`, `it - n`, `it += n`, `it -= n`.
   - Supports offset dereference: `it[n]`.
   - Supports ordering comparisons: `it1 < it2`, `it1 >= it2`.
   - Supports distance measurement: `it1 - it2`.
   - Provided by: `std::vector`, `std::deque`.
6. **Contiguous Iterator** (C++17 / C++20): A refined Random-Access iterator guaranteeing that elements are stored contiguously in memory.
   - Provided by: `std::vector`, `std::array`, raw arrays, `std::string`.

### Category recap: what each supports

<!-- FIG s43: iterator category ladder — Input/Output → Forward → Bidirectional → Random-Access → Contiguous -->

| Category | Passes | Read | Write | `--` | `it + n` / `it[n]` | Typical sources |
|---|---|---|---|---|---|---|
| Input | single | yes | no | no | no | `istream_iterator`, single-pass views |
| Output | single | no | yes | no | no | `ostream_iterator`, inserters |
| Forward | multi | yes | yes\* | no | no | `forward_list`, unordered containers |
| Bidirectional | multi | yes | yes\* | yes | no | `list`, `set`, `map` |
| Random-access | multi | yes | yes\* | yes | yes, O(1) | `vector`, `deque`, `string` |
| Contiguous | multi | yes | yes\* | yes | yes + `&*it` contiguous | `vector`, `array`, raw arrays |

\*Write access requires a non-`const` iterator; associative containers often expose only `const` element access through iterators.

```cpp
#include <vector>
#include <list>
#include <iterator>

std::vector<int> v = {0, 1, 2, 3, 4};  // random-access
std::list<int>   l = {0, 1, 2, 3, 4};  // bidirectional only

auto vit = v.begin();
vit += 3;                 // OK — random-access
int x = vit[-1];          // OK — equivalent to *(vit - 1)

auto lit = l.begin();
// lit += 3;              // ERROR — list iterators are not random-access
std::advance(lit, 3);     // OK — works for any iterator category
```

::: interview
**Name the classic five iterator categories** (plus Contiguous in modern C++): Input, Output, Forward, Bidirectional, Random-Access — Contiguous refines Random-Access. Interviewers often ask which category `std::list` provides (bidirectional) versus `std::vector` (contiguous / random-access), and why `std::sort` cannot be used on `std::list` (it needs random-access; use `list::sort` instead).
:::

### Tag types and `iterator_traits`

The standard library encodes categories as empty **tag types** so algorithms can dispatch on capability:

```cpp
#include <iterator>

std::input_iterator_tag
std::output_iterator_tag
std::forward_iterator_tag        // also isa input_iterator_tag
std::bidirectional_iterator_tag  // also isa forward_iterator_tag
std::random_access_iterator_tag  // also isa bidirectional_iterator_tag
// C++20: std::contiguous_iterator_tag
```

```cpp
#include <iterator>
#include <vector>
#include <type_traits>

using It = std::vector<int>::iterator;
using Cat = typename std::iterator_traits<It>::iterator_category;
static_assert(std::is_base_of_v<std::random_access_iterator_tag, Cat>);
```

::: keypoint
You rarely invent tags yourself, but you *use* them: `std::advance` and `std::distance` inspect the category and pick an O(1) path for random-access iterators versus an O(N) loop for the rest.
:::

## Iterator helpers

The `<iterator>` header provides helpful free functions to manipulate iterators, abstracting away the differences between categories. 

```cpp
#include <iterator>
#include <vector>
#include <list>

std::vector<int> v = {1, 2, 3, 4, 5};
std::list<int> l = {1, 2, 3, 4, 5};

auto vit = v.begin();
auto lit = l.begin();

// std::advance: moves an iterator by n elements.
// O(1) for random-access iterators, O(N) for others.
std::advance(vit, 3); 
std::advance(lit, 3); 

// std::next / std::prev: returns a new iterator offset by n, leaving the original unchanged
auto next_it = std::next(vit, 1);
auto prev_it = std::prev(vit, 1);

// std::distance: returns the number of hops between two iterators
std::ptrdiff_t dist = std::distance(v.begin(), vit);
```

Additionally, `std::begin()` and `std::end()` are generic free functions that can return iterators for both STL containers and built-in raw arrays (which lack `.begin()` and `.end()` member functions).

### Why helpers exist for non-random-access iterators

Writing `it + 3` or `end - begin` is legal only for **random-access** iterators. A `std::list` iterator has no `operator+`. The helpers in `<iterator>` give you one spelling that works for *every* category, with complexity that degrades gracefully:

| Function | Mutates argument? | Returns | Complexity |
|---|---|---|---|
| `std::advance(it, n)` | yes | `void` | O(1) random-access; O(\|n\|) otherwise |
| `std::next(it, n = 1)` | no | new iterator | same as `advance` |
| `std::prev(it, n = 1)` | no | new iterator | same; requires bidirectional |
| `std::distance(first, last)` | no | hop count | O(1) random-access; O(N) otherwise |

```cpp
#include <iterator>

// Signatures (simplified)
template<class InputIt, class Distance>
void advance(InputIt& it, Distance n);

template<class InputIt>
InputIt next(InputIt it, typename std::iterator_traits<InputIt>::difference_type n = 1);

template<class BidirIt>
BidirIt prev(BidirIt it, typename std::iterator_traits<BidirIt>::difference_type n = 1);

template<class InputIt>
typename std::iterator_traits<InputIt>::difference_type
distance(InputIt first, InputIt last);
```

#### `std::advance` — mutate in place

```cpp
#include <iostream>
#include <iterator>
#include <list>

int main() {
    std::list<int> l = {10, 20, 30, 40, 50};
    auto it = l.begin();
    std::advance(it, 2);          // it now points at 30; O(2) increments
    std::cout << *it << "\n";     // 30
    std::advance(it, -1);         // bidirectional: may go backwards
    std::cout << *it << "\n";     // 20
    return 0;
}
```

#### `std::next` / `std::prev` — non-mutating offsets

Prefer these when you need a neighbour without disturbing the current iterator (e.g. peeking ahead while erasing, or expressing `it + 1` portably).

```cpp
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4};
    auto it = v.begin();

    auto nxt = std::next(it);       // points at 2; it still at 1
    auto nxt2 = std::next(it, 2);   // points at 3
    auto prv = std::prev(v.end());  // points at 4

    std::cout << *it << " " << *nxt << " " << *nxt2 << " " << *prv << "\n";
    // 1 2 3 4
    return 0;
}
```

::: trap
`std::prev(it)` requires a **bidirectional** (or stronger) iterator. Calling it on a pure forward or input iterator is a compile-time error. `std::next` works from input iterators upward.
:::

#### `std::distance` — portable length of a range

```cpp
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::list<int>   l = {1, 2, 3, 4, 5};

    // vector: O(1) via operator-
    std::cout << std::distance(v.begin(), v.end()) << "\n";  // 5

    // list: O(N) — walks the links
    std::cout << std::distance(l.begin(), l.end()) << "\n";  // 5
    return 0;
}
```

::: keypoint
On a random-access range, `std::distance(a, b)` is just `b - a`. On a linked structure it walks from `a` to `b`. Never assume `distance` is free when the iterator category is unknown (templates!).
:::

::: trap
For `std::distance(first, last)`, `last` must be reachable by incrementing `first`. Passing iterators into unrelated containers, or in the wrong order on a non-random-access range, is undefined behaviour.
:::

## Iterator adaptors

An **iterator adaptor** is a special kind of iterator that wraps a container, changing the behaviour of an assignment (`*it = value`). The most common are inserters, which convert assignments into container insertions.

- `std::back_inserter(container)`: Calls `container.push_back(value)`.
- `std::front_inserter(container)`: Calls `container.push_front(value)`.
- `std::inserter(container, iterator)`: Calls `container.insert(iterator, value)`.

```cpp
#include <algorithm>
#include <vector>
#include <iterator>

std::vector<int> src = {1, 2, 3};
std::vector<int> dest;

// std::copy normally overwrites existing elements. 
// Wrapping 'dest' in a back_inserter forces it to append new elements instead.
std::copy(src.begin(), src.end(), std::back_inserter(dest));
```

### Adaptor catalogue

All of the following live in `<iterator>`. Factory functions (`back_inserter`, etc.) are the usual spelling; the class templates are what those factories return.

#### `std::reverse_iterator`

Wraps a bidirectional (or stronger) iterator so that `++` moves toward the beginning. Container `rbegin()`/`rend()` return this type.

```cpp
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4};

    // Explicit reverse_iterator over [v.begin(), v.end())
    std::reverse_iterator<std::vector<int>::iterator>
        rit(v.end()), rend(v.begin());

    for (; rit != rend; ++rit)
        std::cout << *rit << " ";   // 4 3 2 1
    std::cout << "\n";

    // Equivalent and preferred:
    for (auto it = v.rbegin(); it != v.rend(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";
    return 0;
}
```

```cpp
// base() recovers the underlying (forward) iterator — careful with off-by-one
auto rit = v.rbegin();
auto base = rit.base();   // points one past the element rit refers to
```

::: trap
`reverse_iterator::base()` does **not** point at the same element as `*rit`. By definition, `rit.base()` is the forward iterator *one past* the element `rit` dereferences. Mixing reverse and forward iterators without accounting for this is a classic off-by-one bug.
:::

#### `std::back_insert_iterator` / `std::back_inserter`

```cpp
// Class + factory
template<class Container>
class back_insert_iterator { /* *it = value  →  container.push_back(value) */ };

template<class Container>
back_insert_iterator<Container> back_inserter(Container& c);
```

Requires the container to provide `push_back`. Typical targets: `vector`, `deque`, `list`, `string`.

```cpp
#include <algorithm>
#include <iterator>
#include <vector>

std::vector<int> src = {1, 2, 3};
std::vector<int> dest;
dest.reserve(src.size());           // optional; avoids reallocations

std::copy(src.begin(), src.end(), std::back_inserter(dest));
// dest == {1, 2, 3}
```

#### `std::front_insert_iterator` / `std::front_inserter`

```cpp
template<class Container>
front_insert_iterator<Container> front_inserter(Container& c);
// *it = value  →  container.push_front(value)
```

Requires `push_front` — so `deque` or `list`, **not** `vector`.

```cpp
#include <algorithm>
#include <deque>
#include <iterator>

std::deque<int> src = {1, 2, 3};
std::deque<int> dest;

std::copy(src.begin(), src.end(), std::front_inserter(dest));
// Each push_front reverses relative order → dest == {3, 2, 1}
```

::: trap
`front_inserter` on a sequence reverses the apparent order of a `copy`, because each insertion lands at the front. If you need stable order, prefer `back_inserter` or `inserter` at `end()`.
:::

#### `std::insert_iterator` / `std::inserter`

```cpp
template<class Container>
insert_iterator<Container>
inserter(Container& c, typename Container::iterator i);
// *it = value  →  container.insert(hint, value); hint advances
```

Works with any container that has `insert(iterator, value)` — including associative containers (`set`, `map`).

```cpp
#include <algorithm>
#include <iterator>
#include <set>
#include <vector>

std::vector<int> src = {3, 1, 4, 1, 5};
std::set<int> dest = {2, 7};

std::copy(src.begin(), src.end(), std::inserter(dest, dest.end()));
// dest == {1, 2, 3, 4, 5, 7}  — duplicates dropped by set
```

```cpp
#include <algorithm>
#include <iterator>
#include <list>

std::list<int> src = {8, 9};
std::list<int> dest = {1, 2, 3};
auto pos = std::next(dest.begin());   // before element 2

std::copy(src.begin(), src.end(), std::inserter(dest, pos));
// dest == {1, 8, 9, 2, 3}
```

#### `std::move_iterator` / `std::make_move_iterator`

A **move iterator** adapts another iterator so that dereferencing yields an rvalue (`std::move(*it)`), enabling algorithms to *move* from a source range instead of copying.

```cpp
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

std::vector<std::string> src = {"alpha", "beta", "gamma"};
std::vector<std::string> dest(src.size());

std::copy(std::make_move_iterator(src.begin()),
          std::make_move_iterator(src.end()),
          dest.begin());
// dest holds the strings; elements of src are in a valid but unspecified (moved-from) state
```

::: keypoint
Use move iterators when transferring ownership of expensive elements (e.g. `string`, `unique_ptr`) from one container to another. After the move, do not rely on the values left in the source.
:::

### Stream iterators

**Stream iterators** adapt iostreams so that algorithms can read from an input stream or write to an output stream as if they were ordinary ranges.

#### `std::istream_iterator`

```cpp
#include <iterator>
#include <iostream>
// template<class T, class CharT = char, ...>
// class istream_iterator;   // input iterator; end-of-stream is the default-constructed sentinel
```

- Constructed from an `istream`: reads successive `T` values with `operator>>`.
- Default-constructed `istream_iterator<T>{}` is the **end-of-stream** sentinel (compare against it like `end()`).
- Single-pass **input** iterator — once you advance past a value, it is gone.

#### `std::ostream_iterator`

```cpp
#include <iterator>
#include <iostream>
// template<class T, class CharT = char, ...>
// class ostream_iterator;   // output iterator
// ostream_iterator(ostream& os, const CharT* delim = 0);
// *it = value  →  os << value << delim
```

#### Worked example: `std::copy` with stream iterators

```cpp
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

int main() {
    std::istringstream input("10 20 30 40");
    std::vector<int> values;

    // Read ints from the stream until EOF / fail, appending into values
    std::copy(std::istream_iterator<int>(input),
              std::istream_iterator<int>(),          // end-of-stream sentinel
              std::back_inserter(values));

    // Write them back, space-separated
    std::copy(values.begin(), values.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";   // 10 20 30 40
    return 0;
}
```

```cpp
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

// One-liner pattern: dump a container to stdout
std::vector<int> v = {1, 2, 3};
std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, ","));
// prints: 1,2,3,
```

::: keypoint
Stream iterators let you reuse the same algorithms (`copy`, `transform`, `accumulate`, …) on files and console I/O that you use on containers. The default-constructed `istream_iterator` is the range's `end`.
:::

::: trap
`istream_iterator` uses `operator>>`, so formatting and locale rules apply. Mixing typed reads (`istream_iterator<int>`) with leftover characters in the stream is a common source of surprising early termination.
:::

## Range-based `for` loop

The modern range-based `for` loop is entirely powered by iterators. It is pure syntactic sugar over manually requesting `begin()` and `end()`.

```cpp
std::vector<int> numbers = {1, 2, 3};

// Range-based for loop:
for (int num : numbers) {
    std::cout << num << "\n";
}

// What the compiler translates this to (conceptually):
{
    auto __begin = std::begin(numbers);
    auto __end = std::end(numbers);
    for (; __begin != __end; ++__begin) {
        int num = *__begin;
        std::cout << num << "\n";
    }
}
```

### Desugaring details

A range-based `for` requires that `begin(range)` and `end(range)` are findable — either as members or as free functions (via argument-dependent lookup). Roughly (C++17-shaped):

```cpp
// for ( init-statement(optional) for-range-declaration : for-range-initializer ) statement
// desugars to something like:

{
    auto&& __range = for-range-initializer;
    auto __begin = begin-expr;   // __range.begin() or begin(__range)
    auto __end   = end-expr;     // __range.end()   or end(__range)
    for (; __begin != __end; ++__begin) {
        for-range-declaration = *__begin;
        statement
    }
}
```

```cpp
#include <iostream>
#include <vector>

struct Point { int x, y; };

int main() {
    std::vector<Point> pts = {{1, 2}, {3, 4}};

    // By value — copies each Point
    for (Point p : pts) { (void)p; }

    // By const reference — read-only, no copy
    for (const Point& p : pts)
        std::cout << p.x << "," << p.y << "\n";

    // By reference — may mutate elements
    for (Point& p : pts)
        p.x *= 10;

    // Structured bindings (C++17) still sit on iterators underneath
    for (auto& [x, y] : pts)
        std::cout << x << " " << y << "\n";

    return 0;
}
```

::: keypoint
If a type should work with range-based `for`, give it `begin`/`end` (members or ADL free functions) returning iterators that support `!=`, `++`, and `*`. That is the entire contract.
:::

::: trap
`for (auto x : temporary_container())` extends the lifetime of the temporary for the whole loop (bound to the hidden `__range`). But if you iterate over a reference into a temporary subobject incorrectly, you can still dangle — e.g. binding to an element of a temporary that dies earlier. Prefer named locals when unsure.
:::

## Iterator invalidation

::: trap
Adding or removing elements from a container can cause existing iterators, pointers, and references to that container's elements to become invalid (dangling).
:::

If you hold an iterator to an element in a `std::vector` and then trigger a reallocation (e.g., by calling `push_back`), the vector might move its entire memory block. Your existing iterator will still point to the old, now-freed memory. Dereferencing it results in undefined behaviour. The specific rules for when operations invalidate iterators vary by container and will be covered in their respective sections.

### Invalidation: a short orientation

Think of an iterator as a cached address (or node pointer) into the container's storage. Any operation that **moves elements**, **frees nodes**, or **rebuilds the backing store** may leave that cached address meaningless.

```cpp
#include <vector>

std::vector<int> v = {1, 2, 3};
auto it = v.begin();     // points at 1
v.push_back(4);          // may reallocate
// *it;                  // UNDEFINED if reallocation occurred — it is invalidated
```

::: trap
Using an **invalidated** iterator (or dereferencing `end()`) is undefined behaviour — not a guaranteed crash, not a guaranteed exception. It may appear to work in debug builds and corrupt data in release. After any mutating operation, re-obtain iterators you still need (e.g. from the return value of `erase` / `insert`, or by calling `begin()` again).
:::

<!-- FIG s43: iterator invalidation — vector reallocation leaves old iterators dangling -->

Cross-reference: the **full per-container invalidation tables** (which operations invalidate which iterators for `vector`, `deque`, `list`, `map`, …) live in the dedicated container sections later in these notes. This section only introduces the concept.

::: keypoint
Rules of thumb (details differ by container): `vector`/`string` reallocation invalidates everything; `deque` insert/erase at the middle invalidates everything; `list`/`map`/`set` typically invalidate only iterators to erased elements. Always check the container you are using.
:::

## Modern evolution: C++20 Ranges

C++20 introduced the `<ranges>` library, which evolves the STL by allowing algorithms to operate on entire "ranges" directly rather than requiring explicit pairs of iterators.

```cpp
std::vector<int> v = {3, 1, 4};

// Pre-C++20:
// std::sort(v.begin(), v.end());

// C++20 Ranges:
std::ranges::sort(v); 
```

Ranges also introduce views, enabling lazily evaluated transformations and filters without allocating intermediate containers.

::: keypoint
Under the hood, a C++20 **range** is still something with a beginning and an end (iterators or a sentinel). Everything you learned about half-open ranges, categories, and invalidation still applies — Ranges mainly remove the ceremony of passing two iterators by hand.
:::

::: interview
**Name the iterator categories:** Input, Output, Forward, Bidirectional, Random-Access, Contiguous.  
**What does `end()` point to?** The theoretical element one-past-the-last. It must never be dereferenced.  
**Why use half-open ranges?** They elegantly handle empty ranges (`begin == end`), looping conditions (`it != end`), and distance calculations (`end - begin`).
:::
