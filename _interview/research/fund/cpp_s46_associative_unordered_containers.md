# Associative and Unordered Containers

::: heavy
Dense section — large API. This introduces the two major families of node-based containers: ordered (trees) and unordered (hash tables).
:::

**Associative containers** automatically arrange their elements to allow fast retrieval by key. Unlike sequence containers (`std::vector`, `std::list`), where elements are placed at a specific position by the programmer, associative containers place elements based on their key. 

The Standard Library provides these in two distinct families based on their underlying data structure: **ordered** containers and **unordered** containers.

## The ordered family

The ordered associative containers are backed by a balanced binary search tree (typically a red-black tree). They keep their elements sorted according to a comparison function, which defaults to `std::less<T>`. Operations like search, insertion, and removal take $\mathcal{O}(\log n)$ time.

There are four ordered containers, defined in `<set>` and `<map>`:
- `std::set<Key>`: A collection of unique keys.
- `std::multiset<Key>`: A collection of keys where duplicates are allowed.
- `std::map<Key, Value>`: A collection of key-value pairs with unique keys.
- `std::multimap<Key, Value>`: A collection of key-value pairs where multiple values can share the same key.

Template signatures (defaults shown):

```cpp
#include <set>
#include <map>
#include <functional> // std::less

template<class Key, class Compare = std::less<Key>,
         class Allocator = std::allocator<Key>>
class set;

template<class Key, class Compare = std::less<Key>,
         class Allocator = std::allocator<Key>>
class multiset;

template<class Key, class T, class Compare = std::less<Key>,
         class Allocator = std::allocator<std::pair<const Key, T>>>
class map;

template<class Key, class T, class Compare = std::less<Key>,
         class Allocator = std::allocator<std::pair<const Key, T>>>
class multimap;
```

::: definition
A **`std::map<Key, T>`** stores `std::pair<const Key, T>` elements. The key is `const` because changing it would break the tree's ordering invariant — you erase and re-insert if the key must change.
:::

### Construction and iteration

Iteration over an ordered container always yields elements **in sorted order**.

```cpp
#include <iostream>
#include <set>
#include <map>
#include <string>

int main() {
    // Default construction
    std::set<int> mySet = {5, 2, 8, 2}; // duplicates ignored
    
    // Iteration yields sorted order: 2, 5, 8
    for (int x : mySet) {
        std::cout << x << " "; 
    }
    std::cout << "\n";
    
    // Map stores std::pair<const Key, Value>
    std::map<std::string, int> scores = {
        {"Alice", 90},
        {"Bob", 85}
    };
    
    // Structured binding (C++17) for clean map iteration
    for (const auto& [name, score] : scores) {
        std::cout << name << ": " << score << "\n"; // Alphabetical: Alice, Bob
    }
    return 0;
}
```

Additional construction forms you will see in practice:

```cpp
#include <set>
#include <map>
#include <string>
#include <functional>

std::set<int> a;                          // empty
std::set<int> b = {3, 1, 4};              // initialiser list
std::set<int> c(b.begin(), b.end());      // iterator range
std::set<int, std::greater<int>> desc;    // custom Compare
std::map<std::string, int> m({{"x", 1}}); // list of pairs
```

### Capacity and iterators (ordered)

Shared by all four ordered containers:

| Member | Signature (conceptually) | Complexity | Role |
| :--- | :--- | :--- | :--- |
| `empty` | `bool empty() const noexcept` | $O(1)$ | `true` if size is zero |
| `size` | `size_type size() const noexcept` | $O(1)$ | number of elements |
| `max_size` | `size_type max_size() const noexcept` | $O(1)$ | theoretical upper bound |
| `clear` | `void clear() noexcept` | $O(n)$ | erase all elements |
| `begin` / `end` | `iterator begin()/end()` | $O(1)$ | forward (sorted) iteration |
| `cbegin` / `cend` | `const_iterator …` | $O(1)$ | const forward |
| `rbegin` / `rend` | `reverse_iterator …` | $O(1)$ | reverse sorted order |
| `swap` | `void swap(container&)` | $O(1)$ | exchange contents |

```cpp
#include <set>
#include <iostream>

int main() {
    std::set<int> s = {10, 20, 30};
    std::cout << s.size() << " " << s.empty() << "\n"; // 3 0

    // begin() is the smallest key; rbegin() is the largest
    std::cout << *s.begin() << " " << *s.rbegin() << "\n"; // 10 30

    s.clear(); // size() == 0; iterators from before clear are invalid
    return 0;
}
```

### Insertion and `emplace`

`insert` copies or moves an existing object into the container, while `emplace` constructs it in-place to avoid temporary copies. For containers with unique keys (`set`, `map`), insertion returns a `std::pair<iterator, bool>` where the boolean is `true` if the insertion took place, and `false` if the key already existed.

```cpp
#include <map>
#include <string>

int main() {
    std::map<int, std::string> directory;

    // insert takes a std::pair for a map
    auto [it, success] = directory.insert({1, "Alice"}); // success is true

    // emplace forwards arguments to the pair's constructor
    auto [it2, success2] = directory.emplace(1, "Bob");  // success2 is false, key 1 exists
    
    return 0;
}
```

Full insertion surface (unique-key containers `set` / `map` — multi-variants omit the `bool` and always insert):

```cpp
// set / map (unique keys) — return pair<iterator, bool>
std::pair<iterator, bool> insert(const value_type& value);
std::pair<iterator, bool> insert(value_type&& value);
iterator insert(const_iterator hint, const value_type& value); // hint may speed search
iterator insert(const_iterator hint, value_type&& value);
template<class InputIt>
void insert(InputIt first, InputIt last);
void insert(std::initializer_list<value_type> ilist);

template<class... Args>
std::pair<iterator, bool> emplace(Args&&... args);           // unique
template<class... Args>
iterator emplace_hint(const_iterator hint, Args&&... args);

// multiset / multimap — always insert; return iterator to the new element
iterator insert(const value_type& value);
template<class... Args>
iterator emplace(Args&&... args);
```

::: keypoint
**`emplace_hint`** / hinted `insert` let you pass an iterator near the insertion point. If the hint is correct (or adjacent), libstdc++ can avoid a full tree walk — useful when inserting already-sorted data. A bad hint is harmless but wastes the optimisation.
:::

```cpp
#include <set>

int main() {
    std::set<int> s;
    auto hint = s.end();
    for (int x : {1, 2, 3, 4, 5}) {
        // Sorted ascending → end() is a perfect hint each time
        hint = s.emplace_hint(hint, x);
    }
    return 0;
}
```

For `map`, prefer `try_emplace` / `insert_or_assign` (C++17) when you want clearer “insert if absent” / “overwrite value” semantics than raw `operator[]`:

```cpp
#include <map>
#include <string>

int main() {
    std::map<std::string, int> m;

    // Inserts only if key missing; does not overwrite existing value
    m.try_emplace("Alice", 90);

    // Inserts or replaces the mapped value
    m.insert_or_assign("Alice", 95); // now 95

    return 0;
}
```

### Lookup: `find`, `count`, `contains`

| Member | Signature | Complexity | Notes |
| :--- | :--- | :--- | :--- |
| `find` | `iterator find(const Key& k)` | $O(\log n)$ | `end()` if absent |
| `count` | `size_type count(const Key& k)` | $O(\log n)$ (+ $O(m)$ for multi to count duplicates) | `0`/`1` on unique; multiplicity on multi |
| `contains` | `bool contains(const Key& k) const` | $O(\log n)$ | C++20; prefer over `count` for presence tests |
| `at` | `T& at(const Key& k)` (`map` only) | $O(\log n)$ | throws `std::out_of_range` if missing |
| `operator[]` | `T& operator[](const Key& k)` (`map` only) | $O(\log n)$ | **inserts** default if missing — see trap below |

```cpp
#include <set>
#include <iostream>

int main() {
    std::set<int> s = {1, 2, 3};
    if (s.find(2) != s.end()) { /* present */ }
    if (s.count(2)) { /* 1 */ }
    if (s.contains(2)) { /* C++20 */ }
    return 0;
}
```

### Map access: `operator[]` vs `at()` vs lookup

The `std::map` (and `std::unordered_map`) provide array-like access, but its behaviour is a notorious pitfall.

::: trap
`map::operator[]` silently **inserts a default-constructed value** if the key is missing. For pure lookup, always use `find()`, `at()`, `count()`, or C++20's `contains()`.
:::

```cpp
#include <map>
#include <string>
#include <iostream>

int main() {
    std::map<std::string, int> stock;
    stock["Apples"] = 50; // Inserts "Apples" with value 50

    // TRAP: Accidentally inserting while trying to read
    if (stock["Bananas"] == 0) {
        // "Bananas" was not in the map, but operator[] just inserted {"Bananas", 0}!
    }

    // Safer alternatives:
    // 1. at() throws std::out_of_range if missing
    try {
        int v = stock.at("Oranges"); 
    } catch (...) {}

    // 2. find() returns an iterator to the element, or end() if missing
    auto it = stock.find("Apples");
    if (it != stock.end()) {
        std::cout << "Apples: " << it->second << "\n";
    }

    // 3. count() returns 1 if present (for unique keys), 0 if not
    if (stock.count("Apples") > 0) { /* ... */ }

    // 4. contains() (C++20) returns a boolean
    if (stock.contains("Apples")) { /* ... */ }
    
    return 0;
}
```

::: trap
`operator[]` also requires the mapped type to be **DefaultConstructible**. If `T` has no default constructor, `m[k]` will not compile — use `emplace` / `try_emplace` / `insert` instead.
:::

`multimap` and `multiset` have **no** `operator[]` or `at` — duplicates make a single “the value for key $k$” ill-defined. Use `equal_range` (below).

### Erase

You can remove elements using `erase`, passing either a key, a single iterator, or an iterator range.

```cpp
#include <set>

int main() {
    std::set<int> nums = {1, 2, 3, 4, 5, 6, 7};

    nums.erase(3);            // By key: removes 3
    nums.erase(nums.begin()); // By iterator: removes the first element (1)

    auto it1 = nums.find(5);
    auto it2 = nums.end();
    nums.erase(it1, it2);     // By range: removes [it1, it2) (removes 5, 6, 7)
    
    return 0;
}
```

Signatures and return values:

```cpp
iterator erase(const_iterator pos);                 // returns iterator following erased
iterator erase(const_iterator first, const_iterator last);
size_type erase(const Key& key);                    // how many were removed (0/1 unique; ≥0 multi)
```

```cpp
#include <map>
#include <string>
#include <iostream>

int main() {
    std::multimap<std::string, int> mm = {
        {"a", 1}, {"a", 2}, {"b", 3}
    };
    std::cout << mm.erase("a") << "\n"; // 2 — both "a" entries removed
    return 0;
}
```

Complexity: erase-by-iterator is amortised $O(1)$ (tree rebalance is $O(\log n)$ worst, but constant factors are small); erase-by-key is $O(\log n)$ plus the cost of walking equal-range on multi-containers.

### Ordered-only operations: `lower_bound`, `upper_bound`, `equal_range`

Because the underlying tree is sorted, ordered containers support fast $\mathcal{O}(\log n)$ range queries.

- `lower_bound(k)`: Returns an iterator to the first element that is $\ge k$.
- `upper_bound(k)`: Returns an iterator to the first element that is $> k$.
- `equal_range(k)`: Returns a `std::pair` of `(lower_bound, upper_bound)`.

```cpp
#include <set>
#include <iostream>

int main() {
    std::multiset<int> ms = {10, 20, 20, 20, 30};

    auto itLow = ms.lower_bound(20);  // points to first 20
    auto itUp  = ms.upper_bound(20);  // points to 30
    auto range = ms.equal_range(20);  // pair of (itLow, itUp)

    // Iterate over all 20s
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << *it << " "; // 20 20 20
    }
    return 0;
}
```

On **`multimap`**, `equal_range` is the idiomatic way to visit every value sharing a key:

```cpp
#include <map>
#include <string>
#include <iostream>

int main() {
    std::multimap<std::string, int> grades = {
        {"Ada", 90}, {"Ada", 85}, {"Bob", 70}
    };

    auto [lo, hi] = grades.equal_range("Ada");
    for (auto it = lo; it != hi; ++it) {
        std::cout << it->second << " "; // 90 85 (insertion order among equals is unspecified by the standard;
                                        // libstdc++ keeps relative order of equivalent keys stable in practice)
    }
    return 0;
}
```

::: keypoint
On unique-key containers, `equal_range(k)` still works: the half-open range is either empty or a single element. Prefer `find` / `contains` for simple presence checks.
:::

### Ordering via `Compare` (default `std::less`)

The third template parameter is **`Compare`**, a functor implementing a **strict weak ordering** — which means `comp(a, b)` is `true` only when $a$ should sort before $b$, never when equal, and the relation is transitive. The default is `std::less<Key>`, i.e. `operator<`.

```cpp
#include <set>
#include <functional>
#include <iostream>

int main() {
    std::set<int, std::greater<int>> desc = {1, 3, 2};
    for (int x : desc) std::cout << x << " "; // 3 2 1
    return 0;
}
```

::: trap
`Compare` must be consistent with equality used by the container: two keys are considered **equivalent** when `!comp(a,b) && !comp(b,a)`. If your comparator treats keys as equal that `operator==` would not (or vice versa), lookups silently misbehave.
:::

### Transparent comparators and heterogeneous lookup

By default, `find("hello")` on a `std::map<std::string, int>` constructs a temporary `std::string` from the string literal before comparing — an allocation you often do not want. **Transparent comparators** (C++14) fix this.

If `Compare::is_transparent` is a valid nested type (e.g. `std::less<>` — the diamond/`void` specialisation), then `find`, `count`, `contains`, `lower_bound`, `upper_bound`, `equal_range`, and `erase` gain overloads that accept *any* type comparable to `Key` without converting to `Key` first.

```cpp
#include <map>
#include <string>
#include <string_view>
#include <iostream>

int main() {
    // std::less<> is transparent; std::less<std::string> is not
    std::map<std::string, int, std::less<>> scores = {
        {"Alice", 90}, {"Bob", 85}
    };

    // No temporary std::string allocated for the lookup key
    auto it = scores.find(std::string_view("Alice"));
    if (it != scores.end()) {
        std::cout << it->second << "\n";
    }

    if (scores.contains("Bob")) { /* also heterogeneous */ }
    return 0;
}
```

```cpp
#include <set>
#include <string>

struct Cmp {
    using is_transparent = void; // opt into heterogeneous lookup

    bool operator()(const std::string& a, const std::string& b) const {
        return a < b;
    }
    bool operator()(const std::string& a, std::string_view b) const {
        return a < b;
    }
    bool operator()(std::string_view a, const std::string& b) const {
        return a < b;
    }
};

std::set<std::string, Cmp> names;
```

::: interview
Classic follow-up: “How do you look up a `map<string, …>` with a `string_view` / C-string without allocating?” Answer: transparent comparator (`std::less<>` or a custom `is_transparent` comparator) plus the heterogeneous `find`/`contains` overloads.
:::

## Under the hood: ordered containers are red-black trees

::: heavy
Dense section — slow down. This is how `std::map` / `std::set` actually guarantee $O(\log n)$.
:::

*Analogy*: A phone book kept in sorted order lets you binary-search a name. A plain binary search tree is that idea in pointer form — but if you always insert names in alphabetical order, the “tree” collapses into a stick (a linked list), and every lookup walks the whole book. A **red-black tree** is a phone book that quietly reshuffles a few pages after every edit so the spine never becomes a stick.

![A red-black tree keeps a BST balanced through node colours, so every operation stays O(log n).](assets/s46_rbtree.png)

### Plain BST: ordered, but height can be $n$

A **binary search tree (BST)** stores one key per node with the invariant **left subtree $<$ node $<$ right subtree**. Search, insert, and erase follow a root-to-leaf path, so they cost $O(h)$ where $h$ is the tree height. In a perfectly bushy tree $h = \Theta(\log n)$. In a degenerate tree (always insert sorted keys into an unbalanced BST) $h = \Theta(n)$ — the structure is a linked list.

```cpp
// Conceptual BST node (NOT what you write — the library owns this)
struct BstNode {
    int key;
    BstNode* left;
    BstNode* right;
    BstNode* parent;
};
```

### Red-black invariants keep height $O(\log n)$

A **red-black tree** is a BST whose nodes are coloured **red** or **black** and obey:

1. The root is black.
2. Every leaf (NIL sentinel) is black.
3. No red node has a red child (**no red-red** parent-child pair).
4. Every path from a node down to a leaf contains the **same number of black nodes** (the black-height).

These constraints force the longest root-to-leaf path to be at most about twice the shortest, which proves $h = O(\log n)$. That is why every `find` / `insert` / `erase` / `lower_bound` on `std::map` and friends is $O(\log n)$ worst-case — not merely average-case.

### What a library node looks like

In practice (libstdc++, libc++), each tree node holds roughly:

| Field | Role |
| :--- | :--- |
| `key` / `value` | For `set`: the `Key`. For `map`: `pair<const Key, T>` |
| `color` | Red or black (often a bit packed into a parent pointer) |
| `parent` | Pointer up the tree (enables iterator `--`/`++` without a stack) |
| `left`, `right` | Child links |

```cpp
// Conceptual red-black node used by ordered associative containers
enum Colour { Red, Black };

template<class Value>
struct RbNode {
    Value value;      // Key, or pair<const Key, T>
    Colour colour;
    RbNode* parent;
    RbNode* left;
    RbNode* right;
};
```

### Rotations and recolouring fix violations

After an insert (new nodes start red) or erase, one or more invariants may break. The implementation restores them with:

- **Recolouring** — flip red ↔ black on a small local set of nodes.
- **Rotations** — **left rotate** or **right rotate** around an edge to reshape the tree while preserving the BST in-order sequence.

Rotations do **not** change the sorted order of keys; they only change parent/child geometry so black-height constraints can be repaired. Iteration still walks the tree **in-order** (left, node, right), which is why `begin()` → `end()` yields sorted keys and why `lower_bound` / `upper_bound` are ordinary binary searches down the tree in $O(\log n)$.

::: keypoint
**Why sorted iteration?** In-order traversal of any BST visits keys in sorted order. The red-black machinery never breaks the BST ordering invariant — it only rebalances — so iterators remain sorted after every mutation.
:::

::: interview
“How is `std::map` implemented?” — Expected answer: a self-balancing BST, in practice a **red-black tree**; operations $O(\log n)$; nodes hold key/value, colour, parent, left, right; rotations + recolouring maintain balance; iteration is sorted in-order.
:::

## The unordered family

The **unordered** associative containers are backed by a hash table. They provide average $\mathcal{O}(1)$ time complexity for search, insertion, and removal (worst-case $\mathcal{O}(n)$ if many collisions occur). They require a hash function (to compute a hash value from the key) and an equality function (to resolve collisions).

There are four unordered containers, defined in `<unordered_set>` and `<unordered_map>`:
- `std::unordered_set<Key>`
- `std::unordered_multiset<Key>`
- `std::unordered_map<Key, Value>`
- `std::unordered_multimap<Key, Value>`

::: keypoint
In Python, the built-in `dict` is equivalent to `std::unordered_map` (a hash table), and `set` is equivalent to `std::unordered_set`; there is no built-in ordered-by-key map.
:::

Template signatures:

```cpp
#include <unordered_set>
#include <unordered_map>
#include <functional> // std::hash, std::equal_to

template<class Key,
         class Hash = std::hash<Key>,
         class KeyEqual = std::equal_to<Key>,
         class Allocator = std::allocator<Key>>
class unordered_set;

template<class Key, class T,
         class Hash = std::hash<Key>,
         class KeyEqual = std::equal_to<Key>,
         class Allocator = std::allocator<std::pair<const Key, T>>>
class unordered_map;
// unordered_multiset / unordered_multimap follow the same pattern
```

The API is nearly identical to the ordered family, **minus** `lower_bound`, `upper_bound`, and `equal_range` (since elements are not sorted), and **plus** hash table management functions.

::: keypoint
C++20 actually adds `equal_range` to unordered containers too (returning the bucket-local equal range for a key), but there is still **no** `lower_bound` / `upper_bound` — those require a total order on keys. Prefer `find` / `equal_range` for duplicates in `unordered_multimap`.
:::

### Shared unordered lookup / modifiers

| Member | Role | Average | Worst |
| :--- | :--- | :--- | :--- |
| `insert` / `emplace` / `emplace_hint` | same return conventions as ordered | $O(1)$ | $O(n)$ |
| `erase` | by key, iterator, or range | $O(1)$ avg by key | $O(n)$ |
| `find` / `count` / `contains` (C++20) | lookup | $O(1)$ | $O(n)$ |
| `at` / `operator[]` | `unordered_map` only — same insert trap as `map` | $O(1)$ | $O(n)$ |
| `begin` / `end` / `clear` / `size` / `empty` | as usual; iteration order **unspecified** | — | — |

```cpp
#include <unordered_map>
#include <string>
#include <iostream>

int main() {
    std::unordered_map<std::string, int> id;
    id.emplace("alice", 1);
    if (id.contains("alice")) {
        std::cout << id.at("alice") << "\n";
    }
    // Prefer find/contains/at for read-only checks — not operator[]
    return 0;
}
```

### Hashing, buckets, and collisions

Imagine a hash table as a large mailroom with many pigeonholes (buckets). When you insert a key, a hash function acts as a sorting clerk, crunching the key's data to output an integer, and assigning it to a specific pigeonhole. 

![A hash table maps keys to buckets; colliding keys are chained together in the same bucket.](assets/s46_hash_buckets.png)

```cpp
#include <unordered_map>
#include <string>
#include <iostream>

int main() {
    std::unordered_map<std::string, int> ages = {{"Alice", 30}, {"Bob", 25}};
    
    // Hash table specific API
    std::cout << "Buckets: " << ages.bucket_count() << "\n";
    std::cout << "Load factor: " << ages.load_factor() << "\n"; // elements / buckets
    
    ages.max_load_factor(0.75); // Tell it to rehash if load exceeds 75%
    ages.reserve(100);          // Pre-allocate buckets for at least 100 elements
    
    // Iteration order is unspecified
    for (const auto& [name, age] : ages) {
        std::cout << name << " "; 
    }
    return 0;
}
```

The plain-English rule is: unordered containers place items in buckets based on a mathematical hash of the key, allowing instant lookup. If two keys hash to the same bucket, they form a chain.

Technically, the hash function produces a `std::size_t`, which is modulated by the current number of buckets to find the index. If multiple keys land in the same bucket (a **collision**), they are stored in a linked list within that bucket. When the **load factor** (the ratio of elements to buckets) exceeds the `max_load_factor`, the container automatically allocates more buckets and **rehashes** all elements to maintain $\mathcal{O}(1)$ average performance. Because of this hashing mechanism, iteration order is entirely unspecified.

### Hash policy and bucket interface

| Member | Signature | What it does |
| :--- | :--- | :--- |
| `bucket_count` | `size_type bucket_count() const` | current number of buckets $B$ |
| `max_bucket_count` | `size_type max_bucket_count() const` | implementation limit |
| `bucket_size` | `size_type bucket_size(size_type n) const` | elements in bucket $n$ |
| `bucket` | `size_type bucket(const Key& k) const` | which bucket key $k$ hashes to |
| `load_factor` | `float load_factor() const` | `size() / bucket_count()` |
| `max_load_factor` | `float max_load_factor() const` / `void max_load_factor(float z)` | get/set threshold that triggers growth |
| `rehash` | `void rehash(size_type n)` | set bucket count to at least $n$; re-insert all elements |
| `reserve` | `void reserve(size_type n)` | prepare for $n$ elements without exceeding `max_load_factor` (computes buckets, then rehashes) |

Bucket-local iteration (rarely needed outside debugging / specialised algorithms):

```cpp
local_iterator begin(size_type n);
local_iterator end(size_type n);
const_local_iterator cbegin(size_type n) const;
const_local_iterator cend(size_type n) const;
```

```cpp
#include <unordered_set>
#include <iostream>

int main() {
    std::unordered_set<int> s = {1, 2, 3, 4, 5};
    s.reserve(1000);              // avoid mid-loop rehashes when you know the size
    std::cout << s.bucket_count() << "\n";
    std::cout << s.load_factor() << "\n";

    std::size_t b = s.bucket(3);
    std::cout << "bucket 3 size: " << s.bucket_size(b) << "\n";
    for (auto it = s.begin(b); it != s.end(b); ++it) {
        std::cout << *it << " ";
    }
    return 0;
}
```

::: trap
A single `insert` that triggers **`rehash`** costs $O(n)$ time and **invalidates all iterators** (though references/pointers to elements stay valid). Call `reserve(expected_size)` up front in hot loops to keep inserts amortised $O(1)$ and keep iterators stable across a batch of inserts.
:::

## Under the hood: unordered containers are hash tables

::: heavy
Dense section — slow down. This is why unordered containers are “$O(1)$” — and when they are not.
:::

*Analogy*: The mailroom again. Buckets are pigeonholes. The hash function is the clerk who reads a name and points at a hole. When two people get the same hole, their letters stack in a tray (**chaining**). If every letter lands in one tray, the mailroom is just a slow pile — that is the $O(n)$ worst case.

### Bucket array, hash, and modular indexing

An unordered container owns a **bucket array** of size $B$ (`bucket_count()`). To place or find a key:

1. Compute `h = Hash{}(key)` → a `std::size_t`.
2. Map to an index — conceptually `h % B` (implementations may use bit masks when $B$ is a power of two).
3. Search that bucket’s chain for a key where `KeyEqual{}(candidate, key)` is true.

```cpp
// Conceptual lookup (illustrative — not production code)
template<class Key, class Hash, class KeyEqual>
std::size_t bucket_index(const Key& key, std::size_t B, Hash hash, KeyEqual eq) {
    return hash(key) % B; // real libraries may use & (B-1) for power-of-two B
}
```

### Collision resolution by chaining

Different keys that map to the same index **collide**. Standard library unordered containers resolve collisions by **chaining**: each bucket holds a linked list of entries. In **libstdc++**, nodes form a singly-linked list and typically **cache the hash code** in the node so rehash and equality-short-circuiting do not recompute `Hash` every time.

```cpp
// Conceptual chained hash-table node (libstdc++-style sketch)
template<class Value>
struct HashNode {
    Value value;
    std::size_t cached_hash;
    HashNode* next; // next in this bucket's chain
};
```

### Load factor and rehash

\[
\text{load\_factor} = \frac{\text{size()}}{\text{bucket\_count()}}
\]

When an insert would push `load_factor` past `max_load_factor` (default typically $1.0$), the table **rehashes**: allocate a larger bucket array, walk every element, and re-link each node into its new bucket. One unlucky insert therefore costs $O(n)$, and **bucket iteration order changes**.

Average lookup stays $O(1)$ while chains stay short (a few elements per bucket). If many keys collide — whether by accident or a **crafted anti-hash input** that exploits a weak `std::hash` — one chain grows to $O(n)$ and every operation on those keys becomes linear. Competitive-programming defence: supply a strong **custom hash** (see section s55 — custom hashing / anti-hash tests), or fall back to `std::map` for guaranteed $O(\log n)$.

::: trap
**Unordered worst-case / anti-hash:** average $O(1)$ is not a guarantee. Adversarial keys can force long chains and $O(n)$ (even $O(n^2)$ over $n$ inserts). Do not treat `unordered_map` as “always faster than `map`” on untrusted input without a custom hash.
:::

::: interview
“Why can `unordered_map` be $O(n)$?” — Because hash collisions are chained; a bad hash or adversarial keys put many elements in one bucket, and lookup scans that chain linearly. Rehash also makes a single insert $O(n)$.
:::

## Custom keys

To use a user-defined type as a key, the container must know how to organise it.

### Custom comparator for ordered containers

For `std::map` or `std::set`, you must provide a strict weak ordering. You can do this by overloading `operator<` for your type, or by passing a custom comparator functor.

```cpp
#include <set>

struct Point { 
    int x, y; 
};

// Option 1: Overload operator< (used by default std::less)
bool operator<(const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}
std::set<Point> pointSet; // Works naturally

// Option 2: Provide a custom functor
struct CompareByY {
    bool operator()(const Point& a, const Point& b) const {
        return a.y < b.y;
    }
};
std::set<Point, CompareByY> pointSetByY; 
```

### Custom hash and equality for unordered containers

For `std::unordered_map` or `std::unordered_set`, the type needs a hash function (to find the bucket) and `operator==` (to confirm the exact key during a collision).

```cpp
#include <unordered_set>
#include <functional>

struct Point { 
    int x, y; 
    
    // 1. Equality operator
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// 2. Hash functor
struct PointHash {
    std::size_t operator()(const Point& p) const {
        // Combine hashes of x and y (a simple XOR for demonstration)
        return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
    }
};

// 3. Supply the hash functor to the template
std::unordered_set<Point, PointHash> pointHashSet;
```
*(Note: You can also specialise `std::hash<Point>` inside the `std` namespace to avoid passing the functor type explicitly).*

#### Full example: hashing a `std::pair` / struct key

`std::hash` is **not** defined for `std::pair` in the standard library, so `unordered_map<pair<int,int>, V>` will not compile until you provide `Hash` (and rely on `pair`’s existing `operator==` for `KeyEqual`).

```cpp
#include <unordered_map>
#include <utility>
#include <string>
#include <cstddef>
#include <functional>

struct PairHash {
    std::size_t operator()(const std::pair<int, int>& p) const noexcept {
        std::size_t h1 = std::hash<int>{}(p.first);
        std::size_t h2 = std::hash<int>{}(p.second);
        // Decent combine (Boost-like); better than plain XOR alone
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};

struct Edge {
    int u, v;
    bool operator==(const Edge& o) const { return u == o.u && v == o.v; }
};

struct EdgeHash {
    std::size_t operator()(const Edge& e) const noexcept {
        return PairHash{}(std::pair{e.u, e.v});
    }
};

int main() {
    std::unordered_map<std::pair<int, int>, std::string, PairHash> cell_name;
    cell_name[{2, 3}] = "goal";

    std::unordered_map<Edge, int, EdgeHash> weight;
    weight[{0, 1}] = 10;
    return 0;
}
```

::: trap
`Hash` and `KeyEqual` must agree: if two keys compare equal, they **must** hash equal. Violating that breaks the container (lost elements, failed lookups). Also, a weak combine like `h1 ^ h2` alone collides on swaps — prefer a mixing step as above; for adversarial CP input, use a randomised 64-bit mix (section s55).
:::

## Node handles: `extract`, `insert(node)`, `merge`

Since C++17, associative containers expose **node handles** — which means ownership of a tree/hash node can be taken out of one container and spliced into another **without copying or reallocating the element**.

| Operation | Role |
| :--- | :--- |
| `extract(const Key&)` / `extract(iterator)` | Removes the node and returns a `node_type` owning it (empty handle if key missing) |
| `insert(node_type&&)` | Splices a node in; for unique containers returns an insert-return type with `inserted`, `position`, `node` |
| `merge(other)` | Bulk-transfer nodes from a compatible container (same key/allocator family); duplicates stay in the source for unique containers |

```cpp
#include <map>
#include <string>
#include <iostream>

int main() {
    std::map<int, std::string> a = {{1, "one"}, {2, "two"}};
    std::map<int, std::string> b;

    // Take ownership of the node for key 1 out of a
    auto nh = a.extract(1);          // a no longer contains 1
    nh.key() = 10;                   // may mutate key while node is owned by the handle
    b.insert(std::move(nh));         // splice into b — no copy of the string

    // merge: move all nodes from a into b when keys do not collide
    b.merge(a);

    for (const auto& [k, v] : b) {
        std::cout << k << ":" << v << " ";
    }
    return 0;
}
```

Compatible `merge` pairs include `map`↔`map`, `map`↔`multimap` (and the set analogues), provided `Key`, allocator, and comparator/hash policies match as required by the standard. Extracted nodes from ordered containers can also be inserted into unordered ones of the same value type only when the node handle types match — in practice, merge within the same ordered or unordered family is the portable pattern.

```cpp
#include <set>
#include <iostream>

int main() {
    std::set<int> src = {1, 2, 3};
    std::set<int> dst = {3, 4};
    dst.merge(src);          // 1 and 2 move; 3 stays in src (duplicate)
    std::cout << src.size() << " " << dst.size() << "\n"; // 1 4
    return 0;
}
```

::: keypoint
`extract` + mutating `nh.key()` is the clean way to **change a map key** without copy-erase-reinsert of a heavy mapped value.
:::

## Iterator invalidation

Node-based containers guarantee strong iterator stability compared to `std::vector`.

- **Ordered (`map`, `set`)**: Erasing an element invalidates **only** the iterators and references pointing to that specific erased element. All other iterators and references remain valid. Insertion invalidates nothing.
- **Unordered (`unordered_map`, `unordered_set`)**: Insertion may trigger a **rehash** (reallocating the bucket array). A rehash invalidates **all iterators**, but remarkably, **pointers and references** to the elements remain valid (because the nodes themselves do not move in memory, only the bucket pointers change). Erase invalidates only the iterators/references to the erased element.

### Per-container rules (summary)

| Container | Insert | Erase | Rehash / clear |
| :--- | :--- | :--- | :--- |
| `set` / `multiset` / `map` / `multimap` | Never invalidates iterators or references | Invalidates only iterators/refs to erased elements; returned iterator from `erase(it)` is the next element | `clear` invalidates everything |
| `unordered_set` / `unordered_multiset` / `unordered_map` / `unordered_multimap` | Invalidates iterators **if and only if** a rehash occurs; references/pointers stay valid | Invalidates only the erased element’s iterators/refs | `rehash` / `reserve` (that grows) / `clear` invalidate iterators |

```cpp
#include <map>
#include <unordered_map>
#include <iostream>

int main() {
    std::map<int, int> ordered = {{1, 1}, {2, 2}};
    auto it = ordered.find(1);
    ordered.insert({3, 3});          // it still valid
    ordered.erase(2);                // it still valid (1 was not erased)

    std::unordered_map<int, int> u = {{1, 1}};
    auto uit = u.find(1);
    u.reserve(100000);               // rehash → uit INVALID as an iterator
    // auto x = uit->second;         // undefined behaviour
    // References taken before rehash would still be OK:
    // int& ref = u[1]; before reserve — ref remains valid after rehash
    return 0;
}
```

::: trap
**Rehash invalidates iterators** on every unordered container. Holding an iterator across an `insert` / `rehash` / `reserve` without checking `bucket_count` growth is a classic use-after-invalid-iterator bug. Prefer indices/keys, or call `reserve` before the loop.
:::

## Comparison: ordered vs unordered

| Feature | Ordered (`std::map`, `std::set`) | Unordered (`std::unordered_map`, `std::unordered_set`) |
| :--- | :--- | :--- |
| **Underlying structure** | Balanced Binary Search Tree | Hash Table |
| **Time complexity**| $\mathcal{O}(\log n)$ | Average $\mathcal{O}(1)$, Worst-case $\mathcal{O}(n)$ |
| **Ordering** | Keys are sorted | Unspecified / random |
| **Key requirements** | `operator<` (or custom comparator) | `operator==` and a Hash function |
| **Memory overhead** | Higher (typically 3 pointers per node) | Lower per node, but has bucket array overhead |

Expanded comparison (interview cheat-sheet):

| Criterion | Ordered (RB-tree) | Unordered (hash table) |
| :--- | :--- | :--- |
| Structure | Red-black tree | Bucket array + chains |
| Search / insert / erase | Guaranteed $O(\log n)$ | Avg $O(1)$, worst $O(n)$ |
| Iteration | Sorted, stable order | Unspecified; changes on rehash |
| Range queries | `lower_bound` / `upper_bound` / `equal_range` | Not ordered — no meaningful lower/upper bound |
| Duplicates | `multiset` / `multimap` + `equal_range` | `unordered_multi*` + `equal_range` / `count` |
| Iterator stability | Insert never invalidates | Insert may rehash → all iterators die |
| When to prefer | Sorted traversal, predecessor/successor, worst-case guarantees | Pure “is this key present?” / dictionary lookups on trusted hashes |

**When to use which:** Default to `std::unordered_map` or `std::unordered_set` for pure key-value lookups due to their $\mathcal{O}(1)$ speed. Fall back to the ordered versions only if you need to iterate over the keys in a specific sorted order, or if you need range queries like "find all keys between X and Y" using `lower_bound` and `upper_bound`.

::: interview
"What is the difference between `map` and `unordered_map`?" is a staple C++ question. Be prepared to explain how `unordered_map` works internally (buckets and collisions), how to key a map or unordered_map by a custom type, and why you would choose one over the other based on ordering requirements and Big-$\mathcal{O}$ complexity.
:::

::: interview
“Ordered vs unordered — when?” — Need sorted order, `lower_bound`, or hard $O(\log n)$ ceilings → ordered. Need average-$O(1)$ dictionaries and can live with unspecified order (and either trust the hash or ship a custom one) → unordered.
:::

::: trap
Three traps interviewers probe together: (1) `map::operator[]` / `unordered_map::operator[]` **inserts** a default-mapped value; (2) unordered containers degrade to $O(n)$ under collisions / anti-hash input; (3) **rehash invalidates iterators** even though references to elements survive.
:::
